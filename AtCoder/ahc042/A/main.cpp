#ifdef _MSVC_LANG
#include <float.h>
#include <limits.h>
#include <stdio.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#else
#include <bits/stdc++.h>
#endif

using namespace std;

// clang-format off
/* accelration */
// 高速バイナリ生成
#ifndef _DEBUG
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
struct Fast {Fast() {std::cin.tie(0); ios::sync_with_stdio(false);}} fast;
#endif

/* alias */
using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<long>;
using vll = vector<long long>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvll = vector<vll>;
using vs = vector<string>;
using pii = pair<int, int>;

const int inf = 1001001001;
const ll linf = 1001001001001001001ll;

/* define short */
#define CIN(type, name) type name; cin >> name;
#define pb push_back
#define all(obj) (obj).begin(), (obj).end()
#define YESNO(bool) if(bool){cout<<"YES"<<endl;}else{cout<<"NO"<<endl;}
#define yesno(bool) if(bool){cout<<"yes"<<endl;}else{cout<<"no"<<endl;}
#define YesNo(bool) if(bool){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}
#define sb(var,l,r) {var[l].pb(r); var[r].pb(l);}

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i,n) for(ll i=n-1;i>=0;i--)
#define rrepd(i,n) for(ll i=n;i>=1;i--)
#define repr(i, n) for(auto&& i: n)


/* func */
inline int in_int() {int x; cin >> x; return x;}
inline ll in_ll() {ll x; cin >> x; return x;}
inline string in_str() {string x; cin >> x; return x;}
// search_length: 走査するベクトル長の上限(先頭から何要素目までを検索対象とするか、1始まりで)
template <typename T> inline bool vector_finder(std::vector<T> vec, T element, unsigned int search_length) {
    auto itr = std::find(vec.begin(), vec.end(), element);
    size_t index = std::distance( vec.begin(), itr );
    if (index == vec.size() || index >= search_length) {return false;} else {return true;}
}
template <typename T> inline void print(const vector<T>& v, string s = " ")
    {rep(i, v.size()) cout << v[i] << (i != (ll)v.size() - 1 ? s : "\n");}
template <typename T, typename S> inline void print(const pair<T, S>& p)
    {cout << p.first << " " << p.second << endl;}
template <typename T> inline void print(const T& x) {cout << x << "\n";}
template <typename T, typename S> inline void print(const vector<pair<T, S>>& v)
    {for (auto&& p : v) print(p);}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
        os << v[i] << (i + 1 != (int)v.size() ? " " : "");
    }
    return os;
}
// 第一引数と第二引数を比較し、第一引数(a)をより大きい/小さい値に上書き
template <typename T> inline bool chmin(T& a, const T& b) {bool compare = a > b; if (a > b) a = b; return compare;}
template <typename T> inline bool chmax(T& a, const T& b) {bool compare = a < b; if (a < b) a = b; return compare;}

namespace std{
    template<>
    class hash<pair<ll,ll>>{
        public:
        size_t operator () ( const pair<ll,ll> &p ) const{
            auto hash1 = hash<ll>{}(p.first);
            auto hash2 = hash<ll>{}(p.second);
            return hash1 ^ hash2;
        }
    };
}

// clang-format on
using P = pair<ll, ll>;
static void debug(const char* format, ...) {
#if 0
    va_list args;
    va_start(args, format);
    char buffer[65535];
    vsnprintf(buffer, sizeof(buffer), format, args);
    cout << buffer;
    va_end(args);
#else
    (void)format;
#endif
}

struct Timer {
    Timer(ll msLimit) : msLimit(msLimit), start(chrono::system_clock::now()) {}
    const ll msLimit;
    const chrono::system_clock::time_point start;
    auto getMilliSeconds() const {
        return chrono::duration_cast<chrono::milliseconds>(
                   chrono::system_clock::now() - start)
            .count();
    };
    bool isIntime() {
        auto msElapsed = getMilliSeconds();
        bool ok = msLimit > 0 ? msElapsed < msLimit : true;
        if (!ok) debug("# timeout\n");
        return ok;
    };
};
using P = pair<ll, ll>;
using T = tuple<ll, char, P>;

class Solver {
    ll limit;
    ll N;
    vs S;
    Timer timer;

