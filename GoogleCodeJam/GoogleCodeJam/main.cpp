#include <map>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
#include <stack>
#include <float.h>
#include <cmath>
using namespace std;

//#include <boost/tokenizer.hpp>
//#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/format.hpp>
//#include <boost/multiprecision/cpp_int.hpp>
using namespace boost;
//using namespace boost::multiprecision;

#define X first
#define Y second

static auto solve = [](int a, int b, int k)
{
	int res = 0;
	res += k*(a - 1);
	res += k*(b - 1);
	vector<int> va;
	vector<int> vb;
	int mask = 0;
	for (int i = 0; i < k; ++i)
		mask |= i;
	for (int i = 0; i < a; ++i)
	{
		if (i&mask)
			va.push_back(i);
	}
	for (int i = 0; i < b; ++i)
	{
		if (i&mask)
			vb.push_back(i);
	}
	for (auto i:va)
	{
		for (auto j:vb)
		{
			res += (i&j) < k;
		}
	}
	return res;
};

int main(int argv, char* argc[])
{
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; ++i)
	{
		int a, k, b;
		cin >> a >> b >> k;
		cout << "Case #" << i + 1 << ": " << solve(a, b, k) << endl;

	}
	return 0;
}