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
#ifndef ONLINE_JUDGE
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

class SolverB {
   public:
    SolverB(ll N, vll&& A, vll&& B, vvll&& to, vvll&&G, vll&& T, Timer&& timer):
    to(to),
    G(G),
    A(A),
    Z(),
    B(B),
    T(T),
    shortestPath(),
    ans(),
    timer(timer),
    N(N),
    tried(0)
    {
    }
    ~SolverB() {
    }
    void write()const{
// #ifdef ONLINE_JUDGE
        ans.write();
// #endif
        debug("# tried: %lld\n", tried);
        debug("# score: %lld\n", ans.getScore());

    }
    void solve() {
        initialize(A, to, G, T);
        // 初期解の生成
        {
            vll a(A.size());
            vll b(B.size());
            rep(i,N){
                a[i] = i;
            }
            ans.setA(a);
            for (auto &&v : shortestPath)
            {
                // インデックスと値が一致するように初期化しているのでvをそのまま入れればよい
                ans.requestChangeSignal(1, v, 0);
                ans.travel({v});
            }
        }
        while (timer.isIntime()) {
            Result now;
            now.setA(A);
            ll cur = 0;
            auto t = T.begin();
            while (now.valid()) {
                if (t == T.end()) break;
                cur = strictSearch(cur, *t, now);
                if (!timer.isIntime()) return;
                if (cur == *t)++t;
                if(now > ans){
                    debug("# %lld attempt was aborted due to worse score.\n", tried);
                    break;
                }
            }
            debug("# score of %lld: %lld with %lld at %lld.\n", tried, now.getScore(), now.getCount(), timer.getMilliSeconds());
            if (t == T.end() && now.valid() && ans > now) {
                ans = move(now);
            }
            ++tried;
            vll gomi(B.size(), -1);
            swap(B,gomi);
            if(Z.size() == A.size()){
                refine(A, 20);
            }
        }
    }
    ll getScore() const { return ans.getScore(); }

   private:
    class Result {
       public:
        void write() const { cout << oss.str() << flush; }
        ll travel(const vll& path) {
            ll cur = 0;
            const ll p_len = path.size();
            rep(i, p_len) {
                add("m %lld\n", path[i]);
                cur = path[i];
                --cnt;
            }
            return cur;
        }
        bool valid() const { return cnt >= 0; }
        ll getScore() const { return score; }
        ll getCount() const { return cnt; }
        Result() : score(0), cnt(1e5), oss() {}
        Result(ll score) : score(score), cnt(1e5), oss() {}
        Result(const Result&) = delete;
        Result& operator=(const Result&) = delete;
        Result(Result&& other) noexcept = default;
        Result& operator=(Result&& other) noexcept = default;
        void setA(const vll& A) {
            const ll a_len = A.size();
            rep(i, a_len) {
                add("%lld ", A[i]);
            }
            add("\n");
        }
        void requestChangeSignal(const ll l, const ll a, const ll b) {
            add("s %lld %lld %lld\n", l, a, b);
            score++;
        }
        void changeSignal(const ll l, const ll a, const ll b,const vll& A, vll& B) {
            requestChangeSignal(l,a,b);
            for (int i = a, j = b; i < a + l; ++i, ++j) {
                B[j] = A[i];
            }
        }

        void changeSignal(const ll l, const ll a, const ll b,const vll& A, vll& B, vll& Z) {
            requestChangeSignal(l,a,b);
            Z = vll(A.size(), 0);
            for (int i = a, j = b; i < a + l; ++i, ++j) {
                B[j] = A[i];
                Z[i] += l;
            }
        }
        bool operator==(const Result& rhs) const { return score == rhs.score; }
        bool operator!=(const Result& rhs) const { return !(*this == rhs); }
        bool operator<(const Result& rhs) const { return score < rhs.score; }
        bool operator>=(const Result& rhs) const { return !(*this < rhs); }
        bool operator<=(const Result& rhs) const { return score <= rhs.score; }
        bool operator>(const Result& rhs) const { return !(*this <= rhs); }

