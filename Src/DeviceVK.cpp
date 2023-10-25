//
// Created by Zzz on 2023/10/25.
//

#include "DeviceVK.h"
namespace White {
    DeviceVKPtr CreateDeviceVK() {
        return std::make_shared<DeviceVK>();
    }
}
