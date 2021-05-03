#include <iostream>
#include "menu.h"

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
   Menu menu;
   menu.run();
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bag.h"
#include <utility>

TEST_CASE("[]", "[Bag]")
{
    Bag b;
    b.insert_entry(1);
    std::pair<int, int> p1 = { 1,1 };
    CHECK(b[0] == p1);

    b.insert_entry(2);
    std::pair<int, int> p2 = { 2,1 };
    CHECK(b[1] == p2);


    try
    {
        b[2].first;
    }
    catch (Bag::BagErrors e)
    {
        CHECK(e == Bag::OVERFLOW_ERROR);
    }
}

TEST_CASE("==", "[Bag]")
{
    Bag b;
    b.insert_entry(12);
    Bag c;
    c.insert_entry(12);

    CHECK(((b[0].first == c[0].first && c[0].second == b[0].second) == (b[0] == c[0])));

    c.insert_entry(14);
    CHECK_FALSE(b[0] == c[1]);

    b.insert_entry(14);
    CHECK(b[1] == c[1]);
}

TEST_CASE("insert_entry", "[Bag]")
{
    // enumerator based


    SECTION("empty_entry")
    {
        Bag b;
        b.insert_entry(2);
        CHECK((b[0].first == 2 && b[0].second == 1));

        b.insert_entry(10);
        CHECK((b[1].first == 10 && b[1].second == 1));
    }

    SECTION("multiple_entry")
    {
        Bag b;
        b.insert_entry(2);
        b.insert_entry(3);
        b.insert_entry(4);
        CHECK((b[2].first == 4 && b[2].second == 1));
    }

    SECTION("check bag property")
    {
        // check if duplicate insertion works correctly for one element
        Bag b;
        b.insert_entry(2);
        b.insert_entry(2);
        CHECK((b[0].first == 2 && b[0].second == 2));

        // check if duplicate insertion works if we have both unique and non-unique elements
        Bag c;
        c.insert_entry(12);
        c.insert_entry(12);
        c.insert_entry(11);
        CHECK((c[0].first == 12 && c[0].second == 2));
        CHECK((c[1].first == 11 && c[1].second == 1));

        // check if multiple duplicate works
        Bag d;
        d.insert_entry(44);
        d.insert_entry(44);
        d.insert_entry(44);
        d.insert_entry(22);


        std::pair<int, int > n = { 44,3 };
        std::pair<int, int> l = {22, 1};
        CHECK(d[0] == n);
        CHECK(d[1] == l);

    }

    SECTION("check last elem")
    {
        Bag b;
        b.insert_entry(18);
        b.insert_entry(18);
        b.insert_entry(9);

        std::pair<int, int > n1 = { 9,1 };
        CHECK(b[1] == n1);

        Bag c;
        c.insert_entry(18);
        c.insert_entry(18);
        c.insert_entry(9);
        c.insert_entry(9);
        std::pair<int, int > n2 = { 9,2 };
        CHECK(c[1] == n2);
    }

    SECTION("check first elem")
    {
        Bag c;
        c.insert_entry(18);
        c.insert_entry(9);
        c.insert_entry(9);
        c.insert_entry(18);
        std::pair<int, int > n2 = { 18,2 };
        CHECK(c[0] == n2);

    }

    SECTION("check middle elem")
    {
        Bag c;
        c.insert_entry(18);
        c.insert_entry(9);
        c.insert_entry(19);
        c.insert_entry(21);
        c.insert_entry(19);
        std::pair<int, int > n2 = { 19,2 };
        CHECK(c[2] == n2);
    }
}

