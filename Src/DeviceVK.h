//
// Created by Zzz on 2023/10/25.
//

#ifndef WHITE_DEVICEVK_H
#define WHITE_DEVICEVK_H

#include "Device.h"
#include "Vulkan/vulkan.h"

    namespace White {

        struct DeviceVK : public IDevice, public std::enable_shared_from_this<DeviceVK> {
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            virtual ~DeviceVK();
        };

    }

#endif //WHITE_DEVICEVK_H
