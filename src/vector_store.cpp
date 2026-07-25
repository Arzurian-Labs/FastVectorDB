#include "fastvectordb/vector_store.hpp"
#include <stdexcept>
#include <cstdint> // Required for uint64_t

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
}

