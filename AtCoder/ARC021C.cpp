#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
//#include <boost/format.hpp>
//#include <boost/tokenizer.hpp>
//#include <boost/foreach.hpp>
//#include <boost/lexical_cast.hpp>
//using namespace boost;
using namespace std;

template<int n>
class Human
{
	enum { leg = n };
public:
	int legNum(int num)
	{
		static int result[1500];
		if(result[num] == 0)
			result[num] = num * leg;
		return result[num];
	}
};


static auto solve = [](int n, int m)
{
	
	Human<2> adult;
	Human<3> elder;
	Human<4> child;
	for (int a = 0; a <= n; ++a)
	{
		for (int e = 0; e <= n; ++e)
		{
			for (int c = 0; c <= n;++c)
			{
				if (a + e + c == n)
				{
					if (adult.legNum(a) + elder.legNum(e) + child.legNum(c) == m)
					{
						cout << a << " ";
						cout << e << " ";
						cout << c << endl;
						return;
					}
				}
			}
		}
	}
	cout << "-1 -1 -1" << endl;
};

int main(int argv, char* argc[])
{
	int n, m;
	cin >> n >> m;
	solve(n, m);

	return 0;
}


