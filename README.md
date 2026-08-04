# FastVectorDB

FastVectorDB is a high-performance, low-latency in-memory vector database engine written in C++20. It is designed to serve as a fast semantic memory subsystem for edge AI applications and local agent frameworks.

---

## Features

- **Contiguous Memory Layout**: Aligned float buffer storing high-dimensional vectors back-to-back in contiguous memory to eliminate pointer-chasing and maximize CPU cache line efficiency.
- **SIMD Hardware Acceleration**: Target support for AVX2/FMA (x86_64) and ARM NEON SIMD vector instruction sets.
- **k-NN Vector Similarity Search**: Top-k similarity search utilizing SIMD-accelerated Cosine Similarity and `std::partial_sort`.
- **Binary Serialization**: Efficient binary database saving (`save_to_file`) and loading (`load_from_file`) with magic signature validation (`VECD`).
- **C-ABI Gateway**: `extern "C"` functions for FFI integration with Python (`ctypes`) and local AI runtime microservices.
- **C++20 Architecture**: Modern type safety, capacity pre-allocation, `[[nodiscard]]`, and dimension validation.

---

## Directory Structure

```
FastVectorDB/
├── CMakeLists.txt            # CMake build configuration script
├── README.md                 # Project overview and documentation
├── ARCHITECTURE.adoc         # Detailed architecture design specification
├── SIMD_INTRINSICS_GUIDE.md  # SIMD architecture and intrinsics reference guide
├── include/                  # Header files
│   └── fastvectordb/
│       ├── vector_store.hpp  # Contiguous vector storage engine
│       ├── simd_math.hpp     # SIMD distance and similarity math
│       ├── persistence.hpp   # Binary serialization interface
│       └── c_api.h           # C-ABI FFI exports
└── src/                      # Implementation files
    ├── vector_store.cpp
    ├── simd_math.cpp
    ├── persistence.cpp
    ├── c_api.cpp
    └── main.cpp              # Full 5-phase test runner
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

## Implementation Roadmap (100% Complete)

- [x] **Phase 1: Memory Layout & Storage Core**: Contiguous float buffer with 64-byte cache alignment and dimension validation.
- [x] **Phase 2: Contiguous Accessors**: Pointer accessors (`get_vector`, `data`, `ids`).
- [x] **Phase 3: SIMD Acceleration & k-NN Search**: AVX2/FMA & ARM NEON SIMD `dotProduct` and `search_knn`.
- [x] **Phase 4: Binary Persistence**: `save_to_file` and `load_from_file` binary file I/O.
- [x] **Phase 5: C-ABI Gateway**: `extern "C"` wrapper functions (`vdb_store_create`, `vdb_insert`, `vdb_search_knn`, `vdb_destroy`).

---

## Documentation Logs

- [`ARCHITECTURE.adoc`](ARCHITECTURE.adoc) — System design and module specifications.
- [`SIMD_INTRINSICS_GUIDE.md`](SIMD_INTRINSICS_GUIDE.md) — SIMD architecture and intrinsics reference guide.
- [`PROGRESS_2026_07_24.md`](PROGRESS_2026_07_24.md) — Initial build system and storage core implementation log.
- [`PROGRESS_2026_08_02.md`](PROGRESS_2026_08_02.md) — Development and architecture progress log.
