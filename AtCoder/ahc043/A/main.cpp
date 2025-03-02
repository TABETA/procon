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
#include <atcoder/all>
using namespace atcoder;
using P = pair<ll, ll>;
ll N;
ll distance(P a, P b) {
    return abs(a.first - b.first) + abs(a.second - b.second) + 1;
}
ll toID(P p) {
    auto [y, x] = p;
    return y * N + x;
}
struct Resident {
    P home;
    P work;
    ll dist;
    Resident() : home{}, work{}, dist{} {}
    Resident(P home, P work) : home{home}, work{work}, dist{distance(home,work)} {}
    Resident(ll dist) : home{}, work{}, dist{dist} {}
    bool operator<(const Resident& r) const {
        return dist < r.dist;
    }
    bool isConnected(dsu& uf) {
        return uf.same(toID(home), toID(work));
    }
    ll getIncome(dsu& uf){
        if (isConnected(uf)) {
            return dist-1;
        }
        return 0;
    }
};


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
class Solver {
    enum BuildResult {
        NOP = 0,
        NOMONEY = 1,
        DONE = 2,
    };

    ll limit;
    ll M;
    ll K;
    ll T;
    set<Resident> R;
    vvll G;
    dsu uf;
    ll income;
    Timer timer;

   public:
    Solver(ll M, ll K, ll T, vector<Resident> R, Timer&& timer)
        :
          M(M),
          K(K),
          T(T),
          R{R.begin(), R.end()},
          G(N, vll(N, -1)),
          uf(N * N),
          income(),
          timer(timer) {}
    ~Solver() {}
    auto pathToRails(deque<P> path) {
        deque<pair<ll, P>> rails;
        reps(i, 1, path.size() - 1) {
            auto [sy, sx] = path[i - 1];  // 前の点
            auto [cy, cx] = path[i];      // 現在の点
            auto [ty, tx] = path[i + 1];  // 次の点

            int type;
            if (sy == ty) {  // 横方向の線路
                type = 1;
            } else if (sx == tx) {  // 縦方向の線路
                type = 2;
            } else {  // カーブの線路
                // 現在の点から見て、前の点と次の点の位置関係を判定
                bool from_left = (sx < cx);
                bool from_right = (sx > cx);
                bool from_up = (sy < cy);
                bool from_down = (sy > cy);
                bool to_left = (tx < cx);
                bool to_right = (tx > cx);
                bool to_up = (ty < cy);
                bool to_down = (ty > cy);

                if ((from_left && to_down) || (from_down && to_left)) {
                    type = 3;  // 左から下、または下から左
                } else if ((from_left && to_up) || (from_up && to_left)) {
                    type = 4;  // 左から上、または上から左
                } else if ((from_right && to_up) || (from_up && to_right)) {
                    type = 5;  // 右から上、または上から右
                } else {  // (from_right && to_down) || (from_down && to_right)
                    type = 6;  // 右から下、または下から右
                }
            }
            rails.emplace_back(type, path[i]);
        }
        // 建築コストが高いので後回し
        rails.emplace_back(0, path.front());
        rails.emplace_back(0, path.back());
        return rails;
    }
    int connectStation(P a, P b) {
        return uf.merge(toID(a), toID(b));
    }
    void buildStation(P a){
        auto [sy, sx] = a;
        reps(dy, -2, 3) {
            reps(dx, -2, 3) {
                if (abs(dy) + abs(dx) > 2) continue;
                auto np = P(sy + dy, sx + dx);
                auto [ny, nx] = np;
                if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                connectStation(a, np);
            }
        }
    }
    bool shouldBeBuild(ll remainTime, ll timeToBuild) {
        return calcProfit(remainTime, timeToBuild) > 0;
    }
    ll calcProfit(ll remainTime, ll timeToBuild) {
        auto before = income * remainTime;
        auto costToBuild = (((timeToBuild-2) * 100) + 2*5000);
        if(costToBuild > K) return -linf;
        auto after = (income + timeToBuild) * (remainTime - timeToBuild) + income * timeToBuild - costToBuild;
        return after - before;
    }
    void solve() {
        set<Resident> remains = R;
        auto getRails = [&](auto it){
            auto p = searchPath(it->home, it->work);
            return pathToRails(p);
        };
        auto toD = [](ll K)->ll{
            if(K > 10000){
                return 2 + (K-10000)/100;
            } else {
                return 0;
            }
        };
        auto it = remains.lower_bound(Resident{toD(K)});
        if(it != remains.begin())--it;
        deque<pair<ll, P>> rails = getRails(it);
        bool done = false;
        repd(remT, T) {
            if(done || remains.empty()){
                wait();
            } else {
                if(rails.empty()){
                    if(it != remains.end()){
                        buildStation(it->home);
                        buildStation(it->work);
                        connectStation(it->home, it->work);
                        remains.erase(it);
                        calcIncome();
                    }
                    it = remains.lower_bound(Resident{toD(K)});
                    if(it != remains.begin())--it;
                    if(it != remains.end()){
                        rails = getRails(it);
                        if(!shouldBeBuild(remT, rails.size())){
                            done = true;
                        }
                    }
                }
                if(!done && !rails.empty()){
                    auto [t, p] = rails.front();
                    switch (tryBuild(t, p))
                    {
                    case BuildResult::NOMONEY:
                        break;
                    case BuildResult::DONE:
                        rails.pop_front();
                        break;
                    case BuildResult::NOP:
                        rails.pop_front();++remT;
                        continue;
                    default:
                        break;
                    }
                } else {
                    wait();
                }
            }
            K += income;
            printf("#%lld\n", K);
        }
    }
    void solve1() {
        set<Resident> remains = {R.begin(), R.end()};
        set<pair<ll, Resident>, greater<pair<ll, Resident>>> orderedRemains;
        auto it = orderedRemains.end();
        deque<pair<ll, P>> rails;
        bool done = false;
        repd(remT, T) {
            auto refresh = [&](){
                if(!done && rails.empty()){
                    if(it != orderedRemains.end()){
                        auto [p, r] = *it;
                        buildStation(r.home);
                        buildStation(r.work);
                        connectStation(r.home, r.work);
                        remains.erase(r);
                        calcIncome();
                    }
                    orderedRemains.clear();
                    for (auto &&r : remains){
                        ll p = calcProfit(remT, r.dist);
                        orderedRemains.emplace(p, r);
                    }
                    for(it = orderedRemains.begin(); it != orderedRemains.end(); ++it){
                        auto profit = it->first;
                        if(profit <= 0){
                            done = true;
                            break;
                        }
                        auto r = it->second;
                        auto p = searchPath(r.home, r.work);
                        if(p.size() == 0) continue;
                        rails = pathToRails(p);
                        break;
                    }
                }
            };
            if(done || remains.empty()){
                wait();
            } else {
                refresh();
                if(!done && !rails.empty()){
                    auto [t, p] = rails.front();
                    switch (tryBuild(t, p))
                    {
                    case BuildResult::NOMONEY:
                        break;
                    case BuildResult::DONE:
                        rails.pop_front();
                        break;
                    case BuildResult::NOP:
                        rails.pop_front();++remT;
                        continue;
                    default:
                        break;
                    }
                } else {
                    wait();
                }
            }
            refresh();
            K += income;
        }
        printf("#%lld\n", K);
    }
    void solve2() {
        set<Resident> remains = {R.begin(), R.end()};
        using TP = pair<ll, tuple<P, P, vector<Resident>>>;
        set<TP, greater<TP>> orderedStations;  // <収益, <駅1の位置, 駅2の位置, Residents>>
        deque<pair<ll, P>> rails;
        vector<P> stationsToBuild;  // 駅の建設を保留するためのキュー
        vector<Resident> residentsToConnect; 
        bool done = false;
    
        auto calcPathCost = [&](const deque<P>& path) -> ll {
            if (path.empty()) return linf;
            return (path.size() - 2) * 100; // 中間の線路のみ
        };
        map<P, set<P>> cached_area;
    
        auto getArea = [&](P pos) {
            if (cached_area.count(pos)) return cached_area[pos];
            set<P> area;
            reps(dy, -2, 3) reps(dx, -2, 3) {
                if (abs(dy) + abs(dx) > 2) continue;
                ll ny = pos.first + dy;
                ll nx = pos.second + dx;
                if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                area.emplace(ny, nx);
            }
            return cached_area[pos] = area;
        };

        auto calcStationsPair = [&](P pos1, P pos2, ll remT) -> pair<ll, vector<Resident>> {
            ll totalBuildCost = 0;  
            // 既存の駅でない場合のみコストを加算
            if (G[pos1.first][pos1.second] != 0) totalBuildCost += 5000;
            if (G[pos2.first][pos2.second] != 0) totalBuildCost += 5000;
            
            auto area1 = getArea(pos1);
            auto area2 = getArea(pos2);
            
            ll rails_count = abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second)-1;
            ll rails_cost = rails_count * 100;  // 駅間の経路建設コストの見積もり
            totalBuildCost += rails_cost;
            vector<Resident> residents;
            if (totalBuildCost > K) {
                return {-linf, residents};
            }
            
            ll expectedIncome = 0;
            // 各Residentについて、2つの駅との接続可能性を確認
            for (const auto& r : remains) {
                bool ok = false;
                if(area1.count(r.home)){
                    if(area2.count(r.work)){
                        ok = true;
                    }
                } else {
                    if(area1.count(r.work)){
                        if(area2.count(r.home)){
                            ok = true;
                        }
                    }
                }
                // home-workが別々の駅のエリアにある場合のみ有効
                if (ok) {
                    ll unitProfit = abs(r.home.first - r.work.first) + abs(r.home.second - r.work.second);
                    expectedIncome += unitProfit;
                    residents.emplace_back(r);
                }
            }
            auto turnsToBuild = rails_count + 2;
            auto totalExpectedIncome =  (totalBuildCost > K) ? -linf : expectedIncome * (remT - turnsToBuild) - totalBuildCost + turnsToBuild * income;
            return {totalExpectedIncome, residents};
        };
    
