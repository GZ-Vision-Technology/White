//
// Created by Zzz on 2023/11/7.
//

#ifndef WHITE_ENGINEFACTORY_H
#define WHITE_ENGINEFACTORY_H

#include "GraphicsTypes.h"

namespace White {

    class IEngineFactory {
    public:
        virtual void EnumerateAdapters(Version, uint32_t&, GraphicsAdapterInfo* ) = 0;
        virtual void SetMessageCallback(DebugMessageCallbackType) = 0;
    };

}
#endif //WHITE_ENGINEFACTORY_H
