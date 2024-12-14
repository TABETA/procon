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
using P = pair<ll, ll>;
static void debug(const char* format, ...) {
#if 0
    va_list args;
    va_start(args, format);
    char buffer[65535];
    vsnprintf(buffer, sizeof(buffer), format, args);
    cout << buffer;
    va_end(args);
#else
    (void)format;
#endif
}

struct Timer {
    Timer(ll msLimit) : msLimit(msLimit), start(chrono::system_clock::now()) {}
    const ll msLimit;
    const chrono::system_clock::time_point start;
    auto getMilliSeconds() const {
        return chrono::duration_cast<chrono::milliseconds>(
                   chrono::system_clock::now() - start)
            .count();
    };
    bool isIntime() {
        auto msElapsed = getMilliSeconds();
        bool ok = msLimit > 0 ? msElapsed < msLimit : true;
        if (!ok) debug("# timeout\n");
        return ok;
    };
};

random_device rd;
mt19937 g(rd());
using P = pair<ll, ll>;

struct Placement{
    ll p;
    ll r;// rotate
    char d;// direction
    ll b;// boundary
};

ostream &operator<<(ostream &os, const Placement &v) {
    os << v.p << " " << v.r << " " << v.d << " " << v.b;
    return os;
}
struct Rectangle{
    ll w;
    ll h;
};

class Solver {
    ll limit;
    ll N;
    ll T;
    ll S;
    vector<Rectangle> dR;
    Timer timer;
   public:
    Solver(ll N, ll T, ll S, vll W, vll H, Timer&& timer):
        N(N),
        T(T),
        S(S),
        dR(N),
        timer(timer) {
            rep(i,N){
                dR[i] = {W[i], H[i]};
            }
        }
    ~Solver() {}
    virtual pair<ll, ll> input() {
        ll w, h;
        cin >> w >> h;
        return pair<ll, ll>{w, h};
    }
    random_device rd;
    mt19937 gen = mt19937(rd());
    vector<Placement> modifyRandomly(vector<Placement> now, int ratio){
        uniform_int_distribution<> distR(0, 1);  // r: 0 or 1
        uniform_int_distribution<> distD(0, 1);  // d: 'U' or 'L'
        uniform_int_distribution<> distRatio(0, 100);
        for (ll i = 0; i < N; ++i) {
            if(distRatio(gen) > ratio) continue;
            ll r = distR(gen);
            char d = (distD(gen) == 0) ? 'U' : 'L';
            uniform_int_distribution<> distB(-1, i-1);
            ll b = distB(gen);
            now[i] = {i, r, d, b};
        }
        return now;
    }
    void solve() {
        map<ll, vector<Placement>> res;
        vector<Placement> now(N);
        ll col = sqrt(N);
        rep(i,N){
            ll r = dR[i].w > dR[i].h ? 1 : 0;
            ll b = i % col == 0 ? -1 : i-1;
            now[i] = {i, r, 'U', b};
        }
        rep(t,T){
            cout << now.size() << '\n';
            rep(i,N){
                cout << now[i] << '\n';
            }
            cout << flush;
            auto [w, h] = input();
            res[w+h] = now;
            now = modifyRandomly(res.begin()->second, 10);
        }
    }
};
class DebugSolver: public Solver{
    vector<Rectangle> tR;
    vector<Rectangle> gosa;
    ll t;
    public:
    DebugSolver(ll N, ll T, ll S, vll W, vll H, Timer&& timer):
        Solver(N, T, S, W, H, move(timer)),
        tR(N),
        gosa(T),
        t(0) {
        rep(i,N){
            ll w, h;
            cin >> w >> h;
            tR[i] = {w, h};
        }
        rep(i,T){
            ll w, h;
            cin >> w >> h;
            gosa[i] = {w, h};
        }
    }
    pair<ll, ll> input() override {
        auto ret = pair<ll, ll>{500ll+gosa[t].w, 500ll+gosa[t].h};
        ++t;
        return ret;
    }
};


#ifndef TIMELIMIT
constexpr ll msLimit = 2800;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    ll N, T, S;
    cin >> N >> T >> S;
    vll W(N), H(N);
    rep(i,N){
        cin >> W[i] >> H[i];
    }
#ifdef ONLINE_JUDGE
    Solver solver(N,T,S,W,H,move(timer));
#else
    DebugSolver solver(N,T,S,W,H,move(timer));
#endif
    solver.solve();
    return 0;
}
