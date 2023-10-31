//
// Created by Zzz on 2023/10/24.
//

#include "Device.h"
#include "DeviceVK.h"

namespace White {

    IDevicePtr IDevice::CreateDevice() {
        switch (White::sCurrentAPI) {
            case API::Vulkan:
                return CreateDeviceVK();
            case API::Dx12:
            case API::Metal:
            case API::WebGPU:
            default:
                return nullptr;
        }
    }

}