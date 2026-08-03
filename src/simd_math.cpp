#include "fastvectordb/simd_math.hpp"
#include <cmath>

// SIMD vector similarity implementations will go here.

// SIMD Hardware Intrinsics Header Inclusion
#if defined(__AVX2__)
    #include <immintrin.h>
#elif defined(__ARM_NEON)
    #include <arm_neon.h>
#endif

// Namespace fastvectordb is here
namespace fastvectordb {

    // Dot product (AVX2 / ARM NEON SIMD + Scalar Fallback)
    float dotProduct(const float *a, const float *b, std::size_t size) {
        if (a == nullptr || b == nullptr || size == 0) {
            return 0.0f;
        }
        float sum = 0.0f;
        std::size_t i = 0;

#if defined(__AVX2__)
        // AVX2 256-bit registers that processes 8 floats per loop iteration
        __m256 v_sum = _mm256_setzero_ps();
        for (; i + 7 < size; i += 8) {
            __m256 v_a = _mm256_loadu_ps(a + i);
            __m256 v_b = _mm256_loadu_ps(b + i);
            v_sum = _mm256_fmadd_ps(v_a, v_b, v_sum);
        }
        alignas(32) float buffer[8];
        _mm256_storeu_ps(buffer, v_sum);
        for (int k = 0; k < 8; ++k) {
            sum += buffer[k];
        }
#elif defined (__ARM_NEON)
        // ARM-NEON 128-bit registers for Jetson AGX Orin which processes 4 float per loop
        for (; i + 3 < size; i += 4) {
            float32x4_t v_a = vld1q_f32(a + i);
            float32x4_t v_b = vld1q_f32(b + i);
            v_sum = vaddq_f32(v_sum, v_b);
        }
        sum = vaddq_f32(v_sum);
#endif

        // Scalar loop for remaining elements
        for (; i < size; ++i) {
            sum += a[i] * b[i];
        }
        return sum;
    }

    // Vector L2 Norm (Magnitude is: sqrt(dotProduct(vec,vec)))
    float vectorNorm(const float *vec, std::size_t size) {
        return std::sqrt(dotProduct(vec, vec, size));
    }

    // Cosine similarity (dot(a,b) / (|a| * |b|))
    float cosineSimilarity(const float* a, const float* b, std::size_t size) {
        float norm_a = vectorNorm(a, size);
        float norm_b = vectorNorm(b, size);
        if (norm_a == 0.0f || norm_b == 0.0f) {
            return 0.0f;
        }
        return dotProduct(a,b,size) / (norm_a * norm_b);
    }

    // L2 Distance Squared (sum((a_i - b_i)^2))
    float l2_distanceSquared(const float* a, const float* b, std::size_t size) {
        if (a == nullptr || b == nullptr || size == 0) {
            return 0.0f;
        }
        float diffSum = 0.0f;
        for (std::size_t i = 0; i < size; ++i) {
            float diff = a[i] - b[i];
            diffSum += diff * diff;
        }
        return diffSum;
    }
}


