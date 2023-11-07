//
// Created by Zzz on 2023/11/7.
//

#ifndef WHITE_ENGINEFACTORYVKIMPL_H
#define WHITE_ENGINEFACTORYVKIMPL_H

#include "EngineFactoryVk.h"

namespace White {
    class EngineFactoryVkImpl : public IEngineFactoryVk {
    public:
        static EngineFactoryVkImpl* GetInstance() {
            static EngineFactoryVkImpl imp;
            return &imp;
        }

        virtual void CreateDeviceAndContextsVk() override final;
        virtual void CreateSwapChainVk() override final;
        virtual void EnumerateAdapters(Version, uint32_t&, GraphicsAdapterInfo* ) override final;
        virtual void SetMessageCallback(DebugMessageCallbackType) override final;

    };
}

#endif //WHITE_ENGINEFACTORYVKIMPL_H
