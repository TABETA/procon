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
auto solve(ll N ,vector<set<ll>>& G)->ll{
    vector<vector<vector<ll>>> C;
    vector group(N,-1ll);
    bool ng = false;
    auto f = [&](auto f, ll cur, vvll& B, ll i)->void{
        B[i].emplace_back(cur);
        group[cur] = i;
        for (auto &&v : G[cur])
        {
            if(group[v] == i) {
                ng = true;
            }
            if(group[v] != -1) continue;
            f(f, v, B, i^1);
        }
    };
    rep(i,N){
        if(group[i] == -1){
            vector B(2, vector<ll>{});
            f(f, i, B, 0);
            C.emplace_back(B);
        }
    }
    if(ng){
        return 0;
    }
    vector V(C.size()+1, vector(2, 0ll));
    rep(i,C.size()){
        V[i+1][0] = V[i][0] + C[i][0].size();
        V[i+1][1] = V[i][1] + C[i][1].size();
    }
    ll ans = 0;
    rep(i,C.size()){
        for (auto &&a : C[i][0])
        {
            ans += C[i][1].size() - G[a].size();
        }
        ll r = (V[C.size()][0] - V[i+1][0]) + (V[C.size()][1] - V[i+1][1]);
        ans += (r)*C[i][0].size();
        ans += (r)*C[i][1].size();
    }
    return ans;
}
auto solve_slow(ll N ,vector<set<ll>>& G)->ll{
    ll ans = 0;
    rep(u,N){
        reps(v,u+1,N){
            if(G[u].count(v))continue;
            auto GG{G};
            GG[u].emplace(v);
            GG[v].emplace(u);
            vector B(2, vector<ll>{});
            vector group(N,-1ll);
            bool ng = false;
            auto f = [&](auto f, ll cur, ll i)->void{
                B[i].emplace_back(cur);
                group[cur] = i;
                for (auto &&v : GG[cur])
                {
                    if(group[v] == i) {
                        ng = true;
                    }
                    if(group[v] != -1) continue;
                    f(f, v, i^1);
                }
            };
            rep(i,N){
                if(group[i] == -1){
                    f(f, i, 0);
                }
            }
            if(!ng){
                // printf("%lld %lld\n", u+1,v+1);
                ++ans;
            }
        }
    }
    return ans;
}
/*
# description

頂点数Nの単純グラフを構成する辺の集合を返します。
ここで単純グラフとは以下を指します。
・自己ループが無い
・多重辺が無い
辺の情報は文字列で表現され、頂点Uと頂点Vを繋ぐことを以下の書式で表現します。
"U V"
例えば、頂点1と頂点2を繋ぐ場合、以下の文字列が返されます。
"1 2"

# args

N: 頂点数。1から200000を取ることが可能。

# return value

辺の集合を表すvector

*/
std::vector<std::string> generate_edges(long long N){
    std::vector<std::string> edges;
    srand(static_cast<unsigned int>(time(0)));
    for (long long U = 1; U <= N; ++U) {
        for (long long V = U + 1; V <= N; ++V) {
            if (rand() % 5 == 0) {
                edges.push_back(std::to_string(U) + " " + std::to_string(V));
            }
        }
    }
    return edges;
}

auto test(ll N, ll M, istringstream& cin, ostringstream& cout)->bool{
    vector G(N, set<ll>{});
    for(int i = 0 ; i < M ; i++){
        CIN(ll,u);--u;
        CIN(ll,v);--v;
        G[u].emplace(v);
        G[v].emplace(u);
    }
    ll expected = solve_slow(N, G);
    ll actual = solve(N, G);
    if(expected != actual){
        printf("expected: %lld\n", expected);
        printf("actual: %lld\n", actual);
        return true;
    }
    return false;
}

#if 1
int main() {
    long long N;
    std::cin >> N;
    long long M;
    std::cin >> M;
    vector G(N, set<ll>{});
    for(int i = 0 ; i < M ; i++){
        CIN(ll,u);--u;
        CIN(ll,v);--v;
        G[u].emplace(v);
        G[v].emplace(u);
    }
    cout << solve(N, G) << endl;
    // cout << solve_slow(N, G) << endl;
    return 0;
}
#else
int main() {
    while(true){
        long long N = 10;
        auto edges = generate_edges(N);
        ll M = edges.size();
        string input = "";
        rep(i,M){
            input += edges[i] + '\n';
        }
		istringstream iss(input);
		ostringstream oss;
        auto ok = test(N, M, iss, oss);
        if(ok)break;
    }
    return 0;
}
#endif
