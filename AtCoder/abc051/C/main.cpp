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
int main() {
    CIN(ll,SX);
    CIN(ll,SY);
    CIN(ll,TX);
    CIN(ll,TY);
    ll H = TY - SY+4;
    ll W = TX - SX+4;
    TX = TX - SX + 1;
    TY = TY - SY + 1;
    SX = 1;
    SY = 1;
    string ans = "";
    using P = pair<ll,ll>;
    using PP = pair<P,P>;
    vector used(H, vector(W, false));
    
    for(auto pp: vector<PP>{PP{{SY,SX},{TY,TX}},PP{{TY,TX},{SY,SX}},PP{{SY,SX},{TY,TX}},PP{{TY,TX},{SY,SX}}}){
        auto [s, t] = pp;
        auto [sy, sx] = s;
        auto [ty, tx] = t;
        queue<P> Q;
        Q.push(s);
        vector distance(H, vector(W, pair<ll, P>{linf, P{}} ));
        distance[sy][sx] = {0, P{0,0}};
        while(!Q.empty()){
            auto [cy, cx] = Q.front();Q.pop();
            if(cy == ty && cx == tx){
                string now;
                while(cy != sy || cx != sx){
                    auto [d, pre] = distance[cy][cx];
                    if(cy != ty || cx != tx){
                        used[cy][cx] = true;
                    }
                    auto [py, px] = pre;
                    if(cy < py)now += 'D';
                    if(cy > py)now += 'U';
                    if(cx < px)now += 'L';
                    if(cx > px)now += 'R';
                    cy = py;
                    cx = px;
                }
                reverse(all(now));
                ans += now;
                break;
            }
            auto [cc, pre] = distance[cy][cx];
            ll dx[] = {0, 1, 0, -1};
            ll dy[] = {1, 0, -1, 0};
            rep(i,4){
                auto nx = cx + dx[i];
                auto ny = cy + dy[i];
                auto nc = cc + 1;
                if(nx < 0 || nx >= W || ny < 0 || ny >= H)continue;
                if(used[ny][nx])continue;
                if(distance[ny][nx].first <= nc)continue;
                distance[ny][nx] = {nc, P{cy, cx}};
                Q.emplace(ny, nx);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
