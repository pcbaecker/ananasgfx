#include <ananasgfx/gfx/FileManager.hpp>
#include <unistd.h>

namespace gfx {

    bool fileExists(const std::string& name) {
        return access(name.c_str(), F_OK) != -1;
    }

    FileManager::FileManager(std::string resourcePath, std::string userPath) noexcept :
    mResourcePath(std::move(resourcePath)), mUserPath(std::move(userPath)) {

    }

    std::optional<std::string> FileManager::tryResource(const std::string &filename) const noexcept {
        // Get the combined filepath
        std::string file = getResource(filename);

        // Check if file exists
        if (!fileExists(file)) {
            return std::nullopt;
        }

        return file;
    }

    std::optional<std::string> FileManager::tryUserfile(const std::string &filename) const noexcept {
        // Get the combined filepath
        std::string file = getUserfile(filename);

        // Check if file exists
        if (!fileExists(file)) {
            return std::nullopt;
        }

        return file;
    }

    std::string FileManager::getResource(const std::string &filename) const noexcept {
        return this->mResourcePath + filename;
    }

    std::string FileManager::getUserfile(const std::string &filename) const noexcept {
        return this->mUserPath + filename;
    }

}