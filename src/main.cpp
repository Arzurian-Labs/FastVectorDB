#include <iostream>
#include <vector>
#include <stdexcept>
#include "fastvectordb/vector_store.hpp"

int main() {

    std::cout << "FastVectorDB Engine Test Procedure" << std::endl;

    // Initial storing of 3-dimensional vectors
    fastvectordb::VectorStore store(3, 10);

    // Printing initial status.
    std::cout << "Initial Dimension: " << store.dimension()
              << ", Size: " << store.size() << std::endl;

    // Inserting valid vectors
    store.insert(101, {1.0f, 2.0f, 3.0f});
    store.insert(102, {4.0f, 5.0f, 6.0f});
    std::cout << "Inserted two vectors. Verified size: " << store.size() << std::endl;

    // Test dimension validation using try-catch procedure
    try {
        std::cout << "Testing invalid vector insert, for example: dimension 2..." << std::endl;
       store.insert(103, {1.0f, 2.0f});
    } catch (const std::exception& e) {
        std::cout << "Catch expected error: " << e.what() << std::endl;
    }

    // Verify that all tests are completed
    std::cout << "FastVectorDB Engine Initialized successfully." << std::endl;

    return 0;
}
