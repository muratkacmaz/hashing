
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <list>
#include "Header.h"
#define M 131071
using namespace std;


void inputFileRead(vector<BookCharacter>& insertion_array) {
	string p, l, i, c;
	char character;
	int page, line, index;
	ifstream fileRead;
	fileRead.open("ds-set-input.txt");
	string lineRead;
	while (getline(fileRead, lineRead))
	{
		istringstream iss(lineRead);
		getline(iss, p, '\t');
		getline(iss, l, '\t');
		getline(iss, i, '\t');
		getline(iss, c, '\n');

		page = atoi(p.c_str());
		line = atoi(l.c_str());
		index = atoi(i.c_str());

		character = c[0];


		BookCharacter newData(page, line, index, character);
		insertion_array.push_back(newData);
	}
	fileRead.close();
}

void lookUpFileRead(vector<BookCharacter>& lookup_array)
{
	string p, l, i, character;
	int page, line, index;
	ifstream fileRead;
	fileRead.open("ds-set-lookup.txt");
	string lineRead;
	while (getline(fileRead, lineRead))
	{
		istringstream iss(lineRead);
		getline(iss, p, '\t');
		getline(iss, l, '\t');
		getline(iss, i, '\n');

		page = atoi(p.c_str());
		line = atoi(l.c_str());
		index = atoi(i.c_str());

		BookCharacter newData(page, line, index);
		lookup_array.push_back(newData);
	}
	fileRead.close();


}





int main(int argc, char* argv[])
{
	vector<BookCharacter> insertion_array;
	inputFileRead(insertion_array);
	Dictionary dict;
	List list;
	
	
	clock_t begin = clock();
	dict.insertion(insertion_array);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "DICTIONARY " << endl;
	cout << "Insertion finished after "<< elapsed_secs << endl;
	cout << "Average Number Of Collisions (first 1,000) :   |  " << dict.coll1/1000 << endl;
	cout << "Average Number Of Collisions (first 10,000) :   |  " << dict.coll2/10000 << endl;
	cout << "Average Number Of Collisions (first 100,000) :   |  " << dict.coll3/100000 << endl;
	cout << "Average Number Of Collisions (Overall) :   |  " << dict.coll4/M << endl;

	vector<BookCharacter> lookup_array;
	lookUpFileRead(lookup_array);


	clock_t begin1 = clock();
	dict.lookUp(lookup_array);
	clock_t end1 = clock();
	double elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
	cout <<endl << "Lookup finished after " << elapsed_secs1 << endl << endl;
	dict.writeToDict(lookup_array);

	vector<BookCharacter> list_array;
	vector<char> charArray;

	clock_t begin2 = clock();
	list.listInsertion(list_array, insertion_array);
	clock_t end2 = clock();
	double elapsed_secs2 = double(end2 - begin2) / CLOCKS_PER_SEC;
	cout << "LIST";
	cout << endl << "Insertion finished after " << elapsed_secs2 << endl;


	

	clock_t begin3 = clock();
	list.listLookup(list_array, lookup_array, charArray);
	clock_t end3 = clock();
	double elapsed_secs3 = double(end3 - begin3) / CLOCKS_PER_SEC;
	cout << endl << "LookUp finished after " << elapsed_secs3 << endl;


	list.writeToList(charArray);

	return 0;
}

