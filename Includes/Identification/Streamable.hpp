#pragma once

#include <string>


#define MANGLED_NAME(type) typeid(type).name()  // Used for debugging. Compiler specific. Not portable.


struct Streamable {
    virtual ~Streamable();

    friend std::ostream &operator<<(std::ostream &os, const Streamable &obj);

    [[nodiscard]] std::string as_string() const;

protected:
    Streamable();

    std::string stream_{};  // This is big performance tax, but good for debugging and development.
};
