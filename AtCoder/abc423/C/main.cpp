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
ll solve2(ll N, ll c, vll D){
    using P = pair<ll,vll>;
    queue<P> Q;
    Q.emplace(c, D);
    map<P, ll> dist;
    dist[{c,D}] = 0;
    while(!Q.empty()){
        auto [u, d] = Q.front();Q.pop();
        if(u < N){
            ll nu = u+1;
            if(d[u] == 0){
                auto key = P{nu,d};
                if(!dist.count(key) || dist[key] > dist[P{u,d}]){
                    dist[key] = dist[P{u,d}];
                    Q.emplace(nu, d);
                }
            }
            {
                vll nd = d;
                nd[u] ^= 1;
                auto key = P{u,nd};
                if(!dist.count(key) || dist[key] > dist[P{u,d}] + 1){
                    dist[key] = dist[P{u,d}] + 1;
                    Q.emplace(u, nd);
                }
            }
        }
        if(u > 0){
            ll nu = u-1;
            if(d[u-1] == 0){
                auto key = P{nu,d};
                if(!dist.count(key) || dist[key] > dist[P{u,d}]){
                    dist[key] = dist[P{u,d}];
                    Q.emplace(nu, d);
                }
            }
            {
                vll nd = d;
                nd[u-1] ^= 1;
                auto key = P{u,nd};
                if(!dist.count(key) || dist[key] > dist[P{u,d}] + 1){
                    dist[key] = dist[P{u,d}] + 1;
                    Q.emplace(u, nd);
                }
            }
        }
    }
    vll expected(N,1);
    ll ans = linf;
    rep(i,N+1){
        if(dist.count(P{i,expected})){
            chmin(ans, dist[P{i,expected}]);
        }
    }
    return ans;
}
ll solve(ll N, ll c, vll D){
    ll ans = 0;
    ll L = 0;
    for(; D[L]; L++);
    ll R = N-1;
    for(; D[R]; R--);

    reps(i,c,R+1){
        if(D[i]==1){
            ans += 2;
        } else {
            ans += 1;
        }
    }
    for(int i = c; i > L; i--){
        if(D[i-1]==1){
            ans += 2;
        } else {
            ans += 1;
        }
    }
    return ans;
}
auto rand_between = [](ll min, ll max) -> ll {
    return min + rand() % (max - min);
};
int main() {
    while(true){
        ll N = 11;
        ll c = rand_between(0, N);
        vll D(N);
        rep(i,N) D[i] = rand_between(0, 1);
        ll ans1 = solve(N, c, D);
        ll ans2 = solve2(N, c, D);
        if(ans1 != ans2){
            cout << N << " " << c << endl;
            print(D);
            cout << ans1 << " " << ans2 << endl;
            return 0;
        }
    }
    // ll N, c;
    // cin >> N >> c;
    // vll D(N);
    // rep(i,N) cin >> D[i];
    // cout << solve(N, c, D) << endl;
    return 0;
}
