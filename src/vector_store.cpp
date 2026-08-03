#include "fastvectordb/vector_store.hpp"

#include <algorithm>
#include <stdexcept>
#include <cstdint> // Required for uint64_t

#include "fastvectordb/simd_math.hpp"

// Implementation of VectorStore class methods will go here.

namespace fastvectordb {
    VectorStore::VectorStore(std::size_t dimension, std::size_t initial_capacity)
        : dimension_(dimension) // Assign incoming 'dimension' parameter into member variable 'dimension_'
    {
        // Constructor body starts here, first checking if the dimension equals to zero.
        if (dimension_ == 0) {
            throw std::invalid_argument("VectorStore::VectorStore: dimension must be greater than 0.");
        }
        // Possible pre-allocate memory for initial_capacity will be located here.
        if (initial_capacity > 0) {
            data_.reserve(initial_capacity * dimension_);
            ids_.reserve(initial_capacity);
        }
    }
    std::size_t VectorStore::dimension() const {
        return dimension_;
    }

    std::size_t VectorStore::size() const {
        return ids_.size();
    }

    void VectorStore::insert(std::uint64_t id, const std::vector<float>& vec) {
        if (vec.size() != dimension_) {
            throw std::invalid_argument("VectorStore::insert: vector size does not match dimension.");
        }
        data_.insert(data_.end(), vec.begin(), vec.end());
        ids_.push_back(id);
    }

    // Getting the pointer to float array for vector at a specific index
    const float* VectorStore::get_vector(std::size_t index) const {
        if (index >= ids_.size()) {
            throw std::out_of_range("VectorStore::get_vector: index out of range.");
        }
        return &data_[index * dimension_];
    }

    // Get the pointer to the raw underlying contiguous float buffer
    const float* VectorStore::data() const {
        return data_.data();
    }

    // Get reference to vector IDs list
    const std::vector<std::uint64_t>& VectorStore::ids() const {
        return ids_;
    }

    std::vector<std::pair<std::uint64_t, float> > VectorStore::search_knn(const std::vector<float> &query,
        std::size_t k) const {
        if (query.size() != dimension_) {
            throw std::invalid_argument("VectorStore::search: query size does not match dimension.");
        }
        if (k == 0 || size() == 0) {
            return {};
        }

        // Cosine Similarity calculation for every stored vectors using SIMD Math
        std::vector<std::pair<std::uint64_t, float>> result;
        result.reserve(size());

        for (std::size_t i = 0; i < size(); ++i) {
            const float* vecPtr = get_vector(i);
            float score = cosineSimilarity(query.data(), vecPtr, dimension_);
            result.push_back({ids_[i], score});
        }

        // Using similarity scores to sort in the descending order.
        std::size_t topK = std::min(k, result.size());
        std::partial_sort(result.begin(), result.begin() + topK, result.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            }
        );
        result.resize(topK);
        return result;
    };

}

