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


static auto solve = [](double c, double f, double x)
{
	double a = 2;
	double curRemain = (x - c) / a;
	double result = c / a;
	for (int i = 1;; ++i)
	{
		double nextHalf = c / (a + f * i);
		double nextRemain = (x - c) / (a + f * i);
		if (curRemain < (nextHalf + nextRemain))
			return result + curRemain;
		else
		{
			result += nextHalf;
			curRemain = nextRemain;
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