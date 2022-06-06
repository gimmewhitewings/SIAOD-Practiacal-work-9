#pragma once

#include <list>
#include <vector>
#include "City.h"

using namespace std;

class ChainedHashTable
{
public:
	ChainedHashTable(vector<city> cities);

	void insertItem(city city)
	{
		int index = hashFunc(city.key);
		table->at(index).push_back(city);
	}

	city searchItem(int key)
	{
		list<city> cityList = table->at(hashFunc(key));
		for (auto city : cityList)
		{
			if (city.key == key)
			{
				return city;
			}
		}
		return city(0, "");
	}
private:
	size_t size;
	vector<list<city>>* table;

	int hashFunc(int key)
	{
		return key % this->size;
	}
};

ChainedHashTable::ChainedHashTable(vector<city> cities)
{
	this->size = cities.size();
	table = new vector<list<city>>(size);
	for (auto city : cities)
	{
		this->insertItem(city);
	}
}
