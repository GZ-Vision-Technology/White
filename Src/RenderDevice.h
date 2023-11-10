//
// Created by Zzz on 2023/11/10.
//

#ifndef WHITE_RENDERDEVICE_H
#define WHITE_RENDERDEVICE_H

namespace White {
    class IRenderDevice {
        virtual void CreateBuffer() = 0;

        virtual void CreateShader() = 0;
    };
}
#endif //WHITE_RENDERDEVICE_H