        auto refresh = [&](ll remT){
            set<pair<P,P>> used;
            if (rails.empty()) {
                if (!stationsToBuild.empty()) {
                    for (auto pos : stationsToBuild) {
                        buildStation(pos);
                    }
                    stationsToBuild.clear();
                    for (auto &&r : residentsToConnect){
                        connectStation(r.home, r.work);
                    }
                    residentsToConnect.clear();
                }

                orderedStations.clear();
                
                // 各Residentについて、homeとwork周辺の駅候補を探索
                for (const auto& r : remains) {
                    // home周辺の候補点を列挙
                    auto home_candidates = getArea(r.home);
                    auto work_candidates = getArea(r.work);
                    
                    // home_candidatesとwork_candidatesの組み合わせを評価
                    for (const auto& pos1 : home_candidates) {
                        for (const auto& pos2 : work_candidates) {
                            auto p1 = pos1;
                            auto p2 = pos2;
                            if (p1 > p2) swap(p1, p2);
                            if (used.count({p1, p2})) continue;
                            used.emplace(p1, p2);
                            if (abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second) <= 4) continue;
                            if (uf.same(toID(pos1), toID(pos2))) continue;
                            
                            auto [profit, residents] = calcStationsPair(pos1, pos2, remT);
                            if (profit > 0) {
                                orderedStations.emplace(profit, make_tuple(pos1, pos2, residents));
                                if(orderedStations.size() > 3) {
                                    orderedStations.erase(--orderedStations.end());
                                }
                            }
                        }
                    }
                }
            }
        };
        repd(remT, T) {
            if (done || remains.empty()) {
                wait();
                K += income;
                continue;
            }
            refresh(remT);
            while (rails.empty()) {
                if(orderedStations.empty()){
                    done = true;
                    wait();
                    break;
                }
                auto it = orderedStations.begin();
                auto [profit, station_info] = *it;
                auto [pos1, pos2, residents] = station_info;
                auto path = searchPath(pos1, pos2);
                ll pathCost = calcPathCost(path);
                if (pathCost == linf) {
                    orderedStations.erase(it);
                    continue;
                }
                if (G[pos1.first][pos1.second] != 0) pathCost += 5000;
                if (G[pos2.first][pos2.second] != 0) pathCost += 5000;
                if (pathCost > K) {
                    orderedStations.erase(it);
                    continue;
                }
                rails = pathToRails(path);
                stationsToBuild.emplace_back(pos1);
                stationsToBuild.emplace_back(pos2);
                residentsToConnect = residents;
                break;
            }
            if (!done && !rails.empty()) {
                auto [t, p] = rails.front();
                switch (tryBuild(t, p)) {
                    case BuildResult::NOMONEY:
                        break;
                    case BuildResult::DONE:
                        rails.pop_front();
                        break;
                    case BuildResult::NOP:
                        rails.pop_front();
                        ++remT;
                        continue;
                    default:
                        break;
                }
            }
            refresh(remT);
            calcIncome();  // 収入を計算
            K += income;
        }
    }

    deque<P> searchPath(P s, P t) {
        auto next_adjacents = [&](P p) {
            auto [r, c] = p;
            vector<P> ret;
            for (auto&& q : {
                     P{r - 1, c},
                     P{r + 1, c},
                     P{r, c - 1},
                     P{r, c + 1},
                 }) {
                auto [y, x] = q;
                if (y < 0 || y >= N || x < 0 || x >= N) continue;
                if(G[y][x] > 0) continue;
                ret.push_back(q);
            }
            return ret;
        };
        deque<P> result;
        queue<tuple<P, set<P>, deque<P>>> Q;
        Q.emplace(s, set<P>{s}, deque<P>{s});
        set<P> used;
        used.insert(s);
        while (!Q.empty()) {
            auto [u, ps, path] = Q.front();Q.pop();
            if(u == t){
                result = path;
                break;
            }
            for (auto&& v : next_adjacents(u)) {
                if (ps.count(v)) continue;
                if (used.count(v)) continue;
                used.insert(v);
                auto nps = ps;
                nps.insert(v);
                auto npath = path;
                npath.emplace_back(v);
                Q.emplace(v, nps, npath);
            }
        }
        return result;
    }
    void wait() {
        cout << -1 << '\n';
    }
    BuildResult tryBuild(ll i, P p) {
        auto [y, x] = p;
        if (G[y][x] != -1) return BuildResult::NOP;
        auto cost = i == 0 ? 5000 : 100;
        if (K < cost) {
            wait();
            return BuildResult::NOMONEY;
        }
        K -= cost;
        G[y][x] = i;
        cout << i << " " << y << " " << x << '\n';
        return BuildResult::DONE;
    }
    ll calcIncome() {
        income = 0;
        for (auto r : R){
            income += r.getIncome(uf);
        }
        return income;
    }
};
#ifndef TIMELIMIT
constexpr ll msLimit = 2800;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    cin >> N;
    CIN(ll, M);
    CIN(ll, K);
    CIN(ll, T);
    vector R(M, Resident{});
    rep(i, M) {
        CIN(ll, home_y);
        CIN(ll, home_x);
        CIN(ll, work_y);
        CIN(ll, work_x);
        R[i] = Resident{P(home_y, home_x), P(work_y, work_x)};
    }
    Solver solver(M, K, T, move(R), move(timer));
    solver.solve2();
    return 0;
}
