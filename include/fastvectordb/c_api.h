#ifndef FASTVECTORDB_C_API_H
#define FASTVECTORDB_C_API_H

// Necessary libraries
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Plain C interface function declarations will be placed here.


typedef void* vdbStore_t;

vdbStore_t vdb_store_create (size_t dimension, size_t initial_capacity);
void vdb_destroy (vdbStore_t handle);

size_t vdb_dimension (vdbStore_t handle);
size_t vdb_size (vdbStore_t handle);

int vdb_insert(vdbStore_t handle, uint64_t ID, const float* vecData, size_t vecLen);

size_t vdb_search_knn(vdbStore_t handle, const float* queryData, size_t queryLen, size_t k, uint64_t* outIDs, float* outScores);

#ifdef __cplusplus
}
#endif

#endif // FASTVECTORDB_C_API_H
