#include "Identification/Streamable.hpp"

#include <iostream>


Streamable::~Streamable() = default;

std::string Streamable::as_string() const {
    return stream_;
}

Streamable::Streamable() = default;

std::ostream &operator<<(std::ostream &os, const Streamable &obj) {
    os << obj.stream_;
    return os;
}
