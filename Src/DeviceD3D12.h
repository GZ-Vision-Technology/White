//
// Created by Zzz on 2023/10/25.
//

#ifndef WHITE_DEVICE_D3D12_H
#define WHITE_DEVICE_D3D12_H

#include "Device.h"
#include <memory>

namespace White {
struct DeviceD3D12 : public IDevice, public std::enable_shared_from_this<DeviceD3D12> {

};
}
#endif //WHITE_DEVICE_D3D12_H
