// dmMaxWay.cpp : Defines the entry point for the console application.
//

#include<locale.h> 
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <iostream>
#include <fstream>


using namespace std;

void printMatrix(int **M, int size)
{
	for (int i = 0; i<size - 1; i++)
	{
		for (int j = 0; j<size; j++)
		{
			cout << M[i][j] << " ";
		}
	}
}

int* addToArray(int *M, int length, int num)
{
	int i;
	for (i = 0; i < length && M[i]!=-1; i++)
	{
		if (M[i] == num)return M;
	}
	M[i] = num;
	return M;
}

void printArray(int *workMatrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (workMatrix[i] > 9)
		{
			cout << workMatrix[i] << "|";
		}
		else
		{
			cout << " " << workMatrix[i] << "|";
		}
	}
}

int* removeFirstFromArray(int *M, int length)
{
	int i;
	for (i = 0; i < length && M[i]!=-1; i++)
	{
		M[i] = M[i + 1];
	}
	M[i - 1] = -1;
	return M;
}

void firstStep(int *workMatrix, int size)
{
	for (int i = 0; i < size; i++)workMatrix[i] = 0;
}


void printM(int *M, int length)
{	
	for (int i = 0; i < length; i++)
	{
		if (!(M[i]+1))break;
		cout << "|" << (M[i] + 1); 
	}
	cout << endl;
}

void expandInRow(int *workMatrix, int **uM, int size, int *M)
{
	int vertex = M[0]; //????? ??????? ?? ??????? ?????????????
	int value = workMatrix[vertex]; //?? ????????
	M = removeFirstFromArray(M, size); //???????? ??????? ?? ?
	for (int i = 0; i < size; i++) 
	{
		if (uM[vertex][i])
		{
			int newValue = value + uM[vertex][i];
			if (newValue > workMatrix[i])
			{
				workMatrix[i] = newValue;
				M = addToArray(M, size, i);
			}
			/*max
			if (newValue > workMatrix[i])
			{
			workMatrix[i] = newValue;
			M = addToArray(M, size, i);
			}*/
			/*min
			if ((newValue < workMatrix[i] || !workMatrix[i]) && i)
			{
				workMatrix[i] = newValue;
				M = addToArray(M, size, i);
			}*/
		}
	}
	printArray(workMatrix, size);
	printM(M, size);
}

void printHeader(int size)
{
	for (int i = 0; i < size; i++)
	{
		if (i + 1 < 10)
		{
			cout << " " << i + 1 << "|";
		}
		else 
		{
			cout << i + 1 << "|";
		}
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "--|";
	}
	cout << endl;
}

int *fillM(int size)
{
	int *arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = -1;
	}
	return arr;
}

void findMaxWay(int **uM, int size, int workIndex, int *wM, int *savedVertexes, int position)
{
	if (workIndex == 0)
	{
		int length = 0;
		cout << "?????? ???? ";
		for (int i = 0; i < position - 1; i++)
		{
			cout << "{x" << savedVertexes[i] << ", x" << savedVertexes[i + 1] << "}(" 
				<< uM[savedVertexes[i + 1] - 1][savedVertexes[i] - 1] << "), ";
			length += uM[savedVertexes[i+1]-1][savedVertexes[i]-1];
		}
		length += uM[workIndex][savedVertexes[position - 1] - 1];
		cout << "{x" << savedVertexes[position - 1] << ", x" << workIndex + 1 << "}("
			<< uM[workIndex][savedVertexes[position - 1] - 1] << ") ? ?????? " << length << endl;
		return;
	}
	position++;
	int *save = new int[position];
	for (int i = 0; savedVertexes && i < position - 1; i++)save[i] = savedVertexes[i];
	save[position - 1] = workIndex + 1;
	
	cout << "G^-1 (x" << workIndex + 1 << ")={";
	for (int i = 0; i < size; i++)
	{
		if (uM[i][workIndex] != 0)
			cout << "x" << i + 1 << ", ";
	}
	cout << "}" << endl;
	for (int i = 0; i < size; i++)
	{
		if (uM[i][workIndex] != 0)
		{
			cout << "???? (x" << i + 1 << ", x" << workIndex + 1 << "): ";
			int sum = wM[workIndex] - wM[i];
			int len = uM[i][workIndex];
			cout << "????? = " << len << ",a ??????? ????? = " << sum << " - ";
			if (sum == len) 
			{
				cout << "??????????" << endl;
				findMaxWay(uM, size, i, wM, save, position);
			} else 
			{
				cout << "?? ??????????" << endl;
			}
		}
	}
}

void work(int **uM, int size)
{
	int *workMatrix = (int*)malloc(size * sizeof(int)),
		*M = fillM(size);
	firstStep(workMatrix, size);
	M = addToArray(M, size, 0);
	printHeader(size);
	printArray(workMatrix, size);
	printM(M, size);
	do
	{
		expandInRow(workMatrix, uM, size, M);
	} while (M[0]!=-1);
	cout << "????????? ????: " << endl;
	findMaxWay(uM, size, size-1, workMatrix, NULL, 0);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int size;
	ifstream file;
	file.open("in.txt");
	file >> size;
	int **uM = new int*[size];
	for (int i = 0; i<size; i++)
	{
		uM[i] = new int[size];
		for (int j = 0; j<size; j++)
		{
			file >> uM[i][j];
		}
	}
	
	file.close();
	work(uM, size);
	cin >> size;
}

