//
// Created by Zzz on 2023/10/20.
//

#ifndef VK_COMMON_H
#define VK_COMMON_H

#include <cassert>
#include "vulkan/vulkan.h"
#include "Common.h"
#if __has_include(<vk_enum_string_helper.h>)
#include <vk_enum_string_helper.h>
#endif
#if __has_include(<vulkan/vk_enum_string_helper.h>)
#include <vulkan/vk_enum_string_helper.h>
#endif

#define VK_CHECK(a) {auto VK_CHECK_RESULT = a; Assert(VK_CHECK_RESULT == VK_SUCCESS, std::string("Vulkan assertion failed: ") + # a + " -> " + string_VkResult(VK_CHECK_RESULT));}
#define VK_VALID(a) {assert(a != VK_NULL_HANDLE);}

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
    void DestoryVK();
}

#endif //VK_COMMON_H
