#ifndef FASTVECTORDB_VECTOR_STORE_HPP
#define FASTVECTORDB_VECTOR_STORE_HPP
#include <atomic>
#include <cstddef>
#include <vector> // If necessary for storages
#include <cstdint> // Required for std::uint64_t to work

// VectorStore class header will be implemented here.

namespace fastvectordb {
    // 1. A constructor known as VectorStore with size_t dimension as parameter
    // explicit VectorStore(std::size_t dimension, std::size_t initial_capacity = 0);
    class VectorStore {
    public:
        explicit VectorStore(std::size_t dimension, std::size_t initial_capacity = 0);

        // Getters
        std::size_t dimension() const;
        std::size_t size() const;

        // Insertion Method
        void insert(std::uint64_t id, const std::vector<float>& vec);

    private:
        std::size_t dimension_;
        std::vector<float> data_;
        std::vector<std::uint64_t> ids_;
    };
}

#endif // FASTVECTORDB_VECTOR_STORE_HPP

/*
 * Variabled used:
 *  explicit
 *  std::size_t (due to not using the namespace std;)
 *  namespace
 *  class with public and private declared
 */