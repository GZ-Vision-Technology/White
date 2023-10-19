cmake_minimum_required(VERSION 3.17)

# Set project info
project(White VERSION 1.0
        DESCRIPTION "The White Framework"
        LANGUAGES C CXX)

# Language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FLOAT_AS_DOUBLE "Use 64-bits floats" OFF)

# Find vulkan package
find_package(Vulkan)
if (NOT_FOUND_Vulkan)
    message(FATAL_ERROR "Could not find Vulkan package.")
endif ()

# Set vulkan libs and includes
set(VK_LIBS ${Vulkan_LIBRARIES} VulkanMemoryAllocator)
set(VK_INCLUDE ${Vulkan_INCLUDE_DIRS} Deps/VulkanMemoryAllocator/include)

# Source group
file(GLOB_RECURSE SOURCES Src/*.h Src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

# Build VulkanMemoryAllocator
add_subdirectory(Deps/VulkanMemoryAllocator EXCLUDE_FROM_ALL)
target_include_directories(VulkanMemoryAllocator PUBLIC ${Vulkan_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_compile_features(VulkanMemoryAllocator PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE ${VK_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${VK_INCLUDE})


# Add test executable
add_executable(White_test White.cpp)
target_link_libraries(White_test PRIVATE White)
target_include_directories(White_test PRIVATE Src)