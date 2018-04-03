#include "word.h"
int m;

int DoubleProcessing(string s)
{
	string s1 = "";
	int i = 0, result = 0;
	while ((s[i] != ':') && (i<s.length()))
	{
		s1 += s[i];
		i++;
	}
	for (i = 0;i < s1.length();i++)
	{
		int temp = 1;
		for (int j = i + 1;j < s1.length();j++)
		{
			temp = temp * 128;
			if (temp > m) temp = (m - 2) - temp % (m - 2);
		}
		temp = temp*int(s[i]);
		result = result + temp;
		if (result > m)result = (m - 2) - result % (m - 2)	;
	}
	return result;
}

int Processing(string s)
{
	string s1 = "";
	int i = 0, result = 0;
	while ((s[i] != ':') && (i<s.length()))
	{
		s1 += s[i];
		i++;
	}
	for (i = 0;i < s1.length();i++)
	{
		int temp = 1;
		for (int j = i + 1;j < s1.length();j++)
		{
			temp = temp * 128;
			if (temp > m) temp = temp%m;
		}
		temp = temp*int(s[i]);
		result = result + temp;
		if (result > m)result = result %m;
	}
	return result;
}

void Default(ifstream &fdata, word* Data)
{
	string stemp;
	int i;
	while (!fdata.eof())
	{
		getline(fdata, stemp);
		i = Processing(stemp);
		Data[i].InsertDefault(stemp);
	}
	fdata.close();
}
void SearchDefault(ifstream &fi, ofstream &fo, word* Data)
{
	string keyword;
	int i;
	word p;
	
	while (!fi.eof())
	{
		fi >> keyword;
		i = Processing(keyword);
		p = Data[i];
		while ((p.key != keyword))
		{
			if (p.key == "")
			{
				fo << "KHONG TIM THAY" << endl;
				break;
			}
			p = *p.next;
		}
		fo << p.mean;
	}
	fi.close();
	fo.close();
}

void LinearHash(ifstream &fdata, word *Data)
{
	string stemp;
	int i;
	while (!fdata.eof())
	{
		getline(fdata, stemp);
		i = Processing(stemp);
		while (Data[i].Insert(stemp) == false)
		{
			i++;
			i = i % m;
		}
	}
	fdata.close();
}
void SearchLinear(ifstream &fi, ofstream &fo, word *Data)
{
	string keyword;
	while (!fi.eof())
	{
		fi >> keyword;
		int i = Processing(keyword);
		if (Data[i].key == keyword)
			fo << Data[i].mean;
		else
		{
			while (Data[i].key != keyword)
			{
				i++;
				i = i % m;
				if (Data[i].key == keyword)
				{
					fo << Data[i].mean;
					break;
				}
				if (Data[i].key == "")
				{
					fo << "KHONG TIM THAY" << endl;
					break;
				}
			}
		}
	}
	fi.close();
	fo.close();
}

void QuadraticHash(ifstream &fdata, word *Data)
{
	string stemp;
	int i;
	while (!fdata.eof())
	{
		getline(fdata, stemp);
		i = Processing(stemp);
		int j = i;
		int count = 0;
		while (Data[j].Insert(stemp) == false)
		{
			count++;
			j = (i + count * count) % m;
		}
	}
	fdata.close();
}
void SearchQuadratic(ifstream &fi, ofstream &fo, word *Data)
{
	string keyword;
	while (!fi.eof())
	{
		fi >> keyword;
		int i = Processing(keyword);
		if (Data[i].key == keyword)
			fo << Data[i].mean;
		else
		{
			int count = 0;
			int j = i;
			while (Data[j].key != keyword)
			{
				count++;
				j = (i + count*count) % m;
				if (Data[j].key == keyword)
				{
					fo << Data[j].mean;
					break;
				}
				if (Data[j].key == "")
				{
					fo << "KHONG TIM THAY" << endl;
					break;
				}
			}
		}
	}
	fi.close();
	fo.close();
}

void DoubleHash(ifstream &fdata, word *Data)
{
	string stemp;
	int i, t;
	while (!fdata.eof())
	{
		getline(fdata, stemp);
		i = Processing(stemp);
		int j = i;
		int count = 0;
		t = DoubleProcessing(stemp);
		while (Data[j].Insert(stemp) == false)
		{
			count++;
			j = (i + count * t) % m;
		}
	}
	fdata.close();
}
void SearchDouble(ifstream &fi, ofstream &fo, word *Data)
{
	string keyword;
	while (!fi.eof())
	{
		fi >> keyword;
		int i = Processing(keyword);
		if (Data[i].key == keyword)
			fo << Data[i].mean;
		else
		{
			int t = DoubleProcessing(keyword);
			int count = 0;
			int j = i;
			while (Data[j].key != keyword)
			{
				count++;
				j = (i + count*t) % m;
				if (Data[j].key == keyword)
				{
					fo << Data[j].mean;
					break;
				}
				if (Data[j].key == "")
				{
					fo << "KHONG TIM THAY" << endl;
					break;
				}
			}
		}
	}
	fi.close();
	fo.close();
}

int main(int argc, char** argv)
{
	ifstream fi, fdata;
	ofstream fo;
	fi.open(argv[3]);
	fo.open(argv[4]);
	fdata.open("English-Vietnamese Dictionary.dat", ios::binary);
	word *Data;
	m = atoi(argv[1]);
	if (atoi(argv[2]) == 1)
	{
		Data = new word[atoi(argv[1])];
		Default(fdata, Data);
		SearchDefault(fi, fo, Data);
	}
	else if (atoi(argv[2]) == 2)
	{
		Data = new word[atoi(argv[1])];
		LinearHash(fdata, Data);
		SearchLinear(fi, fo, Data);
	}
	else if (atoi(argv[2]) == 3)
	{
		Data = new word[atoi(argv[1])];
		QuadraticHash(fdata, Data);
		/*for (int i = 0;i < 12000;i++)
		{
			if (Data[i].key!="")
				fo << Data[i].key << endl;
		}*/
		SearchQuadratic(fi, fo, Data);
	}
	else
	{
		Data = new word[atoi(argv[1])];
		DoubleHash(fdata, Data);
		SearchDouble(fi, fo, Data);
	}
	return 0;
}