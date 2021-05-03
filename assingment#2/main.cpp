//
//  main.cpp
//  enumerators_asignment_2
//
//  Created by Andrei on 4/1/21.
//

#include <iostream>
#include <iostream>
#include <string>
#include "include/CaughtItemsEnumerator.h"
#include "include/NameAnglerEnumerator.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


// first task - Give the average number of caught catfishes. If no catfish is caught, the average is zero.
float averageNumberOfCaughtItem(const string& filename, const string& itemName) throw (CaughtItemsEnumerator::FileErrors)
{
    CaughtItemsEnumerator enor(filename, itemName);
    int sum = 0;
    int count = 0;

    for (enor.first(); !enor.end(); enor.next())
    {
        CaughtItem caught = enor.current();
        sum += caught.countOftems;
        count++;
    }

    return count == 0 ? 0.0f : ((float) sum / (float)count);
}


// second task - Name the angler who has caught the biggest number of catfishes
string biggerNumberOfItemsName(const string& filename, const string& itemName)
{
    NameAnglerEnumerator enor(filename, itemName);
    string name = "";
    int number = 0;

    for (enor.first(); !enor.end(); enor.next())
    {
        NameAngler caught = enor.current();
        if (caught.sumOfItems > number)
        {
            name = caught.name;
            number = caught.sumOfItems;
        }
    }

    return name;
}


#define NORMAL_MODE
#ifdef NORMAL_MODE2

int main(int argc, const char* argv[])
{
    cout << "Input a path to your file\n";
    string filename;
    cin >> filename;

    cout << "First subtask" << endl;
    try
    {
        string item = "catfish";
        const float average = averageNumberOfCaughtItem(filename, item);
        if (average == 0)
        {
            cout << "No average for catfishes. Not catfishes in file or file is empty\n";
        }
        else
        {
            cout << "Average of caught catfishes: " << average << endl;
        }


        const string name = biggerNumberOfItemsName(filename, item);
        if (name == "")
        {
            cout << "Could not get maximum. File is empty\n";
        }
        else
        {
            cout << "Name of the angler who who has biggest number of catfishes: " << name << endl;
        }
    }
    catch (CaughtItemsEnumerator::FileErrors e)
    {
        cout << "Can not find input file " << filename << " . Please double check your input\n";
    }

    return 0;
}

#else
#define CATCH_CONFIG_MAIN

#include "include/catch.hpp"

string ITEM_NAME = "catfish";

// summation and counting for the main averageNumberOfCaughtItem function
TEST_CASE("Enor’s end() => true", "t0.txt")
{
    float avg = averageNumberOfCaughtItem("t8.txt", ITEM_NAME);
    CHECK(avg == 0.0);
}

TEST_CASE("Enor does one iteration, after which it has end() => true", "t2.txt")
{
    float avg = averageNumberOfCaughtItem("t2.txt", ITEM_NAME);
    CHECK(avg == 2.0f);
}


TEST_CASE("Enor does more than one iteration, after which it has end() => true", "t4.txt")
{
    float avg = averageNumberOfCaughtItem("t4.txt", ITEM_NAME);
    CHECK(avg == 1.6f);
}

TEST_CASE("Last one only enor.current().countOfItems > 0", "t19.txt")
{
    float avg = averageNumberOfCaughtItem("t19.txt", ITEM_NAME);
    CHECK(avg == 0.4f);
}

TEST_CASE("First one only enor.current().countOfItems > 0", "t18.txt")
{
    float avg = averageNumberOfCaughtItem("t18.txt", ITEM_NAME);
    CHECK(avg == 0.4f);
}


TEST_CASE("All  enor.current().countOfItems are equal to 0", "t20.txt")
{
    float avg = averageNumberOfCaughtItem("t20.txt", ITEM_NAME);
    CHECK(avg == 0.0);
}

TEST_CASE("Only one countOfItems from Enor is not equal to 0", "t21.txt")
{
    float avg = averageNumberOfCaughtItem("t21.txt", ITEM_NAME);
    CHECK(avg == 0.4f);
}

TEST_CASE("More than one sum from Enor are not equal to 0", "t7.txt")
{
    float avg = averageNumberOfCaughtItem("t7.txt", ITEM_NAME);
    CHECK(avg == 2.2f);
}


