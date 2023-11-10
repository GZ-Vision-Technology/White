//
// Created by Zzz on 2023/10/20.
//

#ifndef WHITE_COMMON_H
#define WHITE_COMMON_H

#include <stdexcept>
#include <memory>
#include "vulkan/vulkan.h"

namespace White {

    #define DEFINE_OBJECT_SHARED_POINTER(obj)           \
            struct obj;                                 \
            using obj##SharedPtr = std::shared_ptr<obj>;

    #define CHECK_VK_ERROR_AND_THROW(rst)                                                    \
    {                                                                                        \
            if (rst != VK_SUCCESS)                                                           \
            {                                                                                \
                std::string rstS = "VK ERROR : Error number: " + std::to_string(rst) + " | " \
                                    + "File name: " + __FILE__ + " | "                       \
                                    + "Function name: " + __FUNCTION__ + " | "               \
                                    + "Line number: " + std::to_string(__LINE__) ;           \
                throw std::runtime_error(rstS);                                              \
            }                                                                                \
    }

    constexpr bool ENABLE_VALIDATION =
    #ifdef DEBUG
            true;
    #else
            false;
    #endif

    template<typename T>
    struct DefineSharedPtr : public std::enable_shared_from_this<T> {
        using SharedPtr = std::shared_ptr<T>;
    };

    enum class MessageSeverity : uint8_t {
        Info = 0,
        Warning,
        Error,
        Fatal
    };
    void LogMessage(MessageSeverity, const std::string&);
    void FatalError(const std::string&);

    template<typename T>
    static void Assert(bool cond, const T& msg) {
        if (!cond) {
            FatalError(msg);
        }
    }
}

#endif //WHITE_COMMON_H
