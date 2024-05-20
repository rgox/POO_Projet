#ifndef TEST_HPP
#define TEST_HPP

#include <boost/test/unit_test.hpp>

// Déclaration de la suite de tests
class TestSuite {
public:
    TestSuite();
    ~TestSuite();
    void runTests();
};

#endif // TEST_HPP
