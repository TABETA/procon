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
int main() {
    long long N;
    std::cin >> N;
    std::vector<std::string> S(N);
    using P = pair<ll,ll>;
    vector<P> ps;
    for(int i = 0 ; i < N ; i++){
        std::cin >> S[i];
        rep(j, S[i].size()){
            if(S[i][j] == 'P'){
                S[i][j] = '.';
                ps.emplace_back(i,j);
            }
        }
    }
    using PP = pair<P,P>;
    auto next = [&](PP p){
        auto f = [&](P p){
            vector<P> res;
            auto [y, x] = p;
            ll dx[] = {0, 1, 0, -1};
            ll dy[] = {1, 0, -1, 0};
            rep(i, 4){
                ll nx = x + dx[i];
                if(nx < 0) nx = 0;
                if(nx >= N) nx = N-1;
                ll ny = y + dy[i];
                if(ny < 0) ny = 0;
                if(ny >= N) ny = N-1;
                if(S[ny][nx] == '#') nx = x, ny = y;
                res.emplace_back(ny, nx);
            }
            return res;
        };
        auto res1 = f(p.first);
        auto res2 = f(p.second);
        vector<PP> res;
        rep(i, 4){
            res.emplace_back(res1[i], res2[i]);
        }
        return res;
    };
    vector used(N, vector(N, vector(N, vector(N, false))));
    queue<pair<PP, ll>> Q;
    PP s = {ps[0], ps[1]};
    Q.emplace(PP{ps[0], ps[1]},0);
    auto use = [&](PP p){
        auto [p1, p2] = p;
        auto [y1, x1] = p1;
        auto [y2, x2] = p2;
        used[y1][x1][y2][x2] = true;
        used[y2][x2][y1][x1] = true;
    };
    auto isUsed = [&](PP p){
        auto [p1, p2] = p;
        auto [y1, x1] = p1;
        auto [y2, x2] = p2;
        return used[y1][x1][y2][x2] || used[y2][x2][y1][x1];
    };
    use(s);
    while(!Q.empty()){
        auto [u, cost] = Q.front();Q.pop();
        auto [p, q] = u;
        if(p == q){
            cout << cost << endl;
            return 0;
        }
        for(auto&& v: next(u)){
            if(isUsed(v))continue;
            use(v);
            Q.emplace(v, cost+1);
        }
    }
    cout << -1 << endl;
    return 0;
}
