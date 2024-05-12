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

using P = pair<ll,ll>;
using T = tuple<ll,ll, ll>;
// clang-format on

int main() {
    ll N;
    cin >> N;
    vs C(N);
    rep(y, N) { cin >> C[y]; }
    const ll X = N*N;
    set<P> ans;
    auto dijkstra = [&](P start, P goal, char O){
        vvll distance(N,vll(N, LONG_LONG_MAX));
        distance[start.first][start.second] = 0;
        priority_queue<T, vector<T>, greater<T>> q;
        q.emplace(0,start.first, start.second);
        while(!q.empty()){
            auto [d, y, x] = q.top(); q.pop();
            if(P{y,x} == goal ) break;
            if(distance[y][x] < d) continue;
            auto cells = {
                    P{y+1, x},
                    P{y-1, x},
                    P{y, x+1},
                    P{y, x-1},
                };
            for (auto [y2, x2] : cells)
            {
                if(y2 < 0 || N <= y2 || x2 < 0 || N <= x2) continue;
                auto newDistance = distance[y][x] + (O == C[y2][x2] ? 1 : X);
                if(distance[y2][x2] > newDistance){
                    distance[y2][x2] = newDistance;
                    q.emplace(newDistance, y2, x2);
                }
            }
        }
        P c = goal;
        while(c != start){
            auto [y,x] = c;
            if(O != C[y][x]){
                ans.insert(c);
            }
            auto cells = {
                    P{y+1, x},
                    P{y-1, x},
                    P{y, x+1},
                    P{y, x-1},
                };
            ll mind = distance[y][x];
            P next;
            for (auto c : cells){
                auto [y2, x2] = c;
                if(y2 < 0 || N <= y2 || x2 < 0 || N <= x2) continue;
                if(mind > distance[y2][x2]){
                    mind = distance[y2][x2];
                    next = c;
                }
            }
            c = next;
        }
        if(O != C[start.first][start.second]){
            ans.insert(start);
        }
    };
    dijkstra({0,0},{N-1,N-1}, 'R');
    dijkstra({0,N-1},{N-1,0}, 'B');
    cout << ans.size() << endl;
    return 0;
}
