#include <iostream>
#include "Session.h"

using namespace std;

int main(int argc, char** argv){
    Session testSession("../config1.json");
    testSession.simulate();
    return 0;
}

