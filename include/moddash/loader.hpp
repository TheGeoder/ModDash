#pragma once
#include <vector>
#include <string>

namespace ModDash {
    struct ModMetadata {
        std::string id;
        std::string name;
        std::string version;
        std::string author;
    };

    class Loader {
    private:
        std::vector<ModMetadata> m_loadedMods;
        Loader() = default; // Enforce Singleton pattern

    public:
        static Loader* get() {
            static Loader instance;
            return &instance;
        }

        void registerMod(const ModMetadata& meta) {
            m_loadedMods.push_back(meta);
        }

        size_t getModCount() const { return m_loadedMods.size(); }
    };
}
