#ifndef UTILITIES_H
#define UTILITIES_H

#include<vector>
#include<string>
#include<map>

template <typename ElementType>
class TypedArray {
    public:
    TypedArray() : capacity(INITIAL_CAPACITY), origin(0), end(0), buffer(new ElementType[INITIAL_CAPACITY]) {}

    TypedArray(const TypedArray& other) : capacity(other.capacity), origin(other.origin), end(other.end), buffer(new ElementType[other.capacity]) {
        std::copy(other.buffer, other.buffer + other.capacity, buffer);
    }

    TypedArray& operator=(const TypedArray& other) {
        if (this != &other) {
            delete[] buffer;
            capacity = other.capacity;
            origin = other.origin;
            end = other.end;
            buffer = new ElementType[capacity];
            std::copy(other.buffer, other.buffer + other.capacity, buffer);
        }
        return *this;
    }

    ~TypedArray() {
        delete[] buffer;
    }

    ElementType& get(int index) const{
        return buffer[index_to_offset(index)];
    }

    const ElementType& safe_get(int index) const {
        return buffer[index_to_offset(index)];
    }

    int size() const {
        return end - origin;
    }

    void set(int index, ElementType value) {
        int offset = index_to_offset(index);
        if (out_of_buffer(offset)) {
            extend_buffer();
        }
        buffer[offset] = value;
    }

private:
    int capacity, origin, end;
    ElementType* buffer;
    static constexpr int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const {
        return origin + index;
    }

    bool out_of_buffer(int offset) const {
        return offset >= capacity;
    }

    void extend_buffer() {
        
    }
};

void sort_by_magnitude(std::vector<double>& vec);

TypedArray<TypedArray<double>> read_matrix_csv(const std::string& path);

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string& path);

std::map<std::string, int> occurrence_map(const std::string path);

#endif