// summation and counting for the CaughtItemsEnumerator
TEST_CASE("Line without catches", "t0.txt")
{
    CaughtItemsEnumerator enor("t0.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 0);
}

TEST_CASE("Line with one catfish", "t12.txt")
{
    CaughtItemsEnumerator enor("t12.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 1);
}

TEST_CASE("Line with more than one catfish", "t2.txt")
{
    CaughtItemsEnumerator enor("t2.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 2);
}

TEST_CASE("Line with haul, first one is catfish", "t12.txt")
{
    CaughtItemsEnumerator enor("t12.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 1);
}

TEST_CASE("Line with haul, last one is catfish", "t16.txt")
{
    CaughtItemsEnumerator enor("t16.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 1);
}

TEST_CASE("Line with haul, and without catfishes", "t20.txt")
{
    CaughtItemsEnumerator enor("t20.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 0);
}

TEST_CASE("Line with haul,Line with one catfish", "t17.txt")
{
    CaughtItemsEnumerator enor("t17.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 1);
}


TEST_CASE("Line with haul, and with one or more catfishes", "t9.txt")
{
    CaughtItemsEnumerator enor("t9.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().countOftems == 3);
}

// Summation in second part (NameAngleEnumerator)

TEST_CASE("Enor has no items to enumerate in", "t20.txt")
{
    NameAnglerEnumerator enor("t20.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 0);
}

TEST_CASE("Enor has one item to enumerate in", "t22.txt")
{
    NameAnglerEnumerator enor("t22.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 1);
}


TEST_CASE("Enor has more than one item to enumerate in", "t11.txt")
{
    NameAnglerEnumerator enor("t11.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 4);
}

TEST_CASE("All caught catfishes are found in first enum call", "t29.txt")
{
    NameAnglerEnumerator enor("t29.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 3);
}

TEST_CASE("All caught catfishes are found in last enum call", "t30.txt")
{
    NameAnglerEnumerator enor("t30.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 3);
}



TEST_CASE("All items are placed in one row", "t23.txt")
{
    NameAnglerEnumerator enor("t23.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 4);
}


TEST_CASE("All items are placed in several rows", "t25.txt")
{
    NameAnglerEnumerator enor("t25.txt", ITEM_NAME);
    enor.first();
    CHECK(enor.current().sumOfItems == 3);
}


// Maximum Search in second part (main program)


TEST_CASE("NameAngleEnumerator end() = true", "t1.txt")
{
    string name = biggerNumberOfItemsName("t1.txt", ITEM_NAME);
    CHECK(name == "");
}


TEST_CASE("NameAngleEnumerator will iterate over one item and then end() = true", "t26.txt")
{
    string name = biggerNumberOfItemsName("t26.txt", ITEM_NAME);
    CHECK(name == "Peter");
}

TEST_CASE("NameAngleEnumerator will iterate over more than one item and then end() = true", "t6.txt")
{
    string name = biggerNumberOfItemsName("t6.txt", ITEM_NAME);
    CHECK(name == "Peter");
}

TEST_CASE("Maximum value of current().sum will be in a first call to NameAngleEnumerator ", "t7.txt")
{
    string name = biggerNumberOfItemsName("t7.txt", ITEM_NAME);
    CHECK(name == "Peter");
}

TEST_CASE("Maximum value of current().sum will be in a last call to NameAngleEnumerator ", "t27.txt")
{
    string name = biggerNumberOfItemsName("t27.txt", ITEM_NAME);
    CHECK(name == "John");
}

TEST_CASE("Maximum value = 0 for all items in enumeration", "t28.txt")
{
    string name = biggerNumberOfItemsName("t28.txt", ITEM_NAME);
    CHECK(name == "");
}


TEST_CASE("Maximum value will have only one item in enumeration", "t11.txt")
{
    string name = biggerNumberOfItemsName("t11.txt", ITEM_NAME);
    CHECK(name == "Bob");
}

TEST_CASE("Maximum value will have more than one item in enumeration", "t5.txt")
{
    string name = biggerNumberOfItemsName("t5.txt", ITEM_NAME);
    CHECK(name == "Peter");
}


#endif

