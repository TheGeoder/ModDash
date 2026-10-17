#include <iostream>

#if defined(_WIN32)
    #define MOD_API __declspec(dllexport)
#else
    #define MOD_API __attribute__((visibility("default")))
#endif

// This links to your second file
void sayHelloFromUtils();

extern "C" MOD_API void moddashInit() {
    std::cout << "ModDash Mod Initialized!" << std::endl;
    sayHelloFromUtils();
}
