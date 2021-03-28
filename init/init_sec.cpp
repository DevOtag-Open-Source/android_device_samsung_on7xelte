#include <stdio.h>
#include <stdlib.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

#include "init_sec.h"

#define MODEL_NAME_LEN 5  // e.g. "G610F"
#define BUILD_NAME_LEN 8  // e.g. "DDU1BQH9"
#define CODENAME_LEN   10 // e.g. "on7xeltedd"


static void property_override(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    const std::string bootloader = android::base::GetProperty("ro.bootloader", "");
    const std::string bl_model = bootloader.substr(0, MODEL_NAME_LEN);
    const std::string bl_build = bootloader.substr(BUILD_NAME_LEN);
    const std::string device = "on7xelte";

    std::string model;
    std::string name;
    std::string description;
    std::string fingerprint;

    model = "SM-" + bl_model;

    for (size_t i = 0; i < TOTAL_VARIANTS; i++) {
        if (model.compare(all_variants[i]->model) == 0) {
            name = all_variants[i]->codename;
        }
    }

    if (name.size() == 0) {
        LOG(ERROR) << "Could not detect codename, forcing on7xeltedd";
        name = "on7xeltedd";
    }

    description = "on7xeltedd-user 7.0 NRD90M G610FDDU1BRG2 release-keys";
    fingerprint = "samsung/on7xeltedd/on7xelte:7.0/NRD90M/G610FDDU1BRG2:user/release-keys";

    LOG(INFO) << "Found bootloader: %s", bootloader.c_str();
    LOG(INFO) << "Setting ro.product.model: %s", model.c_str();
    LOG(INFO) << "Setting ro.product.device: %s", device.c_str();
    LOG(INFO) << "Setting ro.product.name: %s", name.c_str();
    LOG(INFO) << "Setting ro.build.product: %s", device.c_str();
    LOG(INFO) << "Setting ro.build.description: %s", description.c_str();
    LOG(INFO) << "Setting ro.build.fingerprint: %s", fingerprint.c_str();

    property_override_dual("ro.product.model", "ro.vendor.product.model", model.c_str());
    property_override_dual("ro.product.device", "ro.vendor.product.device", device.c_str());
    property_override_dual("ro.product.name", "ro.vendor.product.name", name.c_str());
    property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", fingerprint.c_str());

    property_override("ro.build.product", device.c_str());
    property_override("ro.build.description", description.c_str());
}
