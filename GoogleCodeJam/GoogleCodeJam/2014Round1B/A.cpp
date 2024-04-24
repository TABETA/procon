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

#define Key first;
#define Val second;
#define CONSTRAINT 100

static bool isFeglaWon(int n, vector<string> s)
{
	s[0].erase(unique(s[0].begin(), s[0].end()), s[0].end());
	for (int i = 1; i < n; ++i)
	{
		s[i].erase(unique(s[i].begin(), s[i].end()), s[i].end());
		if (s[0] != s[i])
			return true;
	}
	return false;
}

static auto solve = [](int n, vector<string>& s)
{
	map<char, int> base;
	vector<pair<char, int> > m[CONSTRAINT];
	vector<string> temp;
	if (isFeglaWon(n, s))
		return string("Fegla Won");
	for (int i = 0; i < n; ++i)
		for (auto v : s[i])
		{
			if (m[i].empty() || (v != m[i].back().first))
				m[i].push_back(make_pair(v, 1));
			else
				m[i].back().second++;
		}
	int ret = 0;
	for (int i = 0; i<m[0].size(); i++)
	{
		int x[CONSTRAINT];
		for (int j = 0; j<n; j++)
			x[j] = m[j][i].second;
		sort(x, x + n);
		for (int j = 0, k = n - 1; j<k; j++, k--)
			ret += x[k] - x[j];
	}

	return lexical_cast<string>(ret);
};

int main(int argv, char* argc[])
{
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; ++i)
	{
		int n;
		cin >> n;
		vector<string> s(n);
		for (auto &v : s)
			cin >> v;
		cout << "Case #" << i + 1 << ": " << solve(n, s) << endl;

	}
	return 0;
}