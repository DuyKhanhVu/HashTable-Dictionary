#include "word.h"

void word::InsertDefault(string s)
{
	if (this->key == "")
	{
		this->key = s.substr(0, s.find(':'));
		this->mean = s.substr(s.find(':') + 1, s.length());
		this->next = NULL;
	}
	else
	{
		word* p = this;
		while (p->next != NULL)
			p = p->next;
		p->next = new word;
		p->next->key= s.substr(0, s.find(':'));
		p->next->mean = s.substr(s.find(':') + 1, s.length());
		p->next->next = NULL;
	}
}

bool word::Insert(string s)
{
	if (this->key == "")
	{
		this->key = s.substr(0, s.find(':'));
		this->mean = s.substr(s.find(':') + 1, s.length());
		this->next = NULL;
		return true;
	}
	else return false;
}