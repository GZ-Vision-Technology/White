//
// Created by Zzz on 2023/11/7.
//

#ifndef WHITE_GRAPHICSTYPES_H
#define WHITE_GRAPHICSTYPES_H

#include <cstdint>
#include <cstring>

namespace White {

    struct Version {
        uint32_t Major = 0;
        uint32_t Minor = 0;

        constexpr Version() = default;

        constexpr Version(uint32_t ma, uint32_t mi) : Major(ma), Minor(mi) {}

        constexpr bool operator==(const Version &rhs) const {
            return Major == rhs.Major && Minor == rhs.Minor;
        }

        constexpr bool operator!=(const Version &rhs) const {
            return !(*this == rhs);
        }

        constexpr bool operator>(const Version &rhs) const {
            return Major == rhs.Major ? Minor > rhs.Minor : Major > rhs.Major;
        }

        constexpr bool operator>=(const Version &rhs) const {
            return (*this > rhs) || (*this == rhs);
        }

        constexpr bool operator<(const Version &rhs) const {
            return !(*this >= rhs);
        }

        constexpr bool operator<=(const Version &rhs) const {
            return !(*this > rhs);
        }

        static constexpr Version Min(const Version &v1, const Version &v2) {
            return v1 > v2 ? v2 : v1;
        }

        static constexpr Version Max(const Version &v1, const Version &v2) {
            return v1 > v2 ? v1 : v2;
        }
    };

    enum class ADAPTER_TYPE : uint8_t {
        ADAPTER_TYPE_UNKNOWN = 0,
        ADAPTER_TYPE_SOFTWARE,
        ADAPTER_TYPE_INTEGRATED,
        ADAPTER_TYPE_DISCRETE,
        ADAPTER_TYPE_COUNT
    };

    enum class ADAPTER_VENDOR : uint8_t {
        ADAPTER_VENDOR_UNKNOWN = 0,
        ADAPTER_VENDOR_NVIDIA,
        ADAPTER_VENDOR_AMD,
        ADAPTER_VENDOR_INTEL,
        ADAPTER_VENDOR_APPLE
    };

    enum class CPU_ACCESS_FLAG : uint8_t {
        CPU_ACCESS_NONE = 0,
        CPU_ACCESS_READ = 1,
        CPU_ACCESS_WRITE = 4,
    };

    enum class BIND_FLAGS : uint32_t {
        BIND_NONE = 0,
        BIND_VERTEX_BUFFER = 1u << 0,
        BIND_INDEX_BUFFER = 1u << 1u,
        BIND_UNIFORM_BUFFER = 1u << 2u,
        BIND_SHADER_RESOURCE = 1u << 3u,
        BIND_STREAM_OUTPUT = 1u << 4u,
        BIND_RENDER_TARGET = 1u << 5u,
        BIND_DEPTH_STENCIL = 1u << 6u,
        BIND_UNORDERED_ACCESS = 1u << 7u,
        BIND_INDIRECT_DRAW_ARGS = 1u << 8u,
        BIND_INPUT_ATTACHMENT = 1u << 9u,
        BIND_RAY_TRACING = 1u << 10u,
        BIND_SHADING_RATE = 1u << 11u,
    };

    struct AdapterMemoryInfo {
        uint64_t LocalMemory = 0;
        uint64_t HostVisibleMemory = 0;
        uint64_t UnifiedMemory = 0;
        uint64_t MaxMemoryAllocation = 0;
        CPU_ACCESS_FLAG UnifiedMemoryCPUAccess = CPU_ACCESS_FLAG::CPU_ACCESS_NONE;
        BIND_FLAGS MemorylessTextureBindFlags = BIND_FLAGS::BIND_NONE;

        constexpr bool operator== (const AdapterMemoryInfo& rhs) const {
            return LocalMemory == rhs.LocalMemory &&
            HostVisibleMemory == rhs.HostVisibleMemory &&
            UnifiedMemory == rhs.UnifiedMemory &&
            MaxMemoryAllocation == rhs.MaxMemoryAllocation &&
            UnifiedMemoryCPUAccess == rhs.UnifiedMemoryCPUAccess &&
            MemorylessTextureBindFlags == rhs.MemorylessTextureBindFlags;
        }
    };

    enum class RAY_TRACING_CAP_FLAGS : uint8_t {
    RAY_TRACING_CAP_FLAG_NONE                 = 0,
    RAY_TRACING_CAP_FLAG_STANDALONE_SHADERS   = 1u << 0,
    RAY_TRACING_CAP_FLAG_INLINE_RAY_TRACING   = 1u << 1,
    RAY_TRACING_CAP_FLAG_INDIRECT_RAY_TRACING = 1u << 2
};

    struct RayTracingProperties
    {
        uint32_t MaxRecursionDepth = 0;

        /// For internal use
        uint32_t ShaderGroupHandleSize    = 0;
        uint32_t MaxShaderRecordStride    = 0;
        uint32_t ShaderGroupBaseAlignment = 0;

