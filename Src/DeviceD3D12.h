//
// Created by Zzz on 2023/10/25.
//

#ifndef WHITE_DEVICE_D3D12_H
#define WHITE_DEVICE_D3D12_H

#include "Device.h"
#include <memory>

namespace White {

    IMPLEMENT_OBJECT_POINTER(DeviceD3D12)
    struct DeviceD3D12 {

        virtual ~DeviceD3D12();
    };
    DeviceD3D12Ptr CreateDeviceD3D12();
}
#endif //WHITE_DEVICE_D3D12_H
