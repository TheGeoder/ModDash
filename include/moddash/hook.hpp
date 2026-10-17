#pragma once
#include <string>

namespace ModDash {
    // A modern C++ wrapper for managing function injections
    class Hook {
    public:
        std::string m_targetFunction;
        uintptr_t m_address;

        Hook(std::string functionName, uintptr_t address);
        bool apply();
    };
}
