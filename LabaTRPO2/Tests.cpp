#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Deque.h"

using namespace fefu_laboratory_two;

TEST_CASE("Test1") {
    Deque<int> a;
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    REQUIRE(a.back() == 2);
}

TEST_CASE("Test2") {
    Deque<int> a;
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    Deque<int> b(a);
    REQUIRE(a.size() == 3);
}

TEST_CASE("Test3") {
    Deque<int> a;
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    Deque<int> b(a);
    REQUIRE(a.front() == 4);
}