#ifndef FASTVECTORDB_SIMD_MATH_HPP
#define FASTVECTORDB_SIMD_MATH_HPP
#include <cstddef>

// SIMD distance calculation function declarations will be placed here.
namespace fastvectordb {

    // Dot product (SIMD AVX2 / ARM NEON accelerated with scalar fallback)
    float dotProduct(const float* a, const float* b, std::size_t size);

    // Vector L2 Norm (Euclidean Magnitude: sqrt(sum(a_i^2)))
    float vectorNorm(const float* vec, std::size_t size);

    // Cosine similarity (returns the score between -1.0 and 1.0)
    float cosineSimilarity(const float* a, const float* b, std::size_t size);

    // L2 Distance Squared (Euclidean distance squared: sum((a_i - b_i)^2)
    float l2_distanceSquared(const float* a, const float* b, std::size_t size);

}

#endif // FASTVECTORDB_SIMD_MATH_HPP
