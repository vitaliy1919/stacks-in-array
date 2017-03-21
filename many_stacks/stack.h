#pragma onces
#include "stdafx.h"
template <typename T>
class stack;

struct stack_info //info about each stack - start, end points and wheather this stack is really in the mas
{
	int begin;
	int end;
	bool created;
	stack_info() :begin(0), end(0), created(false) {}
};

template <typename T>
class array_s // êarray class for stacks
{
	template <typename T>
	friend class stack;
	static const int SIZE = 100 ;
	int max_numb_of_stacks;
	T items[SIZE];
	vector<stack_info> beg_end;
public:
	array_s(int m_n = 3);
	inline const T* it() const {return items;}
	bool full();
	bool add_stack(stack<T> &s);
};

template <typename T>
class stack //stack class
{
	array_s<T> &mas; //reference to array for this stack
	int stack_num; //number of the stack in array
private:
	template <typename T>
	friend class array_s;

	inline int begin() const { return mas.beg_end[stack_num].begin; } //operations to get end and begin from array
	inline int end() const { return mas.beg_end[stack_num].end; }
	inline int& begin() { return mas.beg_end[stack_num].begin; }
	inline int& end() { return mas.beg_end[stack_num].end; }
public:
	stack(array_s<T> &m) :mas(m)
	{
		stack_num = mas.add_stack(*this);
		if (stack_num == -1)
			cout << "array is full!\n";
	}
	~stack() { mas.beg_end[stack_numb].created = false; } //when stack is deleted we can use memory of the stack for new stacks
	bool push(const T& item); //add item to stack
	bool pop(T& item); //pop item from stack into T& item
	bool empty() const { return begin() >= end(); } 
	int size() const { return end() - begin(); }
};

template<typename T>
array_s<T>::array_s(int m_n) :max_numb_of_stacks(m_n), beg_end(m_n)
{
	fill(items, items + SIZE, 0);
	for (int i = 0; i < m_n; ++i) 
		beg_end[i].begin = beg_end[i].end = SIZE / m_n*i; //memory is allocated for all stacks evenly, when array is created
}

template<typename T>
bool array_s<T>::full()
{
	for (int i = 0; i < max_numb_of_stacks; i++)
		if (!beg_end[i].created) //find first "empty" stack
			return false;
	return true;
}

template <typename T>
bool array_s<T>::add_stack(stack<T> & s) //add stack to aray
{
	for (int i = 0; i < max_numb_of_stacks; i++) 
		if (!beg_end[i].created) //find first "empty" stack
		{
			beg_end[i].created = true; //set that the stack is now used
			return i;
		}
	return -1;
}

template<typename T>
bool stack<T>::push(const T & item)
{
	bool flag = true; //flag checks if we can add item (true because we assume that we have free place)
	if (end() + 1>=mas.beg_end[stack_num + 1].begin) //condition that there is no place to add new element
	{
		/*try to find place in left part array from current stack*/
		int i = stack_num;
		flag = false;
		while (!flag && i>=0)
		{
			int diff = mas.beg_end[i].begin; //diff checks "place" between 2 stacks (between first stack end and second stack begin). 1 means that there is no place.
			if (i) //if stack is the first in the array (i==0) we should find "place" between "0 element" and stack begin
				diff -= mas.beg_end[i - 1].end;
			else
				diff++;
			if (diff > 1) //if there is free place we should use it
			{
				for (int j = mas.beg_end[i].begin; j <= mas.beg_end[stack_num].end; j++) //shift items in our array to the left (from i to stack_num stacks)
					mas.items[j - diff + 1] = mas.items[j];
				for (int j = i; j <= stack_num; j++) //and then change stack's begin and end
				{
					mas.beg_end[j].begin -= diff - 1;
					mas.beg_end[j].end -= diff - 1;
				}
				flag = true; //because we can add item
			}
			i--;
		}
		if (!flag) //if we still don't find space - we'll try to find it in the right part of array
		{
			i = stack_num + 1;
			while (!flag && i < mas.max_numb_of_stacks)
			{
				int diff= - mas.beg_end[i].end; //also trying to find "place" diff==1 means that there is no place
				if (i == mas.max_numb_of_stacks - 1) //if i is the last stack in array - we should find place between last item and stack end
					diff += mas.SIZE;
				else
					diff += mas.beg_end[i + 1].begin;
				if (diff > 1) //if there is place
				{
					flag = true;
					for(int j = mas.beg_end[i].end; j >= mas.beg_end[stack_num+1].begin; j--) //shift array to the right
						mas.items[j + diff - 1] = mas.items[j];
					for (int j = i; j >= stack_num+1; j--) //and then change beging and end of each stack in the range
					{
						mas.beg_end[j].begin += diff - 1;
						mas.beg_end[j].end += diff - 1;
					}
				}
				i++;
			}
		}
	}
	if (flag) //if we freed space - we can item
	{
		mas.items[end()++] = item;
		return true;
	}
	return false;
}

template<typename T>
bool stack<T>::pop(T & item)
{
	if (!empty()) //if stack isn't empty - we can pop into item
	{
		item = mas.items[begin()++];
		return true;
	}
	return false;
}
