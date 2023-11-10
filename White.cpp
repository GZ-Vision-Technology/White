#include <iostream>
#include "Common.h"
#include "VulkanInstance.h"

int main()
{
    try
    {
        White::VulkanInstance::CreateInfo CI {
            .ApiVersion = VK_API_VERSION_1_0,
            .EnableValidation = true,
        };
        auto p = White::VulkanInstance::Create(CI);

        std::cout << "This is \"White\" Framework" << std::endl;
    }
    catch (std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
