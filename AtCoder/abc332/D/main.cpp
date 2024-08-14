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

/* debug */
#define debug(x) cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << endl;

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
int main() {
    long long H;
    std::cin >> H;
    long long W;
    std::cin >> W;
    std::vector<std::vector<long long>> A(H, std::vector<long long>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            std::cin >> A[i][j];
        }
    }
    std::vector<std::vector<long long>> B(H, std::vector<long long>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            std::cin >> B[i][j];
        }
    }
    if (A == B) {
        cout << 0 << endl;
        return 0;
    }
    {
        vector mp(2, vector<map<ll, ll>>(H));
        rep(i, H) {
            rep(j, W) {
                mp[0][i][A[i][j]]++;
                mp[1][i][B[i][j]]++;
            }
        }
        ranges::sort(mp[0]);
        ranges::sort(mp[1]);
        if (mp[0] != mp[1]) {
            cout << -1 << endl;
            return 0;
        }
    }
    {
        vector mp(2, vector<map<ll, ll>>(W));
        rep(j, W) {
            rep(i, H) {
                mp[0][j][A[i][j]]++;
                mp[1][j][B[i][j]]++;
            }
        }
        ranges::sort(mp[0]);
        ranges::sort(mp[1]);
        if (mp[0] != mp[1]) {
            cout << -1 << endl;
            return 0;
        }
    }

    using P = pair<vvll, ll>;
    set<vvll> used;
    queue<P> Q;
    used.emplace(A);
    Q.emplace(A, 0);
    auto next_grids = [&](vvll& a) -> vector<vvll> {
        vector<vvll> results;
        auto swap_row = [&](ll r) { swap(a[r], a[r + 1]); };
        auto swap_col = [&](ll c) {
            rep(r, H) { swap(a[r][c], a[r][c + 1]); }
        };
        rep(i, H - 1) {
            swap_row(i);
            results.emplace_back(a);
            swap_row(i);
        }
        rep(i, W - 1) {
            swap_col(i);
            results.emplace_back(a);
            swap_col(i);
        }
        return results;
    };
    while (!Q.empty()) {
        auto [a, cnt] = Q.front();
        Q.pop();
        for (auto&& g : next_grids(a)) {
            if (used.count(g)) continue;
            if (g == B) {
                cout << cnt + 1 << endl;
                return 0;
            }
            used.emplace(g);
            Q.emplace(g, cnt + 1);
        }
    }
    return 0;
}
