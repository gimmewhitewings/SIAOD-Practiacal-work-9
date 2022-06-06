#pragma once

struct city
{
	int key;
	std::string name;

	city(int key, std::string name)
	{
		this->key = key;
		this->name = name;
	}
};