# SIMD Architecture and Intrinsics Reference Guide

**Author**: Hazushiro  
**Repository**: FastVectorDB  
**Scope**: Low-level x86_64 (AVX2/FMA) and ARM64 (NEON) Vector Programming

---

## 1. Architectural Foundations (Flynn's Taxonomy)

In computer architecture (as detailed by Hennessy & Patterson), SIMD (Single Instruction, Multiple Data) is a hardware paradigm where a single instruction stream operates simultaneously on multiple data elements packed inside wide vector registers.

- **SISD (Scalar)**: Standard CPU pipeline executing 1 instruction on 1 data word (32-bit/64-bit).
- **SIMD (Vector)**: Single instruction executing across packed vector registers ($N \times 32$-bit elements per cycle).
- **MIMD (Multi-Core)**: Multiple independent CPU cores executing distinct instruction streams.

---

## 2. Vector Register Data Types

Hardware registers hold packed data elements:

| Architecture | Intrinsic Type | Register Width | Single-Precision Floats | Double-Precision Floats |
| :--- | :--- | :--- | :--- | :--- |
| **x86_64 AVX2** | `__m256` | 256 bits | 8 floats ($8 \times 32$-bit) | 4 doubles ($4 \times 64$-bit) |
| **x86_64 AVX-512** | `__m512` | 512 bits | 16 floats ($16 \times 32$-bit) | 8 doubles ($8 \times 64$-bit) |
| **ARM64 NEON** | `float32x4_t` | 128 bits | 4 floats ($4 \times 32$-bit) | 2 doubles ($2 \times 64$-bit) |

---

## 3. Intel SIMD Intrinsic Naming Convention Formula

Intel C/C++ SIMD intrinsic function names follow a standardized formula:

`_mm<width>_<operation>_<datatype>`

### Breakdown:

1. **Width Prefix**:
   - `_mm_`: 128-bit register (SSE / SSE2 / SSE4)
   - `_mm256_`: 256-bit register (AVX / AVX2 / FMA)
   - `_mm512_`: 512-bit register (AVX-512)

2. **Operation Name**:
   - `setzero`: Initialize vector register elements to zero.
   - `loadu`: Load unaligned data from memory into register.
   - `load`: Load aligned data from memory into register.
   - `fmadd`: Fused Multiply-Add.
   - `storeu`: Store unaligned vector register contents to memory.
   - `store`: Store aligned vector register contents to memory.

3. **Data Type Suffix**:
   - `ps`: Packed Single-precision floats (`float`, 32-bit).
   - `pd`: Packed Double-precision floats (`double`, 64-bit).
   - `epi32`: Extended Packed Signed 32-bit Integers (`int32_t`).
   - `epu8`: Extended Packed Unsigned 8-bit Integers (`uint8_t`).

### Example Decoding:

`_mm256_fmadd_ps(a, b, c)`
- `_mm256_`: Operates on 256-bit registers (8 floats).
- `fmadd`: Computes Fused Multiply-Add: $(a \times b) + c$.
- `ps`: Operates on Packed Single-precision floats.

---

## 4. Fused Multiply-Add (FMA)

Standard floating-point accumulation requires two separate instruction cycles:
1. Multiply: $T = A \times B$ (with rounding)
2. Add: $S = T + C$ (with second rounding)

FMA executes the unified operation $S = (A \times B) + C$ in a single hardware clock cycle with only one final rounding step. 

### Benefits:
- **Performance**: 2x throughput (16 floating-point operations per 256-bit instruction).
- **Precision**: Higher numerical accuracy due to eliminating intermediate rounding errors.

---

## 5. Memory Alignment (`alignas`)

CPU memory buses transfer data in 64-byte cache lines. If a vector array starts at an unaligned memory address, a vector load instruction may span across two cache lines, incurring split-cache transaction penalties.

```cpp
// Ensures 32-byte alignment matching 256-bit AVX2 register width
alignas(32) float buffer[8];
```

---

## 6. Cross-Platform SIMD Mapping (x86_64 vs ARM NEON)

| Operation | x86_64 AVX2 Intrinsic | ARM64 NEON Intrinsic |
| :--- | :--- | :--- |
| **Zero Register** | `_mm256_setzero_ps()` | `vdupq_n_f32(0.0f)` |
| **Vector Load** | `_mm256_loadu_ps(ptr)` | `vld1q_f32(ptr)` |
| **Fused Multiply-Add** | `_mm256_fmadd_ps(a, b, c)` | `vmlaq_f32(c, a, b)` |
| **Vector Horizontal Add**| Manual reduction | `vaddvq_f32(v_sum)` |
| **Vector Store** | `_mm256_storeu_ps(ptr, reg)` | `vst1q_f32(ptr, reg)` |

---

## 7. Header Inclusion Pattern

To ensure portability across x86_64 and ARM architectures, use preprocessor feature guards in implementation files (`.cpp`):

```cpp
#if defined(__AVX2__)
  #include <immintrin.h>
#elif defined(__ARM_NEON)
  #include <arm_neon.h>
#endif
```
