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

auto solveByCumulativeSum(ll N, vll&& A) -> ll {
    vll S(N + 1);
    rep(i, N) { S[i + 1] = S[i] ^ A[i]; }
    ll ans = 0;
    for (ull k = 0; k < 31ull; ++k) {
        ull mask = 1ull << k;
        ll t = 0;
        ll f = 0;
        rep(i, N + 1) {
            if ((S[i] & mask) != 0) {
                t++;
            } else {
                f++;
            }
        }
        ans += t * f * mask;
    }
    ll minus = reduce(all(A));
    return ans - minus;
}

auto solveByDP(ll N, vll&& A) -> ll {
    ll ans = 0;
    rep(k, 30) {
        // DP[i番目のAが][j番目のセクションであるとき][セクション1に含まれるk桁目の1の個数が奇数かどうか]
        vector DP(3, vector(2, 0ll));
        DP[0][0] = 1;
        rep(i, N) {
            auto x = (A[i] >> k) & 1;
            vector pre(3, vector(2, 0ll));
            swap(DP, pre);
            rep(j, 3) {
                rep(nj, 3){
                    if(nj < j)continue;
                    if (x && nj == 1) {
                        // A[i]のk桁目のbitが立っていた場合、セクション1に含まれるk桁目の1の個数の偶奇はA[i-1]の時の結果から変化する
                        DP[nj][0] += pre[j][1];
                        DP[nj][1] += pre[j][0];
                    } else {
                        // A[i]のk桁目のbitが立っていた場合、セクション1に含まれるk桁目の1の個数の偶奇はA[i-1]の時の結果から変化しないので前回の値をkeep
                        // A[i]のk桁目のbitが立っていない場合、偶奇は変化しないので前回の値をkeep
                        DP[nj][0] += pre[j][0];
                        DP[nj][1] += pre[j][1];
                    }
                }
            }
        }
        ll now = (DP[1][1]+DP[2][1])*(1ull<<k);
        ans += now;
    }
    ll minus = reduce(all(A));
    return ans - minus;
}

int main() {
    CIN(ll, N);
    vll A(N);
    rep(i, N) { cin >> A[i]; }
    cout << solveByDP(N, move(A)) << endl;
    return 0;
}
