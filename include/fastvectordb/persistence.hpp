#ifndef FASTVECTORDB_PERSISTENCE_HPP
#define FASTVECTORDB_PERSISTENCE_HPP

// Necessary libraries here
#include <string>
#include <cstdint>
#include "fastvectordb/vector_store.hpp"

// Binary serialization and mmap persistence interface will be placed here.

namespace fastvectordb {

    // Binary header structure for the .vdb database files
    struct Header {
        char magic[4] = {'V', 'E', 'C', 'D'}; // Signature codenames
        std::uint32_t version = 1;
        std::uint64_t dimension = 0;
        std::uint64_t vector_count = 0;
    };

    // Saving VectorStore to a binary file
    void save_to_file (const VectorStore& store, const std::string& filepath);

    // Load VectorStore from a binary file
    VectorStore load_from_file (const std::string& filepath);
}

#endif // FASTVECTORDB_PERSISTENCE_HPP
