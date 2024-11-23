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

auto solve1(){
    CIN(ll,N);
    CIN(ll,Q);
    CIN(string,S);
    vll A(N+1);
    vll B(N+1);
    vll C(N+1);
    rep(i,N){
        if(S[i] == '1'){
            A[i+1]++;
        }
        if(S[i] == '2'){
            B[i+1]++;
        }
        if(S[i] == '/'){
            C[i+1]++;
        }
    }
    rep(i,N){
        A[i+1] += A[i];
        B[i+1] += B[i];
        C[i+1] += C[i];
    }
    rep(_,Q){
        CIN(ll,L);
        CIN(ll,R);

        auto f = [&](ll X){
            if(X == 0) {
                ll y  = C[L-1] + 1;
                auto ci = ranges::lower_bound(C, y)-C.begin();
                return ci <= R;
            } else {
                ll x = X + A[L-1];
                auto a = ranges::lower_bound(A, x);
                if(a == A.end()) return false;
                ll ai = a-A.begin();
                ll y  = C[ai] + 1;
                ll ci = ranges::lower_bound(C, y) - C.begin();
                if(ci > R) return false;
                return B[R] - B[ci] >= X;
            }
        };
        auto binary_search = [&](auto f, ll ac, ll wa) -> ll {
            while (abs(ac - wa) > 1) {
                ll wj = (ac + wa) / 2;
                if (f(wj))
                    ac = wj;
                else
                    wa = wj;
            }
            return ac;
        };
        auto v = binary_search(f, -1, 1e9);
        cout << max(0ll, 1+v*2) << '\n';
    }
}
#include <atcoder/all>
using namespace atcoder;
auto solve2(){
    CIN(ll,N);
    CIN(ll,Q);
    CIN(string,S);
    fenwick_tree<ll> A(N+2);
    fenwick_tree<ll> B(N+2);
    fenwick_tree<ll> C(N+2);
    rep(i,N){
        if(S[i] == '1'){
            A.add(i, 1);
        }
        if(S[i] == '2'){
            B.add(i, 1);
        }
        if(S[i] == '/'){
            C.add(i, 1);
        }
    }
    rep(_,Q){
        CIN(ll,L);--L;
        CIN(ll,R);

        auto binary_search = [&](auto f, ll ac, ll wa) -> ll {
            while (abs(ac - wa) > 1) {
                ll wj = (ac + wa) / 2;
                if (f(wj))
                    ac = wj;
                else
                    wa = wj;
            }
            return ac;
        };
        auto f = [&](ll X){
            if(X == 0) {
                return C.sum(L, R) >= 1;
            } else {
                auto ai =  binary_search([&](ll i){
                    return A.sum(L, i) >= X;
                }, N+2, L);
                if(ai > R) return false;
                auto ci =  binary_search([&](ll i){
                    return C.sum(ai, i) >= 1;
                }, N+2, ai);
                if(ci > R) return false;
                return B.sum(ci, R) >= X;
            }
        };
        auto v = binary_search(f, -1, 1e9);
        cout << max(0ll, 1+v*2) << '\n';
    }
}
auto solve3(){
    CIN(ll,N);
    CIN(ll,Q);
    CIN(string,S);
    vll A;
    vll B;
    vll C;
    rep(i,N){
        if(S[i] == '1'){
            A.emplace_back(i);
        }
        if(S[i] == '2'){
            B.emplace_back(i);
        }
        if(S[i] == '/'){
            C.emplace_back(i);
        }
    }
    rep(_,Q){
        CIN(ll,L);--L;
        CIN(ll,R);--R;

        auto f = [&](ll X){
            if(X == 0) {
                auto ci = ranges::lower_bound(C, L) - C.begin();
                if(ci >= (ll)C.size()) return false;
                return C[ci] <= R;
            } else {
                --X;
                auto al = ranges::lower_bound(A, L) - A.begin();
                if(al+X >= (ll)A.size()) return false;
                auto ar = A[al+X];
                auto ci = ranges::lower_bound(C, ar) - C.begin();
                if(ci >= (ll)C.size()) return false;
                auto c = C[ci];
                if(c > R) return false;
                auto bl = ranges::lower_bound(B, c) - B.begin();
                if(bl+X >= (ll)B.size()) return false;
                auto b = B[bl+X];
                return b <= R;
            }
        };
        auto binary_search = [&](auto f, ll ac, ll wa) -> ll {
            while (abs(ac - wa) > 1) {
                ll wj = (ac + wa) / 2;
                if (f(wj))
                    ac = wj;
                else
                    wa = wj;
            }
            return ac;
        };
        auto v = binary_search(f, -1, 1e9);
        cout << max(0ll, 1+v*2) << '\n';
    }
}
int main() {
    solve3();
    return 0;
}
