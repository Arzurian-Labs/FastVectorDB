// Necessary libraries here
#include "fastvectordb/persistence.hpp"
#include <fstream>
#include <stdexcept>

// Persistence and mmap implementation details will go here.

// Namespace fastvectordb
namespace fastvectordb {

    // Saving VectorStore to binary file
    void save_to_file(const VectorStore &store, const std::string &filepath) {
        std::ofstream out(filepath, std::ios::binary);
        if (!out.is_open()) {
            throw std::runtime_error("Could not open file for writing" + filepath);
        }

        // Preparing the binary header
        Header header;
        header.dimension = store.dimension();
        header.vector_count = store.size();

        // Write header, ID array, and the flat float data buffer
        out.write(reinterpret_cast<const char*>(&header), sizeof(header));
        out.write(reinterpret_cast<const char*>(store.ids().data()), store.size() * sizeof(uint64_t));
        out.write(reinterpret_cast<const char*>(store.data()), store.size() * store.dimension() * sizeof(float));
    }

    // Load VectorStore from the binary file
    VectorStore load_from_file(const std::string &filepath) {
        std::ifstream in(filepath, std::ios::binary);
        if (!in.is_open()) {
            throw std::runtime_error("Could not open file for reading" + filepath);
        }

        // Read and validate binary header signature
        Header header;
        in.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (header.magic[0] != 'V' || header.magic[1] != 'E' || header.magic[2] != 'C' || header.magic[3] != 'D') {
            throw std::runtime_error("Invalid file format signature in: " + filepath);
        }
        VectorStore store(header.dimension, header.vector_count);

        // Read IDs array and float data buffer
        std::vector<std::uint64_t> ids(header.vector_count);
        in.read(reinterpret_cast<char*>(ids.data()), header.vector_count * sizeof(std::uint64_t));

        std::vector<float> data(header.vector_count * header.dimension);
        in.read(reinterpret_cast<char*>(data.data()), header.vector_count * header.dimension * sizeof(float));

        // Reconstructing the vectors into store
        for (std::size_t i = 0; i < header.vector_count; ++i) {
            std::vector<float> vec(data.begin() + i * header.dimension, data.begin() + (i + 1) * header.dimension);
           store.insert(ids[i], vec);
        }
        return store;
    }
}
