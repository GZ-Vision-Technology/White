//
// Created by Zzz on 2023/10/20.
//

#include <stdexcept>
#include <algorithm>
#include <cstring>
#include "VKCommon.h"

namespace White {

    void InitVK(const InitOptions& option) {
        VkApplicationInfo appInfo {
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pApplicationName = option.appName.c_str(),
                .applicationVersion = VK_MAKE_API_VERSION(option.appVersion.variant, option.appVersion.major, option.appVersion.minor, option.appVersion.patch),
                .pEngineName = option.engineName.c_str(),
                .engineVersion = VK_MAKE_API_VERSION(option.engineVersion.variant, option.engineVersion.major, option.engineVersion.minor, option.engineVersion.patch),
                .apiVersion = VK_API_VERSION_1_3
        };
        VkInstanceCreateInfo insInfo {
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pApplicationInfo = &appInfo
        };

        // Pack validation layer info.
        std::vector<VkLayerProperties> availableLayers;
        if (enableValidationLayer) {
            uint32_t layerNum;
            vkEnumerateInstanceLayerProperties (&layerNum, nullptr);
            availableLayers.resize(layerNum);
            vkEnumerateInstanceLayerProperties(&layerNum, availableLayers.data());
            for (auto layerName : validationLayers) {
                if (std::find_if(availableLayers.begin(), availableLayers.end(),
                                 [layerName](auto& layerProperties) {
                                     return strcmp(layerName, layerProperties.layerName) == 0;
                                 }
                ) == availableLayers.end()) {
                    throw std::runtime_error(std::string("required validation layer not found: ") + layerName);
                }
            }
            insInfo.enabledLayerCount = std::size(validationLayers);
            insInfo.ppEnabledLayerNames = validationLayers;
        }
        const char* extension[] = {
                "VK_KHR_surface",
        #ifdef _WIN32
                "VK_KHR_win32_surface",
        #else
                "VK_KHR_xlib_surface"
        #endif
        };

        insInfo.enabledExtensionCount = std::size(extension);
        std::vector<const char*> extensions(extension, extension + insInfo.enabledExtensionCount);
        if constexpr (enableValidationLayer) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME); // debug callback
        }
        insInfo.ppEnabledExtensionNames = extensions.data();
        insInfo.enabledExtensionCount = extensions.size();

        vkCreateInstance(&insInfo, nullptr, &vkIns);
    }

}
