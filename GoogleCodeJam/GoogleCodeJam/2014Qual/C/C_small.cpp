#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
#include <stack>
//#include <boost/tokenizer.hpp>
//#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <float.h>
using namespace boost;
using namespace std;
using namespace boost::multiprecision;

#if 0
static auto solve = [](int r, int c, int m)
{
	string result = "";
	int safe = r * c - m;
	if (safe == 1 || r == 1 || c == 1)
	{
		for (int i = 0; i < r*c; ++i)
		{
			if (i == 0)
				result += 'c';
			else if (--safe > 0)
				result += '.';
			else
				result += '*';
			if ((i + 1) % c == 0)
				result += '\n';
		}
	}
	else
	{
		switch (safe)
		{
		case 2:
		case 3:
		case 4:
		case 5:
		case 7:
			result = "Impossible\n";
			break;
		default:
			for (int i = 0; i < r*c; ++i)
			{
				if (i == 0)
					result += 'c';
				else if (--safe> 0)
					result += '.';
				else
					result += '*';
				if ((i + 1) % c == 0)
					result += '\n';
			}
			break;
		}
	}
	return result;
};
#endif


vector<vector<char> > create(int i, int r, int c)
{
	vector<vector<char> > b(r);
	for (auto &v : b)
		v.resize(c, '0');
	for (int j = 0; j < r*c; ++j)
	{
		if ((i&(1 << j)) != 0)
		{
			int y = j / c;
			int x = j%c;
			b[y][x] = '*';
		}
	}
	return b;
}

bool isValidCell(const vector<vector<char> >& b, int r, int c, int y, int x)
{
	if (!(x >= 0 && x < c))	return true;
	if (!(y >= 0 && y < r))	return true;
	if (!(b[y][x] != '*'))	return false;
	return true;
}

void pushCell(stack<pair<int, int> >& s, vector<vector<char> >& b, int r, int c, int y, int x)
{
	if (!(x >= 0 && x < c))	return;
	if (!(y >= 0 && y < r))	return;
	if (!(b[y][x] != '.'))	return;
	b[y][x] = '.';
	s.push(make_pair(y,x));
}

bool isSuccess(const vector<vector<char> >& b)
{
	for (auto v : b)
	{
		if (count(v.begin(), v.end(), '0') != 0)
			return false;

	}
	return true;
}

string validate(const vector<vector<char> >& b, int r, int c)
{
	size_t e = r*c;
	for (size_t i = 0; i < e; ++i)
	{
		vector<vector<char> > temp = b;
		stack<pair<int, int> > s;
		s.push(make_pair(i / c, i%c));
		while (!s.empty())
		{
			pair<int, int> t = s.top();
			s.pop();
			int y = t.first;
			int x = t.second;
			if (
				isValidCell(temp, r, c, y - 1, x - 1) &&
				isValidCell(temp, r, c, y - 1, x + 0) &&
				isValidCell(temp, r, c, y - 1, x + 1) &&
				isValidCell(temp, r, c, y + 0, x - 1) &&
				isValidCell(temp, r, c, y + 0, x + 0) &&
				isValidCell(temp, r, c, y + 0, x + 1) &&
				isValidCell(temp, r, c, y + 1, x - 1) &&
				isValidCell(temp, r, c, y + 1, x + 0) &&
				isValidCell(temp, r, c, y + 1, x + 1))
			{
				pushCell(s, temp, r, c, y - 1, x - 1);
				pushCell(s, temp, r, c, y - 1, x + 0);
				pushCell(s, temp, r, c, y - 1, x + 1);
				pushCell(s, temp, r, c, y + 0, x - 1);
				pushCell(s, temp, r, c, y + 0, x + 0);
				pushCell(s, temp, r, c, y + 0, x + 1);
				pushCell(s, temp, r, c, y + 1, x - 1);
				pushCell(s, temp, r, c, y + 1, x + 0);
				pushCell(s, temp, r, c, y + 1, x + 1);

			}
		}
		if (isSuccess(temp))
		{
			string result = "";
			temp[i / c][i%c] = 'c';
			for (auto v : temp)
				result += string(v.begin(), v.end()) + '\n';
			return result;
		}
	}
	return "Impossible\n";

}
static auto solve = [](int r, int c, int m)
{
	string result;
	if (r * c - m == 1)
	{
		string result = "";
		for (int i = 0; i < r; ++i)
		{
			string temp(c, '*');
			result += temp +'\n';
		}
		result[0] = 'c';
		return result;
	}

	for (int i = 0; i < (1 << r*c);++i)
	{
		if (__popcnt(i) == m)
		{
			vector<vector<char> > b = create(i, r, c);
			result = validate(b, r, c);
			if (result != "Impossible\n")
				break;
		}
	}
	return result;
};

int main(int argv, char* argc[])
{
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; ++i)
	{
		int r, c, m;
		cin >> r >> c >> m;
		cout << "Case #" << i + 1 << ":" << endl;
		cout << solve(r, c, m);

	}

	return 0;
}