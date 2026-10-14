#include <iostream>
#include <string>
#include "array.h"

using namespace std;

void MInitArray(Array& array, size_t capacity) {
    array.data = new string[capacity];
    array.size = 0;
    array.capacity = capacity;
}

void MResize(Array& array) {
    size_t newCapacity = (array.capacity == 0) ? 4 : array.capacity * 2;
    string* new_data = new string[newCapacity];
    for (size_t i = 0; i < array.size; ++i) {
        new_data[i] = array.data[i];
    }
    delete[] array.data;
    array.data = new_data;
    array.capacity = newCapacity;
}

void MAddEnd(Array& array, const string& text) {
    if (array.size == array.capacity) {
        MResize(array);
    }
    array.data[array.size] = text;
    array.size++;
}

void MAddIndex(Array& array, const string& text, size_t index) {
    if (index < 0 || index > array.size) {
        cout << "no\n";
        return;
    }
    if (array.size == array.capacity) {
        MResize(array);
    }
    for (int i = array.size; i > index; --i) {
        array.data[i] = array.data[i - 1];
    }
    array.data[index] = text;
    array.size++;
}

string MGet(const Array& array, size_t index) {
    return array.data[index];
}

void MDeleteIndex(Array& array, size_t index) {
    if (index < 0 || index >= array.size) {
        cout << "no\n";
        return;
    }
    for (size_t i = index; i < array.size - 1; ++i) {
        array.data[i] = array.data[i + 1];
    }
    array.size--;
}

void MReplace(Array& array, const string& text, size_t index) {
    if (index < 0 || index >= array.size) {
        return;
    }
    array.data[index] = text;
}

size_t MLength(const Array& array) {
    return array.size;
}

void MPrint(const Array& array) {
    for (size_t i = 0; i < array.size; ++i) {
        cout << array.data[i] << " ";
    }
    cout << "\n";
}

void MPrintAddresses(const Array& array) {
    for (size_t i = 0; i < array.size; ++i) {
        cout << "[" << i << "] " << array.data[i] << " | адрес: " << &array.data[i] << '\n';
    }
    cout << "size = " << array.size << " capacity = " << array.capacity << "\n\n";
}

void MFree(Array& array) {
    delete[] array.data;
    array.data = nullptr; array.size = 0; array.capacity = 0;
}