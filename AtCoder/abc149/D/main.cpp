#ifdef _MSVC_LANG 
#include <tuple>
#include <sstream>
#include <queue>
#include <map>
#include <numeric>
#include <list>
#include <limits.h>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
#include <stack>
#include <float.h>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <chrono>

#else
#include <bits/stdc++.h>
#endif

using namespace std;

// clang-format off
/* accelration */
// 高速バイナリ生成
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
struct Fast {Fast() {std::cin.tie(0); ios::sync_with_stdio(false);}} fast;

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

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i,n) for(ll i=n-1;i>=0;i--)
#define rrepd(i,n) for(ll i=n;i>=1;i--)

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


template <typename T>
std::string toStringHelper(const T &value)
{
    return std::to_string(value);
}
template <>
std::string toStringHelper<std::string>(const std::string &value)
{
    return value;
}
template <typename T>
std::string join(const std::vector<T> &v, const char *delim = nullptr)
{
    std::string s;
    if (!v.empty())
    {
        s += toStringHelper(v[0]);
        for (size_t i = 1, c = v.size(); i < c; ++i)
        {
            if (delim)
                s += delim;
            s += toStringHelper(v[i]);
        }
    }
    return s;
}


void func(long long N, long long K, long long R, long long S, long long P, std::string T){

}
// clang-format on

int main() {
    long long N;
    cin >> N;
    long long K;
    cin >> K;
    long long R;
    cin >> R;
    long long S;
    cin >> S;
    long long P;
    cin >> P;
    std::string T;
    std::cin >> T;
    vs g(K);
    rep(i,N)
    {
        g[i%K] += T[i];
    }
    char rsp[] = {'r','s','p'};
    
    auto score = [&](char me, char you) -> ll {
        return
            me == 'r' && you == 's' ? R :
            me == 's' && you == 'p' ? S :
            me == 'p' && you == 'r' ? P :
            0LL;
    };
    ll ans = 0;
    rep(k,K)
    {
        const auto& s = g[k];
        ll size = (ll)s.size();
        auto dp = vvll(size+1, vll(3, 0));
        rep(i,size)
        {
            dp[i+1][0] = max(dp[i][1], dp[i][2]) + score(rsp[0], s[i]);
            dp[i+1][1] = max(dp[i][0], dp[i][2]) + score(rsp[1], s[i]);
            dp[i+1][2] = max(dp[i][0], dp[i][1]) + score(rsp[2], s[i]);
        }
        ans += *max_element(all(dp[size]));
    }
    cout << ans << endl;
    return 0;
}
