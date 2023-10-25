//
// Created by Zzz on 2023/10/24.
//

#ifndef WHITE_DEVICE_H
#define WHITE_DEVICE_H

#include "Common.h"
// The Device Interface struct.
namespace White {
    IMPLEMENT_OBJECT_POINTER(IDevice);
    struct IDevice {
        virtual ~IDevice() {}
        static IDevicePtr CreateDevice();

        // Virtual auto CreateSwapchain(auto, RGLCommandQueuePtr, int width, int height) = 0;
    };
}

#endif //WHITE_DEVICE_H
