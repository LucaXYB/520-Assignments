#include "utilities.h"

#include<algorithm>
#include<fstream>
#include<sstream>
#include<string>
#include<stdexcept>
#include<cctype>

void sort_by_magnitude(std::vector<double>& vec) {
    sort(vec.begin(), vec.end(), [](double a, double b) {
        return std::abs(a) < std::abs(b);
    });
}

TypedArray<TypedArray<double>> read_matrix_csv(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file" + path);
    }

    TypedArray<TypedArray<double>> matrix;
    std::string line;

    while (std::getline(file, line)) {
        TypedArray<double> row;
        std::istringstream lineStream(line);
        std::string cell;
        
        while (std::getline(lineStream, cell, ',')) {
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);

            try {
                double value = std::stod(cell);
                row.set(row.size(), value);
            }
            catch (const std::invalid_argument& e){
                throw std::runtime_error("Invalid number format in files:" + path);
            }
        }

        if (matrix.size() > 0 && row.size() != matrix.get(0).size()) {
            throw std::runtime_error("Irregular row size in matrix: " + path);
        }

        matrix.set(matrix.size(), row);
    }
    file.close();
    return matrix;
}

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + path);
    }

    for (int i = 0 ; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.get(i).size(); ++j) {
            file << matrix.get(i).get(j);
            if (j < matrix.get(i).size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
    file.close();
}

bool isValidChar(char c) {
    return std::isalnum(c) || c == '\'';
}

std::vector<std::string> extractWords(const std::string& line) {
    std::vector<std::string> words;
    std::string word;
    for (char c : line) {
        if (isValidChar(c)) {
            word += std::tolower(c);
        }
        else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

std::map<std::string, int> occurrence_map(const std::string path) {
    std::map<std::string, int> wordCount;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }

    while (getline(file, line)) {
        auto words = extractWords(line);
        for (const auto& word : words) {
            ++wordCount[word];
        }
    }

    file.close();
    return wordCount;
}