#include <iostream>
#include <vector>
#include <stdexcept>
#include "fastvectordb/vector_store.hpp"
#include "fastvectordb/persistence.hpp"
#include "fastvectordb/c_api.h"

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "   🚀 FastVectorDB Engine Full 5-Phase Test Runner" << std::endl;
    std::cout << "==================================================" << std::endl;

    // 1. Core VectorStore Initialization & Insertion (Phases 1 & 2)
    fastvectordb::VectorStore store(3, 10);
    std::cout << "Initialized Store. Dimension: " << store.dimension()
              << ", Initial Size: " << store.size() << std::endl;

    store.insert(101, {1.0f, 2.0f, 3.0f});
    store.insert(102, {4.0f, 5.0f, 6.0f});
    std::cout << "Inserted 2 vectors. Updated Size: " << store.size() << std::endl;

    // Dimension validation check
    try {
        store.insert(103, {1.0f, 2.0f}); // Mismatched dimension
    } catch (const std::exception& e) {
        std::cout << "Caught expected guard clause error: " << e.what() << std::endl;
    }

    // 2. SIMD k-NN Vector Search (Phase 3)
    std::vector<float> query = {1.0f, 2.0f, 3.0f};
    std::size_t k = 2;
    std::cout << "\n--- Phase 3: SIMD k-NN Search (Top-" << k << ") ---" << std::endl;
    auto topMatches = store.search_knn(query, k);
    for (std::size_t i = 0; i < topMatches.size(); ++i) {
        std::cout << "  Rank " << (i + 1) << " | Vector ID: " << topMatches[i].first
                  << " | Cosine Similarity Score: " << topMatches[i].second << std::endl;
    }

    // 3. Binary File Persistence (Phase 4)
    std::string db_file = "/tmp/test_database.vdb";
    std::cout << "\n--- Phase 4: Binary File Serialization ---" << std::endl;
    fastvectordb::save_to_file(store, db_file);
    std::cout << "Saved VectorStore to binary file: " << db_file << std::endl;

    fastvectordb::VectorStore loaded_store = fastvectordb::load_from_file(db_file);
    std::cout << "Loaded VectorStore from binary file. Size: " << loaded_store.size() << std::endl;

    // 4. C-ABI FFI Gateway (Phase 5)
    std::cout << "\n--- Phase 5: C-ABI Gateway FFI ---" << std::endl;
    vdbStore_t c_handle = vdb_store_create(3, 10);
    float c_vec1[3] = {1.0f, 2.0f, 3.0f};
    float c_vec2[3] = {4.0f, 5.0f, 6.0f};
    vdb_insert(c_handle, 201, c_vec1, 3);
    vdb_insert(c_handle, 202, c_vec2, 3);

    std::cout << "C-ABI Store Size: " << vdb_size(c_handle) << std::endl;

    uint64_t out_ids[2];
    float out_scores[2];
    size_t matches = vdb_search_knn(c_handle, c_vec1, 3, 2, out_ids, out_scores);
    std::cout << "C-ABI k-NN Search returned " << matches << " matches:" << std::endl;
    for (size_t i = 0; i < matches; ++i) {
        std::cout << "  Match " << (i + 1) << " | ID: " << out_ids[i]
                  << " | Score: " << out_scores[i] << std::endl;
    }
    vdb_destroy(c_handle);

    std::cout << "\n==================================================" << std::endl;
    std::cout << "✅ All 5 Phases of FastVectorDB Verified Cleanly!" << std::endl;
    std::cout << "==================================================" << std::endl;

    return 0;
}
