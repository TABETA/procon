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
using namespace boost;
using namespace std;


static auto solve = [](const vector<vector<int> >& in)->string
{
	int result = 0;
	vector<int> merged = in[0];
	merged.insert(merged.end(), in[1].begin(), in[1].end());
	sort(merged.begin(), merged.end());
	size_t num = merged.size();
	for (size_t i = 0; i < num-1; ++i)
	{
		if (result == 0)
		{
			if (merged[i] == merged[i + 1])
			{
				result = merged[i];
			}
		}
		else
		{
			if (merged[i] == merged[i + 1])
			{
				return "Bad magician!";
			}
		}

	}
	if (result == 0)
	{
		return "Volunteer cheated!";
	}
	else
	{
		return lexical_cast<string>(result);
	}

};

int main(int argv, char* argc[])
{
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; ++i)
	{
		vector<vector<int> > choosen(2);
		for (auto &v: choosen)
		{
			v.resize(4);
			int row;
			cin >> row;
			for (int j = 0; j < 4; ++j)
			{
				if (j == row-1)
				{
					cin >> v[0] >> v[1] >> v[2] >> v[3];
				}
				else
				{
					int temp;
					cin >> temp >> temp >> temp >>temp;
				}

			}
		}
		cout << "Case #" << i+1 << ": " << solve(choosen) << endl;

	}

	return 0;
}