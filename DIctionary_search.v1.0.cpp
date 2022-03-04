/*******************************************************************
* Name: Dictionary Search
* File: Dictionary_search.v1.0.cpp
* Author: Cooper cdUAH 
* Desc: Searches a dictionary using binary, sequential, and hash 
        search algorithms
* Date: 9/12/2021
* Do not replicate or sell without express permission of cdUAH
* https://github.com/cdUAH
*******************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <new>
#include <list>

using namespace std;

int comparison_count = 1;
void sequential_search(int total, string* array, string line, string searchedWord);
void binary_search(int total, string* array, string line, string searchedWord);
void hash_search(int total, string* array, string line, string searchedWord, int hashArray);
int hash_function(string input_string, int array_size);



int main ()
{
	vector<string> words;
	ifstream in("dictionary.txt", ios::in);
	string line;
	long location;
	
	if (in.fail()) {cerr << "error reading input file" << endl; exit(-1);} //error message if file doesn't open/can't be found
	while (in >>line)
	{
		words.push_back(line);
	}
	in.close();
	
	//creates program header with name, date, and description
	cout << string(53,'*') << endl;
	cout << "*********************** START ***********************" << endl;
	cout << string(53,'*') << endl;
	cout << "*Created by*: Cooper (cdUAH) ";
	cout << "https://github.com/cdUAH" <<endl;
	cout << "*Date*: 9/12/2021" << endl;
	cout << "*Description*: Searches a dictionary and counts the\n";
	cout << "               comparisons made with a binary,\n";
	cout << "               sequential, and hash search algorithm"<<endl;
	cout << "*Inputs*: *Word you want to look for\n";
	cout << "          *dictionary.txt" <<endl;
	cout << "*Outputs*: *Amount of comparisons for each search\n";
	cout << string(53,'*') << endl;
	cout << string(53,'*') << endl;
	cout << string(53,'*') << endl << endl;
	
	
	
	string searchedWord; //prompt for word to look for
	cout << "Word to look for: ";
	cin >> searchedWord;
	
	int total = words.size();
	string* array = new string[total];
	std::copy(words.begin(), words.end(), array);
	
	cout << "\n[SYS] Dictionary read with " << total << " words \n"<<endl;
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	int size_table = words.size();
	int hash_size = size_table *2; //remove and see performance
	
	int counter = 0;
	int hash;
	string temp;
	vector<vector<string> > hash_table(hash_size); //creates vector of vector string for the hash table
	for (counter = 0; counter < size_table; counter++)
	{
	
		//cout <<words[counter] << endl;
		temp = words[counter];
		hash = hash_function(temp, hash_size);
		hash_table[hash].push_back(temp); //pushes temp onto the vector at that point
	}
	cout << "[SYS] Hash Table created successfully\n" << endl;
	//////////////////////////////////////////////////////////////////////////////////////////
	
	
	

		
	while (1)
	{
		if (searchedWord.length()  == 0) //check if prompted word is empty
			return -1;
		else
		{
		sequential_search(total, array, line, searchedWord);
		comparison_count = 1;
		binary_search(total, array, line, searchedWord);
		comparison_count = 1;
		
		////////////////////////////////////////////////////////////////////////
		int searching_hash = hash_function(searchedWord, size_table);
		vector<string> result_vector = hash_table[searching_hash];
		for (int v = 0; v < result_vector.size(); v++)
		{
			comparison_count++;
			if(result_vector[v].compare(searchedWord) == 0)
			{
				cout << "Hash: Word found in " << comparison_count <<" comparisons" <<endl;
				break;
			}
			else if(result_vector[v].compare(searchedWord) >= 1) //This also kind of works, not fully however. Doesn't work for lower ranges
			{
				cout << "Hash: Word *NOT* found in " << comparison_count <<" comparisons" <<endl;
				break;
			}
		}
		////////////////////////////////////////////////////////////////////////
		comparison_count = 1;	
		cout << "\nWord to look for: ";
		cin >> searchedWord;	
		cout<<endl;
		}

	}
	
	

	
}

void sequential_search(int total, string* array, string line, string searchedWord)
{	

//total is total amount of words in dictionary
//array is 
	long i;
	while( i <= total)
	{
		if (array[i] != searchedWord) //If the word we're on is not the one we're looking for,  move to next element
		{
			i++;
			comparison_count++;
			if(i == total) //If word isnt found, print word isn't found. Had to nest it for some reason. Will figure out. 
			{
				cout << "Linear: Word *NOT* found in " << i << " comparisons" <<endl;
				break;
			}
		}
		
		else //If the word we're on is the word we're looking for, print out comparison_count
		{
			cout << "Linear: Word found in " << comparison_count <<" comparisons" <<endl;
			break;	
		}
	}
}

void binary_search(int total, string* array, string line, string searchedWord)
{
	long i = 0; //lower value holder
	long r = total-1; //upper value holder -1 since arrays start at 0
	long m; //middle value holder
	bool flag = 0; //flag for if word has been found because I'm stupid and can't figure out why binary doesn't work for a word not found
	while (i <= r)
	{
		m = floor((r+i)/2); //basis of binary. Add the lower and the upper bounds, then divide by two. This sorts the array in halves
		if (array[m] == searchedWord)
		{
			cout << "Binary: Word found in " << comparison_count <<" comparisons" <<endl;
			flag = 1;
			break;		
		}
		if (array[m] > searchedWord) //If our current array value is greater than the spot where the word is, end = middle -1
		{
			r = m-1;
			comparison_count++;
		}
		if (array[m] < searchedWord)
		{
			i = m+1;
			comparison_count++;	
		}
	}
	if (comparison_count >= 19 && flag == 0)
		cout << "Binary: Word *NOT* found in " << comparison_count << " comparisons" <<endl;
}


int hash_function(string input_string, int array_size)
{
    int counter2;
    int ascii_value = 0;
    for(counter2 = 0; counter2 < input_string.size(); counter2++)
    {
        ascii_value += int(input_string[counter2]);
    }
    return (ascii_value  % array_size);
}















