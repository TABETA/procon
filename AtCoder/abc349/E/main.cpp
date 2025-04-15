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
template<typename T>
vector<vector<T>> rotate90(const vector<vector<T>>& arr) {
    int N = arr.size();
    vector<vector<T>> rotated(N, vector<T>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            rotated[j][N - 1 - i] = arr[i][j];
        }
    }
    return rotated;
}

int main() {
    using P = pair<ll,ll>;
    vvll A(3,vll(3));
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            ll a;
            cin >> a;
            A[i][j] = a;
        }
    }
    auto pss = {
        vector<P>{P{0,0},P{0,1},P{0,2}},
        vector<P>{P{1,0},P{1,1},P{1,2}},
        vector<P>{P{2,0},P{2,1},P{2,2}},
        vector<P>{P{0,0},P{1,0},P{2,0}},
        vector<P>{P{0,1},P{1,1},P{2,1}},
        vector<P>{P{0,2},P{1,2},P{2,2}},
        vector<P>{P{0,0},P{1,1},P{2,2}},
        vector<P>{P{2,0},P{1,1},P{0,2}},
    };
    map<vvll, ll> memo;
    auto dfs = [&](auto dfs, vvll used, ll me) -> ll {
        if(memo.count(used)) return memo[used];
        ll you = me^1;
        ll ans = [&](){
            for (auto &&ps : pss){
                ll mine = 0;
                ll yours = 0;
                for (auto &&[y,x] : ps){
                    if(used[y][x] == me) {
                        mine++;
                    } else if(used[y][x] == you){
                        yours++;
                    }
                }
                if(mine == 3) return me;
                if(yours == 3) return you;
            }
            bool hasAns = false;
            for(int i = 0 ; i < 3 ; i++){
                for(int j = 0 ; j < 3 ; j++){
                    if(used[i][j] != -1) continue;
                    hasAns = true;
                    auto temp = used;
                    temp[i][j] = me;
                    if(me == dfs(dfs, temp, you)) {
                        return me;
                    }
                }
            }
            if(hasAns) return you;

            ll myScore = 0;
            ll yourScore = 0;
            for(int i = 0 ; i < 3 ; i++){
                for(int j = 0 ; j < 3 ; j++){
                    if(used[i][j] == me) myScore += A[i][j];
                    else yourScore += A[i][j];
                    
                }
            }
            return myScore > yourScore ? me : you;
        }();
        return memo[used] = ans;
    };
    vvll used(3,vll(3,-1));
    auto ans = dfs(dfs,used,0);
    if(ans == 0) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
    return 0;
}
