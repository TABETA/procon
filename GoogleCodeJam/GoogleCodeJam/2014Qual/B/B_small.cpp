#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
//#include <boost/format.hpp>
//#include <boost/tokenizer.hpp>
//#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
using namespace boost;
using namespace std;
#include <float.h>

double calc(double c, double f, double x, int rep)
{
	double result = 0;
	double prod = 2;
	for (int i = 0; i<rep; ++i)
	{
		//sec[0] =												x / (prod + f * 0);
		//sec[1] = c / (prod + f * 0) +							x / (prod + f * 1);
		//sec[2] = c / (prod + f * 0) + c / (prod + f * 1) +	x / (prod + f * 2);
		result += c / (prod + f * i);
	}
	result += x / (prod + f * rep);
	return result;
}

static auto solve = [](double c, double f, double x)
{
	double pre = DBL_MAX;
	double cookies = 0;
	for (int j = 0;; ++j)
	{
		double result = calc(c, f, x, j);
		if (pre < result)
		{
			result = pre;
			return result;
		}
		else
		{
			pre = result;
		}
	}

};

int main(int argv, char* argc[])
{
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; ++i)
	{
		double c, f, x;
		cin >> c >> f >> x;
		cout << "Case #" << i+1 << ": " << format("%.7lf") % solve(c, f, x) << endl;

	}

	return 0;
}