#include <iostream>
#include <vector>
#include "./include/petkeeper.h"



using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    cout << "Please enter the name of the file for taking animals and days" << endl;
    std::string filename;
    cin >> filename;
    PetKeeper* petKeeper = new PetKeeper(filename);
    petKeeper->populate();
    petKeeper->daysSimulation();

    vector<string> stillAlive = petKeeper->getLowestExhalationAlive();

    for (int i = 0; i < stillAlive.size(); i++)
    {
        cout << stillAlive[i] << endl;
    }

    delete petKeeper;
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "./include/catch.hpp"
#include <vector>
#include "./include/petkeeper.h"


TEST_CASE("1", "length-based-no-days")
{
    // no  days and pets
    PetKeeper* petKeeper = new PetKeeper("test.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK((petKeeper->daysSize() == 0 && petKeeper->petsSize() == 0));
    CHECK((petKeeper->getLowestExhalationAlive().size() == 0));
    delete petKeeper;

    PetKeeper* pk = new PetKeeper("test00.txt");
    pk->populate();
    pk->daysSimulation();
    CHECK((pk->daysSize() == 0));
    CHECK((pk->getLowestExhalationAlive().size() == 1 && pk->getLowestExhalationAlive()[0] == "Lassie"));
    delete pk;
}

TEST_CASE("2", "length-based-one-day-only")
{
    // no  days and pets
    PetKeeper* petKeeper = new PetKeeper("test01.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK((petKeeper->daysSize() == 1));
    CHECK(petKeeper->getLowestExhalationAlive().size() == 1);
    delete petKeeper;
}

TEST_CASE("3", "length-based-more-days")
{
    // no  days and pets
    PetKeeper* petKeeper = new PetKeeper("test10.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK((petKeeper->daysSize() == 14));
    CHECK((petKeeper->getLowestExhalationAlive().size() == 1 && petKeeper->getLowestExhalationAlive()[0] == "Lassie"));
    delete petKeeper;
}


TEST_CASE("4", "same-day")
{
    // no  days and pets
    PetKeeper* petKeeper = new PetKeeper("test02.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK((petKeeper->getLowestExhalationAlive()[0] == "Nemo"));
    delete petKeeper;

    PetKeeper* pk = new PetKeeper("test02.1.txt");
    pk->populate();
    pk->daysSimulation();
    CHECK((pk->getLowestExhalationAlive().size() == 0));
    delete pk;

    PetKeeper* pk1 = new PetKeeper("test02.2.txt");
    pk1->populate();
    pk1->daysSimulation();
    CHECK(pk1->getLowestExhalationAlive().size() == 3);
    delete pk1;
}

TEST_CASE("5", "no-pets")
{
    PetKeeper* petKeeper = new PetKeeper("test03.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK(petKeeper->petsSize() == 0);
    CHECK(petKeeper->getLowestExhalationAlive().size() == 0);
    delete petKeeper;
}

TEST_CASE("6", "one-pet-only")
{
    PetKeeper* petKeeper = new PetKeeper("test04.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK(petKeeper->petsSize() == 1);
    CHECK(petKeeper->getLowestExhalationAlive().size() == 1);
    delete petKeeper;
}

TEST_CASE("7", "first-last-multiple")
{
    PetKeeper* petKeeper = new PetKeeper("test05.txt");
    petKeeper->populate();
    petKeeper->daysSimulation();
    CHECK(petKeeper->getLowestExhalationAlive().size() == 1);
    CHECK(petKeeper->getLowestExhalationAlive()[0] == "Lassie");
    delete petKeeper;


    PetKeeper* pk = new PetKeeper("test05.01.txt");
    pk->populate();
    pk->daysSimulation();
    CHECK(pk->getLowestExhalationAlive().size() == 1);
    CHECK(pk->getLowestExhalationAlive()[0] == "Lassie");
    delete pk;

    PetKeeper* pk1 = new PetKeeper("test05.02.txt");
    pk1->populate();
    pk1->daysSimulation();
    CHECK(pk1->getLowestExhalationAlive().size() == 2);
    CHECK(pk1->getLowestExhalationAlive()[0] == "Leva");
    CHECK(pk1->getLowestExhalationAlive()[1] == "Lassie");
    delete pk1;
}


TEST_CASE("8", "algorithm-based")
{
    PetKeeper* pk1 = new PetKeeper("test06.txt");
    pk1->populate();
    pk1->daysSimulation();
    CHECK(pk1->getLowestExhalationAlive().size() == 3);
}

#endif
