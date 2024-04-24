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
	vll S = vll(N+1);
	vll T = vll(N + 1);
	S[0] = 0; REP(i, N) cin >> S[i + 1];
	T[0] = 0; REP(i, N) cin >> T[i + 1];

	vvll E = vvll(N+1, vll(N + 1));
	vll V = vll(N + 1);
	V[0] = 0;
	REP(i, N + 1)REP(j, N + 1)E[i][j] = INT32_MAX;
	for (size_t i = 1; i < N+1; i++)
	{
		auto s = S[i];
		auto t = T[i];
		auto j = i + 1 == N + 1 ? 1 : i + 1;
		E[i][j] = s;
		T.push_back(t);
		E[0][i] = t;
	}
	auto c = [&](ll l, ll r) { return V[l] > V[r]; };
	priority_queue<ll, vll, decltype(c)> Q(c);

	Q.push(0);

	while (!Q.empty())
	{
		auto q = Q.top(); Q.pop();
		for (int i = 1; i < N + 1; i++)
		{
			if (i == q) continue;
			if (E[q][i] == INT32_MAX) continue;
			auto nc = V[q] + E[q][i];
			if (V[i] > nc)
			{
				V[i] = nc;
				Q.push(i);
			}
		}
	}
	for (size_t i = 1; i < N+1; i++)
		cout << V[i] << endl;

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
		"3\n4 1 5\n3 10 100\n"
		,
		"3\n7\n8"
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