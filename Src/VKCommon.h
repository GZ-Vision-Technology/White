//
// Created by Zzz on 2023/10/20.
//

#ifndef VK_COMMON_H
#define VK_COMMON_H

#include "vulkan/vulkan.h"
#include "Common.h"

constexpr bool enableValidationLayer =
#ifdef DEBUG
        true;
#else
        false;
#endif

constexpr const char* validationLayers[] = {
     "VK_LAYER_KHRONOS_validation"
};


namespace White {
    static VkInstance vkIns;
    void InitVK(const InitOptions& option);

}

#endif //VK_COMMON_H
