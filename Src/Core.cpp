//
// Created by Zzz on 2023/10/18.
//
#include <iostream>
#include "Core.h"
#include "VKCommon.h"

namespace White {

    static CallbackType callbackFn = [](MessageSeverity severity, const std::string& message){
        constexpr auto severityToStr = [](MessageSeverity severity){
            switch (severity) {
                case MessageSeverity::Info:
                    return "Info";
                case MessageSeverity::Warning:
                    return "Warning";
                case MessageSeverity::Error:
                    return "Error";
                case MessageSeverity::Fatal:
                    return "Fatal";
                case MessageSeverity::Noop:
                default:
                    return "Noop";
            }
        };
        std::cout << "RHI [" << severityToStr(severity) << "] : " << message << std::endl;
    };

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
