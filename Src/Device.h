//
// Created by Zzz on 2023/10/24.
//

#ifndef WHITE_DEVICE_H
#define WHITE_DEVICE_H
#include <memory>
namespace White {
    struct IDevice {
        static DevicePtr CreateDevice();

        //Virtual auto CreateSwapchain(auto, RGLCommandQueuePtr, int width, int height) = 0;
    };
    using DevicePtr = std::shared_ptr<IDevice>;
}
#endif //WHITE_DEVICE_H
