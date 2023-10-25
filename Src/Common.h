//
// Created by Zzz on 2023/10/20.
//

#ifndef WHITE_COMMON_H
#define WHITE_COMMON_H

#include <cstdint>
#include <functional>
#include <string>
#include <memory>

namespace White{
    enum class API : uint8_t {
        Noop,
        Metal,
        Dx12,
        Vulkan,
        WebGPU
    };
    static API sCurrentAPI = API::Noop;

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

    void LogMessage(MessageSeverity, const std::string&);
    void FatalError(const std::string&);

    template<typename T>
    static void Assert(bool cond, const T& msg) {
        if (!cond) {
            FatalError(msg);
        }
    }

#define IMPLEMENT_OBJECT_POINTER(obj) \
struct obj;                            \
using obj##Ptr = std::shared_ptr<obj>;


}

#endif //WHITE_COMMON_H
