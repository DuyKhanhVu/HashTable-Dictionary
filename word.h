#pragma once
#include <fstream>
#include <string>

using namespace std;

class word
{
public:
	string key;
	string mean;
	word* next;
public:
	void InsertDefault(string a);
	bool Insert(string a);
	
};