TEST_CASE("remove entry", "[Bag]")
{
    SECTION("empty remove")
    {
        Bag b;
        try
        {
            b.remove_entry();
        }
        catch (Bag::BagErrors e)
        {
            CHECK(e == Bag::UNDERFLOW_ERROR);
        }

        try
        {
            b.remove_entry(12);
        }
        catch (Bag::BagErrors e)
        {
            CHECK(e == Bag::UNDERFLOW_ERROR);
        }

    }

    SECTION("remove one element")
    {
        // simple remove
        Bag b;
        b.insert_entry(18);
        b.remove_entry(18);
        CHECK(b.size() == 0);

        b.insert_entry(18);
        b.remove_entry();
        CHECK(b.size() == 0);

        // remove duplicated
        b.insert_entry(9);
        b.insert_entry(9);
        b.remove_entry(9);
        std::pair<int, int > n = { 9, 1 };
        CHECK(b[0] == n);

        // remove unexisting
        b.insert_entry(900);
        try
        {
            b.remove_entry(901);
        }
        catch (Bag::BagErrors e)
        {
            CHECK(e == Bag::FOUND_ITEM_ERROR);
        }

    }

    SECTION("remove one last elem")
    {
        Bag b;
        b.insert_entry(18);
        b.insert_entry(18);
        b.insert_entry(9);
        b.remove_entry(9);

        CHECK(b.size() == 1);

        Bag c;
        c.insert_entry(18);
        c.insert_entry(18);
        c.insert_entry(9);
        c.insert_entry(9);
        c.remove_entry(9);
        c.remove_entry(9);
        CHECK(b.size() == 1);

        Bag d;
        d.insert_entry(18);
        d.insert_entry(18);
        d.insert_entry(9);
        d.insert_entry(9);
        d.remove_entry();
        d.remove_entry();
        CHECK(b.size() == 1);

    }

    SECTION("remove first elem")
    {
        Bag b;
        b.insert_entry(18);
        b.insert_entry(18);
        b.insert_entry(9);
        b.remove_entry(18);

        CHECK(b.size() == 2);

        Bag c;
        c.insert_entry(18);
        c.insert_entry(18);
        c.insert_entry(9);
        c.insert_entry(9);
        c.remove_entry(18);
        c.remove_entry(18);
        CHECK(c.size() == 1);

    }

    SECTION("check middle elem")
    {
        Bag c;
        c.insert_entry(18);
        c.insert_entry(9);
        c.insert_entry(19);
        c.insert_entry(21);
        c.insert_entry(19);
        c.remove_entry(9);
        CHECK(c.size() == 3);
    }
}


TEST_CASE("get frequency of item", "[Bag]")
{
    Bag b;
    // item not found in empty
    try
    {
        b.frequency_of_element(12);
    }
    catch (Bag::BagErrors e)
    {
        CHECK(e == Bag::FOUND_ITEM_ERROR);
    }

    b.insert_entry(12);

    // frequency = 1, one elem
    CHECK(b.frequency_of_element(12) == 1);

    // frequency = 1, two elem
    b.insert_entry(13);
    CHECK(b.frequency_of_element(12) == 1);

    // frequncy = 1, three elem
    b.insert_entry(11);
    b.insert_entry(2);
    CHECK(b.frequency_of_element(11) == 1);

    // not found item in non-empty bag
    try
    {
        b.frequency_of_element(999);
    }
    catch (Bag::BagErrors e)
    {
        CHECK(e == Bag::FOUND_ITEM_ERROR);
    }

    // item is first or last
    CHECK(b.frequency_of_element(12) == 1);
    CHECK(b.frequency_of_element(2) == 1);

    // result: frequency > 2
    b.insert_entry(12);
    b.insert_entry(12);
    CHECK(b.frequency_of_element(12) == 3);
}

