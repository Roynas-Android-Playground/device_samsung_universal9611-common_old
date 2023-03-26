/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_dalvik_heap.h>
#include <libinit_utils.h>
#include "vendor_init.h"

#include <android-base/properties.h>

using android::base::GetProperty;

void vendor_load_properties() {
    std::string model;

    model = GetProperty("ro.boot.product.model", "");
    if (model.empty()) {
       model = GetProperty("ro.boot.em.model", "");
    }
    set_ro_build_prop("model", model, true);
    set_ro_build_prop("product", model, false);

    set_dalvik_heap();
}
