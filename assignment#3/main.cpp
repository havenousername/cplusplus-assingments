#include <iostream>
#include <vector>
#include "petkeeper.h"



using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    PetKeeper* petKeeper = new PetKeeper("test01.txt", "Cathy");
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
