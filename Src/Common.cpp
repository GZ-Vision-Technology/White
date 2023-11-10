//
// Created by Zzz on 2023/10/20.
//

#include <cstdio>
#include <functional>
#include "iostream"
#include "Common.h"

namespace White {
    using CallBackFunc = std::function<void(MessageSeverity, const std::string&)>;
    static CallBackFunc CBFunc = [](MessageSeverity severity, const std::string& message) {
        constexpr auto SeverityToStr = [](MessageSeverity severity) {
            switch (severity) {
                case MessageSeverity::Info:
                    return "Info";
                case MessageSeverity::Warning:
                    return "Warning";
                case MessageSeverity::Error:
                    return "Error";
                case MessageSeverity::Fatal:
                    return "Fatal";
                default:
                    return "Unknown";
            }
        };
        std::cout << "White [" << SeverityToStr(severity) << "] - " << message << "\n";
    };

    void LogMessage(MessageSeverity severity, const std::string& str) {
        CBFunc(severity, str);
        if (severity == MessageSeverity::Fatal) {
            throw std::runtime_error(str);
        }
    }

    void FatalError(const std::string& str) {
        LogMessage(MessageSeverity::Fatal, str);
    }

}