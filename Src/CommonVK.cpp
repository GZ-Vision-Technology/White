//
// Created by Zzz on 2023/10/25.
//

#include "CommonVK.h"
#include <stdexcept>
#include <cstring>

namespace White {

    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData) {

        constexpr auto vkToDebugSeverity = [](VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
            if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                return MessageSeverity::Fatal;
            } else if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                return MessageSeverity::Warning;
            } else {
                return MessageSeverity::Info;
            }
        };

        auto severity = vkToDebugSeverity(messageSeverity);


        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            //TODO: pass through more message types if the user wants them
            LogMessage(severity, pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                               "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT Messenger,
                                       const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                                "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, Messenger, pAllocator);
        }
    }

    void InitVK(const InitOptions &option) {
        VkApplicationInfo appInfo{
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pApplicationName = option.appName.c_str(),
                .applicationVersion = VK_MAKE_API_VERSION(option.appVersion.variant, option.appVersion.major,
                                                          option.appVersion.minor, option.appVersion.patch),
                .pEngineName = option.engineName.c_str(),
                .engineVersion = VK_MAKE_API_VERSION(option.engineVersion.variant, option.engineVersion.major,
                                                     option.engineVersion.minor, option.engineVersion.patch),
                .apiVersion = VK_API_VERSION_1_3
        };
        VkInstanceCreateInfo insInfo{
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pApplicationInfo = &appInfo
        };

        // Pack validation layer info.
        std::vector<VkLayerProperties> availableLayers;
        if (enableValidationLayer) {
            uint32_t layerNum;
            vkEnumerateInstanceLayerProperties(&layerNum, nullptr);
            availableLayers.resize(layerNum);
            vkEnumerateInstanceLayerProperties(&layerNum, availableLayers.data());
            for (auto layerName: validationLayers) {
                if (std::find_if(availableLayers.begin(), availableLayers.end(),
                                 [layerName](auto &layerProperties) {
                                     return strcmp(layerName, layerProperties.layerName) == 0;
                                 }
                ) == availableLayers.end()) {
                    throw std::runtime_error(std::string("required validation layer not found: ") + layerName);
                }
            }
            insInfo.enabledLayerCount = std::size(validationLayers);
            insInfo.ppEnabledLayerNames = validationLayers;
        }
        const char *extension[] = {
                "VK_KHR_surface",
#ifdef _WIN32
                "VK_KHR_win32_surface",
#else
                "VK_KHR_xlib_surface"
#endif
        };

        insInfo.enabledExtensionCount = std::size(extension);
        std::vector<const char *> extensions(extension, extension + insInfo.enabledExtensionCount);
        if constexpr (enableValidationLayer) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME); // debug callback
        }
        insInfo.ppEnabledExtensionNames = extensions.data();
        insInfo.enabledExtensionCount = extensions.size();

        VK_CHECK(vkCreateInstance(&insInfo, nullptr, &vkIns));

        if constexpr (enableValidationLayer) {
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{
                    .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                    .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                    .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                    .pfnUserCallback = debugCallback,
                    .pUserData = nullptr
            };
            VK_CHECK(CreateDebugUtilsMessengerEXT(vkIns, &debugCreateInfo, nullptr, &debugMessenger));
        }
    }

    void DestoryVK() {
        DestroyDebugUtilsMessengerEXT(vkIns, debugMessenger, nullptr);
        vkDestroyInstance(vkIns, nullptr);
    }
}