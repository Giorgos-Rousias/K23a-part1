#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "../include/utils/vector_file_readers.hpp"

using namespace std;


/**
 * @brief Read vectors from a file
 *
 * @param filename The name of the file to read
 * @param vectors The vectors to populate
 *
 * @tparam T The type of the vector components
 */
template <typename T>
void read_file_vecs(const string& filename, vector<vector<T>>& vectors) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    while (!file.eof()) {
        int dim;
        file.read(reinterpret_cast<char*>(&dim), sizeof(int));  // Read dimension
        if (file.eof()) break;  // To prevent reading beyond the file

        vector<T> vec(dim);
        file.read(reinterpret_cast<char*>(vec.data()), dim * sizeof(T));  // Read vector components

        if (file.gcount() != static_cast<streamsize>(dim * sizeof(T))) {
            break;  // Prevent adding an incomplete vector at the end
        }
        vectors.push_back(vec);
    }
    file.close();
}

// Explicit instantiations
template void read_file_vecs<unsigned char>(const std::string&, std::vector<std::vector<unsigned char>>&);
template void read_file_vecs<float>(const std::string&, std::vector<std::vector<float>>&);
template void read_file_vecs<int>(const std::string&, std::vector<std::vector<int>>&);