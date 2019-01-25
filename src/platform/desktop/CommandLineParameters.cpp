#include <ananasgfx/platform/desktop/CommandLineParameters.hpp>
#include <iostream>
#include <regex>

namespace platform::desktop {

    CommandLineParameters::CommandLineParameters(int argc, const char **argv) noexcept {
        std::regex nameValueRegex("([-]{2}[a-z]{1}[a-z-0-9]*[=][a-zA-Z0-9-\\/#+]*)");

        // Iterate through all arguments
        for (int i = 0; i < argc; i++) {
            // Get the argument
            std::string arg = argv[i];

            // Determine if this argument has a name and value part
            if (arg[0] == '-' && arg[1] == '-' && arg.find('=') == std::string::npos) {
                // Is a boolean command
                this->mCommands.emplace(arg.substr(2, std::string::npos), "true");
            } else {
                // Check if the argument has a valid structure otherwise ignore
                if (std::regex_match(arg, nameValueRegex)) {
                    auto middle = arg.find('=');
                    this->mCommands.emplace(
                            // Store command name
                            arg.substr(2, middle-2),
                            // Store command value
                            arg.substr(middle+1, std::string::npos));
                }
            }
        }
    }

    const std::map<std::string, std::string> &CommandLineParameters::getCommands() const noexcept {
        return this->mCommands;
    }

    std::string CommandLineParameters::getString(
            const std::string &name, const std::string &defaultValue) const noexcept {
        if (this->mCommands.count(name)) {
            return this->mCommands.at(name);
        } else {
            return defaultValue;
        }
    }

    bool CommandLineParameters::getBool(const std::string &name, bool defaultValue) const noexcept {
        if (this->mCommands.count(name)) {
            return true;
        } else {
            return defaultValue;
        }
    }

    long CommandLineParameters::getLong(const std::string &name, long defaultValue) const noexcept {
        if (this->mCommands.count(name)) {
            try {
                return std::stol(this->mCommands.at(name));
            } catch (...) {
                return defaultValue;
            }
        } else {
            return defaultValue;
        }
    }
}