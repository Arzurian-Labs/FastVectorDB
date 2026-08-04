#include "fastvectordb/c_api.h"
#include "fastvectordb/vector_store.hpp"
#include <vector>

// C-ABI wrapper functions implementation will go here.

extern "C" {
// Creating the VectorStore handle
vdbStore_t vdb_store_create(size_t dimension, size_t initial_capacity) {
    try {
        return new fastvectordb::VectorStore(dimension, initial_capacity);
    } catch (...) {
        return nullptr;
    }
}

// Destroying the VectorStore handle
void vdb_destroy(vdbStore_t handle) {
    if (handle) {
        delete static_cast<fastvectordb::VectorStore*>(handle);
    }
};

// Getting the dimension
size_t vdb_dimension(vdbStore_t handle) {
    if (!handle) return 0;
        return static_cast<fastvectordb::VectorStore*>(handle)->dimension();
}

// Getting the total stored vectors count
size_t vdb_size(vdbStore_t handle) {
    if (!handle) return 0;
        return static_cast<fastvectordb::VectorStore*>(handle)->size();
}

// Inserting the vector from the raw float array
int vdb_insert(vdbStore_t handle, uint64_t id, const float* vecData, size_t vecLen) {
    if (!handle || !vecData) return -1;
    try {
        std::vector<float> vec(vecData, vecData + vecLen);
        static_cast<fastvectordb::VectorStore*>(handle)->insert(id, vec);
        return 0; // If it is success.
    } catch (...) {
        return -1; // If it is an error
    }
}

// Performing the SIMD k-NN Query and fill output arrays
size_t vdb_search_knn(vdbStore_t handle, const float* queryData, size_t queryLen, size_t k, uint64_t* outIDs, float* outScores) {
   if (!handle || !queryData || !queryLen || !outIDs || !outScores) return 0;
    try {
        std::vector<float> query(queryData, queryData + queryLen);
        auto results = static_cast<fastvectordb::VectorStore*>(handle)->search_knn(query, k);
       for (size_t i = 0; i < results.size(); ++i) {
           outIDs[i] = results[i].first;
           outScores[i] = results[i].second;
       }
        return results.size(); // Number of matches returned
    } catch (...) {
        return 0;
    }
}

} // The end of the extern "C"
