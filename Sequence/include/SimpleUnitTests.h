#ifndef SIMPLE_UNIT_TESTS_H
#define SIMPLE_UNIT_TESTS_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace UnitTest {
    struct TestCase {
        std::string name;
        std::function<void()> testFunc;
        bool passed = false;
        std::string errorMsg;
    };

    static std::vector<TestCase> testCases;

#define TEST_CASE(test_name) \
    static void test_name(); \
    static const bool test_name##_registered = []() { \
        UnitTest::testCases.push_back({ #test_name, test_name }); \
        return true; \
    }(); \
    static void test_name()

#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            throw std::runtime_error("Assertion failed: " #cond " (" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + ")"); \
        } \
    } while (0)

    inline int RunTests() {
        int passed = 0;
        int failed = 0;
        std::cout << "Running " << testCases.size() << " tests...\n";
        for (auto& test : testCases) {
            try {
                test.testFunc();
                test.passed = true;
                passed++;
                std::cout << "[PASS] " << test.name << "\n";
            }
            catch (const std::exception& e) {
                test.passed = false;
                test.errorMsg = e.what();
                failed++;
                std::cout << "[FAIL] " << test.name << " -> " << e.what() << "\n";
            }
        }
        std::cout << "\nResults: " << passed << " passed, " << failed << " failed.\n";
        return failed == 0 ? 0 : 1;
    }
}
#endif // SIMPLE_UNIT_TESTS_H