/*// dmMaxWay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void printMatrix(int **M, int size)
{
for (int i = 0; i<size - 1; i++)
{
for (int j = 0; j<size; j++)
{
cout << M[i][j] << " ";
}
}
}

int* addToArray(int *M, int length, int num)
{
int i;
for (i = 0; i < length && M[i]!=-1; i++)
{
if (M[i] == num)return M;
}
M[i] = num;
return M;
}

void printArray(int *workMatrix, int size)
{
for (int i = 0; i < size; i++)
{
if (workMatrix[i] > 9)
{
cout << workMatrix[i] << "|";
}
else
{
cout << " " << workMatrix[i] << "|";
}
}
}

int* removeFirstFromArray(int *M, int length)
{
int i;
for (i = 0; i < length && M[i]!=-1; i++)
{
M[i] = M[i + 1];
}
M[i - 1] = -1;
return M;
}

void firstStep(int *workMatrix, int size)
{
for (int i = 0; i < size; i++)workMatrix[i] = 0;
}


void printM(int *M, int length)
{
for (int i = 0; i < length; i++)
{
if (!(M[i]+1))break;
cout << "|" << (M[i] + 1);
}
cout << endl;
}

void expandInRow(int *workMatrix, int **uM, int size, int *M)
{
int vertex = M[0]; //????? ??????? ?? ??????? ?????????????
int value = workMatrix[vertex]; //?? ????????
M = removeFirstFromArray(M, size); //???????? ??????? ?? ?
for (int i = 0; i < size; i++)
{
if (uM[vertex][i])
{
int newValue = value + uM[vertex][i];
if (newValue > workMatrix[i])
{
workMatrix[i] = newValue;
M = addToArray(M, size, i);
}
}
}
printArray(workMatrix, size);
printM(M, size);
}

void printHeader(int size)
{
for (int i = 0; i < size; i++)
{
if (i + 1 < 10)
{
cout << " " << i + 1 << "|";
}
else
{
cout << i + 1 << "|";
}
}
cout << endl;
for (int i = 0; i < size; i++)
{
cout << "--|";
}
cout << endl;
}

int *fillM(int size)
{
int *arr = new int[size];
for (int i = 0; i < size; i++)
{
arr[i] = -1;
}
return arr;
}

void findMaxWay(int **uM, int size, int workIndex, int *wM, int *savedVertexes, int position)
{
if (workIndex == 0)
{
int length = 0;
cout << "?????? ???? ";
for (int i = 0; i < position - 1; i++)
{
cout << "{x" << savedVertexes[i] << ", x" << savedVertexes[i + 1] << "}("
<< uM[savedVertexes[i + 1] - 1][savedVertexes[i] - 1] << "), ";
length += uM[savedVertexes[i+1]-1][savedVertexes[i]-1];
}
length += uM[workIndex][savedVertexes[position - 1] - 1];
cout << "{x" << savedVertexes[position - 1] << ", x" << workIndex + 1 << "}("
<< uM[workIndex][savedVertexes[position - 1] - 1] << ") ? ?????? " << length << endl;
return;
}
position++;
int *save = new int[position];
for (int i = 0; savedVertexes && i < position - 1; i++)save[i] = savedVertexes[i];
save[position - 1] = workIndex + 1;

cout << "G^-1 (x" << workIndex + 1 << ")={";
for (int i = 0; i < size; i++)
{
if (uM[i][workIndex] != 0)
cout << "x" << i + 1 << ", ";
}
cout << "}" << endl;
for (int i = 0; i < size; i++)
{
if (uM[i][workIndex] != 0)
{
cout << "???? (x" << i + 1 << ", x" << workIndex + 1 << "): ";
int sum = wM[workIndex] - wM[i];
int len = uM[i][workIndex];
cout << "????? = " << len << ",a ??????? ????? = " << sum << " - ";
if (sum == len)
{
cout << "??????????" << endl;
findMaxWay(uM, size, i, wM, save, position);
} else
{
cout << "?? ??????????" << endl;
}
}
}
}

void work(int **uM, int size)
{
int *workMatrix = (int*)malloc(size * sizeof(int)),
*M = fillM(size);
firstStep(workMatrix, size);
M = addToArray(M, size, 0);
printHeader(size);
printArray(workMatrix, size);
printM(M, size);
do
{
expandInRow(workMatrix, uM, size, M);
} while (M[0]!=-1);
cout << "????????? ????: " << endl;
findMaxWay(uM, size, size-1, workMatrix, NULL, 0);
}

int main()
{
setlocale(LC_ALL, "RUS");
int size;
ifstream file;
file.open("in.txt");
file >> size;
int **uM = new int*[size];
for (int i = 0; i<size; i++)
{
uM[i] = new int[size];
for (int j = 0; j<size; j++)
{
file >> uM[i][j];
}
}

file.close();
work(uM, size);
cin >> size;
}

*/
