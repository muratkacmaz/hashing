
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>  
#include <stdio.h>
#include <math.h>
#include <list>

using namespace std;
#define M 131071
#define A 0.618

class BookCharacter {
	int pageNo;
	int lineNo;
	int index;
	char character;
	
	unsigned long createKey(int, int, int);

public :
	friend class Dictionary;
	friend class List;
	BookCharacter() {};
	unsigned long key;
	BookCharacter(int, int, int,char);
	BookCharacter(int, int, int);

};

BookCharacter::BookCharacter(int p,int l,int i,char c){
	pageNo = p;
	lineNo = l;
	index = i;
	character = c;
	key = createKey(p, l, i);
}

BookCharacter::BookCharacter(int p, int l, int i)
{
	pageNo = p;
	lineNo = l;
	index = i;
	character = '\0';
	key = createKey(p, l, i);
}

unsigned long BookCharacter::createKey(int page, int line, int ind)
{
	unsigned long unique;

	page = page * 10000;
	line = line * 100;
	unique = page + line + ind;

	return unique;

}


////////////////////////////////////////////////////////////////////


class Dictionary
{
	BookCharacter hashTable[M];
public: 
	double coll1, coll2, coll3,coll4 ;
	Dictionary();
	
	void insertion(vector<BookCharacter>&);
	void hashFunction(vector<BookCharacter>&, unsigned long, int);
	void probingFunction(vector<BookCharacter>&, unsigned long, int);
	void lookUp(vector<BookCharacter>&);
	void writeToDict(vector<BookCharacter>&);
};

Dictionary::Dictionary() {
	for (int i = 0; i < M; i++)
	{
		hashTable[i].key = 0;
	}
}

void Dictionary::insertion(vector<BookCharacter>& insertion_array)
{
	
	for (int i = 0; i < insertion_array.size(); i++)
	{
		hashFunction(insertion_array, insertion_array[i].key, i);

	}
}

void Dictionary::hashFunction(vector<BookCharacter>& arr, unsigned long k, int number) {
	unsigned long h;
	double  kTimesA = k*A;
	double left, right;
	right = modf(kTimesA, &left);


	h = (M*right);
	
	probingFunction(arr,h,number);
	
}



void Dictionary::probingFunction(vector<BookCharacter>& arr, unsigned long h, int number)
{
	unsigned long hNew = h;
	int i = 0;
	unsigned long quadratic;

	while (i<M)
	{
		quadratic = 7 * i + 3 * i*i;
		hNew = (hNew + quadratic) % M;
		if (arr[number].character)
		{
			if (!hashTable[hNew].key)
			{
				hashTable[hNew] = arr[number];
				break;
			}
			i++;
			if (number <= 1000) {
				coll1 += 1;
			}
			if (number <= 10000) {
				coll2 += 1;
			}
			if (number <= 100000) {
				coll3 += 1;
			}
			if (number <= M) {
				coll4 += 1;
			}

		}
		else 
		{	
			if (arr[number].key == hashTable[hNew].key)
			{
				arr[number].character = hashTable[hNew].character;
				//cout << hashTable[hNew].character ;
				break;
			}
			i++;
		}
		
	}

}

void Dictionary::lookUp(vector<BookCharacter>& lookup_array)
{
	for (int i = 0; i < lookup_array.size(); i++)
	{
		hashFunction(lookup_array, lookup_array[i].key, i);

	}
}

void Dictionary::writeToDict(vector<BookCharacter>& lookup_array)
{
	ofstream writing;
	writing.open("ds-set-output-dict.txt");
	for (int i = 0; i < M; i++)
	{
		writing << lookup_array[i].character; 
	}
	writing.close();
}


/////////////////////////////////////////////////////////////////////////////////////////


class List {
public:
	void listInsertion(vector<BookCharacter>&, vector<BookCharacter>&);
	void listLookup(vector<BookCharacter>&, vector<BookCharacter>&, vector<char>&);
	void writeToList(vector<char>&);
};




void  List :: listInsertion(vector<BookCharacter>& list_array, vector<BookCharacter>& insertion_array)
{
	for (int i = 0; i < insertion_array.size(); i++)
	{
		list_array.push_back(insertion_array[i]);

	}


}

void  List::listLookup(vector<BookCharacter>& list_array, vector<BookCharacter>& lookup_array, vector<char>& charArray)
{
	for (int i = 0; i < M; i++)
	{
		
		for (int j = 0; j < M; j++)
		{
			
			if (lookup_array[i].key == list_array[j].key)
			{	
				charArray.push_back(lookup_array[i].character);
				break;
			}
		}
	}
}

void List::writeToList(vector<char>& charArray)
{
	ofstream writing;
	writing.open("ds-set-output-list.txt");
	for (int i = 0; i < M; i++)
	{
		writing << charArray[i];
	}
	writing.close();
}
