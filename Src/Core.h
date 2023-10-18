//
// Created by Zzz on 2023/10/18.
//

#ifndef WHITE_CORE_H
#define WHITE_CORE_H

#include <functional>

namespace White {
    enum class API : uint8_t {
        Noop,
        Metal,
        Dx12,
        Vulkan,
        WebGPU
    };

    enum class MessageSeverity : uint8_t {
        Info,
        Warning,
        Error,
        Fatal
    };

    using CallbackType = std::function<void(MessageSeverity, const string&)>;
    struct InitOptions {
        API api = API::Vulkan;
        CallbackType callback;

        struct Version{
            uint8_t variant = 0;
            uint8_t major = 0;
            uint8_t minor = 0;
            uint8_t patch = 0;
        }
        appVersion,
        engineVersion;
    };

    void Init(const InitOptions& options);
    void ShutDown();
}
#endif //WHITE_CORE_H
