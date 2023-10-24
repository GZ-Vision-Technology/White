//
// Created by Zzz on 2023/10/24.
//

#ifndef WHITE_VKDEVICE_H
#define WHITE_VKDEVICE_H

#include "Device.h"

namespace White {
struct VKDevice : public IDevice, public std::enable_shared_from_this<VKDevice> {

};
using VKDevicePtr = std::shared_ptr<VKDevice>;
}
#endif //WHITE_VKDEVICE_H
