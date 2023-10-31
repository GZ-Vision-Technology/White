//
// Created by Zzz on 2023/10/24.
//

#ifndef WHITE_DEVICE_H
#define WHITE_DEVICE_H

#include "Common.h"

namespace White {

    IMPLEMENT_OBJECT_POINTER(IDevice);
    struct IDevice {
        IDevice() = default;
        virtual ~IDevice() {}
        static IDevicePtr CreateDevice();
        // virtual RGLSwapchainPtr CreateSwapchain(RGLSurfacePtr, RGLCommandQueuePtr presentQueue, int width, int height) = 0;
    };

}

#endif //WHITE_DEVICE_H
