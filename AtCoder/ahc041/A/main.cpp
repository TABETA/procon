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

using P = pair<ll, ll>;
constexpr ll NA = -2;

class Solver {
    ll limit;
    ll N;
    ll M;
    ll H;
    vll A;
    vvll to;
    vector<P> B;
    Timer timer;

   public:
    Solver(ll N, ll M, ll H, vll&& A, vvll&& to, vector<P>&& B, Timer&& timer)
        : N(N), M(M), H(H), A(A), to(to), B(B), timer(timer) {}
    ~Solver() {}
    void solve() {
        map<ll, set<ll>, greater<ll>> mp;
        rep(i, N) { mp[A[i]].emplace(i); }
        vll p(N, -1);
        cout << p << endl;
        ll best = 0;
        rep(i,N){
            best += A[i];
        }
        ll ans = 0;
        UnionFind uf(N, A);
        set<ll> roots;
        rep(i, N) { roots.emplace(i); }
        vll parents(N);
        rep(i, N) { parents[i] = i; }
        map<ll, set<ll>> neighbors;
        for (auto &&u : roots){
            for (auto&& v : to[u]){
                neighbors[u].emplace(v);
            }
        }
        ll f = [&](ll root){
            ll h = 0;
            auto dfs = [&](auto dfs, ll u) -> ll {
                ++h;
                auto now = 0;
                for (auto&& v : to[u]) {
                    if (parents[v] != root) continue;
                    now += dfs(dfs, v);
                }
                if (now == 0) now = h;
                --h;
                return now;
            };
            return dfs(dfs, root) * A[root];
        };
        auto merge = [&](ll u, ll v){
            for (auto &&w : childlen[v]){
                parents[w] = u;
            }
            parents[v] = u;
        };
        while(true){
            ll diff = 0;
            bool isMerged = false;
            P t;
            for (auto &&uu : roots){
                for (auto &&n : neighbors[uu]){
                    auto v = parents[n];
                    ll u = uu;
                    if(A[uu] < A[v]){
                        swap(u,v);
                    } 
                    auto cur = f(u) + f(v);
                    auto tp = parents;
                    swap(tp, parents);
                    merge(u,v);
                    auto next = f(u);
                    swap(tp, parents);
                    if(chmax(diff, next - cur)){
                        isMerged = true;
                        p = {u,v};
                    }
                    
                    if(chmax(diff, f(u,v))){
                        isMerged = true;
                    }
                }
            }
            if(!isMerged)break;
            else {
                ans += diff;
                auto [u,v] = t;
                merge(u,v);
                cout << p << endl;
            }
        }
        ll h = 0;
        auto dfs = [&](auto dfs, ll u, vll& p) -> ll {
            ++h;
            auto now = 0;
            if (h == H) {
                now = h;
            } else {
                for (auto&& v : to[u]) {
                    if (p[v] != NA) continue;
                    p[v] = u;
                    now += dfs(dfs, v, p);
                }
                if (now == 0) now = h;
            }
            --h;
            return now;
        };
        for (auto&& [a, s] : mp) {
            auto S = s;
            while (S.size()) {
                if (!timer.isIntime()) return;
                ll now = 0;
                ll j = -1;
                vll Q(N, NA);
                vll toErase;
                for (auto&& i : S) {
                    vll q = p;
                    if (q[i] != NA) {
                        toErase.emplace_back(i);
                        continue;
                    }
                    q[i] = -1;
                    if (chmax(now, dfs(dfs, i, q) * a)) {
                        j = i;
                        Q = q;
                    }
                }
                for (auto&& i : toErase) {
                    S.erase(i);
                }
                if (j != -1) {
                    S.erase(j);
                    p = Q;
                    ans += now;
                }
            }
        }
        if (chmax(best, ans)) {
            cout << p << endl;
        }
    }
    void solve_1() {
        vector<P> AA(N);
        rep(i, N) { AA[i] = P{A[i], i}; }
        ranges::sort(AA, greater<P>());
        vll p(N, NA);
        ll best = 0;
        ll ans = 0;
        for (auto&& [a, i] : AA) {
            ll h = 0;
            auto dfs = [&](auto dfs, ll u) -> ll {
                ++h;
                auto now = 0;
                if (h == H) {
                    now = h;
                } else {
                    for (auto&& v : to[u]) {
                        if (p[v] != NA) continue;
                        p[v] = u;
                        now += dfs(dfs, v);
                    }
                    if (now == 0) now = h;
                }
                --h;
                return now;
            };
            if (p[i] != NA) continue;
            p[i] = -1;
            ans += dfs(dfs, i) * a;
        }
        if (chmax(best, ans)) {
            cout << p << endl;
        }
    }
    void solve_2() {
        map<ll, set<ll>, greater<ll>> mp;
        rep(i, N) { mp[A[i]].emplace(i); }
        ll best = 0;
        map<ll, set<vll>> used;
        random_device rd;
        mt19937 g = mt19937(rd());
        while (true) {
            ll ans = 0;
            vll p(N, NA);
            ll h = 0;
            auto dfs = [&](auto dfs, ll u) -> ll {
                ++h;
                auto now = 0;
                if (h == H) {
                    now = h;
                } else {
                    for (auto&& v : to[u]) {
                        if (p[v] != NA) continue;
                        p[v] = u;
                        now += dfs(dfs, v);
                    }
                    if (now == 0) now = h;
                }
                --h;
                return now;
            };
            for (auto&& [a, s] : mp) {
                vector<ll> is(all(s));
                do {
                    shuffle(is.begin(), is.end(), g);
                    if (!timer.isIntime()) return;
                } while (used[a].count(is));
                used[a].emplace(is);
                for (auto&& i : is) {
                    if (p[i] != NA) continue;
                    p[i] = -1;
                    ans += dfs(dfs, i) * a;
                }
                if (!timer.isIntime()) return;
            }
            if (chmax(best, ans)) {
                cout << p << endl;
            }
        }
    }
    void solve_3() {
        map<ll, set<ll>, greater<ll>> mp;
        rep(i, N) { mp[A[i]].emplace(i); }
        ll best = 0;
        ll ans = 0;
        vll p(N, NA);
        ll h = 0;
        auto dfs = [&](auto dfs, ll u, vll& p) -> ll {
            ++h;
            auto now = 0;
            if (h == H) {
                now = h;
            } else {
                for (auto&& v : to[u]) {
                    if (p[v] != NA) continue;
                    p[v] = u;
                    now += dfs(dfs, v, p);
                }
                if (now == 0) now = h;
            }
            --h;
            return now;
        };
        for (auto&& [a, s] : mp) {
            auto S = s;
            while (S.size()) {
                if (!timer.isIntime()) return;
                ll now = 0;
                ll j = -1;
                vll Q(N, NA);
                vll toErase;
                for (auto&& i : S) {
                    vll q = p;
                    if (q[i] != NA) {
                        toErase.emplace_back(i);
                        continue;
                    }
                    q[i] = -1;
                    if (chmax(now, dfs(dfs, i, q) * a)) {
                        j = i;
                        Q = q;
                    }
                }
                for (auto&& i : toErase) {
                    S.erase(i);
                }
                if (j != -1) {
                    S.erase(j);
                    p = Q;
                    ans += now;
                }
            }
        }
        if (chmax(best, ans)) {
            cout << p << endl;
        }
    }
};
#ifndef TIMELIMIT
constexpr ll msLimit = 1800;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    ll N, M, H;
    cin >> N >> M >> H;
    vll A(N);
    rep(i, N) { cin >> A[i]; }
    vvll to(M);
    rep(_, M) {
        CIN(ll, u);
        CIN(ll, v);
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    vector<P> B(N);
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        B[i] = {x, y};
    }
    Solver solver(N, M, H, move(A), move(to), move(B), move(timer));
    solver.solve();
    return 0;
}
