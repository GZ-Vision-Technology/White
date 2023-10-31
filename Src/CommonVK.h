//
// Created by Zzz on 2023/10/25.
//

#ifndef WHITE_COMMONVK_H
#define WHITE_COMMONVK_H

#include <cassert>
#include "vulkan/vulkan.h"
#include "Common.h"
#include "vulkan/vk_enum_string_helper.h"

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
    struct CommonVK {
        static VkInstance sVkIns;

        static void InitVK(const InitOptions &option);

        static void DestoryVK();
    };
}

#endif //WHITE_COMMONVK_H
