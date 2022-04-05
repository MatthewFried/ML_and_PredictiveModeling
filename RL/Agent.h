#pragma once
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Agent {
private:
	double personalValue;
	double* reward;
	int gamesPlayed;
	int counter = 1;
	

public:
	double bid;
	double learnedValue = 100;
	
	Agent() {
		this->bid = 5;
		this->personalValue = 85;
		gamesPlayed = 10'000;
		reward = new double[gamesPlayed + 1];
		reward[0] = 0;
		for (int i = 1; i <= gamesPlayed; i++) { reward[i] = 0; }
	}

	void reset() {
		this->bid = 5;
		this->personalValue = 85;
		this->counter = 1;
	}

	double makeBid(double currentPrice) {
		//if previous rolling reward is less than zero, then be more aggresive
		//if currentPrice is far from bid, then be more aggressive
		if (reward[counter - 1] <= 0) {
			double holder = bid;
			if ((personalValue - bid) > 0) {
				if (((currentPrice - bid) / bid) > .15) { bid *= 1.15; }
				else bid *= (1.03 + (rand() % 100) / 1000.0);
			}
			//learn from previous aggessive bidding by keeping it lower than learned value
			if (bid > learnedValue) {
				bid *= .95;
				if (bid > currentPrice) return bid;
				else return holder;
			}
			return bid;
		}
		else {
			double holder = bid;
			if ((personalValue - bid) > 0) {
				if (((currentPrice - bid) / bid) > .15) { bid *= 1.10; }
				else bid *= (1.03 + (rand() % 100) / 1000.0);
			}
			//learn from previous aggessive bidding by keeping it lower than learned value
			if (bid > learnedValue) {
				bid *= .95;
				if (bid > currentPrice) return bid;
				else return holder;
			}
			return bid;
		}
	}

	void rewardEvaluation(bool won, double finalPrice) {
		bid = 0;
		reward[counter++] = reward[counter-1]*.3 + (personalValue-finalPrice + (won ? 2 : -5))*.7;
	}

};