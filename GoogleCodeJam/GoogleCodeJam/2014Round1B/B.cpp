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
#include <queue>
#include <utility>
using namespace std;

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/format.hpp>
//#include <boost/multiprecision/cpp_int.hpp>
using namespace boost;
//using namespace boost::multiprecision;

#include <tuple>
#include <sstream>
#include <queue>
#include <map>
#include <numeric>
#include <list>
#include <limits.h>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
#include <stack>
#include <float.h>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define INITVAL INT_MAX
#define REP(i, N) for(int i = 0; i < N; ++i)
#define MP(a, b) make_pair(a, b)
#define X first
#define Y second
#define WHITE first
#define BLACK second
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using vc = vector<char>;
using vvc = vector<vc>;
using vb = vector<bool>;
using vvb = vector<vb>;
#define INPUT(type, name) type name; cin >> name;

#define IN_H(h) (0 <= (h) && (h) < H)
#define IN_W(w) (0 <= (w) && (w) < W)
#define CELL(cell, h, w) (IN_H(h) && IN_W(w) ? cell[h][w] : INT_MAX)

#define BETWEEN(x1, x, x2) (x1 <= x && x < x2)
#define PUSH(x, y) (t[y][x] == 0){q.push(pii(x, y));t[y][x] = 1;}
#define sq(x) ((x)*(x))

#ifdef _MSC_VER
#include <intrin.h>
#include <stdint.h>
#define __builtin_popcount __popcnt
#define __builtin_ctz ctz
#define __builtin_clz clz

static uint32_t inline ctz(uint32_t x)
{
	unsigned long r = 0;
	_BitScanReverse(&r, x);
	return r;
}

static uint32_t inline clz(uint32_t x)
{
	unsigned long r = 0;
	_BitScanForward(&r, x);
	return r;
}

#endif


static auto solve = [](int a, int b)
{
	if (b%2 != 0)
		return string("impossible");
	map<pair<int,int>, int> ret;
	queue<pair<int, int> > q;
	pair<int, int> ip = MP(a,b);
	q.push(ip);
	ret[ip] = 0;
	while (!q.empty())
	{
		pair<int, int> cur = q.front(); q.pop();
		int gen = ret[cur];
		if (gen > 40)
			continue;
		if (cur.Y % 2 != 0) cur.X *= 2;
		else				cur.Y /= 2;
		if (cur.Y > cur.X)
		{
			for (int i = 1; i <= cur.X; ++i)
			{
				int x = i;
				int y = cur.Y;
				int temp = gcd(x, y);
				x /= temp;
				y /= temp;
				ip = MP(x, y);
				if (ret.find(ip) == ret.end())
				{
					q.push(ip);
					ret[ip] = gen + 1;
				}
			}
		}
		else
		{
			return lexical_cast<string>(gen + 1);
		}
	}
	return string("impossible");
};
int main(int argv, char* argc[])
{
	INPUT(int , T);
	for (int i = 0; i < T; ++i)
	{
		INPUT(int, S);
		vi k(S+1);
		for (auto& i : k)
			cin >> i;
		stringstream buf(temp);
		buf >> a >> b;
		cout << "Case #" << i + 1 << ": " << solve(a, b) << endl;
	}
	return 0;
}
