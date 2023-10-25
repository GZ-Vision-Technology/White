//
// Created by Zzz on 2023/10/25.
//

#ifndef WHITE_DEVICE_VK_H
#define WHITE_DEVICE_VK_H

#include "Device.h"
#include "Vulkan/vulkan.h"

    namespace White {
        IMPLEMENT_OBJECT_POINTER(DeviceVK)
        struct DeviceVK : public IDevice, public std::enable_shared_from_this<DeviceVK> {
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            virtual ~DeviceVK();
        };
        DeviceVKPtr CreateDeviceVK();
    }

#endif //WHITE_DEVICE_VK_H