        /// The maximum total number of ray generation threads in one dispatch.
        uint32_t MaxRayGenThreads         = 0;

        /// The maximum number of instances in a top-level AS.
        uint32_t MaxInstancesPerTLAS      = 0;

        /// The maximum number of primitives in a bottom-level AS.
        uint32_t MaxPrimitivesPerBLAS     = 0;

        /// The maximum number of geometries in a bottom-level AS.
        uint32_t MaxGeometriesPerBLAS     = 0;

        /// The minimum alignment for vertex buffer offset in BLASBuildTriangleData::VertexOffset.
        uint32_t VertexBufferAlignment  = 0;

        /// The minimum alignment for index buffer offset in BLASBuildTriangleData::IndexOffset.
        uint32_t IndexBufferAlignment     = 0;

        /// The minimum alignment for transform buffer offset in BLASBuildTriangleData::TransformBufferOffset.
        uint32_t TransformBufferAlignment = 0;

        /// The minimum alignment for box buffer offset in BLASBuildBoundingBoxData::BoxOffset.
        uint32_t BoxBufferAlignment        = 0;

        /// The minimum alignment for scratch buffer offset in BuildBLASAttribs::ScratchBufferOffset and BuildTLASAttribs::ScratchBufferOffset.
        uint32_t ScratchBufferAlignment = 0;

        /// The minimum alignment for instance buffer offset in BuildTLASAttribs::InstanceBufferOffset.
        uint32_t InstanceBufferAlignment = 0;

        /// Ray tracing capability flags, see Diligent::RAY_TRACING_CAP_FLAGS.
        RAY_TRACING_CAP_FLAGS CapFlags = RAY_TRACING_CAP_FLAGS::RAY_TRACING_CAP_FLAG_NONE;

        constexpr bool operator==(const RayTracingProperties& rhs) const
        {
            return MaxRecursionDepth        == rhs.MaxRecursionDepth        &&
                   ShaderGroupHandleSize    == rhs.ShaderGroupHandleSize    &&
                   MaxShaderRecordStride    == rhs.MaxShaderRecordStride    &&
                   ShaderGroupBaseAlignment == rhs.ShaderGroupBaseAlignment &&
                   MaxRayGenThreads         == rhs.MaxRayGenThreads         &&
                   MaxInstancesPerTLAS      == rhs.MaxInstancesPerTLAS      &&
                   MaxPrimitivesPerBLAS     == rhs.MaxPrimitivesPerBLAS     &&
                   MaxGeometriesPerBLAS     == rhs.MaxGeometriesPerBLAS     &&
                   VertexBufferAlignment    == rhs.VertexBufferAlignment    &&
                   IndexBufferAlignment     == rhs.IndexBufferAlignment     &&
                   TransformBufferAlignment == rhs.TransformBufferAlignment &&
                   BoxBufferAlignment       == rhs.BoxBufferAlignment       &&
                   ScratchBufferAlignment   == rhs.ScratchBufferAlignment   &&
                   InstanceBufferAlignment  == rhs.InstanceBufferAlignment  &&
                   CapFlags                 == rhs.CapFlags;
        }

    };

    struct GraphicsAdapterInfo {
        char Description[128] = {};
        ADAPTER_TYPE   Type     = ADAPTER_TYPE::ADAPTER_TYPE_UNKNOWN;
        ADAPTER_VENDOR Vendor = ADAPTER_VENDOR::ADAPTER_VENDOR_UNKNOWN;
        uint32_t VendorId = 0;
        uint32_t DeviceId = 0;
        uint32_t NumOutputs = 0;
        AdapterMemoryInfo Memory;
        RayTracingProperties RayTracing;
        // Add the properties that we need.

        bool operator== (const GraphicsAdapterInfo& rhs) const {
            return std::memcmp(Description, rhs.Description, sizeof(Description)) == 0 &&
                    Type == rhs.Type &&
                    Vendor == rhs.Vendor &&
                    VendorId == rhs.VendorId &&
                    DeviceId == rhs.DeviceId &&
                    NumOutputs == rhs.NumOutputs &&
                    Memory == rhs.Memory &&
                    RayTracing == rhs.RayTracing;
        }

    };

    enum DEBUG_MESSAGE_SEVERITY {
        DEBUG_MESSAGE_SEVERITY_INFO = 0,
        DEBUG_MESSAGE_SEVERITY_WARNING,
        DEBUG_MESSAGE_SEVERITY_ERROR,
        DEBUG_MESSAGE_SEVERITY_FATAL_ERROR
    };
    using DebugMessageCallbackType = void(*)(DEBUG_MESSAGE_SEVERITY Severity,
                                            const char* Message,
                                            const char* Function,
                                            const char* File,
                                            int Line);
}
#endif //WHITE_GRAPHICSTYPES_H
