//
// Created by Zzz on 2023/10/25.
//

#include <map>
#include <set>
#include "DeviceVK.h"
#include "CommonVK.h"

namespace White {
    constexpr const char* const gDeviceExtensions[] = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_IMAGELESS_FRAMEBUFFER_EXTENSION_NAME,
            VK_KHR_IMAGE_FORMAT_LIST_EXTENSION_NAME,
            VK_KHR_DEPTH_STENCIL_RESOLVE_EXTENSION_NAME,
            VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME,
            VK_KHR_MAINTENANCE1_EXTENSION_NAME,
            VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME,
            VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME,
            VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME,
            VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME,
            VK_EXT_CUSTOM_BORDER_COLOR_EXTENSION_NAME,
            VK_EXT_MEMORY_BUDGET_EXTENSION_NAME
    };

    template<typename T>
    void LoadFuntion(const VkDevice device, T& ptr, const char* funName) {
        ptr = (std::remove_reference_t<decltype(ptr)>)vkGetDeviceProcAddr(device, funName);
        if (!ptr)
            FatalError(std::string("Cannot get Vulkan function pointer: ") + funName);
    }

    QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice vkPhyDev) {
        QueueFamilyIndices queueFamily;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(vkPhyDev, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(vkPhyDev, &queueFamilyCount, queueFamilies.data());
        uint32_t index = 0;
        for (auto familyProp: queueFamilies) {
            if (familyProp.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                // Do we need the present queue ?
                queueFamily.graphicsFamily = index;
                queueFamily.presentFamily = index;
                break;
            }
            ++index;
        }
        return queueFamily;
    }

    DeviceVK::DeviceVK(VkPhysicalDevice dv) : physicalDevice(dv) {
        indices = FindQueueFamilies(dv);
        float priority = 1.0f;
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueFamilies = {indices.presentFamily.value(), indices.graphicsFamily.value()};
        for (uint32_t queueFamily : uniqueFamilies) {
            VkDeviceQueueCreateInfo createInfo {
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .queueFamilyIndex = queueFamily,
                .queueCount = 1,
                .pQueuePriorities = &priority
            };
            queueCreateInfos.emplace_back(createInfo);
        }
        VkDeviceCreateInfo createInfo {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .queueCreateInfoCount = (uint32_t)queueCreateInfos.size(),
            .pQueueCreateInfos = queueCreateInfos.data()
        };
        VK_CHECK( vkCreateDevice(dv, &createInfo, nullptr, &device));
    }

    DeviceVKPtr CreateDeviceVK() {
        uint32_t deviceCount;
        vkEnumeratePhysicalDevices( CommonVK::sVkIns, &deviceCount, nullptr);
        Assert(deviceCount != 0, "Do not have available physical device");
        std::vector<VkPhysicalDevice> phyDevices(deviceCount);
        vkEnumeratePhysicalDevices(CommonVK::sVkIns, &deviceCount, phyDevices.data());

        auto isDeviceSuitable = [](const VkPhysicalDevice& phyDevice) -> bool {
            // Check whether the device is suitable.
            QueueFamilyIndices queueFamily = FindQueueFamilies(phyDevice);

            return queueFamily.isComplete() ? true : false;
        };

        auto ratePhyDevice = [](const VkPhysicalDevice& phyDevice) -> uint32_t {
            VkPhysicalDeviceProperties deviceProperties;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceFeatures(phyDevice, &deviceFeatures);
            vkGetPhysicalDeviceProperties(phyDevice, &deviceProperties);
            uint32_t rateCore(0);
            if (deviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                rateCore += 10000;
            return rateCore;
        };
        std::multimap<uint32_t, VkPhysicalDevice> scoreDeviceMap;
        std::for_each(std::begin(phyDevices), std::end(phyDevices), [&](const VkPhysicalDevice& dv) {
            scoreDeviceMap.insert({ratePhyDevice(dv), dv});
        });

        VkPhysicalDevice targetPhyDevice = VK_NULL_HANDLE;
        for (const auto& dv : scoreDeviceMap) {
            if (isDeviceSuitable(dv.second)) {
                targetPhyDevice = dv.second;
                break;
            }
        }
        Assert(targetPhyDevice != VK_NULL_HANDLE, "Have no suitable GPU.");

        return std::make_shared<DeviceVK>(targetPhyDevice);
    }

}
