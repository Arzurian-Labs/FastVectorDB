# FastVectorDB

FastVectorDB is a high-performance, low-latency in-memory vector database engine written in C++20. It is designed to serve as a fast semantic memory subsystem for edge AI applications and local agent frameworks.

---

## Features

- **Contiguous Memory Layout**: Aligned float buffer storing high-dimensional vectors back-to-back in contiguous memory to eliminate pointer-chasing and maximize CPU cache line efficiency.
- **SIMD Hardware Acceleration**: Target support for AVX2/FMA (x86_64) and ARM NEON SIMD vector instruction sets.
- **C++20 Architecture**: Modern type safety, capacity pre-allocation, and dimension validation.
- **Zero-Copy Persistence**: Binary serialization and memory-mapped file loading (`mmap`).
- **C-ABI Gateway**: FFI ready exports for Python and local AI runtime integration.

---

## Directory Structure

```
FastVectorDB/
├── CMakeLists.txt            # CMake build configuration script
├── README.md                 # Project overview and documentation
├── ARCHITECTURE.adoc         # Detailed architecture design specification
├── include/                  # Header files
│   └── fastvectordb/
│       ├── vector_store.hpp  # Contiguous vector storage engine
│       ├── simd_math.hpp     # SIMD distance and similarity math
│       ├── persistence.hpp   # Binary serialization and mmap I/O
│       └── c_api.h           # C-ABI FFI exports
└── src/                      # Implementation files
    ├── vector_store.cpp
    ├── simd_math.cpp
    ├── persistence.cpp
    ├── c_api.cpp
    └── main.cpp              # Engine test runner
```

---

## Build and Execution Instructions

```bash
# 1. Configure CMake build
cmake -B build

# 2. Compile the engine runner
cmake --build build

# 3. Run test runner
./build/fastvectordb_cli
```

---

## Documentation Logs

- [`ARCHITECTURE.adoc`](ARCHITECTURE.adoc) — System design and module specifications.
- [`PROGRESS_2026_07_24.md`](PROGRESS_2026_07_24.md) — Initial build system and storage core implementation log.
- [`PROGRESS_2026_08_02.md`](PROGRESS_2026_08_02.md) — Contiguous memory accessors development log.
