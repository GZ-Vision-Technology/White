//
// Created by Zzz on 2023/10/20.
//

#ifndef WHITE_COMMON_H
#define WHITE_COMMON_H

#include <cstdint>
#include <functional>
#include <string>

namespace White{
    enum class API : uint8_t {
        Noop,
        Metal,
        Dx12,
        Vulkan,
        WebGPU
    };

    enum class MessageSeverity : uint8_t {
        Noop,
        Info,
        Warning,
        Error,
        Fatal
    };

    using CallbackType = std::function<void(MessageSeverity, const std::string&)>;
    struct InitOptions {
        API api = API::Vulkan;
        CallbackType callback;
        std::string appName;
        std::string engineName;
        struct Version{
            uint8_t variant = 0;
            uint8_t major = 0;
            uint8_t minor = 0;
            uint8_t patch = 0;
        }
                appVersion,
                engineVersion;
    };
}

#endif //WHITE_COMMON_H
