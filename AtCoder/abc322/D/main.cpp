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

const string YES = "Yes";
const string NO = "No";

// clang-format on
using P = pair<ll,ll>;
struct Mino {
    auto operator<=>(const Mino&) const = default;
    set<P> S;
    Mino(): S() {}
    void input(){
        rep(i, 4) {
            string s;
            cin >> s;
            rep(j, 4) {
                if (s[j] == '#') S.insert(P(i, j));
            }
        }
    }
    void normalize(){
        ll x = linf, y = inf;
        repr(p, S) chmin(y, p.first), chmin(x, p.second);
        set<P> T;
        repr(p, S) T.emplace(p.first - y, p.second - x);
        S = T;
    }
    Mino rotate()const{
        Mino ans;
        repr(p, S) ans.S.emplace(p.second, 3 - p.first);
        ans.normalize();
        return ans;
    }
    set<Mino> getRotated()const{
        set<Mino> ans;
        auto cur = *this;
        ans.emplace(cur);
        rep(i, 3) {
            cur = cur.rotate();
            ans.emplace(cur);
        }
        return ans;
    }

    Mino shift(ll x, ll y)const{
        Mino ans;
        repr(p, S) {
            ll nx = p.first + x, ny = p.second + y;
            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) return {};
            ans.S.emplace(ny, nx);
        }
        return ans;
    }
    set<Mino> getShifted()const{
        set<Mino> ans;
        rep(y,3)rep(x,3){
            auto now = shift(x, y);
            if(now.S.size() != 0) ans.insert(now);
        }
        return ans;
    }
    void print()const{
        vector<string> ans(4, "....");
        repr(p, S) ans[p.second][p.first] = '#';
        repr(s, ans) cout << s << endl;
        cout << endl;
    }
};
int main() {
    vector<Mino> minos(3);
    rep(i, 3) minos[i].input();
    vector<set<Mino>> A(3);
    rep(i,3){
        for (auto &&mino : minos[i].getRotated()){
            A[i].merge(mino.getShifted());
        }
    }
    repr(a, A[0]){
        repr(b, A[1]){
            repr(c, A[2]){
                set<P> S;
                auto aa = a.S;
                S.merge(aa);
                auto bb = b.S;
                S.merge(bb);
                auto cc = c.S;
                S.merge(cc);
                if (S.size() == 16 && aa.size() == 0 && bb.size() == 0 && cc.size() == 0) {
                    cout << YES << endl;
                    return 0;
                }
            }
        }
    }
    cout << NO << endl;
    return 0;
}
