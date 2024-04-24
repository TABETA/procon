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
template<typename Container, typename Value> struct InsertHelper;
template<typename Value>
struct InsertHelper<std::set<Value>, Value> {
    static void insert(std::set<Value>& container, const Value& value) {
        container.emplace(value);
    }
};

template<typename Value>
struct InsertHelper<std::vector<Value>, Value> {
    static void insert(std::vector<Value>& container, const Value& value) {
        container.push_back(value);
    }
};

template<typename Value>
struct InsertHelper<std::map<Value, bool>, Value> {
    static void insert(std::map<Value, bool>& container, const Value& value) {
        container[value] = true;
    }
};
template<typename T, template<typename...> class Container>
Container<T> enumeratePrimeNumbers(const T N) {
    std::vector<bool> is_prime(N + 1, true);
    Container<T> P;
    for (T i = 2; i <= N; i++) {
        if (is_prime[i]) {
            for (T j = 2 * i; j <= N; j += i) {
                is_prime[j] = false;
            }
            InsertHelper<Container<T>, T>::insert(P, i);
        }
    }
    return P;
}

// clang-format on

int main() {
    long long N;
    std::cin >> N;
    long long M;
    std::cin >> M;
    // auto P = enumeratePrimeNumbers<ll, set>(M);

    set<ll> P;
    auto calc = [&](ll N) {
        for (ll a = 2; a * a <= N; ++a) {
            if (N % a != 0) continue;
            ll ex = 0;
            while (N % a == 0) {
                ++ex;
                N /= a;
            }
            P.emplace(a);
        }
        if (N != 1) P.emplace(N);
    };

    std::vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
        calc(A[i]);
    }
    std::vector<bool> is_ans(M + 1, true);
    for (auto &&p : P)
    {
        for (ll j = p; j <= M; j += p) {
            is_ans[j] = false;
        }
    }
    vll ans;
    reps(i, 1, M+1)
    {
        if(is_ans[i])
        {
            ans.pb(i);
        }
    }
    cout << ans.size() << endl;
    for (auto &&a : ans)
    {
        cout << a << endl;
    }
    

    return 0;
}
