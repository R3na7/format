#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stack>

class UnmatchedBraceError : public std::runtime_error {
public:
    UnmatchedBraceError(const std::string & msg) : std::runtime_error(msg) {}
};

class ArgumentIndexError : public std::runtime_error {
public:
    ArgumentIndexError(const std::string & msg) : std::runtime_error(msg) {}
};

template<typename T, typename Stream>
concept StreamInsertable = requires(Stream& os, T arg) {
    { os << arg } -> std::same_as<Stream&>;
};

template <typename T>
requires StreamInsertable<T, std::ostream>
std::string formatToString(const T & arg) {
    std::ostringstream s;
    s << arg;
    return s.str();
}

template <>
std::string formatToString(const std::string & s) {
    return s;
}

template <typename... Args>
std::string format(const std::string & format_string, Args... args) {

    std::vector<std::string> arguments = {formatToString(args)...};

    std::ostringstream result;

    for (int i = 0; i < format_string.size(); ++i) {

        if (format_string[i] == '{') {

            int j = i + 1;

            if (j >= format_string.size()) {
                throw UnmatchedBraceError("Unmatched '{' at end of format string");
            }

            if (format_string[j] == '}') {
                throw ArgumentIndexError("Empty argument index at position " + std::to_string(i));
            }

            size_t arg_num = 0;

            while (j < format_string.size() && format_string[j] != '}') {
                
                if (format_string[j] >= '0' && format_string[j] <= '9') {

                    arg_num = arg_num * 10 + (format_string[j] - '0');
                    ++j;

                }
                else {

                    while (j < format_string.size()) {
                        if (format_string[j] == '{') {
                            throw UnmatchedBraceError("Unmatched '{' at position " + std::to_string(i));
                        }
                        ++j;
                    }

                    throw ArgumentIndexError("Invalid character inside braces at position " + std::to_string(j));
                        
                }
                
            }

            if (j >= format_string.size()) {
                throw UnmatchedBraceError("Unmatched '{' at position " + std::to_string(i));
            }

            if (arg_num >= arguments.size()) {
                throw ArgumentIndexError("Argument index " + std::to_string(arg_num) + 
                " out of range (max " + std::to_string(arguments.size() - 1) + 
                ") at position " + std::to_string(i));
            }
            
            result << arguments[arg_num];

            i = j;

        }
        else if (format_string[i] == '}') {
            throw UnmatchedBraceError("Unmatched '}' at position " + std::to_string(i));
        }
        else {
            result << format_string[i];
        }

    }

    return result.str();
}


