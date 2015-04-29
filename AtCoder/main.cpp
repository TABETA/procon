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

class Timer
{
public:
	Timer() :start_(system_clock::now()){}
	double elapsed() const
	{
#ifndef TEST 
		duration<double> d = system_clock::now() - start_;
		return d.count();
#else
		return 0;
#endif
	}
private:
	system_clock::time_point start_;
};

//if (tim.elapsed() > 2)
//{
//	cout << -1 << endl;
//	return 1;
//}

void bfs(const vvc& s, vector<vector<pll> >& o, int h1, int h2, int w1, int w2, pii start)
{
	const pii m[4] = {
		MP(1, 0),
		MP(0, 1),
		MP(-1, 0),
		MP(0, -1)
	};
	queue<pii> q;
	q.push(start);
	o[start.X][start.Y] = MP(0LL, 0LL);
	while (!q.empty())
	{
		pii c = q.front(); q.pop();
		REP(i, 4)
		{
			int h = c.X + m[i].X;
			int w = c.Y + m[i].Y;
			if (
				BETWEEN(h1, h, h2) &&
				BETWEEN(w1, w, w2)
				)
			{
				pll cost = o[c.X][c.Y];
				switch (s[h][w])
				{
				case '.':
				case 'S':
				case 'G':
					cost.WHITE++;
					break;
				case '#':
					cost.BLACK++;
					break;
				}
				if (o[h][w].BLACK > cost.BLACK)
				{
					o[h][w] = cost;
					q.push(MP(h, w));
				}
			}
		}
	}

}
int solve(istream& cin, ostream& cout)
{
	INPUT(int, N);
	const int T = 1000002;

	vi imosu(T, 0);
	vi r(N + 1, INITVAL);
	imosu[1] = N;
	REP(_,N)
	{
		INPUT(int, s);
		imosu[s + 1]--;
	}
	imosu[0] = imosu[1];
	for (int i = 0; i < T; i++)
	{
		if(1 < i)imosu[i] += imosu[i - 1];
		if (r[imosu[i]] == INITVAL)
			r[imosu[i]] = i;
	}
	for (int i = 1; i < N + 1; i++)
	{
		if (r[i] == INITVAL)
			r[i] = r[i - 1];
	}

	INPUT(int, Q);
	REP(_, Q)
	{
		INPUT(int, k);
		cout << r[k] << endl;
	}

	return 0;
}

#ifndef TEST
int main(int argv, char* argc[])
{
	return solve(cin, cout);
}
#else
class TestCase
{
public:
	string input;
	string expect;
	TestCase(string in, string expc) :input(in), expect(expc){}
};
vector<TestCase> inputs;
#define ADDTEST(i,o) inputs.push_back(TestCase(i,o));
void createTestCase()
{
	ADDTEST(
		"15\n"
		"0\n"
		"0\n"
		"0\n"
		"1\n"
		"1\n"
		"2\n"
		"3\n"
		"4\n"
		"5\n"
		"6\n"
		"6\n"
		"6\n"
		"8\n"
		"9\n"
		"10\n"
		"3\n"
		"0\n"
		"4\n"
		"12\n"
		,
		"11\n"
		"7\n"
		"0\n"
		);
	ADDTEST(
		"9\n"
		"3\n"
		"3\n"
		"3\n"
		"2\n"
		"2\n"
		"2\n"
		"1\n"
		"1\n"
		"1\n"
		"1\n"
		"4\n"
		,
		"3\n"
		);
	ADDTEST(
		"4\n"
		"0\n"
		"0\n"
		"0\n"
		"0\n"
		"1\n"
		"0\n"
		,
		"0\n"
		);
}
int main(int argv, char* argc[])
{
	createTestCase();
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		cout << "Case " << i + 1 << " is ";
		istringstream iss(inputs[i].input);
		ostringstream oss;
		solve(iss, oss);
		string actual = oss.str();
		if (actual == inputs[i].expect)
		{
			cout << "OK" << endl;
		}
		else
		{
			cout << "NG" << endl;
			cout << "\texpected :" << inputs[i].expect << endl;
			cout << "\tactual   :" << actual << endl;
		}
	}
	return 0;
}
#endif