   public:
    Solver(ll N, vs&& S, Timer&& timer) : N(N), S(S), timer(timer) {}
    ~Solver() {}
    void solve() {
        auto detourX = [](const vs& S, ll y, ll x) {
            ll dx = linf;
            for (ll nx = x; nx < (ll)S.size(); ++nx) {
                if (S[y][nx] != 'o') {
                    chmin(dx, abs(nx - x));
                    break;
                }
            }
            for (ll nx = x; nx >= 0; --nx) {
                if (S[y][nx] != 'o') {
                    chmin(dx, abs(nx - x));
                    break;
                }
            }
            return dx;
        };
        auto detourY = [](const vs& S, ll y, ll x) {
            ll dy = linf;
            for (ll ny = y; ny < (ll)S.size(); ++ny) {
                if (S[ny][x] != 'o') {
                    chmin(dy, abs(ny - y));
                    break;
                }
            }
            for (ll ny = y; ny >= 0; --ny) {
                if (S[ny][x] != 'o') {
                    chmin(dy, abs(ny - y));
                    break;
                }
            }
            return dy;
        };
        while (true) {
            auto getOni = [&](const vs& S) {
                deque<T> oni;
                auto calc = [&](T oni) {
                    auto [cost, dir, p] = oni;
                    auto [y, x] = p;
                    if (chmin(cost, [&]() {
                            ll cost = y + 1;
                            for (ll i = y; i >= 0; --i) {
                                if (S[i][x] == 'o') {
                                    cost += detourX(S, i, x);
                                }
                            }
                            return cost;
                        }())) {
                        dir = 'U';
                    }
                    if (chmin(cost, [&]() {
                            ll cost = N - y;
                            for (ll i = y; i < N; ++i) {
                                if (S[i][x] == 'o') {
                                    cost += detourX(S, i, x);
                                }
                            }
                            return cost;
                        }())) {
                        dir = 'D';
                    }
                    if (chmin(cost, [&]() {
                            ll cost = x + 1;
                            for (ll j = x; j >= 0; --j) {
                                if (S[y][j] == 'o') {
                                    cost += detourY(S, y, j);
                                }
                            }
                            return cost;
                        }())) {
                        dir = 'L';
                    }
                    if (chmin(cost, [&]() {
                            ll cost = N - x;
                            for (ll j = x; j < N; ++j) {
                                if (S[y][j] == 'o') {
                                    cost += detourY(S, y, j);
                                }
                            }
                            return cost;
                        }())) {
                        dir = 'R';
                    }
                    return T(cost, dir, p);
                };
                rep(i, N) {
                    rep(j, N) {
                        if (S[i][j] == 'x') {
                            oni.emplace_back(linf, ' ', P(i, j));
                        }
                    }
                }
                if (oni.size() != 0) {
                    rep(_, oni.size()) { oni[_] = calc(oni[_]); }
                    ranges::sort(oni);
                }
                return oni;
            };
            auto oni = getOni(S);
            if (oni.size() == 0) break;
            auto [cost, dir, p] = oni[0];
            auto shift = [&](vs S, char dir, ll distance, ll c) {
                if (dir == 'U') {
                    rep(i, N - distance) { S[i][c] = S[i + distance][c]; }
                    reps(i, N - distance, N) { S[i][c] = '.'; }
                }
                if (dir == 'D') {
                    for (ll i = N - 1; i >= distance; --i) {
                        S[i][c] = S[i - distance][c];
                    }
                    rep(i, distance) { S[i][c] = '.'; }
                }
                if (dir == 'L') {
                    rep(j, N - distance) { S[c][j] = S[c][j + distance]; }
                    reps(j, N - distance, N) { S[c][j] = '.'; }
                }
                if (dir == 'R') {
                    for (ll j = N - 1; j >= distance; --j) {
                        S[c][j] = S[c][j - distance];
                    }
                    rep(j, distance) { S[c][j] = '.'; }
                }
                return S;
            };
            auto [y, x] = p;
            bool ok = false;
            if (dir == 'U') {
                ll i = y;
                while(S[0][x] != 'o' && i>=0){
                    printf("%c %lld\n", dir, x);
                    S = shift(S, dir, 1, x);
                    ok = true;
                    --i;
                }
            }
            if (dir == 'D') {
                ll i = y;
                while(S[N-1][x] != 'o' && i<N){
                    printf("%c %lld\n", dir, x);
                    S = shift(S, dir, 1, x);
                    ok = true;
                    ++i;
                }
            }
            if (dir == 'L') {
                ll i = x;
                while(S[y][0] != 'o' && i>=0){
                    printf("%c %lld\n", dir, y);
                    S = shift(S, dir, 1, y);
                    ok = true;
                    --i;
                }
            }
            if (dir == 'R') {
                ll i = x;
                while(S[y][N-1] != 'o' && i < N){
                    printf("%c %lld\n", dir, y);
                    S = shift(S, dir, 1, y);
                    ok = true;
                    ++i;
                }
            }
            if (!ok) {
                queue<vs> Q;
                Q.emplace(S);
                using Route = vector<pair<char, ll>>;
                map<vs, Route> used;
                while (!Q.empty()) {
                    auto s = Q.front();
                    Q.pop();
                    auto ok = [](const vs& s, char dir, ll y, ll x) {
                        if (dir == 'U') {
                            for (ll i = y; i >= 0; --i) {
                                if (s[i][x] == 'o') return false;
                            }
                            return true;
                        }
                        if (dir == 'D') {
                            for (ll i = y; i < (ll)s.size(); ++i) {
                                if (s[i][x] == 'o') return false;
                            }
                            return true;
                        }
                        if (dir == 'L') {
                            for (ll j = x; j >= 0; --j) {
                                if (s[y][j] == 'o') return false;
                            }
                            return true;
                        }
                        if (dir == 'R') {
                            for (ll j = x; j < (ll)s.size(); ++j) {
                                if (s[y][j] == 'o') return false;
                            }
                            return true;
                        }
                        return false;
                    }(s, dir, y, x);
                    if (ok) {
                        for (auto&& [dir, v] : used[s]) {
                            printf("%c %lld\n", dir, v);
                            S = shift(S, dir, 1, v);
                        }
                        break;
                    }
                    if(dir == 'L' || dir == 'R')
                        rep(x, N) {
                            if (s[0][x] != 'o') {
                                auto ns = shift(s, 'U', 1, x);
                                if (!used.count(ns)) {
                                    auto r = used[s];
                                    r.emplace_back('U', x);
                                    used[ns] = r;
                                    Q.emplace(ns);
                                }
                            }
                            if (s[N - 1][x] != 'o') {
                                auto ns = shift(s, 'D', 1, x);
                                if (!used.count(ns)) {
                                    auto r = used[s];
                                    r.emplace_back('D', x);
                                    used[ns] = r;
                                    Q.emplace(ns);
                                }
                            }
                        }
                    if(dir == 'U' || dir == 'D')
                        rep(y, N) {
                            if (s[y][0] != 'o') {
                                auto ns = shift(s, 'L', 1, y);
                                if (!used.count(ns)) {
                                    auto r = used[s];
                                    r.emplace_back('L', y);
                                    used[ns] = r;
                                    Q.emplace(ns);
                                }
                            }
                            if (s[y][N - 1] != 'o') {
                                auto ns = shift(s, 'R', 1, y);
                                if (!used.count(ns)) {
                                    auto r = used[s];
                                    r.emplace_back('R', y);
                                    used[ns] = r;
                                    Q.emplace(ns);
                                }
                            }
                        }
                }
            }
        }
    }
    void solve1() {
        while (true) {
            auto getOni = [&](const vs& S) {
                deque<T> oni;
                auto calc = [&](T oni) {
                    auto [cost, dir, p] = oni;
                    auto [y, x] = p;
                    if (chmin(cost, [&]() {
                            for (ll i = y; i >= 0; --i) {
                                if (S[i][x] == 'o') return linf;
                            }
                            return y + 1;
                        }())) {
                        dir = 'U';
                    }
                    if (chmin(cost, [&]() {
                            for (ll i = y; i < N; ++i) {
                                if (S[i][x] == 'o') return linf;
                            }
                            return N - y;
                        }())) {
                        dir = 'D';
                    }
                    if (chmin(cost, [&]() {
                            for (ll j = x; j >= 0; --j) {
                                if (S[y][j] == 'o') return linf;
                            }
                            return x + 1;
                        }())) {
                        dir = 'L';
                    }
                    if (chmin(cost, [&]() {
                            for (ll j = x; j < N; ++j) {
                                if (S[y][j] == 'o') return linf;
                            }
                            return N - x;
                        }())) {
                        dir = 'R';
                    }
                    return T(cost, dir, p);
                };
                rep(i, N) {
                    rep(j, N) {
                        if (S[i][j] == 'x') {
                            oni.emplace_back(linf, ' ', P(i, j));
                        }
                    }
                }
                if (oni.size() != 0) {
                    rep(_, oni.size()) { oni[_] = calc(oni[_]); }
                    ranges::sort(oni);
                }
                return oni;
            };
            auto oni = getOni(S);
            if (oni.size() == 0) break;
            auto [cost, dir, p] = oni[0];
            auto shift = [&](vs S, char dir, ll distance, ll c) {
                if (dir == 'U') {
                    rep(i, N - distance) { S[i][c] = S[i + distance][c]; }
                    reps(i, N - distance, N) { S[i][c] = '.'; }
                }
                if (dir == 'D') {
                    for (ll i = N - 1; i >= distance; --i) {
                        S[i][c] = S[i - distance][c];
                    }
                    rep(i, distance) { S[i][c] = '.'; }
                }
                if (dir == 'L') {
                    rep(j, N - distance) { S[c][j] = S[c][j + distance]; }
                    reps(j, N - distance, N) { S[c][j] = '.'; }
                }
                if (dir == 'R') {
                    for (ll j = N - 1; j >= distance; --j) {
                        S[c][j] = S[c][j - distance];
                    }
                    rep(j, distance) { S[c][j] = '.'; }
                }
                return S;
            };
            if (cost == linf) {
                queue<vs> Q;
                Q.emplace(S);
                using Route = vector<pair<char, ll>>;
                map<vs, Route> used;
                while (!Q.empty()) {
                    auto s = Q.front();
                    Q.pop();
                    auto o = getOni(s);
                    auto [cost, dir, p] = o[0];
                    if (cost != linf) {
                        for (auto&& [dir, v] : used[s]) {
                            printf("%c %lld\n", dir, v);
                            S = shift(S, dir, 1, v);
                        }
                        break;
                    }
                    rep(x, N) {
                        if (s[0][x] != 'o') {
                            auto ns = shift(s, 'U', 1, x);
                            if (!used.count(ns)) {
                                auto r = used[s];
                                r.emplace_back('U', x);
                                used[ns] = r;
                                Q.emplace(ns);
                            }
                        }
                        if (s[N - 1][x] != 'o') {
                            auto ns = shift(s, 'D', 1, x);
                            if (!used.count(ns)) {
                                auto r = used[s];
                                r.emplace_back('D', x);
                                used[ns] = r;
                                Q.emplace(ns);
                            }
                        }
                    }
                    rep(y, N) {
                        if (s[y][0] != 'o') {
                            auto ns = shift(s, 'L', 1, y);
                            if (!used.count(ns)) {
                                auto r = used[s];
                                r.emplace_back('L', y);
                                used[ns] = r;
                                Q.emplace(ns);
                            }
                        }
                        if (s[y][N - 1] != 'o') {
                            auto ns = shift(s, 'R', 1, y);
                            if (!used.count(ns)) {
                                auto r = used[s];
                                r.emplace_back('R', y);
                                used[ns] = r;
                                Q.emplace(ns);
                            }
                        }
                    }
                }
            } else {
                auto [y, x] = p;
                rep(i, cost) {
                    if (dir == 'U' || dir == 'D') {
                        printf("%c %lld\n", dir, x);
                    } else {
                        printf("%c %lld\n", dir, y);
                    }
                }
                if (dir == 'U' || dir == 'D') {
                    S = shift(S, dir, cost, x);
                } else {
                    S = shift(S, dir, cost, y);
                }
            }
        }
    }
};
#ifndef TIMELIMIT
constexpr ll msLimit = 1800;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    ll N;
    cin >> N;
    vs S(N);
    rep(i, N) { cin >> S[i]; }
    Solver solver(N, move(S), move(timer));
    solver.solve();
    return 0;
}
