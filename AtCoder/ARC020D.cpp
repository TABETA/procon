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

static int popcnt(int x)
{
	int count;
	for (count = 0; x; ++count)x &= x - 1;
	return count;
}
static int calcDistance(int i, int j, vector<int>& d)
{
	static int costMap[100][100];
	if (i > j)
	{
		swap(i, j);
	}
	if (costMap[i][j] == 0)
	{
		int cost = 0;
		for (int k = i; k < j; ++k)
		{
			cost += d[k];
		}
		costMap[i][j] = cost;
	}
	return costMap[i][j];
}
static auto solve = [](int m, int k, vector<int>& d)
{
	int result = 0;
	int townNum = d.size()+1;
	for (int i = 3; i < (1<<townNum); ++i)
	{
		if (popcnt(i) == k)
		{
			vector<int> temp;
			for (int j = 0;temp.size() < k;++j)
			{
				if (i & (1 << j))
				{
					temp.push_back(j);
				}
			}
			do
			{
				int endNum = temp.size() - 1;
				int cost = 0;
				for (int j =0; j < endNum; ++j)
				{
					cost += calcDistance(temp[j], temp[j + 1], d);
				}
				if (cost % m == 0)
					++result;
			} while (next_permutation(temp.begin(), temp.end()));
		}
	}
	return result % 1000000007;
};

int main(int argv, char* argc[])
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> d(n-1);
	for (auto &i : d)
		cin >> i;
	cout << solve(m, k, d) << endl;
	return 0;
}


