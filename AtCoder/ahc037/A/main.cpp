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
    Timer(ll msLimit): msLimit(msLimit), start(chrono::system_clock::now()) {}
    const ll msLimit;
    const chrono::system_clock::time_point start;
    auto getMilliSeconds() const {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count();
    };
    bool isIntime() {
        auto msElapsed = getMilliSeconds();
        bool ok = msLimit > 0 ? msElapsed < msLimit : true;
        if(!ok)debug("# timeout\n");
        return ok;
    };

};

random_device rd;
mt19937 g(rd());

class Solver {
   public:
    Solver(ll N, vector<P>&& AB, Timer&& timer):
    limit(5*N),
    AB(AB),
    ans(limit, linf),
    timer(timer),
    tried(0)
    {
    }
    ~Solver() {
    }
    void write()const{
// #ifdef ONLINE_JUDGE
        ans.write();
// #endif
        debug("# tried: %lld\n", tried);
        debug("# score: %lld\n", ans.getScore());
    }
    void solve() {
        // while (timer.isIntime()) {
            Result now(limit);
            ranges::sort(AB, [](P l, P r){ return l.first + l.second < r.first + r.second;});
            map<ll, map<ll,P>> V;
            map<ll, map<ll,P>> H;
            set<ll> X; X.emplace(0);
            set<ll> Y; Y.emplace(0);
            for (auto &&[x,y] : AB)
            {
                V[x][y] = P(x, y);
                H[y][x] = P(x, y);
                X.emplace(x);
                Y.emplace(y);
            }
            for (auto &&[x, y] : AB)
            {
                now.create(x,y);
            }
            debug("# score of %lld: %lld with %lld at %lld.\n", tried, now.getScore(), now.getCount(), timer.getMilliSeconds());
            if (now.valid() && ans > now) {
                ans = move(now);
            }
            // ++tried;
        // }
    }
    ll getScore() const { return ans.getScore(); }

   private:
    class Result {
       public:
        ll calcCost(P l, P r){
            ll x = r.first - l.first;
            ll y = r.second - l.second;
            if(x < 0 || y < 0)return linf;
            return x + y;
        }
        pair<P, ll> getNearest_old(ll x, ll y){
            auto tar = P{x,y};
            auto it = S2.lower_bound(tar);
            while(it == S2.end() || it->first > x || it->second >y){
                --it;
            }
            P nearest = *it;
            ll cost = calcCost(nearest, P{x,y});
            return pair<P, ll>{nearest, cost};
        }
        pair<P, ll> getNearest(ll x, ll y){
            auto tar = P{x,y};
            P nearest = P{-1,-1};            
            ll min_cost = linf;
            for(auto &&s: S2){
                ll cost = calcCost(s, tar);
                if(min_cost > cost){
                    min_cost = cost;
                    nearest = s;
                }
            }
            return pair<P, ll>{nearest, min_cost};
        }
        void create(ll x, ll y){
            auto tar = P{x,y};
            if(S2.count(tar))return;
            auto [p, cost] = getNearest(x,y);
            auto pp = p;
            for (auto &&p1 : {P{x, pp.second}, P{pp.first, y}}){
                if(!S2.count(p1)){
                    used.insert(pp);
                    add(pp, p1);
                    score += calcCost(pp, p1);
                    push(p1.first, p1.second);
                    ll newCost = calcCost(p1, tar);
                    if(cost > newCost){
                        cost = newCost;
                        p = p1;
                    }
                }
            }
            if(!S2.count(tar)){
                add(p, tar);
                score += cost;
                push(x, y);
            }
            used.insert(p);
            used.insert(tar);
        }
        void write() const {
            ll cnt = 0;
            ostringstream oss;
            for (auto &&line : operations)
            {
                if(!used.count(line.second))continue;
                cnt++;
                auto [x1, y1] = line.first;
                auto [x2, y2] = line.second;
                char buffer[65535];
                snprintf(buffer, sizeof(buffer), "%lld %lld %lld %lld\n", x1, y1, x2, y2);
                oss << buffer;
            }
            cout << cnt << '\n';
            cout << oss.str() << flush;
        }
        bool valid() const { return cnt >= 0; }
        ll getScore() const { return score; }
        ll getCount() const { return cnt; }
        void push(ll x, ll y){
            auto p = P(x,y);
            S2.insert(p);
        }
        Result(ll limit) : score(0), cnt(limit), operations(), S2(), used() {
            push(0,0);
        }
        Result(ll limit, ll score) : score(score), cnt(limit), operations(), S2(), used() {
            push(0,0);
        }
        Result(const Result&) = delete;
        Result& operator=(const Result&) = delete;
        Result(Result&& other) noexcept = default;
        Result& operator=(Result&& other) noexcept = default;
        bool operator==(const Result& rhs) const { return score == rhs.score; }
        bool operator!=(const Result& rhs) const { return !(*this == rhs); }
        bool operator<(const Result& rhs) const { return score < rhs.score; }
        bool operator>=(const Result& rhs) const { return !(*this < rhs); }
        bool operator<=(const Result& rhs) const { return score <= rhs.score; }
        bool operator>(const Result& rhs) const { return !(*this <= rhs); }

       private:
        ll score;
        ll cnt;
        vector<pair<P, P>> operations;
        set<P> S2;
        set<P> used;
        void add(P src, P dst) {
            operations.emplace_back(src, dst);
        }
    };
    ll limit;
    vector<P> AB;
    Result ans;
    Timer timer;
    ll tried;
};

#ifndef TIMELIMIT
constexpr ll msLimit = 1900;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    CIN(ll, N);
    vector<P> AB(N);
    for (auto& p : AB){
        cin >> p.first;
        cin >> p.second;
    }
    Solver solver(N, move(AB), move(timer));
    solver.solve();
    solver.write();
    return 0;
}
