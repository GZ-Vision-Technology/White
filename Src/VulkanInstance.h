//
// Created by Zzz on 2023/11/7.
//

#ifndef WHITE_VULKANINSTANCE_H
#define WHITE_VULKANINSTANCE_H

#include <vector>
#include <memory>
#include "vulkan/vulkan.h"
#include "Common.h"

namespace White {

    class VulkanInstance : public DefineSharedPtr<VulkanInstance> {
    public:
        // Can not copy and assign.
        VulkanInstance(const VulkanInstance&)  = delete;
        VulkanInstance(VulkanInstance&&) = delete;
        VulkanInstance& operator = (const VulkanInstance&)  = delete;
        VulkanInstance& operator = (VulkanInstance&&) = delete;

        struct CreateInfo {
            uint32_t ApiVersion = 0;
            bool EnableValidation = false;
            bool EnableDeviceSimulation = false;
            bool LogExtensions = false;
            uint32_t EnableLayerCount = 0;
            const char** ppEnabledLayerNames = nullptr;
            uint32_t ExtensionCount = 0;
            const char** ppExtensionNames = nullptr;
            VkAllocationCallbacks* pVkAllocator = nullptr;
            uint32_t IgnoreDebugMessageCount   = 0;
            const char** ppIgnoreDebugMessageNames = nullptr;
        };
        static SharedPtr Create(const CreateInfo& CI);
        SharedPtr GetSharedPtr() { return shared_from_this(); }

        bool IsLayerAvailable(const char* LayerName, uint32_t& Version);

        VkPhysicalDevice SelectPhysicalDevice(uint32_t AdapterId) const;

        VkAllocationCallbacks* GetVkAllocator() { return m_pVkAllocator; }
        VkInstance GetVkInstance() { return m_VkInstance; }
        uint32_t GetVersion() { return m_VkVersion;}

        ~VulkanInstance();
    private:
        explicit VulkanInstance(const CreateInfo&);

        enum DebugMode
        {
            Disabled,
            Utils,
            Report
        };
        DebugMode m_DebugMode = DebugMode::Disabled;

        VkInstance m_VkInstance = VK_NULL_HANDLE;
        uint32_t m_VkVersion = VK_API_VERSION_1_0;
        VkAllocationCallbacks* m_pVkAllocator = nullptr;
        // Support property
        std::vector<VkLayerProperties> m_Layers;
        std::vector<VkExtensionProperties> m_Extensions;
        // Adaptor
        std::vector<VkPhysicalDevice> m_PhysicalDevices;
        std::vector<const char*> m_EnabledExtensions;

        // Debug messenger
        VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
    };

}

#endif //WHITE_VULKANINSTANCE_H
