#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

#include "City.h"
#include "Timer.h"
#include "ChainedHashTable.h"

using namespace std;

void printList(vector<city>& cities);

void generateList(vector<city>& cities, size_t size);

void search(vector<city>& cities, int key);

int linearSearch(vector<city>& cities, int key);

int barierSearch(vector<city>& cities, int key);

//int chainedHashtableSearch(vector<city>& cities, int key);

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	vector<city> cities;

	int task = 1, key = 0;
	size_t size = 0;

	while (task != 0)
	{
		system("cls");
		cout << "����� �9, ��������� �.�., ������� 22\n"
			"��������� ������\n"
			"�������:\n";

		if (cities.size() <= 10)
		{
			printList(cities);
		}
		else
		{
			cout << "����� ������: " << cities.size() << '\n';
		}

		cout << "1 - ������������ �������\n"
			"2 - ����� ��������\n"
			"0 - ����� �� ���������\n"
			"��� �����: ";

		cin >> task;
		cin.ignore();

		switch (task)
		{
		case 1:
			cities.clear();
			cout << "������� ���������� ��������� �������: ";
			cin >> size;

			generateList(cities, size);

			system("pause");
			break;
		case 2:
			if (cities.empty())
			{
				cout << "������� ��������� �������\n";
			}
			else
			{
				cout << "������� ���� ��� ������ ������ � �������: ";
				cin >> key;
				search(cities, key);
			}
			system("pause");
			break;
		case 0:
			cout << "�������, �� ��������!\n";
			break;
		default:
			cout << "� �� ������ ��� �������. ����������, ���������� ��� ���.\n";
			system("pause");
			break;
		}
	}
}

void printList(vector<city>& cities)
{
	if (cities.empty())
	{
		cout << "������� �����\n";
	}
	else
	{
		cout << "��� ������ | �������� ������\n";

		for (size_t i = 0; i < cities.size(); i++)
		{
			cout.fill('-');
			cout << setw(28) << "";
			cout.fill(' ');
			cout << endl;
			cout << setw(11) << cities.at(i).key;
			cout << "|";
			cout << setw(16) << cities.at(i).name;
			cout << endl;
		}
		cout.fill('-');
		cout << setw(28) << "";
		cout.fill(' ');
		cout << endl;
	}
}

void generateList(vector<city>& cities, size_t size)
{
	vector<int> codes;
	for (size_t i = 1; i <= size; i++)
	{
		codes.push_back(i);
	}

	vector<string> names
	{
		"������", "����", "������", "��������", "�������",
		"�������", "�������", "������", "������", "���������",
		"�����������", "���������", "�������", "��������", "�����",
		"�����", "�����������", "���������", "���������",
		"�������", "�������", "������", "�������", "���������"
	};

	for (size_t i = 0; i < size; i++)
	{
		size_t index = rand() % codes.size();
		cities.push_back(city(codes.at(index), names.at(rand() % names.size())));
		codes.erase(codes.begin() + index);
	}
}

void search(vector<city>& cities, int key)
{
	int foundIndex;

	cout << "\n�������� ��������:\n";
	foundIndex = linearSearch(cities, key);

	if (foundIndex < cities.size())
	{
		cout << "������ ������� � �������� " << foundIndex
			<< " � ��������� " << cities.at(foundIndex).name << "\n\n";
	}
	else
	{
		cout << "������� �� ������\n\n";
	}

	cout << "��������� ��������:\n";
	foundIndex = barierSearch(cities, key);
	if (foundIndex < cities.size())
	{
		cout << "������ ������� � �������� " << foundIndex
			<< " � ��������� " << cities.at(foundIndex).name << "\n\n";
	}
	else
	{
		cout << "������� �� ������\n\n";
	}

	cout << "�������� � ����������� ����������� - ������ �����������:\n";
	ChainedHashTable table(cities);
	Timer* timer = new Timer();

	city foundCity = table.searchItem(key);

	delete timer;
	if (foundCity.key != 0)
	{
		cout << "������ ������� � ������ " << foundCity.key
			<< " � ��������� " << foundCity.name << "\n\n";
	}
	else
	{
		cout << "������� �� ������\n\n";
	}
}

int linearSearch(vector<city>& cities, int key)
{
	Timer timer;

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (cities.at(i).key == key)
		{
			return i;
		}
	}
	return cities.size();
}

int barierSearch(vector<city>& cities, int key)
{
	cities.push_back(city(key, ""));

	Timer* timer = new Timer();

	size_t i = 0;
	for ( ; cities.at(i).key != key; i++) { }

	delete timer;

	cities.pop_back();

	return i;

}

