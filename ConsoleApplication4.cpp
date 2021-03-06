#include <iostream>
#include <fstream>
#include <random>
using namespace std;

void fiveDaySetup(double* fiveDay, double* data, int length);
void tenDaySetup(double* tenDay, double* data, int length);
void twentyDaySetup(double* twentyDay, double* data, int length);
void runsFiveDay(double* fiveDay, double* data, double* r_fiveDay, double length);
void runsTenDay(double* tenDay, double* data, double* r_tenDay, double length);
void runsTwentyDay(double* twentyDay, double* data, double* r_twentyDay, double length);

int main()
{
	std::default_random_engine generator;
	normal_distribution<double> distribution(0.0,1.0);

	int length = 10'000;
	double* data = new double[length];
	double mu = .3;
	double sigma = .4;
	double days = length;

	data[0] = 100;
	for (int i = 1; i < length; i++)
	{
		data[i] = data[i - 1] * exp((mu - .5 * sigma * sigma) * (1 / days) + sigma * (sqrt(1 / days)) * distribution(generator));
	}
	
	//simple moving average
	double* fiveDay = new double[length];
	double* tenDay = new double[length];
	double* twentyDay = new double[length];

	//get sma
	fiveDaySetup(fiveDay, data, length);
	tenDaySetup(tenDay, data, length);
	twentyDaySetup(twentyDay, data, length);

	//array for runs 
	double* r_fiveDay = new double[length];
	double* r_tenDay = new double[length];
	double* r_twentyDay = new double[length];

	//get runs
	runsFiveDay(fiveDay, data, r_fiveDay,length);
	runsTenDay(tenDay, data, r_tenDay, length);
	runsTwentyDay(twentyDay, data, r_twentyDay, length);

	//set up for rewards
	int* rewards = new int[length-120];
	rewards[0] = 0;
	for (int i = 20; i < length - 100; i++) {
		double myTotal = abs(r_fiveDay[i]) + abs(r_tenDay[i]) + abs(r_twentyDay[i]);
		double five = r_fiveDay[i] / myTotal;
		double ten = r_tenDay[i] / myTotal;
		double twenty = r_twentyDay[i] / myTotal;
		double choice = five + ten + twenty;
		if (choice > 0) {
			if (data[i + 1] > data[i]) {
				rewards[i - 19] = rewards[i - 20] + 1;
			}
			else {
				rewards[i - 19] = rewards[i - 20] - 1;
			}
		}
		else {
			if (data[i + 1] < data[i]) {
				rewards[i - 19] = rewards[i - 20] + 1;
			}
			else {
				rewards[i - 19] = rewards[i - 20] - 1;
			}
		}
	}
		
	for (int i = 0; i < 1000; i++)
	{
		cout << data[i+20] << "\t" << rewards[i] << endl;
	}
}

void fiveDaySetup(double* fiveDay, double* data, int length) {
	for (int i = 4; i < (length); i++)
	{
		fiveDay[i - 4] = (data[i - 0] + data[i - 1] + data[i - 2] + data[i - 3] + data[i - 4]) / 5.0;
	}
}
void tenDaySetup(double* tenDay, double* data, int length) {
	for (int i = 9; i < (length); i++)
	{
		double val = 0;
		for (int j = 0; j < 10; j++){
			val += data[i - j];
		}
		val /= 10;
		tenDay[i - 9] = val;
	}
}
void twentyDaySetup(double* twentyDay, double* data, int length) {
	for (int i = 19; i < (length); i++)
	{
		double val = 0;
		for (int j = 0; j < 19; j++) {
			val += data[i - j];
		}
		val /= 10;
		twentyDay[i - 19] = val;
	}
}
void runsFiveDay(double* fiveDay, double* data, double* r_fiveDay, double length) {
	double* interim = new double[length];
	for (int i = 4; i < length; i++){
		if ((data[i] - fiveDay[i - 4]) > 0) {
			interim[i - 4] = 1;
		}
		else interim[i - 4] = -1;
	}
	int counter = 0;
	for (int i = 0; i < length-4; i++){
		if (interim[i] == 1) {
			int mid = ++counter;
			r_fiveDay[i] = mid;
			if (interim[i + 1] == 0) {
				counter = 0;
			}
		}
		else { 
			int mid = ++counter;
			r_fiveDay[i] = -mid; 
			if (interim[i + 1] == 1) {
				counter = 0;
			}
		}
	}
}
void runsTenDay(double* tenDay, double* data, double* r_tenDay, double length) {
	double* interim = new double[length];
	for (int i = 9; i < length; i++) {
		if ((data[i] - tenDay[i - 9]) > 0) {
			interim[i - 9] = 1;
		}
		else interim[i - 9] = -1;
	}
	int counter = 0;
	for (int i = 0; i < length - 9; i++) {
		if (interim[i] == 1) {
			int mid = ++counter;
			r_tenDay[i] = mid;
			if (interim[i + 1] == 0) {
				counter = 0;
			}
		}
		else {
			int mid = ++counter;
			r_tenDay[i] = -mid;
			if (interim[i + 1] == 1) {
				counter = 0;
			}
		}
	}
}
void runsTwentyDay(double* twentyDay, double* data, double* r_twentyDay, double length) {
	double* interim = new double[length];
	for (int i = 19; i < length; i++) {
		if ((data[i] - twentyDay[i - 19]) > 0) {
			interim[i - 19] = 1;
		}
		else interim[i - 19] = -1;
	}
	int counter = 0;
	for (int i = 0; i < length - 19; i++) {
		if (interim[i] == 1) {
			int mid = ++counter;
			r_twentyDay[i] = mid;
			if (interim[i + 1] == 0) {
				counter = 0;
			}
		}
		else {
			int mid = ++counter;
			r_twentyDay[i] = -mid;
			if (interim[i + 1] == 1) {
				counter = 0;
			}
		}
	}
}