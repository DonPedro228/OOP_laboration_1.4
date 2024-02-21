#define _CRT_SECURE_NO_WARNINGS
#include "OneVimir.h"
#include <iostream>
#include <string>
using namespace std;

bool OneVimir::Init(int n)
{
	size = n;
	strings = new char* [size];
	for (int i = 0; i < size; ++i) {
		strings[i] = nullptr;
	}
	return true;
}

char* OneVimir::GetString(int index) const
{
	if (index < 0 && index > size) {
		cout << "Index out of range !(" << endl;
		return nullptr;
	}
	return strings[index];
}

void OneVimir::SetString(int index, const char* str)
{
	if (index < 0 && index >= size) {
		cout << "Index out of range !(" << endl;
		return;
	}

	delete[] strings[index];

	size_t len = strlen(str);
	strings[index] = new char[len + 1];
	strcpy_s(strings[index], len + 1, str);
}

void OneVimir::Read()
{
	cin >> size;

	if (Init(size)) {
		for (int i = 0; i < size; ++i) {
			cout << "String " << i << ": ";
			char str[100];
			cin >> str;
			SetString(i, str);
		}
	}
}

void OneVimir::Display() const
{
	for (int i = 0; i < size; ++i) {
		cout << endl;
		cout << "Index: " << i << endl;
		if (strings[i] != nullptr) {
			cout << strings[i];
		}
		else {
			cout << "Null";
		}
		cout << endl;
	}
}

string OneVimir::ToString() const
{
	stringstream sout;

	for (int i = 0; i < size; ++i) {
		if (strings[i] != nullptr) {
			sout << strings[i];
		}
	}
	return sout.str();
}

bool OneVimir::Index_Correct(int index) const
{
	return (index >= 0 && index < size);
}

void OneVimir::Display_Index_Massive(int index) const
{
	if (Index_Correct(index)) {
		cout << "Element at index: " << index << ":  ";
		if (strings[index] != nullptr) {
			cout << strings[index];
		}
		else {
			cout << "Null";
		}
		cout << endl;
	}
	else {
		cout << "Index out of range!" << endl;
	}
}

OneVimir OneVimir::Concat(const OneVimir& other) const
{
	OneVimir con_massive;
	con_massive.Init(size + other.size);
	int index = 0;
	for (int i = 0; i < size; ++i) {
		con_massive.SetString(index++, strings[i]);
	}
	for (int i = 0; i < other.size; ++i) {
		con_massive.SetString(index++, other.strings[i]);
	}
	return con_massive;
}

void OneVimir::Remove(int index)
{
	if (index < 0 || index >= size) {
		cout << "Invalid index for removal" << endl;
		return;
	}

	delete[] strings[index];
	strings[index] = nullptr;

	for (int i = index; i < size - 1; ++i) {
		strings[i] = strings[i + 1];
	}

	--size;
}


OneVimir OneVimir::Merge_Not_Copy(const OneVimir& other) const
{
	OneVimir end_result;
	int new_size = size;
	for (int i = 0; i < other.size; ++i) {
		bool found = false;
		for (int j = 0; j < size; ++j) {
			if (strcmp(other.strings[i], strings[j]) == 0) {
				found = true;
				break;
			}
		}
		if (!found) {
			++new_size;
		}
	}
	end_result.Init(new_size);
	int index = 0;
	for (int i = 0; i < size; ++i) {
		end_result.SetString(index++, strings[i]);
	}
	for (int i = 0; i < other.size; ++i) {
		bool found = false;
		for (int j = 0; j < size; ++j) {
			if (strcmp(other.strings[i], strings[j]) == 0) {
				found = true;
				break;
			}
		}
		if (!found) {
			end_result.SetString(index++, other.strings[i]);
		}
	}

	for (int i = 0; i < end_result.size; ++i) {
		for (int j = i + 1; j < end_result.size;) {
			if (strcmp(end_result.strings[i], end_result.strings[j]) == 0) {
				end_result.Remove(j); 
			}
			else {
				++j;
			}
		}
	}

	return end_result;
}

void OneVimir::Demostration()
{
	OneVimir ar1, ar2;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Select an action: " << endl << endl;
		cout << " [1] - entering data from the keyboard " << endl;
		cout << " [2] - cout data in display" << endl;
		cout << " [3] - do element concatination and doing new" << endl;
		cout << " [4] - marge two massive with create new..." << endl;
		cout << " [5] - cout in display element of massive with input index" << endl;
		cout << " [6] - to string" << endl;
		cout << " [0] - Exit" << endl << endl;
		cout << "Input value: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			cout << "Enter data for the first array:" << endl;
			ar1.Read();
			cout << endl << "Enter data for the second array:" << endl;
			ar2.Read();
			break;
		case 2:
			cout << "First array:" << endl;
			ar1.Display();
			cout << endl << "Second array:" << endl;
			ar2.Display();
			break;
		case 3:
			cout << "Concatenating arrays..." << endl;
			(ar1.Concat(ar2)).Display();
			break;
		case 4:
			cout << "Merging arrays..." << endl;
			(ar1.Merge_Not_Copy(ar2)).Display();
			break;
		case 5:
			int index;
			cout << "Enter the index of the array element to display: ";
			cin >> index;
			cout << "Element at index " << index << " of the first array:" << endl;
			ar1.Merge_Not_Copy(ar2).Display_Index_Massive(index);
			break;
		case 6:
			cout << ar1.Merge_Not_Copy(ar2).ToString() << endl;
			break;
		case 0:
			cout << "Exiting the program..." << endl;
			break;
		default:
			cout << "You choose fake value! " << endl;
		}
	} while (menuItem != 0);
}