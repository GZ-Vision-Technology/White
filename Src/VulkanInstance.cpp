//
// Created by Zzz on 2023/11/7.
//

#include <cstring>
#include "VulkanInstance.h"
#include "Common.h"

namespace White {

    constexpr static const char* const validationLayers[] = {
            "VK_LAYER_KHRONOS_validation"
    };

    bool EnumerateInstanceExtensions(const char* LayerName, std::vector<VkExtensionProperties>& Extensions) {
        uint32_t ExtensionsCount = 0;
        if (vkEnumerateInstanceExtensionProperties(LayerName, &ExtensionsCount, nullptr) != VK_SUCCESS)
            return false;
        Extensions.resize(ExtensionsCount);
        if (vkEnumerateInstanceExtensionProperties(LayerName, &ExtensionsCount, Extensions.data()) != VK_SUCCESS) {
            Extensions.clear();
            return  false;
        }
        return true;
    }

    bool IsExtensionAvailable(const std::vector<VkExtensionProperties>& Extensions, const char* ExtensionName) {
        for (const auto& Extension : Extensions) {
            if (strcmp(Extension.extensionName, ExtensionName) == 0)
                return true;
        }
        return false;
    }

    bool VulkanInstance::IsLayerAvailable(const char* LayerName, uint32_t& Version)
    {
        for (const auto& Layer : m_Layers)
        {
            if (strcmp(Layer.layerName, LayerName) == 0)
            {
                Version = Layer.specVersion;
                return true;
            }
        }
        return false;
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    // unload the debug messenger created above
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT MessageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {

        constexpr auto VktoDebugSeverity = [](VkDebugUtilsMessageSeverityFlagBitsEXT Severity) {
            if (Severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                return MessageSeverity::Fatal;
            }
            else if (Severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                return MessageSeverity::Warning;
            }
            else {
                return MessageSeverity::Info;
            }
        };
        auto Severity = VktoDebugSeverity(MessageSeverity);
        if (MessageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            //TODO: pass through more message types if the user wants them
            LogMessage(Severity, pCallbackData->pMessage);
        }
        return VK_FALSE;
    }

    VulkanInstance::VulkanInstance(const CreateInfo& CI) {
        m_pVkAllocator = CI.pVkAllocator;
        uint32_t LayerCount = 0;
        CHECK_VK_ERROR_AND_THROW( vkEnumerateInstanceLayerProperties(&LayerCount, nullptr) )
        m_Layers.resize(LayerCount);
        CHECK_VK_ERROR_AND_THROW( vkEnumerateInstanceLayerProperties(&LayerCount, m_Layers.data()) )

        if (!EnumerateInstanceExtensions(nullptr, m_Extensions))
            throw std::runtime_error("Failed enumerate instance extensions");

        std::vector<const char*> InstanceExtensions;
        if (IsExtensionAvailable(m_Extensions, VK_KHR_SURFACE_EXTENSION_NAME)) {
            InstanceExtensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
            // (Todo) Handle other platform
            #ifdef _WIN32
                InstanceExtensions.emplace_back("VK_KHR_win32_surface");
            #endif
        }

        if (IsExtensionAvailable(m_Extensions, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
            InstanceExtensions.emplace_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

        if (CI.ppExtensionNames != nullptr) {
            for (uint32_t Index = 0; Index != CI.ExtensionCount; ++Index) {
                const auto ExtName = CI.ppExtensionNames[Index];
                if (ExtName == nullptr)
                    continue;
                if (IsExtensionAvailable(m_Extensions, ExtName))
                    InstanceExtensions.emplace_back(ExtName);
            }
        }

        m_VkVersion = CI.ApiVersion;

        std::vector<const char*> InstanceLayers;
        if (CI.EnableValidation && ENABLE_VALIDATION) {
            InstanceExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            for (const auto LayerName : validationLayers) {
                uint32_t LyVersion;
                if (IsLayerAvailable(LayerName, LyVersion)) {
                    InstanceLayers.emplace_back(LayerName);
                }
            }
        }

        if (CI.ppEnabledLayerNames) {
            for (size_t i = 0; i != CI.EnableLayerCount; ++i) {
                const auto name = CI.ppEnabledLayerNames[i];
                if (!name) continue;
                uint32_t lyVersion = 0;
                if (IsLayerAvailable(name, lyVersion))
                    InstanceLayers.emplace_back(name);
            }
        }

        VkApplicationInfo AppInfo {
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pEngineName = "White",
                .apiVersion = m_VkVersion
        };
        VkInstanceCreateInfo InsCreateInfo {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &AppInfo,
            .enabledLayerCount = (uint32_t)InstanceLayers.size(),
            .ppEnabledLayerNames = InstanceLayers.data(),
            .enabledExtensionCount = (uint32_t)InstanceExtensions.size(),
            .ppEnabledExtensionNames = InstanceExtensions.data(),
        };
        CHECK_VK_ERROR_AND_THROW(vkCreateInstance(&InsCreateInfo, m_pVkAllocator, &m_VkInstance));

        m_EnabledExtensions = std::move(InstanceExtensions);

        if (ENABLE_VALIDATION) {
            VkDebugUtilsMessengerCreateInfoEXT DebugCreateInfo{
                    .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                    .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                    .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                    .pfnUserCallback = DebugCallback,
            };
            CHECK_VK_ERROR_AND_THROW(CreateDebugUtilsMessengerEXT(m_VkInstance, &DebugCreateInfo, m_pVkAllocator, &m_DebugMessenger));
        }

        // Enumerate physical device
        uint32_t PhysicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(m_VkInstance, &PhysicalDeviceCount, nullptr);
        m_PhysicalDevices.resize(PhysicalDeviceCount);
        vkEnumeratePhysicalDevices(m_VkInstance, &PhysicalDeviceCount, m_PhysicalDevices.data());
    }

    std::shared_ptr<VulkanInstance> VulkanInstance::Create(const CreateInfo& CI) {
        return std::shared_ptr<VulkanInstance>{new VulkanInstance{CI} };
    }

    VulkanInstance::~VulkanInstance() {
        DestroyDebugUtilsMessengerEXT(m_VkInstance, m_DebugMessenger, m_pVkAllocator);
        vkDestroyInstance(m_VkInstance, m_pVkAllocator);
    }

    VkPhysicalDevice VulkanInstance::SelectPhysicalDevice(uint32_t AdapterId) const {
        auto IsGraphicsAndComputeQueueSupport = [](VkPhysicalDevice Device) {
            uint32_t QueueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);
            std::vector<VkQueueFamilyProperties> QueueFamilyPropVec(QueueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilyPropVec.data());
            for (const auto& QueueFamilyProp : QueueFamilyPropVec) {
                if ( (QueueFamilyProp.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0 && (QueueFamilyProp.queueFlags & VK_QUEUE_GRAPHICS_BIT) !=0 ) {
                    return true;
                }
            }
            return false;
        };
        VkPhysicalDevice SelectedPhysicalDevice = VK_NULL_HANDLE;
        if (AdapterId < m_PhysicalDevices.size() && IsGraphicsAndComputeQueueSupport(m_PhysicalDevices[AdapterId])) {
            SelectedPhysicalDevice = m_PhysicalDevices[AdapterId];
        }
        if (SelectedPhysicalDevice == VK_NULL_HANDLE) {
            for (auto DV : m_PhysicalDevices) {
                VkPhysicalDeviceProperties Props;
                vkGetPhysicalDeviceProperties(DV, &Props);
                if (IsGraphicsAndComputeQueueSupport(DV)) {
                    SelectedPhysicalDevice = DV;
                    if ( Props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                        break;
                }
            }
        }
    return SelectedPhysicalDevice;
    }

}