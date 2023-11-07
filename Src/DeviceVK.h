//
// Created by Zzz on 2023/10/25.
//

#ifndef WHITE_DEVICE_VK_H
#define WHITE_DEVICE_VK_H

#include <optional>
#include "Vulkan/vulkan.h"
#include "Device.h"

    namespace White {

        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;
            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        IMPLEMENT_OBJECT_POINTER(DeviceVK);
        struct DeviceVK : public  IDevice, public std::enable_shared_from_this<DeviceVK> {
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device = VK_NULL_HANDLE;
            QueueFamilyIndices indices;
            VkQueue queue;

            explicit DeviceVK(VkPhysicalDevice);
            virtual ~DeviceVK() {};
        };

        DeviceVKPtr CreateDeviceVK();
    }

#endif //WHITE_DEVICE_VK_H
