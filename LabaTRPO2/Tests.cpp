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

TEST_CASE("Test4")
{
    Deque<int> a{ 1,3,4,5,6 };
    REQUIRE(a.size() == 5);
}

TEST_CASE("Test5")
{
    Deque<int> a{ 1,3,4,5,6 };

    REQUIRE(a.front() == 1);
}

TEST_CASE("Test6")
{
    Deque<int> a{ 1,3,4,5,6 };

    REQUIRE(a.back() == 6);
}

TEST_CASE("Test7")
{
    Deque<int> a{ 1,3,4,5,6 };
    a.pop_front();

    REQUIRE(a.front() == 3);
}

TEST_CASE("Test8")
{
    Deque<int> a{ 1,3,4,5,6 };
    a.pop_back();

    REQUIRE(a.front() == 1);
}

TEST_CASE("Test9")
{
    Deque<int> a{ 1,3,4,5,6 };
    a.clear();

    REQUIRE(a.size() == 0);
}

TEST_CASE("Test10")
{
    Deque<int> a{ 1,3,4,5,6 };
    Deque<int> b = a;

    REQUIRE(b.size() == 5);
}

TEST_CASE("Test11")
{
    Deque<int> a(6);

    REQUIRE(a.size() == 6);
}

TEST_CASE("Test12")
{
    Deque<int> a(6, 5);

    REQUIRE(a.front() == 5);
}

TEST_CASE("Test13")
{
    Deque<int> a{ 1,3,4,5,6 };

    REQUIRE(a.at(3) == 4);
}

TEST_CASE("Test14")
{
    Deque<int> a{ 1,3,4,5,6 };

    REQUIRE(a.at(1) == *(a.begin()));
}

TEST_CASE("Test15")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    auto it2 = a.begin() + 4;


    REQUIRE(*it2 == 6);
}

TEST_CASE("Test16")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    auto it2 = a.begin() + 4;


    REQUIRE(it1 < it2);
}

TEST_CASE("Test17")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    auto it2 = a.begin() + 4;


    REQUIRE(it1 != it2);
}

TEST_CASE("Test18")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    auto it2 = a.begin() + 4;


    REQUIRE(it1 != it2);
}

TEST_CASE("Test19")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin() + 4;
    auto it2 = a.begin() + 4;


    REQUIRE(it1 == it2);
}

TEST_CASE("Test20")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    auto it2 = a.begin() + 4;


    REQUIRE(it2 > it1);
}

TEST_CASE("Test21")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.rbegin();


    REQUIRE(*it1 == 6);
}

TEST_CASE("Test22")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    (*it1)++;


    REQUIRE(*it1 == 2);
}

TEST_CASE("Test23")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    (*it1)++;


    REQUIRE(a.front() == 2);
}

TEST_CASE("Test24")
{
    Deque<int> a{ 1,3,4,5,6 };
    a.clear();

    REQUIRE(a.empty());
}

TEST_CASE("Test25")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    auto it2 = a.begin() + 3;
    swap(it1, it2);

    REQUIRE(it2 == a.begin());
}

TEST_CASE("Test26")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    it1++;

    REQUIRE(*it1 == 3);
}

TEST_CASE("Test27")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin();
    ++it1;

    REQUIRE(*it1 == 3);
}

TEST_CASE("Test28")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin() + 3;
    it1--;

    REQUIRE(*it1 == 4);
}

TEST_CASE("Test29")
{
    Deque<int> a{ 1,3,4,5,6 };
    auto it1 = a.begin() + 3;
    --it1;

    REQUIRE(*it1 == 4);
}