#include <iostream>
#include <vector>
#include "petkeeper.h"



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

#endif
