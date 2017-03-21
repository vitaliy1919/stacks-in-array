// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


// many_stacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stack.h"

int main()
{
	array_s<int> f(3);
	stack<int> a(f), b(f), c(f), d(f);
	for (int i = 0; i < 98; i++)
	{
		if (!b.push(2*i))
			cout << "error!\n";
//		b.push(3 * i);
	}
	int count = 0;
	cout <<"a.size(): "<< a.size() << "\nb.size()=" << b.size() << endl;
	while (!a.empty())
	{
		int h;
		a.pop(h);
		count++;
		cout << "a" << count << ": " << h << endl;
		//b.pop(h);
		//cout << "b" << count << ": " << h << endl;
	}
	int i = 0;
	for (const int *x = f.it(); x < f.it() + 100; ++x,++i)
	{
		cout << i+1 << ": " << *x << endl;
	}
	system("pause");
    return 0;
}

