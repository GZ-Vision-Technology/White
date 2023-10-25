//
// Created by Zzz on 2023/10/24.
//

#include "Device.h"
#include "Common.h"
#include "DeviceVK.h"
#include "DeviceD3D12.h"

namespace White {

    IDevicePtr IDevice::CreateDevice() {
        switch (White::sCurrentAPI) {
            case API::Vulkan:
                return CreateDeviceVK();
            default:
                return nullptr;
        }
    }
}