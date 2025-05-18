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

constexpr long long MOD = 998244353;
#include <atcoder/modint>
using namespace atcoder;
using mint = static_modint<MOD>;
using vm = vector<mint>;
using vvm = vector<vm>;
ostream &operator<<(ostream &os, const mint &v) {
    os << v.val();
    return os;
}

// clang-format on
int main() {
    ll T;
    cin >> T;
    const ll M = 60;
    while (T--) {
        ll N, K;
        cin >> N >> K;
        ++N;
        vector dp(M+1, vector(2, vector(2, vector(M+1, mint{}))));
        // dp[i][j][s][p] = i桁目まで見て、popcountがp、桁和がj、N未満であることが確定しているかどうかがs
        dp[M][0][0][0] = 1;
        repd(i,M){
            rep(j,2){
                rep(s,2){
                    rep(p,K+1){
                        mint now = dp[i+1][j][s][p];
                        if (now == 0) continue;
                        repd(a,2){
                            ll ns = s;
                            ll np = p+a;// aが1ならpopcountが増える
                            if(s == 0){ // N未満が確定していない
                                // a = 0, Nのi桁目が1: 数値Nを構成するビットが立っている所が1か所でも0になっていたらN未満が確定する
                                if(a < (N>>i&1)) ns = 1;
                                // a = 1, Nのi桁目が0:
                                //  N未満であることが確定していないとき=少なくとも今はビット構成が一致している状態で
                                //  数値Nを構成するビットが立っていない所が1になっていたらNを超えてしまうのでスルー
                                if(a > (N>>i&1)) continue;  
                            }
                            if (np > K) continue; // popcountがKを超えたらスルー
                            dp[i][j][ns][np] += now;
                            if(j == 0 && a) dp[i][1][ns][np] += now*(1ll<<i); // 桁ごとに合計値に加算
                        }
                    }
                }
            }
        }
        mint ans = dp[0][1][1][K];
        cout << ans << '\n';
    }
    return 0;
}
