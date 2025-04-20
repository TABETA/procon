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
class UnionFind {
   public:
    UnionFind() = default;

    /// @brief Union-Find 木を構築します。
    /// @param n 要素数
    explicit UnionFind(size_t n) : p(n, -1), dif(n) {}

    /// @brief 頂点 i の root のインデックスを返します。
    /// @param i 調べる頂点のインデックス
    /// @return 頂点 i の root のインデックス
    ll root(ll a) {
        if (p[a] < 0) return a;
        ll b = p[a];
        p[a] = root(b);
        dif[a] += dif[b];
        return p[a];
    }

    /// @brief a のグループと b のグループを統合します。
    /// @param a 一方のインデックス
    /// @param b 他方のインデックス
    bool merge(ll a, ll b, ll w) {
        root(a);
        root(b);
        w = w + dif[a] - dif[b];
        a = root(a);
        b = root(b);
        if (a == b) return w == 0;
        // union by size (小さいほうが子になる）
        if (-p[a] < -p[b]) {
            std::swap(a, b);
            w = -w;
        }
        p[a] += p[b];
        p[b] = a; dif[b] = w;
        return true;
    }
   private:
    // p[i] は i の 親,
    // ただし root の場合は (-1 * そのグループに属する要素数)
    std::vector<ll> p;
    vll dif;
};
int main() {
    long long N;
    std::cin >> N;
    long long Q;
    std::cin >> Q;
    UnionFind uf(N);
    std::vector<long long> a(Q);
    std::vector<long long> b(Q);
    std::vector<long long> d(Q);
    set<ll> ans;
    for (int i = 0; i < Q; i++) {
        std::cin >> a[i];
        a[i]--;
        std::cin >> b[i];
        b[i]--;
        std::cin >> d[i];
        if(uf.merge(a[i], b[i], d[i])){
            ans.emplace(i);
        }
    }
    repr(a, ans) { cout << a + 1 << " "; }
    return 0;
}
