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

#ifndef SAMSUNG_CAMERA_PROVIDER_H

#include "LegacyCameraProviderImpl_2_5.h"

#include <android/hardware/camera/provider/2.6/ICameraProvider.h>

#define SAMSUNG_CAMERA_DEBUG

using ::android::hardware::camera::provider::V2_5::implementation::LegacyCameraProviderImpl_2_5;
using ::android::hardware::camera::provider::V2_6::CameraIdAndStreamCombination;
using ::android::hardware::camera::provider::V2_6::ICameraProvider;
using ::android::hardware::hidl_bitfield;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Status;
using ::android::hardware::Void;

namespace V1_0 = ::android::hardware::camera::common::V1_0;
namespace V2_4 = ::android::hardware::camera::provider::V2_4;
namespace V2_5 = ::android::hardware::camera::provider::V2_5;

class SamsungCameraProvider : private LegacyCameraProviderImpl_2_5, public ICameraProvider {
public:
    SamsungCameraProvider();
    ~SamsungCameraProvider();

    // Methods from ::android::hardware::camera::provider::V2_4::ICameraProvider follow.
    Return<V1_0::Status> setCallback(const ::android::sp<V2_4::ICameraProviderCallback>& callback) override;
    Return<void> getVendorTags(getVendorTags_cb _hidl_cb) override;
    Return<void> getCameraIdList(getCameraIdList_cb _hidl_cb) override;
    Return<void> isSetTorchModeSupported(isSetTorchModeSupported_cb _hidl_cb) override;
    Return<void> getCameraDeviceInterface_V1_x(const hidl_string& cameraDeviceName,
            getCameraDeviceInterface_V1_x_cb _hidl_cb) override;
    Return<void> getCameraDeviceInterface_V3_x(const hidl_string& cameraDeviceName,
            getCameraDeviceInterface_V3_x_cb _hidl_cb) override;

    // Methods from ::android::hardware::camera::provider::V2_5::ICameraProvider follow.
    Return<void> notifyDeviceStateChange(hidl_bitfield<V2_5::DeviceState> newState) override;

    // Methods from ::android::hardware::camera::provider::V2_6::ICameraProvider follow.
    Return<void> getConcurrentStreamingCameraIds(
            ICameraProvider::getConcurrentStreamingCameraIds_cb _hidl_cb) override;
    Return<void> isConcurrentStreamCombinationSupported(
            const hidl_vec<CameraIdAndStreamCombination>& configs,
            ICameraProvider::isConcurrentStreamCombinationSupported_cb _hidl_cb) override;

private:
    std::vector<int> mExtraIDs;
};

#endif // SAMSUNG_CAMERA_PROVIDER_H