       private:
        ll score;
        ll cnt;
        ostringstream oss;
        void add(const char* format, ...) {
            if (cnt <= 0) {
                score = linf;
                return;
            }
            va_list args;
            va_start(args, format);
            char buffer[65535];
            vsnprintf(buffer, sizeof(buffer), format, args);
#if 0
            cout << buffer;
#else
            oss << buffer;
#endif
            va_end(args);
            --cnt;
        }
    };
    struct Route {
        vll path;
        vll blockers;
        ll progress_max_ = 0;
        tuple<ll,ll,ll,ll> longest_match{-1, -1, -1, -1};
        tuple<ll,ll,ll,ll> getLongestRange2(const vll& A, const vll& B, ll& progress_max) {
            if (get<0>(longest_match) != -1){
                progress_max = progress_max_;
                return longest_match;
            }
            const ll b_len = B.size();
            const ll bl_len = min(blockers.size(),B.size());// Bの長さ以上に候補を覚えても意味が無いので切り詰める
            if(bl_len > 0) {
                map<ll,ll> idx;
                rep(i,bl_len){
                    idx[blockers[i]] = i;
                }
                unordered_set<ll> next_candidate;
                rep(i,bl_len) next_candidate.emplace(blockers[i]);
                unordered_map<ll, ll> founds;
                ll l = 0;
                ll r = b_len;
                bool ok = true;
                uint found_bit = 0u; //Bの長さは最大24なので32bit型でOK
                rep(i,b_len){
                    if(next_candidate.count(B[i])){
                        ++founds[B[i]];
                        found_bit |= 1u<<idx[B[i]];
                        next_candidate.erase(B[i]);
                        if(ok)++l;
                        if(!ok && r == b_len){
                            r = i;
                        }
                    } else {
                        ok = false;
                    }
                }
                auto search = [&](ll bl, ll br){
                    ll len = br - bl;
                    ll a_len = A.size();
                    ll progress = bl;
                    rep(i,a_len){
                        ll l = max(0ll,i-len+1);
                        if(i>=len) {
                            if(founds.count(A[l-1])){
                                if(founds[A[l-1]] > 1) --founds[A[l-1]];
                                else {
                                    founds.erase(A[l-1]);
                                    found_bit &= ~(1u<<idx[A[l-1]]);
                                    next_candidate.emplace(A[l-1]);
                                }
                            }
                        }
                        if(next_candidate.count(A[i])) {
                            next_candidate.erase(A[i]);
                            ++founds[A[i]];
                            found_bit |= 1u<<idx[A[i]];
                            progress = __builtin_ctz(~found_bit);
                            if(progress_max_ < progress){
                                progress_max_ = progress;
                                longest_match = {len, l, bl, blockers[progress-1]};
                                // Bのサイズ以上マッチすることはできない
                                if(progress_max_ == b_len) return;
                            }
                        }
                    }
                };
                search(l, r);
            }
            progress_max = progress_max_;
            return longest_match;
        }
    };
    struct Boundary {
        ll name;
        vll path;
    };
    vvll to;
    vvll G;
    vll A;
    vll Z;
    vll B;
    vll T;
    vll shortestPath;
    Result ans;
    Timer timer;
    ll N;
    ll tried;
    auto getBoundaries(const ll src, const ll dst, const vvll& to, const vll& B,
                       vector<bool>& used) -> pair<vll, vector<Boundary>> {
        vector<Boundary> boundaries;
        queue<pair<ll, vll>> Q;
        Q.emplace(src, vll{});
        while (!Q.empty()) {
            auto [u, path] = Q.front();
            Q.pop();
            used[u] = true;
            bool isBoundary = false;
            for (auto&& v : to[u]) {
                if (used[v]) continue;
                if (find(all(B), v) == B.end()) {
                    isBoundary = true;
                    continue;
                }
                used[v] = true;
                auto np = path;
                np.emplace_back(v);
                if (v == dst) {
                    return {np, {}};
                } else {
                    Q.emplace(v, np);
                }
            }
            if (isBoundary) {
                boundaries.emplace_back(u, path);
            }
        }
        return {{}, boundaries};
    };
    auto getRoutesMulti(const ll src, const ll dst,
                   const vector<Boundary>& boundaries, const vvll& G,
                   const vvll& to, vector<bool>& used) -> vector<Route> {
        vector<Route> routes;
        using Res = pair<ll, Route>;
        queue<Res> Q;
        for (auto&& b : boundaries) {
            ll u = b.name;
            // 現在地点よりも遠い場合はSkip
            if (G[src][dst] < G[u][dst]) continue;
            Q.emplace(u, Route{b.path, {}});
            used[u] = false;
        }
        if (Q.empty()) {
            // 現在地からいけるところまで行った結果、現在地が一番近かった
            Q.emplace(src, Route{{}, {}});
            used[src] = false;
        }
        while (!Q.empty()) {
            auto [u, r] = Q.front();
            Q.pop();
            used[u] = true;
            for (auto&& v : to[u]) {
                if (used[v]) continue;
                if (G[u][dst] < G[v][dst]) continue;  // 遠ざかる場合はSkip
                if (G[u][dst] == G[v][dst] && G[v][dst] > 3)
                    continue;  // 同じ場合でも3近傍以外はSkip
                auto nr = r;
                nr.blockers.emplace_back(v);
                if (v == dst) {
                    routes.emplace_back(nr);
                } else {
                    used[v] = true;
                    Q.emplace(v, nr);
                }
            }
        }
        return routes;
    };
    auto getRoutesSingle(const ll src, const ll dst, const vvll& G, const vvll& to, vector<bool>& used) -> vector<Route> {
        vector<Route> routes;
        using Res = pair<ll, Route>;
        queue<Res> Q;
        Q.emplace(src, Route{{}, {}});
        used[src] = false;
        while (!Q.empty()) {
            auto [u, r] = Q.front();
            Q.pop();
            used[u] = true;
            for (auto&& v : to[u]) {
                if (used[v]) continue;
                if (G[u][dst] < G[v][dst]) continue;  // 遠ざかる場合はSkip
                if (G[u][dst] == G[v][dst] && G[v][dst] > 3)
                    continue;  // 同じ場合でも3近傍以外はSkip
                auto nr = r;
                nr.blockers.emplace_back(v);
                if (v == dst) {
                    routes.emplace_back(nr);
                } else {
                    used[v] = true;
                    Q.emplace(v, nr);
                }
            }
        }
        return routes;
    };
    void initialize(vll& A, const vvll& to, const vvll& G, const vll& T) {
        debug("# start initialize: %lld\n", timer.getMilliSeconds());
        const ll a_len = A.size();
        map<ll, ll> mp;
        ll i = 0;
        unordered_set<ll> notused;
        rep(j, N) { notused.emplace(j); }
        ll src = 0;
        for (auto&& dst : T) {
            while (src != dst) {
                ll dist = G[src][dst];
                for (auto&& v : to[src]) {
                    if (dist > G[v][dst]) {
                        shortestPath.emplace_back(v);
                        if (notused.count(v)) {
                            notused.erase(v);
                            A[i++] = v;
                        }
                        src = v;
                        mp[v]++;
                        break;
                    }
                }
            }
        }
        for (auto&& v : notused) {
            A[i++] = v;
        }
        vector<P> pm;
        for (auto&& [k, v] : mp) {
            pm.emplace_back(v, k);
        }
        ranges::sort(pm, greater<P>{});
        for (auto&& [v, k] : pm) {
            if (i >= a_len) break;
            A[i++] = k;
        }
        debug("# finish initialize: %lld\n", timer.getMilliSeconds());
    }
    void refine(vll& A, const ll th) {
        const ll a_len = A.size();
        rep(i,a_len){
            if(Z[i] < th){
                ll j = i;
                while(j < a_len && Z[j] <  th){
                    if(!timer.isIntime())return;
                    ++j;
                }
                shuffle(A.begin() + i, A.begin() + j, g);
            }
        }
        Z.clear();
    }
    ll fastSearch(ll cur, ll dst, Result& now){
        vector used(N, false);
        auto [path, boundaries] = getBoundaries(cur, dst, to, B, used);
        if (path.size() != 0) {
            cur = now.travel(path);
        } else {
            auto routes = getRoutesMulti(cur, dst, boundaries, G, to, used);
            Route best = *routes.begin();
            for (auto it = next(routes.begin()); it != routes.end(); ++it)
            {
                if(best.blockers.size() != it->blockers.size()) {
                    if(best.blockers.size() > it->blockers.size()) best = *it;
                } else if(best.path.size() != it->path.size()) {
                    if(best.path.size() < it->path.size()) best = *it;
                }
            }
            if (best.path.size() > 0) {
                cur = now.travel(best.path);
            }
            ll _;
            auto [l, a, b, p] = best.getLongestRange2(A, B, _);
            now.changeSignal(l, a, b, A, B);
        }
        return cur;
    }
    ll strictSearch(ll cur, ll dst, Result& now){
        vector used(N, false);
        auto [path, boundaries] = getBoundaries(cur, dst, to, B, used);
        if (path.size() != 0) {
            cur = now.travel(path);
        } else {
            auto routes = getRoutesMulti(cur, dst, boundaries, G, to, used);
            if (!timer.isIntime()) return cur;
            Route best = *routes.begin();
            ll best_distance = linf;
            {
                ll lm1 = 0;
                auto [l1, a1, b1, p1] = best.getLongestRange2(A, B, lm1);
                if(best.path.size()>0)chmin(best_distance, G[best.path.back()][dst]);
                chmin(best_distance, G[p1][dst]);
            }
            for (auto it = next(routes.begin()); it != routes.end() && best_distance != 0; ++it)
            {
                if (!timer.isIntime()) return cur;
                ll lm2 = 0;
                auto [l2, a2, b2, p2] = it->getLongestRange2(A, B, lm2);
                ll d2 = linf;
                if(it->path.size()>0)chmin(d2, G[it->path.back()][dst]);
                chmin(d2, G[p2][dst]);
                if(best_distance > d2){
                    best = *it;
                    best_distance = d2;
                } else if(best_distance == d2){
                    if(best.blockers.size() > it->blockers.size()) {
                        best = *it;
                        best_distance = d2;
                    }
                }
            }
            if (best.path.size() > 0) {
                cur = now.travel(best.path);
            }
            ll _;
            auto [l, a, b, p] = best.getLongestRange2(A, B, _);
            now.changeSignal(l, a, b, A, B, Z);
        }
        return cur;
    }

