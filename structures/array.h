#ifndef ARRAY_H
#define ARRAY_H

#include <string>
using namespace std;

struct Array {
    string* data;
    size_t size;
    size_t capacity;
};

void MInitArray(Array& arr, size_t capacity);
void MResize(Array& arr);
void MAddEnd(Array& arr, const string& text);
void MAddIndex(Array& arr, const string& text, size_t index);
string MGet(const Array& arr, size_t index);
void MDeleteIndex(Array& arr, size_t index);
void MReplace(Array& arr, const string& text, size_t index);
size_t MLength(const Array& arr);
void MPrint(const Array& arr);
void MPrintAddresses(const Array& arr);
void MFree(Array& array);

#endif