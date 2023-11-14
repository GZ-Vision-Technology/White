//
// Created by Zzz on 2023/11/13.
//

#ifndef WHITE_VULKANPHYSICALDEVICE_H
#define WHITE_VULKANPHYSICALDEVICE_H

#include "Common.h"
#include "VulkanInstance.h"

namespace White {

    class VulkanPhysicalDevice : public DefineSharedPtr<VulkanPhysicalDevice> {

    public:
        struct CreateInfo {
            const VulkanInstance& Ins;
            const VkPhysicalDevice VkPhyDevice;
        };
    };
}
#endif //WHITE_VULKANPHYSICALDEVICE_H
