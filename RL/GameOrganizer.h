#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "Agent.h"
using namespace std;

class GameOrganizer {
private:
	double currentPrice;
	double* finalPrices;
	int gameCount;
	int currentWinner = -1;

public:	
	Agent agent1;
	Agent agent2;
	GameOrganizer() {
		currentPrice = 0;
		finalPrices = new double[10'000];
		gameCount = 0;
	};

	void reset() {
		gameCount = 0;
		currentPrice = 0;
		agent1.reset();
		agent2.reset();
	}
	double epoch(int type) {
		if (type == 1) {
			for (int i = 0; i < 10'000; i++) { setEnglish(); }
		}
		else {
			for (int i = 0; i < 10'000; i++) { setVickery(); }
		}
		
		double average = avg();
		agent1.learnedValue = average;
		agent2.learnedValue = average;
		return average;
	}
	double avg() {
		double total = 0;
		for (int i = 0; i < 10'000; i++){
			total += finalPrices[i];
		}
		return total / 10'000;
	}

	int game(int type) {
		currentPrice = 5;
		currentWinner = -1;
		double agent1_offer;
		double agent2_offer;
		while (true) {
			agent1_offer = agent1.makeBid(currentPrice);
			agent2_offer = agent2.makeBid(currentPrice);
			if ((agent1_offer != currentPrice) && (agent1_offer > agent2_offer)) {
				currentWinner = 1;
				currentPrice = agent1_offer;
			}
			else if ((agent2_offer != currentPrice) && (agent2_offer > agent1_offer)) {
				currentWinner = 2;
				currentPrice = agent2_offer;
			}
			else {
				break;
			}
		}	

		//type 1 is English, type 2 is Vickery
		if (type == 1) {
			return currentPrice;
		}
		else if (type == 2) {
			if (currentWinner == 1) {
				return agent2_offer;
			}
			else {
				return agent1_offer;
			}
		}

		return currentWinner;
	}

	void setEnglish() {
		int value = game(1);
		finalPrices[gameCount++] = value;
		if (currentWinner == 1) {
			agent1.rewardEvaluation(true, value);
			agent1.bid = 5;
			agent2.rewardEvaluation(false, value);
			agent2.bid = 5;
		}
		else {
			agent1.rewardEvaluation(false, value);
			agent1.bid = 5;
			agent2.rewardEvaluation(true, value);
			agent2.bid = 5;
		}
	}

	//note that this Vickrey auction is open, and that is why it differs from the expected
	void setVickery() {
		int value = game(2);
		finalPrices[gameCount++] = value;
		if (currentWinner == 1) {
			agent1.rewardEvaluation(true, value);
			agent1.bid = 5;
			agent2.rewardEvaluation(false, value);
			agent2.bid = 5;
		}
		else {
			agent1.rewardEvaluation(false, value);
			agent1.bid = 5;
			agent2.rewardEvaluation(true, value);
			agent2.bid = 5;
		}
	}

};