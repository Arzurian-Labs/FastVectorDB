cmake_minimum_required(VERSION 3.20)

project(FastVectorDB
    VERSION 0.1.0
    LANGUAGES CXX C
)

# Enforce C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimization and SIMD Flags for GCC / Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
       -O3
       -march=native
       -mavx2
       -mfma
       -Wall
       -Wextra
    )
endif ()

# Public Include Directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Shared Library Target (libfastvectordb.so / .dll)
set(LIB_SOURCES
    src/vector_store.cpp
    src/simd_math.cpp
    src/persistence.cpp
    src/c_api.cpp
)

add_library(fastvectordb SHARED ${LIB_SOURCES})

target_include_directories(fastvectordb PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# CLI Executable Target for testing
add_executable(fastvectordb_cli src/main.cpp)
target_link_libraries(fastvectordb_cli PRIVATE fastvectordb)