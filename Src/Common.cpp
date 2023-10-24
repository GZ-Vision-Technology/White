//
// Created by Zzz on 2023/10/20.
//

#include <iostream>
#include "Common.h"

namespace White {

    static CallbackType callbackFn = [](MessageSeverity severity, const std::string &message) {
        constexpr auto severityToStr = [](MessageSeverity severity) {
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

    void LogMessage(MessageSeverity severity, const std::string &str) {
        callbackFn(severity, str);

        // crash the program
        // the user should not try to catch this, UB lies beyond
        if (severity == MessageSeverity::Fatal) {
            throw std::runtime_error(str);
        }
    }

    void FatalError(const std::string& str) {
        LogMessage(MessageSeverity::Fatal, str);
    }
}