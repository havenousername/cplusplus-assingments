#include <iostream>
#include "Pet.h"

using namespace std;

int main()
{
    BoundedValue<int, 0, 100> inner(1);
    BoundedValue<int, 0, 60> outer(5);
    cout << inner;
    return 0;
}
