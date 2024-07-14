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

#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;
using vm = vector<mint>;
using vvm = vector<vm>;
const long long MOD = 998244353;

// clang-format on

auto solve1(ll N, vll&& A){
    map<ll,set<ll>> imp;
    rep(i,N){
        imp[A[i]].emplace(i); 
    }
    map<ll,map<ll,map<ll,mint>>> memo;
    auto f = [&](auto f, ll d, ll rem, ll cur)->mint{
        if(memo[d][rem].count(cur) > 0){
            return memo[d][rem][cur];
        }
        if(rem == 0){
            return 1;
        }
        auto next = A[cur] + d;
        mint ans = 0;
        auto it = imp[next].upper_bound(cur);
        while(it != imp[next].end()){
            ans += f(f, d, rem - 1, *it);
            ++it;
        }
        return memo[d][rem][cur] = ans;
    };
    vector ans(N,mint{});
    ans[0] = N;
    ans[1] = N*(N-1)/2;
    reps(k,2,N){
        rep(i,N){
            reps(j,i+1,N){
                auto d = A[j] - A[i];
                ans[k] += f(f,d, k-1, j);
            }
        }
    }
    return ans;
};

auto solve2(ll N, vll&& A){
    vector ans(N,mint{});
    ans[0] = N;
    ans[1] = N*(N-1)/2;
    vector DP(N, vector(N, vector(N+1, mint{})));
    reps(i,1,N){
        rep(j,i){
            DP[i][j][2] = 1;
        }
    }
    reps(i,1,N){
        rep(j,i){
            reps(k,2,N){
                reps(l,i+1,N){
                    if(A[l] - A[i] == A[i] - A[j]){
                        DP[l][i][k+1] += DP[i][j][k];
                    }
                }
                ans[k] += DP[i][j][k+1];
            }
        }
    }
    return ans;
};

int main() {
    CIN(ll,N);
    vll A(N);
    rep(i,N){
        cin >> A[i];
    }
    auto ans = solve2(N, move(A));
    rep(i,N){
        if(i != 0)cout << " ";
        cout << ans[i].val();
    }
    cout << endl;
    return 0;
}
