#include "Uniform.h"

template<typename T>
Uniform<T>::Uniform(const char *name, const T &data) {
    this->name = name;
    this->data = data;
}