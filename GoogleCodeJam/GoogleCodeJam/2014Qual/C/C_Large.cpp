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

template<typename T>
static vector<T> transpose(const vector<T>& in)
{
	int iMax = in.size();
	int jMax = in[0].size();
	vector<T> out(jMax);
	for (auto &v: out) v.resize(iMax);
	for (int i = 0; i < iMax; ++i)
		for (int j = 0; j < jMax; ++j)
			out[j][i] = in[i][j];
	return out;
}

static vector<string> create(int s, int row, int col, int limit = 100)
{
	vector<string> result;
	int num = std::min(limit, col);
	for (int i = 0; i < row; ++i)
	{
		string temp(col, '*');
		for (int k = 0; k < num && s; ++k)
			temp[k] = '.', s--;
		result.push_back(temp);
	}
	result[0][0] = 'c';
	return result;
}
static auto solve = [](int r, int c, int mine)
{
	vector<string> result;
	int s = r * c - mine;
	if (r == 1 || c == 1 || mine == 0 || s == 1)
		return create(s, r, c);
	if (s == 2 || s == 3 || s == 5 || s == 7)
		return vector<string>(1, "Impossible");
	if( r == 2 || c == 2)
	{
		if(s % 2 == 0)
			return r==2?create(s, r, c, s/2):transpose(create(s, c, r, s/2));
		else
			return vector<string>(1, "Impossible");
	}
	if( s >= 8 || s == 4 || s == 6)
	{
		for(int i = 0; i < r; ++i) result.push_back(string(c, '*'));
		int i = 0;
		int div = min((s / 2) * 2, 2*c+2*r-4);
		s -= div;
		auto putEmpty = [&](int y, int x){if (result[y][x] != '.') result[y][x] = '.', div--; };
		while (div > 0)
		{
			if (i < r) putEmpty(i, 0), putEmpty(i, 1);
			if (div <= 0)break;
			if (i < c) putEmpty(0, i), putEmpty(1, i);
			if (!(i < r || i < c))
				break;
			else
				i++;

		}
		result[0][0] = 'c';
		for(int i = 2; i < r && s; ++i)
			for (int j = 2; j < c && s; ++j)
			{
				result[i][j] = '.', s--;
				if (s <= 0) return result;
			}
		return result;
	}
	return vector<string>(1, "Impossible");
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
		for (auto v : solve(r, c, m))
			cout << v << endl;

	}

	return 0;
}