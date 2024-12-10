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
#include <random>

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

const string YES = "Yes";
const string NO = "No";



// clang-format on
using P = pair<ll, ll>;
struct State2 {
    const ll H;
    const ll W;
    set<P> s;
    State2(ll H, ll W) : H(H), W(W) {
        rep(y, H) {
            rep(x, W) { s.emplace(y, x); }
        }
    }
    State2(ll H, ll W, set<P> s) : H(H), W(W), s(s) {}
    State2(const State2& s) : H(s.H), W(s.W), s(s.s) {}
    State2 fill(P HW, int v) {
        if (s.empty()) return {0,0};
        auto [y, x] = *s.begin();
        auto t = s;
        auto [R, C] = HW;
        rep(r, R) {
            rep(c, C) {
                if (y + r > H) return {0,0};
                if (x + c > W) return {0,0};
                if (!t.count(P{y + r, x + c})) return {0,0};
                t.erase(P{y + r, x + c});
            }
        }
        return {H, W, t};
    }
    bool isFilled() { return s.empty(); }
};
struct State {
    const ll H;
    const ll W;
    vector<vector<int>> used;
    State(ll H, ll W) : H(H), W(W), used(H,vector(W, 0)) {}
    State(ll H, ll W, vector<vector<int>> used) : H(H), W(W), used(used) {}
    State(const State& other) : H(other.H), W(other.W), used(other.used) {}
    P top() const {
        rep(i, H) {
            rep(j, W) {
                if (!used[i][j]) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }
    bool erase(ll y, ll x, int v){
        if (y >= H) return false;
        if (x >= W) return false;
        if(used[y][x]) return false;
        used[y][x] = v+1;
        return true;
    }
    State fill(P HW, int v) {
        auto [y, x] = top();
        if(y==-1) return {0,0};
        auto t = *this;
        auto [R, C] = HW;
        rep(r, R) {
            rep(c, C) {
                if (!t.erase(y + r, x + c, v)) return {0,0};
            }
        }
        return t;
    }
    bool isFilled() {
        rep(i, H) {
            rep(j, W) {
                if (!used[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};


template<typename T>
string solve(ll N, ll H, ll W, const vector<P>& D){
    vector<P> C = D;
    vll is(N);
    iota(all(is), 0);
    auto ans = NO;
    do {
        auto dfs = [&](auto dfs, ll n, T s) -> bool {
            if (s.isFilled()) {
                return true;
            }
            if (n == N) {
                return false;
            }
            auto i = is[n];
            rep(_, 2) {
                auto t = s.fill(C[i], i);
                if (t.H != 0) {
                    if (dfs(dfs, n + 1, t)) {
                        return true;
                    }
                }
                swap(C[i].first, C[i].second);
            }
            return false;
        };
        if (dfs(dfs, 0ll, {H, W})) {
            return YES;
        }
    } while (next_permutation(all(is)));
    return NO;
}
// min_valからmax_valまでの範囲で乱数を生成する関数
int generate_random(int min_val, int max_val) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_val, max_val);
    return dis(gen);
}
int main() {
    long long N;
    std::cin >> N;
    long long H;
    std::cin >> H;
    long long W;
    std::cin >> W;

    vector<P> C(N);
    for (int i = 0; i < N; i++) {
        CIN(ll, h);
        CIN(ll, w);
        C[i] = P{h, w};
    }
#if 1
    cout << solve<State>(N, H, W, C) << endl;
#else
    while (true)
    {
        ll N = generate_random(1, 7);
        ll H = generate_random(1, 10);
        ll W = generate_random(1, 10);
        vector<P> C(N);
        for (int i = 0; i < N; i++) {
            C[i] = P{generate_random(1, 10), generate_random(1, 10)};
        }
        if(solve<State>(N, H, W, C) != solve<State2>(N, H, W, C)){
            printf("N: %lld, H: %lld, W: %lld\n", N, H, W);
            print(C);
            break;
        }
    }
#endif
    return 0;
}
