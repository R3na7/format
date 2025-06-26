#include "format.hpp"
#include <cassert>

void runTests() {

    {
        auto text = format("{1}+{1} = {0}", 2, "one");
        assert(text == "one+one = 2");
    }

    {
        auto text = format("{0} {0} {0}", "repeat");
        assert(text == "repeat repeat repeat");
    }

    {
        auto text = format("Name: {0}, Age: {1}, GPA: {2}", "John", 25, 3.75);
        assert(text == "Name: John, Age: 25, GPA: 3.75");
    }

    {
        auto text = format("{2}, {0}, {1}", "first", "second", "third");
        assert(text == "third, first, second");
    }

    {
        auto text = format("{0}", 123);
        assert(text == "123");
    }

    {
        try {
            auto text = format("{}", 42);
            assert(false && "Expected ArgumentIndexError");
        } catch (const ArgumentIndexError & e) {
            std::cout << "Caught expected ArgumentIndexError: " << e.what() << std::endl;
        }
    }

    {
        try {
            auto text = format("{1}", "only one arg");
            assert(false && "Expected ArgumentIndexError");
        } catch (const ArgumentIndexError & e) {
            std::cout << "Caught expected ArgumentIndexError: " << e.what() << std::endl;
        }
    }

    {
        try {
            auto text = format("Text with extra }} brace", 1);
            assert(false && "Expected UnmatchedBraceError");
        } catch (const UnmatchedBraceError & e) {
            std::cout << "Caught expected UnmatchedBraceError: " << e.what() << std::endl;
        }
    }

    {
        try {
            auto text = format("This is wrong: {0 {1}", "arg1", "arg2");
            assert(false && "Expected UnmatchedBraceError");
        } catch (const UnmatchedBraceError & e) {
            std::cout << "Caught expected UnmatchedBraceError: " << e.what() << std::endl;
        }
    }

    {
        try {
            auto text = format("{a}", 1);
            assert(false && "Expected ArgumentIndexError");
        } catch (const ArgumentIndexError & e) {
            std::cout << "Caught expected ArgumentIndexError: " << e.what() << std::endl;
        }
    }

    std::cout << "All tests passed!\n";
}

int main() {
    runTests();
    return 0;
}

