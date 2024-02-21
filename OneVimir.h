#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


class OneVimir {
private:
	int size;
	char** strings;

public:
	bool Init(int n);
	char* GetString(int index) const;
	void SetString(int index, const char* str);
	void Read();
	void Display() const;
	string ToString() const;
	bool Index_Correct(int index) const;
	void Display_Index_Massive(int index) const;
	OneVimir Concat(const OneVimir& other) const;
	OneVimir Merge_Not_Copy(const OneVimir& other) const;
	void Demostration();
	void Remove(int index);
};