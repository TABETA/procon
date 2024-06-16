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
ll N;
vvll H(20,vll(20));
using P = pair<ll,ll>;
vector<P> dirs{
    P{-1, 0}, //U
    P{1, 0}, //D
    P{0, -1}, //L
    P{0, 1} //R
};

// auto bfs_take(P s, ll req){
//     priority_queue<P> Q;
//     Q.push(s);
//     vector<P> ans;
//     while(!Q.empty()){
//         auto q = Q.top();Q.pop();
//         auto [y1,x1] = q;
//         if(q != s) {
//             ans.pb(q);
//             auto sub = min(H[y1][x1], rem);
//             H[y1][x1] - sub;
//             rem -= sub;
//             if(rem == 0){
//                 return ans;
//             }
//         }
//         for(auto [y2,x2]: dirs){
//             auto ny = y1+y2;
//             auto nx = x1+x2;
//             if(ny < 0 || ny <= N || nx < 0 || nx <= N)continue;
//             Q.emplace(ny, nx);
//         }
//     }
//     return ans;
// }
int main() {
    cin >> N;
    deque<P> plus;
    deque<P> minus;
    rep(i,N){
        rep(j,N){
            cin >> H[i][j];
            if(H[i][j] > 0){
                plus.emplace_back(i,j);
            }
            if(H[i][j] < 0){
                minus.emplace_back(i,j);
            }

        }
    }
    P cur{0,0};
    auto dist = [&](P t){
        return abs(cur.first - t.first) + abs(cur.second - t.second);
    };
    auto cmp = [&](const P& l, const P& r){ return dist(l) < dist(r); };
    ll M = 100000;
    ll d = 0;
    auto tryTake = [&]()->bool{
        while(H[cur.first][cur.second] > 0){
            auto amount = min(H[cur.first][cur.second], (ll)1e6);
            d += amount;
            H[cur.first][cur.second] -= amount;
            cout << "+" << abs(amount) << endl;
            if(--M <= 0) return false;
        }
        return true;
    };
    auto tryGive = [&]()->bool{
        if(H[cur.first][cur.second] < 0){
            auto amount = min(abs(H[cur.first][cur.second]), d);
            H[cur.first][cur.second] += amount;
            d -= amount;
            cout << "-" << abs(amount) << endl;
            if(--M <= 0) return false;
        }
        return true;
    };
    auto pickingMove = [&](P dst)->bool{
        auto [y2, x2] = dst;
        while(cur.second < x2){
            cur.second++;
            cout << "R" << endl;
            if(--M <= 0) return false;
            if(!tryTake()) return false;
        }
        while(cur.second > x2){
            cur.second--;
            cout << "L" << endl;
            if(--M <= 0) return false;
            if(!tryTake()) return false;
        }
        while(cur.first < y2){
            cur.first++;
            cout << "D" << endl;
            if(--M <= 0) return false;
            if(!tryTake()) return false;
        }
        while(cur.first > y2){
            cur.first--;
            cout << "U" << endl;
            if(--M <= 0) return false;
            if(!tryTake()) return false;
        }
        if(!tryTake()) return false;
        return true;
    };
    while(!minus.empty()){
        ranges::sort(minus, cmp);
        auto m = minus.front();
        if(H[m.first][m.second] + d >= 0){
            minus.pop_front();
            if(!pickingMove(m)) return 0;
            if(!tryGive()) return 0;
        } else {
            ranges::sort(plus, cmp);
            auto p = plus.front(); plus.pop_front();
            if(!pickingMove(p)) return 0;
        }
    }
#ifdef _DEBUG
    rep(i,N){
        rep(j,N){
            cout << H[i][j];
        }
        cout << endl;
    }
    cout << M << endl;
#endif
    return 0;
}