TEST_CASE("number of unique elements", "[Bag]")
{

    SECTION("empty bag")
    {
        Bag b;
        CHECK(b.get_unique_element_count() == 0);
    }

    SECTION("insert affects")
    {
        Bag b;
        b.insert_entry(1);
        b.insert_entry(1);
        b.insert_entry(2);

        CHECK(b.get_unique_element_count() == 1);

        b.insert_entry(2);
        CHECK(b.get_unique_element_count() == 0);

        b.insert_entry(4);
        b.insert_entry(5);
        CHECK(b.get_unique_element_count() == 2);
    }

    SECTION("counting beginning and one el")
    {
        Bag b;
        b.insert_entry(1);
        b.insert_entry(3);
        b.insert_entry(3);
        b.insert_entry(4);
        b.insert_entry(4);

        CHECK(b.get_unique_element_count() == 1);
    }

    SECTION("counting end and one el")
    {
        Bag b;
        b.insert_entry(3);
        b.insert_entry(3);
        b.insert_entry(4);
        b.insert_entry(4);
        b.insert_entry(1);

        CHECK(b.get_unique_element_count() == 1);
    }

    SECTION("no unique")
    {
        Bag b;
        b.insert_entry(3);
        b.insert_entry(3);
        b.insert_entry(4);
        b.insert_entry(4);
        b.insert_entry(1);
        b.insert_entry(1);

        CHECK(b.get_unique_element_count() == 0);
    }


    SECTION("unique only")
    {
        Bag b;
        b.insert_entry(3);
        b.insert_entry(5);
        b.insert_entry(4);
        b.insert_entry(7);
        b.insert_entry(2);
        b.insert_entry(1);

        CHECK(b.get_unique_element_count() == b.size());
    }

    SECTION("unique and not unique")
    {
        Bag b;
        b.insert_entry(3);
        b.insert_entry(3);
        b.insert_entry(4);
        b.insert_entry(7);
        b.insert_entry(2);
        b.insert_entry(1);

        CHECK(b.get_unique_element_count() == 4);
    }

    SECTION("insert and remove affects")
    {
        Bag b;
        b.insert_entry(1);
        b.remove_entry(1);
        CHECK(b.get_unique_element_count() == 0);
        b.insert_entry(1);
        CHECK(b.get_unique_element_count() == 1);
        b.insert_entry(1);
        CHECK(b.get_unique_element_count() == 0);
        b.insert_entry(2);
        b.insert_entry(3);
        b.insert_entry(4);

        CHECK(b.get_unique_element_count() == 3);

        b.remove_entry();
        CHECK(b.get_unique_element_count() == 2);
        b.insert_entry(3);
        b.remove_entry();
        CHECK(b.get_unique_element_count() == 2);

        b.remove_entry();
        b.remove_entry();
        CHECK(b.get_unique_element_count() == 0);
    }

    SECTION("insert and remove multiple 2, 4, 1")
    {
        // base scenario -> 2, 4, 1 items
        Bag b;
        b.insert_entry(2);
        b.insert_entry(2);
        for(int i = 0; i < 4; i++)
        {
             b.insert_entry(4);
        }
        b.insert_entry(1);

        CHECK(b.get_unique_element_count() == 1);

        b.remove_entry(2);
        CHECK(b.get_unique_element_count() == 2);
        for(int i = 0; i < 3; i++)
        {
             b.remove_entry(4);
        }
        CHECK(b.get_unique_element_count() == 3);

        for(int i = 2; i >= 0; i--)
        {
            b.remove_entry();
            CHECK(b.get_unique_element_count() == i);
        }
    }

    SECTION("insert and remove multiple 4, 2, 1")
    {
        // base scenario -> 4, 2, 1 items
        Bag b;

        for(int i = 0; i < 3; i++)
        {
             b.insert_entry(4);
        }
        b.insert_entry(2);
        b.insert_entry(2);

        b.insert_entry(1);
        CHECK(b.get_unique_element_count() == 1);


        b.remove_entry(4);
        b.remove_entry(4);

        CHECK(b.get_unique_element_count() == 2);
        b.remove_entry(2);
        CHECK(b.get_unique_element_count() == 3);
        b.remove_entry(4);
        CHECK(b.get_unique_element_count() == 2);
        b.remove_entry(2);
        CHECK(b.get_unique_element_count() == 1);
        b.remove_entry(1);
        CHECK(b.get_unique_element_count() == 0);
    }

    SECTION("insert and remove multiple 1, 2, 4")
    {
        // base scenario -> 1, 2, 4 items
        Bag b;

        b.insert_entry(1);
        b.insert_entry(2);
        b.insert_entry(2);
        for(int i = 0; i < 3; i++)
        {
             b.insert_entry(4);
        }


        CHECK(b.get_unique_element_count() == 1);

        b.remove_entry(1);
        CHECK(b.get_unique_element_count() == 0);
        b.remove_entry(4);
        b.remove_entry(4);
        b.remove_entry(4);
        CHECK(b.get_unique_element_count() == 0);
        b.remove_entry(2);
        CHECK(b.get_unique_element_count() == 1);
        b.remove_entry(2);
        CHECK(b.get_unique_element_count() == 0);

    }

}

#endif


