#pragma once
#include "stdafx.h"
class stack;
class array_s
{
	friend class stack;
	enum { SIZE = 100 };
	int max_numb_of_stacks;
	int cur_numb_of_stack;
	int mas[SIZE];
	vector<pair<int, int>> beg_end;
public:
	array_s(int m_n = 3) :max_numb_of_stacks(m_n), cur_numb_of_stack(0), beg_end(m_n)
	{
		fill(mas, mas + SIZE, 0);
		for (int i = 0; i < m_n; ++i)
			beg_end[i].first = beg_end[i].second = SIZE / m_n*i;
	}
	inline bool full() { return (cur_numb_of_stack >= max_numb_of_stacks); }
	bool add_stack(stack &s);
	
	bool free(int i)
	{
		for (int j = 0; j < cur_numb_of_stack; j++)
			if (i >= beg_end[j].first && i <= beg_end[j].second)
				return false;
		return true;
	}
};
class stack
{
	array_s &mas;
	int begin, end;
	friend class array_s;
	//friend bool array_s::add_stack(stack& s);
public:
	stack(array_s &m):mas(m)
	{
		if (!mas.add_stack(*this))
			cout << "array is full!\n";
	}
	
};
