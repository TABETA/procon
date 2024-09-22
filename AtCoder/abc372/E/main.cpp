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
template <typename T>
class UnionFind {
   public:
    UnionFind() = default;

    /// @brief Union-Find 木を構築します。
    /// @param n 要素数
    explicit UnionFind(size_t n) : m_parentsOrSize(n, -1), m_groups(n) {
        rep(i, n) { m_groups[i].emplace(i); }
    }

    /// @brief 頂点 i の root のインデックスを返します。
    /// @param i 調べる頂点のインデックス
    /// @return 頂点 i の root のインデックス
    T find(T i) {
        if (m_parentsOrSize[i] < 0) {
            return i;
        }

        // 経路圧縮
        return (m_parentsOrSize[i] = find(m_parentsOrSize[i]));
    }

    /// @brief a のグループと b のグループを統合します。
    /// @param a 一方のインデックス
    /// @param b 他方のインデックス
    void merge(T a, T b) {
        a = find(a);
        b = find(b);

        if (a != b) {
            // union by size (小さいほうが子になる）
            if (-m_parentsOrSize[a] < -m_parentsOrSize[b]) {
                std::swap(a, b);
            }

            m_parentsOrSize[a] += m_parentsOrSize[b];
            set<T, greater<T>> s;
            while (s.size() < 10 && m_groups[a].size() + m_groups[b].size() > 0) {
                T va = m_groups[a].size() != 0 ? *m_groups[a].begin() : -1;
                T vb = m_groups[b].size() != 0 ? *m_groups[b].begin() : -1;
                if(va > vb){
                    s.emplace(va);
                    m_groups[a].erase(va);
                } else {
                    s.emplace(vb);
                    m_groups[b].erase(vb);
                }
            }
            m_groups[a].swap(s);
            m_parentsOrSize[b] = a;
        }
    }

    set<T, greater<T>> group(T node) { return m_groups[find(node)]; }

    /// @brief a と b が同じグループに属すかを返します。
    /// @param a 一方のインデックス
    /// @param b 他方のインデックス
    /// @return a と b が同じグループに属す場合 true, それ以外の場合は false
    bool isSame(T a, T b) { return (find(a) == find(b)); }

    /// @brief i が属するグループの要素数を返します。
    /// @param i インデックス
    /// @return i が属するグループの要素数
    T size(T i) { return -m_parentsOrSize[find(i)]; }

   private:
    // m_parentsOrSize[i] は i の 親,
    // ただし root の場合は (-1 * そのグループに属する要素数)
    std::vector<T> m_parentsOrSize;
    vector<set<T, greater<T>>> m_groups;
};
int main() {
    CIN(ll, N);
    CIN(ll, Q);
    vector to(N, set<ll, greater<ll>>{});
    rep(i, N) { to[i].emplace(i); }
    UnionFind<ll> uf(N);
    rep(i, Q) {
        CIN(ll, X);
        CIN(ll, a);
        --a;
        CIN(ll, b);
        --b;
        if (X == 1) {
            uf.merge(a, b);
        } else {
            auto g = uf.group(a);
            if ((ll)g.size() < b + 1) {
                cout << -1 << endl;
            } else {
                cout << *next(g.begin(), b) + 1 << endl;
            }
        }
    }
    return 0;
}
