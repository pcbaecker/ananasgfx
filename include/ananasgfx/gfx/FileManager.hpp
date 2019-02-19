#ifndef GFX_FILEMANAGER_H
#define GFX_FILEMANAGER_H

#include <string>
#include <optional>

namespace gfx {

    /**
     * @brief Provides some easy ways to combine the given filename with user or resource path.
     */
    class FileManager {
    public:
        /**
         * @brief Constructor
         *
         * @param resourcePath The base resource path that will be concatenated with the resource filename.
         * @param userPath The base user path that will be concatenated with the user filename.
         */
        explicit FileManager(std::string resourcePath, std::string userPath) noexcept;

        /**
         * @brief Tries to find a resource file with given name.
         *
         * @param filename The filename to search for.
         * @return Optional that can contain the path to the file.
         */
        std::optional<std::string> tryResource(const std::string &filename) const noexcept;

        /**
         * @brief Tries to find a user file with given name.
         *
         * @param filename The filename to search for.
         * @return Optional that can contain the path to the file.
         */
        std::optional<std::string> tryUserfile(const std::string &filename) const noexcept;

        /**
         * @brief Combines the given filename with the resource path.
         *
         * @param filename The resource file name.
         * @return Concatenated string.
         */
        std::string getResource(const std::string &filename) const noexcept;

        /**
         * @brief Combines the given filename with the user path.
         *
         * @param filename The resource file name.
         * @return Concatenated string.
         */
        std::string getUserfile(const std::string &filename) const noexcept;

    private:
        /**
         * @brief The base resource path.
         */
        std::string mResourcePath;

        /**
         * @brief The base user path.
         */
        std::string mUserPath;
    };

}

#endif