#include <iostream>
#include <string>
#include <time.h>
#include "Agent.h"
#include "GameOrganizer.h"
#include "Learning.h"
using namespace std;

int main()
{
	srand(time(nullptr));
	Learning learning;
	learning.runEpochs();
}
