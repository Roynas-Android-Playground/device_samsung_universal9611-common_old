/*
 * Copyright (C) 2021-2023 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "SamsungCameraProvider@2.6"

#include "SamsungCameraProvider.h"

#include <algorithm>

using ::android::NO_ERROR;
using ::android::OK;

const int kMaxCameraIdLen = 16;

SamsungCameraProvider::SamsungCameraProvider() : LegacyCameraProviderImpl_2_5() {
   mExtraIDs.push_back(4);
   mExtraIDs.push_back(20);
   mExtraIDs.push_back(23);
   mExtraIDs.push_back(50);
   mExtraIDs.push_back(52);
   mExtraIDs.push_back(54);

    if (!mInitFailed) {
        for (int i : mExtraIDs) {
            struct camera_info info;
            auto rc = mModule->getCameraInfo(i, &info);

            if (rc != NO_ERROR) {
                continue;
            }

            if (checkCameraVersion(i, info) != OK) {
                ALOGE("Camera version check failed!");
                mModule.clear();
                mInitFailed = true;
                return;
            }

#ifdef SAMSUNG_CAMERA_DEBUG
            ALOGI("ID=%d is at index %d", i, mNumberOfLegacyCameras);
#endif

            char cameraId[kMaxCameraIdLen];
            snprintf(cameraId, sizeof(cameraId), "%d", i);
            std::string cameraIdStr(cameraId);
            mCameraStatusMap[cameraIdStr] = CAMERA_DEVICE_STATUS_PRESENT;

            addDeviceNames(i);
            mNumberOfLegacyCameras++;
        }
    }
}

SamsungCameraProvider::~SamsungCameraProvider() {}

// Methods from ::android::hardware::camera::provider::V2_4::ICameraProvider follow.
Return<V1_0::Status> SamsungCameraProvider::setCallback(const ::android::sp<V2_4::ICameraProviderCallback>& callback) {
    return LegacyCameraProviderImpl_2_5::setCallback(callback);
}

Return<void> SamsungCameraProvider::getVendorTags(getVendorTags_cb _hidl_cb) {
    return LegacyCameraProviderImpl_2_5::getVendorTags(_hidl_cb);
}

Return<void> SamsungCameraProvider::getCameraIdList(getCameraIdList_cb _hidl_cb) {
    return LegacyCameraProviderImpl_2_5::getCameraIdList(_hidl_cb);
}

Return<void> SamsungCameraProvider::isSetTorchModeSupported(isSetTorchModeSupported_cb _hidl_cb) {
    return LegacyCameraProviderImpl_2_5::isSetTorchModeSupported(_hidl_cb);
}

Return<void> SamsungCameraProvider::getCameraDeviceInterface_V1_x(const hidl_string& cameraDeviceName,
        getCameraDeviceInterface_V1_x_cb _hidl_cb) {
    return LegacyCameraProviderImpl_2_5::getCameraDeviceInterface_V1_x(cameraDeviceName, _hidl_cb);
}

Return<void> SamsungCameraProvider::getCameraDeviceInterface_V3_x(const hidl_string& cameraDeviceName,
        getCameraDeviceInterface_V3_x_cb _hidl_cb) {
    return LegacyCameraProviderImpl_2_5::getCameraDeviceInterface_V3_x(cameraDeviceName, _hidl_cb);
}

// Methods from ::android::hardware::camera::provider::V2_5::ICameraProvider follow.
Return<void> SamsungCameraProvider::notifyDeviceStateChange(hidl_bitfield<V2_5::DeviceState> newState) {
    return LegacyCameraProviderImpl_2_5::notifyDeviceStateChange(newState);
}

// Methods from ::android::hardware::camera::provider::V2_6::ICameraProvider follow.
Return<void> SamsungCameraProvider::getConcurrentStreamingCameraIds(
        ICameraProvider::getConcurrentStreamingCameraIds_cb _hidl_cb) {
    hidl_vec<hidl_vec<hidl_string>> hidl_camera_id_combinations = {{ "0", "50" }};
    _hidl_cb(V1_0::Status::OK, hidl_camera_id_combinations);
    return Void();
}

Return<void> SamsungCameraProvider::isConcurrentStreamCombinationSupported(
        const hidl_vec<CameraIdAndStreamCombination>& /* configs */,
        ICameraProvider::isConcurrentStreamCombinationSupported_cb _hidl_cb) {
    _hidl_cb(V1_0::Status::OK, true);
    return Void();
}
