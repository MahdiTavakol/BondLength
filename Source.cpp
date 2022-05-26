/*
* =============================================================================
*
* This program calculates the bond length from the xyz file for a GO system
*
* =============================================================================
*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <random>
using namespace std;


float distance(float, float, float, float, float, float);
void threeSmallest(float[], float &, float &, float &, int num);
void twoSmallest(float[], float &, float &, int num);

int main()
{
	std::string dummy;
	std::string atomCountString;
	ifstream input("test3.xyz", ios::in);
	ofstream output("BondLength.txt", ios::out);
	if (input.is_open())
	{
		std::getline(input, atomCountString);
		std::getline(input, dummy);
	}
	else
	{
		cout << "there is no Input file";
		return -1;
	}

	int atomCount;
	stringstream(atomCountString) >> atomCount;
	float cutoff = 3.0f;

	int* ID    = new   int[atomCount];
	int* type  = new   int[atomCount];
	float* x   = new float[atomCount];
	float* y   = new float[atomCount];
	float* z   = new float[atomCount];
	std::string line;

	cout << "Welcome to Bond Length Calculator for GO Written by:" << endl;
	cout << "Mahdi Tavakol" << endl << endl << endl;
	cout << "READING INPUT FILE ... " << endl;
	for (int i = 0; i < atomCount; i++)
	{
		std::getline(input, line);
		std::string atomTypeChar;
		std::istringstream iss(line);
		iss >> x[i];
		iss >> y[i];
		iss >> z[i];
		iss >> atomTypeChar;
		iss >> ID[i];
		// atomID = i + 1;
		if (atomTypeChar == "O")
			type[i] = 2;
		else if (atomTypeChar == "C")
			type[i] = 1;
		else
			cout << "What the hell" << endl << "I,m lost in the loop of infinity!!!" << endl;
	}

	cout << "READING THE INPUT FILE IS COMPLETED" << endl << endl;
	cout << "CALCULATING BOND LENGTH... " << endl;

	input.close();

	const int maxNeighborCount = 100;
	for (int i = atomCount; i < atomCount; i++)
	{
		int currentNeighborCount = 0;
		float distances[maxNeighborCount];
		for (int k = 0; k < maxNeighborCount; k++)
			distances[k] = 10000;
		for (int j = i + 1; j < atomCount; j++)
		{
			if ( type[j] == 2)
				continue;
			float distanceValue = distance(x[i], y[i], z[i], x[j], y[j], z[j]);
			// if (distanceValue > CCBondLengthMin && distanceValue < CCBondLengthMax)
			if (distanceValue < cutoff)
			{
				distances[currentNeighborCount] = distanceValue;
				currentNeighborCount++;
			}
			if (currentNeighborCount >= maxNeighborCount)
				break;
			cout << "( " << i << "," << j << ")" << currentNeighborCount << endl;
		}
		float min1, min2, min3;
		threeSmallest(distances, min1, min2, min3, currentNeighborCount); // currentNeighborCount);
		output << min1 << endl;
		output << min2 << endl;
		output << min3 << endl;
	}

	for (int i = 0; i < atomCount; i++)
	{
		int   currentNeighborCount = 0;
		float distances[maxNeighborCount];
		for (int k = 0; k < maxNeighborCount; k++)
			distances[k] = 10000;
		if (type[i] == 1)
			continue;
		for (int j = 0; j < atomCount; j++)
		{
			float distanceValue = distance(x[i], y[i], z[i], x[j], y[j], z[j]);
			if (distanceValue < cutoff)
			{
				distances[currentNeighborCount] = distanceValue;
				currentNeighborCount++;
			}
			if (currentNeighborCount >= maxNeighborCount)
				break;
			cout << "( " << i << "," << j << ")" << currentNeighborCount << endl;
		}
		float min1, min2;
		twoSmallest(distances, min1, min2, currentNeighborCount); // currentNeighborCount);
		output << min1 << endl;
		output << min2 << endl;


	}


	cout << "ALL DONE, BACK TO YOU OS" << endl << endl << endl;

	system("PAUSE");
	return 0;
	//*********************************************************************//
	//*********************************************************************//
	//*********************************************************************//
	//*********************************************************************//
	//*********************************************************************//
}



float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dis = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
	return dis;
}

void threeSmallest(float numbers[], float& min1, float& min2, float& min3, int num)
{
	min1 = numbers[0];
	min2 = numbers[1];
	min3 = numbers[2];

	if (min1 > min2)
	{
		float temp;
		temp = min1;
		min1 = min2;
		min2 = temp;
	}
	if (min2 > min3)
	{
		float temp;
		temp = min2;
		min2 = min3;
		min3 = temp;
	}
	if (min1 > min3)
	{
		float temp;
		temp = min1;
		min1 = min3;
		min3 = temp;
	}

	for (int i = 3; i < num; i++)
	{
		if (numbers[i] < min1)
		{
			min3 = min2;
			min2 = min1;
			min1 = numbers[i];
		}
		else if (numbers[i] < min2)
		{
			min3 = min2;
			min2 = numbers[i];
		}
		else if (numbers[i] < min3)
		{
			min3 = numbers[i];
		}
	}


}


void twoSmallest(float numbers[], float& min1, float& min2, int num)
{
	min1 = numbers[0];
	min2 = numbers[1];

	if (min1 > min2)
	{
		float temp;
		temp = min1;
		min1 = min2;
		min2 = temp;
	}


	for (int i = 3; i < num; i++)
	{
		if (numbers[i] < min1)
		{
			min2 = min1;
			min1 = numbers[i];
		}
		else if (numbers[i] < min2)
		{
			min2 = numbers[i];
		}

	}


}

