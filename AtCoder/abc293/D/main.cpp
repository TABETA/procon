#ifdef _MSVC_LANG 
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

/* define short */
#define pb push_back
#define mp make_pair
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

template<typename T>
class UnionFind
{
public:

  UnionFind() = default;

  /// @brief Union-Find 木を構築します。
  /// @param n 要素数
  explicit UnionFind(size_t n)
    : m_parentsOrSize(n, -1) {}

  /// @brief 頂点 i の root のインデックスを返します。
  /// @param i 調べる頂点のインデックス
  /// @return 頂点 i の root のインデックス
  T find(T i)
  {
    if (m_parentsOrSize[i] < 0)
    {
      return i;
    }

    // 経路圧縮
    return (m_parentsOrSize[i] = find(m_parentsOrSize[i]));
  }
  T groups()
  {
    T count = 0;
    for(auto&& v: m_parentsOrSize){
        if (v < 0)
        {
            count++;
        }
    }
    return count;
  }

  /// @brief a のグループと b のグループを統合します。
  /// @param a 一方のインデックス
  /// @param b 他方のインデックス
  void merge(T a, T b)
  {
    a = find(a);
    b = find(b);

    if (a != b)
    {
      // union by size (小さいほうが子になる）
      if (-m_parentsOrSize[a] < -m_parentsOrSize[b])
      {
        std::swap(a, b);
      }

      m_parentsOrSize[a] += m_parentsOrSize[b];
      m_parentsOrSize[b] = a;
    }
  }

  /// @brief a と b が同じグループに属すかを返します。
  /// @param a 一方のインデックス
  /// @param b 他方のインデックス
  /// @return a と b が同じグループに属す場合 true, それ以外の場合は false
  bool isSame(T a, T b)
  {
    return (find(a) == find(b));
  }

  /// @brief i が属するグループの要素数を返します。
  /// @param i インデックス
  /// @return i が属するグループの要素数
  T size(T i)
  {
    return -m_parentsOrSize[find(i)];
  }

private:

  // m_parentsOrSize[i] は i の 親,
  // ただし root の場合は (-1 * そのグループに属する要素数)
  std::vector<T> m_parentsOrSize;
};

int main() {
    long long N;
    std::cin >> N;
    long long M;
    std::cin >> M;
    std::vector<long long> A(M);
    std::vector<std::string> B(M);
    std::vector<long long> C(M);
    std::vector<std::string> D(M);
    auto uf = UnionFind<ll>(N*2);
    rep(i,N){
        uf.merge(i+1, i+N+1);
    }
    ll X = 0;
    for(int i = 0 ; i < M ; i++){
        std::cin >> A[i];
        std::cin >> B[i];
        std::cin >> C[i];
        std::cin >> D[i];
        ll a = A[i] + (B[i]=="R" ? 0: N);
        ll c = C[i] + (D[i]=="R" ? 0: N);
        if(uf.isSame(a,c)){
            X++;
        }
        uf.merge(a,c);
    }
    ll Y = uf.groups() - X;
    cout << X << " " << Y << endl;
    return 0;
}
