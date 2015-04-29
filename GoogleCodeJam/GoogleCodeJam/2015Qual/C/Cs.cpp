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

static char mul(char l, char r, bool& b)
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
	b = b == u[row][col];
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
//static int isok(const string& a, char c, char& t, int i)
//{
//	bool u = true;
//	int s = a.size();
//	if (s == 1) return (a[0] == c);
//	for (int i = 1; i < s; ++i) u = u == mul(a[i - 1], a[i]);
//	return (a[s-1] == c && u);
//}

static auto solve = []()
{
	INPUT(int, L);
	INPUT(int, X);
	INPUT(string, l);
	l = str_repeat(X, l);
	int E = L*X;
	
	char a[3] = { 'h', 'h', 'h' };
	char b[3] = { 'i', 'j', 'k' };
	bool c[3] = { true, true, true };
	vi d[3];
	for (int i = 0; i < E; ++i)
	{
		a[0] = mul(a[0], l[i], c[0]);
		if (a[0] == b[0] && c[0])d[0].push_back(i);
	}
	if (a[0] != 'h' || c[0])return "NO";
	for (int k = E - 1; k > 0; --k)
	{
		a[2] = mul(l[k], a[2], c[2]);
		if (a[2] == b[2] && c[2])d[2].push_back(k);
	}
	sort(d[2].begin(), d[2].end());
	int I = d[0].size();
	int K = d[2].size();
	for (int i = 0; i < I; ++i)
	{
		for (int k = 0; k < K; ++k)
		{
			if (d[0][i] + 1 >= d[2][k]) continue;
			for (int j = d[0][i] + 1; j < d[2][k]; ++j)
			{
				a[1] = mul(a[1], l[j], c[1]);
				if (a[1] == b[1] && c[1])return "YES";
			}
		}
	}

	return "NO";
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
