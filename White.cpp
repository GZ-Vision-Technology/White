#include <iostream>
#include "Core.h"
#include "Device.h"

int main()
{
    White::InitOptions opt;
    Init(opt);
    auto p = White::IDevice::CreateDevice();
    std::cout << "This is \"White\" Framework" << std::endl;
    return 0;
}
