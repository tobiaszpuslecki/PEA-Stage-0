#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

ifstream in;
int opt=1;
string s = "gr17.tsp";

int numberOfCities;
int hamiltonCycleOptimal;

int** matrix;
bool* visited;

void printMatrix(int** matrix, int size)
{
	cout.width(4);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			cout << matrix[i][j] << " ";
			cout.width(4);
		}
		cout << endl;
	}
}

void printNotVisitedCities(bool* visited, int size)
{
	cout << "Not visited cities: ";
	for (size_t i = 0; i < size; i++) {
		if(not visited[i])
		{
			cout << i+1 << " ";
		}
	}
	cout << endl;
}

bool allVisited(bool* visited, int size)
{
	for (size_t i = 0; i < size; i++) {
		if(visited[i] == false)
		{
			return false;
		}
	}
	return true;
}

bool readFrom(string fileName)
{
	//in.open("C:\\instancje\\gr17.tsp");
	in.open(fileName);

	if (!in)
	{
		cout << "No such file" << endl;
		return false;
	}

	string filename;

	in >> filename;
	in >> numberOfCities;
	cout << "File: " << filename << endl;
	cout << "Number of cities: " << numberOfCities << endl;

	visited = new bool[numberOfCities];
	matrix = new int* [numberOfCities];


	for (int i = 0; i < numberOfCities; ++i)
		matrix[i] = new int[numberOfCities];


	for (size_t i = 0; i < numberOfCities; i++)
		for (size_t j = 0; j < numberOfCities; j++)
			in >> matrix[i][j];

	in >> hamiltonCycleOptimal;
	cout << "Optimal Hamilton cycle: " << hamiltonCycleOptimal << endl;

	//printMatrix(matrix, numberOfCities);

	in.close();

	return true;
}

void hamiltonManualOrder(int** matrix, int numberOfCities)
{
	int startCity=0;
	int enteredCity=0;
	int hamiltonCycle=0;

	while(startCity <= 0 || startCity > numberOfCities)
	{
		cout << "Enter start city: ";
		cin >> startCity;
		cout << endl;
		visited = new bool[numberOfCities];
		visited[startCity-1]=true;
	}

	while(!allVisited(visited, numberOfCities))
	{

		printNotVisitedCities(visited, numberOfCities);

		cout << "Enter number of city to visit (enter zero to end): " << endl;
		cin >> enteredCity;
		if(enteredCity<=0 || enteredCity>numberOfCities)
			break;



		if(visited[enteredCity-1])
		{
				cout << "City no. " << enteredCity << " was visited. Try again." << endl;
		}
		else
		{
			visited[enteredCity-1]=true;

			//cout << "sc: " << startCity-1 << " ec: " << enteredCity-1 << endl; // for debug
			hamiltonCycle+=matrix[startCity-1][enteredCity-1];
			startCity=enteredCity;
			cout << "hamiltonCycle: " << hamiltonCycle << endl;
		}

	}
	cout << endl << "Counted Hamilton cycle: " << hamiltonCycle << endl;
	cout << "Optimal Hamilton cycle: " << hamiltonCycleOptimal << endl;
	if(hamiltonCycle == hamiltonCycleOptimal)
	{
		cout << "The cycle is optimal" << endl;
	}
	else
	{
		cout << "The cycle is NOT optimal" << endl;
	}
}

void nearestNeighbour(int** matrix, int numberOfCities)
{
	cout << "Nearest neighbour." << endl;

	int startCity=0;

	while(startCity <= 0 || startCity > numberOfCities)
	{
		cout << "Enter start city: ";
		cin >> startCity;
		cout << endl;
		visited = new bool[numberOfCities];
		visited[startCity-1]=true;
	}

	int minPath=INT_MAX;
	int minCity=-1;
	int pathLen=0;

	int enteredCity=startCity-1;
	cout << startCity << "->";

	while (!allVisited(visited, numberOfCities))
	{
		for (size_t j = 0; j < numberOfCities; j++)
		{
			if (matrix[enteredCity][j]<minPath && matrix[enteredCity][j] != -1 && visited[j] != true)
			{
				minPath = matrix[enteredCity][j];
				minCity=j;
			}
		}

		cout << minCity+1 << "->";
		pathLen+=matrix[enteredCity][minCity];
		visited[minCity]=true;
		minPath=INT_MAX;
		enteredCity=minCity;
	}

	cout << " Final length: " << pathLen << endl;
}

int main()
{
	cout << "PEA - Stage 0." << endl;

	while(opt!=0)
	{
		cout << "1. Matrix print" << endl;
		cout << "2. Hamilton manual order" << endl;
		cout << "3. Nearest neighbour" << endl;
		cout << "0. Exit" << endl;
		cout << "> ";
		cin >> opt;

		if(opt==1)
		{
			if(readFrom(s) == false)
				return -1;
			printMatrix(matrix, numberOfCities);
		}
		if(opt==2)
		{
			if(readFrom(s) == false)
				return -1;
			hamiltonManualOrder(matrix, numberOfCities);
		}
		if(opt==3)
		{
			if(readFrom(s) == false)
				return -1;
			nearestNeighbour(matrix, numberOfCities);
		}

	}


	for (int i = 0; i < numberOfCities; ++i)
		delete[] matrix[i];
	delete[] matrix;
	delete[] visited;

}
