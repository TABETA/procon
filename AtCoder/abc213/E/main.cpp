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

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
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
#define all(obj) (obj).begin(), (obj).end()
#define YESNO(bool) if(bool){cout<<"YES"<<endl;}else{cout<<"NO"<<endl;}
#define yesno(bool) if(bool){cout<<"yes"<<endl;}else{cout<<"no"<<endl;}
#define YesNo(bool) if(bool){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i,n) for(ll i=n-1;i>=0;i--)
#define rrepd(i,n) for(ll i=n;i>=1;i--)
#define repr(i, n) for(auto&& i: n)

/* debug */
#define debug(x) cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << endl;

/* func */
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
template<typename T>
pair<T,T> operator+(const pair<T,T>& lhs, const pair<T,T> rhs){
    return pair<T,T>{lhs.first+rhs.first, lhs.second+rhs.second};
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
auto getNext(P cur, P next) {
    P diff = P{next.first - cur.first, next.second - cur.second};
    static map<P, char> dir = {
        {P{0, 1}, 'R'},
        {P{0, -1}, 'L'},
        {P{1, 0}, 'D'},
        {P{-1, 0}, 'U'},
    };
    vector<vector<P>> ret;
    auto f = [](P b) {
        auto [by, bx] = b;
        vector<P> ps;
        rep(i, 2) {
            rep(j, 2) { ps.emplace_back(by + i, bx + j); }
        }
        return ps;
    };
    switch (dir[diff]) {
        case 'U':
            ret.push_back(f(P{next.first - 1, next.second}));
            ret.push_back(f(P{next.first - 1, next.second - 1}));
            break;
        case 'D':
            ret.push_back(f(P{next.first, next.second}));
            ret.push_back(f(P{next.first, next.second - 1}));
            break;
        case 'R':
            ret.push_back(f(P{next.first, next.second}));
            ret.push_back(f(P{next.first - 1, next.second}));
            break;
        case 'L':
            ret.push_back(f(P{next.first, next.second - 1}));
            ret.push_back(f(P{next.first - 1, next.second - 1}));
            break;
    }
    return ret;
};
int main() {
    CIN(ll, H);
    CIN(ll, W);
    auto next_adjacents = [&](ll r, ll c) {
        vector<P> ret;
        for (auto&& q : {
                 P{r - 1, c},
                 P{r + 1, c},
                 P{r, c - 1},
                 P{r, c + 1},
             }) {
            auto [y, x] = q;
            if (y < 0 || y >= H || x < 0 || x >= W) continue;
            ret.push_back(q);
        }
        return ret;
    };
    using TS = vs;
    TS S(H);
    rep(i, H) {
        cin >> S[i];
    }
    vvll D = vvll(H, vll(W, linf));
    struct T {
        ll cost;
        P cur;
    };
    auto dijkstra = [&]() {
        deque<T> q;
        D[0][0] = 0;
        q.emplace_back(0, P{0, 0});
        while (!q.empty()) {
            auto [d, cur] = q.front();
            q.pop_front();
            auto [y, x] = cur;
            if (D[y][x] < d) continue;
            if (y == H - 1 && x == W - 1) {
                cout << D[y][x] << endl;
                return;
            }
            for (auto&& [ny, nx] : next_adjacents(y, x)) {
                if (S[ny][nx] == '#') {
                    auto nd = d + 1;
                    for (auto&& np : getNext(P{y, x}, P{ny, nx})) {
                        for (auto&& [ny, nx] : np) {
                            if (ny < 0 || ny >= H || nx < 0 || nx >= W)
                                continue;
                            if (chmin(D[ny][nx], nd)) {
                                q.emplace_back(nd, P{ny, nx});
                            }
                        }
                    }
                } else {
                    if (chmin(D[ny][nx], d)) {
                        q.emplace_front(d, P{ny, nx});
                    }
                }
            }
        }
    };
    dijkstra();
    return 0;
}
