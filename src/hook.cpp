#include "moddash/hook.hpp"
#include <iostream>

#if defined(_WIN32)
    #include <windows.h>
    // In a full build, neverdasherr will include MinHook here:
    // #include <MinHook.h>
#else
    #include <sys/mman.h>
    #include <unistd.h>
#endif

namespace ModDash {

    // Global registry container to keep track of applied hijacks
    static std::vector<Hook*> g_activeHooks;

    // Implementation of the Hook constructor
    Hook::Hook(const std::string& name, uintptr_t address)
        : m_displayName(name), m_targetAddress(address), m_originalFunctionTrampoline(nullptr) {}

    // core routine to modify game code memory permissions
    bool setMemoryProtection(void* address, size_t size, bool executable) {
#if defined(_WIN32)
        DWORD oldProtect;
        DWORD newProtect = executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE;
        return VirtualProtect(address, size, newProtect, &oldProtect) != 0;
#else
        // Android/Linux requires aligning to page boundaries
        uintptr_t pageSize = sysconf(_SC_PAGESIZE);
        uintptr_t startPage = (uintptr_t)address & ~(pageSize - 1);
        size_t totalSize = ((uintptr_t)address + size) - startPage;
        
        int protection = PROT_READ | PROT_WRITE;
        if (executable) protection |= PROT_EXEC;
        
        return mprotect((void*)startPage, totalSize, protection) == 0;
#endif
    }

    // Activates the intercept routing inside the game process memory space
    bool Hook::enable() {
        if (m_targetAddress == 0) {
            std::cerr << "[ModDash::Hook] Error: Target address for '" << m_displayName << "' is null." << std::endl;
            return false;
        }

        std::cout << "[ModDash::Hook] Attempting to hook '" << m_displayName << "' at 0x" << std::hex << m_targetAddress << std::endl;

#if defined(_WIN32)
        // 🖥️ Windows: neverdasherr will wrap MinHook like this:
        /*
        if (MH_CreateHook((LPVOID)m_targetAddress, (LPVOID)m_detourFunction, &m_originalFunctionTrampoline) != MH_OK) return false;
        if (MH_EnableHook((LPVOID)m_targetAddress) != MH_OK) return false;
        */
        std::cout << "[Windows Engine] Hook registered via MinHook stub simulation." << std::endl;
#else
        // 📱 Android: Custom inline hook placeholder
        // Changes permissions to patch instruction memory safely
        if (!setMemoryProtection((void*)m_targetAddress, 8, true)) {
            std::cerr << "[Android Engine] Failed to change instruction permissions." << std::endl;
            return false;
        }
        std::cout << "[Android Engine] Instruction page un-locked and hook mounted." << std::endl;
#endif

        g_activeHooks.push_back(this);
        return true;
    }

    // Helper Factory Utility implementation
    void createHook(const std::string& name, uintptr_t address) {
        Hook* newHook = new Hook(name, address);
        if (newHook->enable()) {
            std::cout << "[ModDash] Successfully applied: " << name << std::endl;
        } else {
            std::cerr << "[ModDash] Failed to apply: " << name << std::endl;
            delete newHook;
        }
    }
}
