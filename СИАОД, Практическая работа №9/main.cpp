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
		cout << "СИАОД №9, Поведенок С.С., Вариант 22\n"
			"Алгоритмы поиска\n"
			"Таблица:\n";

		if (cities.size() <= 10)
		{
			printList(cities);
		}
		else
		{
			cout << "Имеет размер: " << cities.size() << '\n';
		}

		cout << "1 - Сформировать таблицу\n"
			"2 - Поиск элемента\n"
			"0 - Выход из программы\n"
			"Ваш выбор: ";

		cin >> task;
		cin.ignore();

		switch (task)
		{
		case 1:
			cities.clear();
			cout << "Введите количество элементов таблицы: ";
			cin >> size;

			generateList(cities, size);

			system("pause");
			break;
		case 2:
			if (cities.empty())
			{
				cout << "Сначала заполните таблицу\n";
			}
			else
			{
				cout << "Введите ключ для поиска записи в таблице: ";
				cin >> key;
				search(cities, key);
			}
			system("pause");
			break;
		case 0:
			cout << "Спасибо, до свидания!\n";
			break;
		default:
			cout << "Я не совсем вас понимаю. Пожалуйста, попробуйте ещё раз.\n";
			system("pause");
			break;
		}
	}
}

void printList(vector<city>& cities)
{
	if (cities.empty())
	{
		cout << "Таблица пуста\n";
	}
	else
	{
		cout << "Код города | Название города\n";

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
		"Москва", "Омск", "Элиста", "Владимир", "Коломна",
		"Грозный", "Нальчик", "Сургут", "Тюмень", "Челябинск",
		"Владивосток", "Краснодар", "Иваново", "Кострома", "Пермь",
		"Пенза", "Архангельск", "Исилькуль", "Череповец",
		"Саратов", "Саранск", "Казань", "Барнаул", "Чебоксары"
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

	cout << "\nЛинейный алгоритм:\n";
	foundIndex = linearSearch(cities, key);

	if (foundIndex < cities.size())
	{
		cout << "Найден элемент с индексом " << foundIndex
			<< " и значением " << cities.at(foundIndex).name << "\n\n";
	}
	else
	{
		cout << "Элемент не найден\n\n";
	}

	cout << "Барьерный алгоритм:\n";
	foundIndex = barierSearch(cities, key);
	if (foundIndex < cities.size())
	{
		cout << "Найден элемент с индексом " << foundIndex
			<< " и значением " << cities.at(foundIndex).name << "\n\n";
	}
	else
	{
		cout << "Элемент не найден\n\n";
	}

	cout << "Алгоритм с применением хеширования - цепное хеширование:\n";
	ChainedHashTable table(cities);
	Timer* timer = new Timer();

	city foundCity = table.searchItem(key);

	delete timer;
	if (foundCity.key != 0)
	{
		cout << "Найден элемент с ключом " << foundCity.key
			<< " и значением " << foundCity.name << "\n\n";
	}
	else
	{
		cout << "Элемент не найден\n\n";
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

