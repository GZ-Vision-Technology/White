//
// Created by Zzz on 2023/11/7.
//

#ifndef WHITE_ENGINEFACTORYVK_H
#define WHITE_ENGINEFACTORYVK_H

#include "EngineFactory.h"
namespace White {

    class IEngineFactoryVk : public IEngineFactory {
        virtual void CreateDeviceAndContextsVk() = 0;
        virtual void CreateSwapChainVk() = 0;
    };

}
#endif //WHITE_ENGINEFACTORYVK_H