    // 現在の信号状態で接近できる最も近いところに移動
    ll approachClosest(const ll cur, const ll dst,  const vector<Boundary>& boundaries, Result& now){
        ll nearest = cur;
        vll nearest_path = vll{};
        for(auto b = boundaries.begin(); b != boundaries.end(); ++b){
            ll u = b->name;
            if (G[nearest][dst] > G[u][dst]){
                nearest = u;
                nearest_path = b->path;
            }
        }
        if(nearest_path.size()>0){
            return now.travel(nearest_path);
        }
        return cur;
    }
    ll tenukiSearch(ll cur, ll dst, const auto& boundaries, Result& now, vector<bool>& used){
        cur = approachClosest(cur, dst, boundaries, now);
        auto routes = getRoutesSingle(cur, dst, G, to, used);
        Route best = *routes.begin();
        ll best_distance = linf;
        {
            ll lm1 = 0;
            auto [l1, a1, b1, p1] = best.getLongestRange2(A, B, lm1);
            if(best.path.size()>0)chmin(best_distance, G[best.path.back()][dst]);
            chmin(best_distance, G[p1][dst]);
        }
        for (auto it = next(routes.begin()); it != routes.end(); ++it)
        {
            ll lm2 = 0;
            auto [l2, a2, b2, p2] = it->getLongestRange2(A, B, lm2);
            ll d2 = linf;
            if(it->path.size()>0)chmin(d2, G[it->path.back()][dst]);
            chmin(d2, G[p2][dst]);
            if(best_distance > d2){
                best = *it;
                best_distance = d2;
            } else if(best_distance == d2){
                if(best.blockers.size() < it->blockers.size()) {
                    best = *it;
                    best_distance = d2;
                }
            }
        }
        if (best.path.size() > 0) {
            cur = now.travel(best.path);
        }
        ll _;
        auto [l, a, b, p] = best.getLongestRange2(A, B, _);
        now.changeSignal(l, a, b, A, B, Z);
        return cur;
    }
};

#ifndef TIMELIMIT
constexpr ll msLimit = 2900;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    CIN(ll, N);
    CIN(ll, M);
    CIN(ll, Lt);
    CIN(ll, La);
    vll A(La);
    CIN(ll, Lb);
    vll B(Lb, -1);
    vvll to(N);
    vvll G(N, vll(N, linf));
    rep(i, N) { G[i][i] = 0; }
    rep(_, M) {
        CIN(ll, u);
        CIN(ll, v);
        to[u].emplace_back(v);
        to[v].emplace_back(u);
        G[u][v] = 1;
        G[v][u] = 1;
    }
    vll T(Lt);
    for (auto& v : T) {
        cin >> v;
    }
    vector XY(N, P{});
    for (auto& [l, r] : XY) {
        cin >> l;
        cin >> r;
    }
    debug("# start wf: %lld\n", timer.getMilliSeconds());
    rep(k, N) rep(i, N) rep(j, N) { chmin(G[i][j], G[i][k] + G[k][j]); }
    debug("# finish wf: %lld\n", timer.getMilliSeconds());
    SolverB solver(N, move(A), move(B), move(to), move(G), move(T), move(timer));
    solver.solve();
    solver.write();
    return 0;
}
