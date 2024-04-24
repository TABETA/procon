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
static string str_repeat(int r, string s)
{
	string l = "";
	REP(_, r) l += s;
	return l;
}

static char mul(char l, char r, bool& b, bool bb)
{
	const char c[4][4] =
	{	// 1	i    j    k
		{ 'h', 'i', 'j', 'k' }, //1
		{ 'i', 'h', 'k', 'j' }, //i
		{ 'j', 'k', 'h', 'i' }, //j
		{ 'k', 'j', 'i', 'h' }, //k
	};
	const bool u[4][4] =
	{	//1		i		j		k
		{ true,	true,	true,	true	}, //1
		{ true,	false,	true,	false	}, //i
		{ true,	false,	false,	true	}, //j
		{ true,	true,	false,	false	}, //k
	};
	int row = l - 'h';
	int col = r - 'h';
	b = b == (u[row][col] == bb);
	return c[row][col];
}

static char div(char l, char r, bool& b)
{
	const char c[4][4] =
	{	// 1	i    j    k
		{ 'h', 'i', 'j', 'k' },
		{ 'i', 'h', 'k', 'j' },
		{ 'j', 'k', 'h', 'i' },
		{ 'k', 'j', 'i', 'h' },
	};
	const bool u[4][4] =
	{	//1		i		j		k
		{ true, false, false, false },
		{ true, true, false, true },
		{ true, true, true, false },
		{ true, false, true, true },
	};
	int row = l - 'h';
	int col = r - 'h';
	b = b == u[row][col];
	return c[row][col];
}
static auto solve = []()
{
	INPUT(int, L);
	INPUT(int, X);
	INPUT(string, l);
	
	char a[3] = { 'h', 'h', 'h' };
	char b[3] = { 'i', 'j', 'k' };
	bool c[3] = { true, true, true };
	set<char> d;
	for (int i = 0; i < l.size(); ++i)
	{
		a[0] = mul(a[0], l[i], c[0], true);
		d.insert(l[i]);
	}
	if (d.size() < 2) return "NO";
	char t = a[0];
	bool bb = c[0];
	REP(i, X)
	{
		a[0] = mul(a[0], t, c[0], bb);

	}
	if (a[0] != 'h' || c[0])return "NO";

	return "YES";
};
int main(int argv, char* argc[])
{
	INPUT(int , T);
	for (int i = 0; i < T; ++i)
	{
		cout << "Case #" << i + 1 << ": " << solve() << endl;
	}
	return 0;
}
