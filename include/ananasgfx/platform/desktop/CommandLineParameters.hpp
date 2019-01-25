#ifndef PLATFORM_DESKTOP_COMMANDLINEPARAMETERS_H
#define PLATFORM_DESKTOP_COMMANDLINEPARAMETERS_H

#include <map>
#include <string>

namespace platform::desktop {

    /**
     * @brief Parses the arguments given to the program and makes them easily accessible.
     */
    class CommandLineParameters {
    public:
        /**
         * @brief Constructor
         *
         * @param argc The number of arguments.
         * @param argv The pointer to the arguments.
         */
        CommandLineParameters(int argc, const char* argv[]) noexcept;

        /**
         * @brief Returns the commands map.
         *
         * @return Reference to the commands map.
         */
        const std::map<std::string,std::string>& getCommands() const noexcept;

        /**
         * @brief Returns the string value for the command with the given name or default value if no value is stored.
         *
         * @param name The command name.
         * @param defaultValue The default value to use if no value is stored.
         * @return The string value.
         */
        std::string getString(const std::string& name, const std::string& defaultValue) const noexcept;

        /**
         * @brief Returns the boolean value for the command with the given name or the default value.
         *
         * @param name The name of the command.
         * @param defaultValue The default value.
         * @return The boolean value.
         */
        bool getBool(const std::string& name, bool defaultValue) const noexcept;

        /**
         * @brief Returns the long value for the command with the given name or the default value.
         *
         * @param name The name of the command.
         * @param defaultValue The default value.
         * @return The long value.
         */
        long getLong(const std::string&name, long defaultValue) const noexcept;

    private:
        /**
         * @brief The commands map.
         */
        std::map<std::string,std::string> mCommands;
    };

}

#endif