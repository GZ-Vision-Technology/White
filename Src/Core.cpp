//
// Created by Zzz on 2023/10/18.
//

#include "Core.h"
#include "CommonVK.h"

namespace White {

    void Init(const White::InitOptions &options) {
        switch (options.api) {
            case API::Vulkan:
                InitVK(options);
                break;
            case API::Dx12:
            case API::Metal:
            case API::WebGPU:
            case API::Noop:
            default:
                break;
        }
    }

    void ShutDown() {}

}
