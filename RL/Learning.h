#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "Agent.h"
#include "GameOrganizer.h"
using namespace std;

class Learning {
private:
	double* epoch;


public:
	GameOrganizer gameOrganizer;

	Learning() {
		epoch = new double[100];
		for (int i = 0; i < 100; i++){ epoch[i] = 0;}
	}

	void runEpochs() {
		for (int i = 0; i < 10; i++)
		{
			epoch[i] = gameOrganizer.epoch(2);
			cout << epoch[i] << endl;
			gameOrganizer.reset();
		}

	}
};