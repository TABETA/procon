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
#include <atcoder/all>
using namespace atcoder;
using P = pair<ll, ll>;

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
        return ok;
    };
};
auto rand_between = [](ll min, ll max) -> ll {
    return min + rand() % (max - min);
};

auto get_random_key = [](map<ll, ll>& mp) -> ll {
    auto it = mp.begin();
    advance(it, rand() % mp.size());
    return it->first;
};

auto decrease_key = [](map<ll, ll>& mp, ll key) {
    mp[key]--;
    if (mp[key] == 0) {
        mp.erase(key);
    }
};

// ---------------------------
// input values
// ---------------------------
ll N, M, Q, L, W;
vll G;
vector<tuple<ll, ll, ll, ll>> R;
#ifndef ONLINE_JUDGE
map<ll, P> TC;
#endif

void g_input() {
    cin >> N >> M >> Q >> L >> W;
    G.resize(M);
    for (auto& i : G) {
        cin >> i;
    }
    R.resize(N);
    for (auto& [i, j, k, l] : R) {
        cin >> i >> j >> k >> l;
    }
#ifndef ONLINE_JUDGE
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        TC[i] = {x, y};
    }
#endif
}

// ---------------------------
double jucridean_distance(const P& a, const P& b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}
auto getMinimumSpanningTree(const map<ll, P>& coords) {
    // 各頂点間の距離を計算
    vector<tuple<double, ll, ll>> edges;
    for (auto&& [i, p1] : coords) {
        for (auto&& [j, p2] : coords) {
            if (i == j) break;
            auto dist = jucridean_distance(p1, p2);
            edges.emplace_back(dist, j, i);
        }
    }
    // Kruskalのアルゴリズムで最小全域木を構築
    sort(all(edges));
    dsu uf(N);
    map<ll, set<ll>> tree;
    for (auto [d, u, v] : edges) {
        if (!uf.same(u, v)) {
            uf.merge(u, v);
            tree[u].emplace(v);
            tree[v].emplace(u);
        }
    }
    return tree;
}
ll getEndPoint(const vvll& tree) {
    // 木の直径を求める（2回のBFS）
    auto bfs = [&](ll start) -> ll {
        vector<ll> dist(N, -1);
        queue<ll> q;
        q.push(start);
        dist[start] = 0;
        ll max_dist = 0, max_vertex = start;

        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            for (ll u : tree[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                    if (dist[u] > max_dist) {
                        max_dist = dist[u];
                        max_vertex = u;
                    }
                }
            }
        }
        return max_vertex;
    };

    // 最初の端点を見つける
    // その端点から最も遠い点（もう一方の端点）を見つける
    return bfs(bfs(0));
}
vll getLeaves(const map<ll, set<ll>>& tree) {
    vll leaves;
    for (auto&& [u, vs] : tree) {
        if (vs.size() == 1) {
            leaves.push_back(u);
        }
    }
    return leaves;
}

struct Group {
    vll cities;
    vector<P> edges;
    Group() {}
    Group(ll n) : cities(n) {}
    vvll split_by_length(const vll& path, ll length) {
        vvll res;
        const ll n = path.size();
        ll i = 0;
        while (i < n) {
            vll now;
            while (i < n && (ll)now.size() < length) {
                now.push_back(path[i++]);
            }
            res.push_back(now);
            if (i == n) break;
            --i;
        }
        return res;
    }
    auto input(vll nodes) {
        const ll n = nodes.size() - 1;
        vector<P> res(n);
#ifdef ONLINE_JUDGE
        rep(i, n) { cin >> res[i].first >> res[i].second; }
#else
        map<ll, P> c;
        for (auto&& j : nodes) {
            c[j] = TC[j];
        }
        auto tree = getMinimumSpanningTree(c);
        ll i = 0;
        for (auto&& [u, vs] : tree) {
            for (auto&& v : vs) {
                if (u > v) continue;
                assert(i < n);
                res[i] = {u, v};
                ++i;
            }
        }
#endif
        return res;
    }
    void query() {
        auto splitted = split_by_length(cities, L);
        vector<P> actual;
        rep(i, splitted.size()) {
            cout << "? " << splitted[i].size();
            for (auto&& j : splitted[i]) {
                cout << " " << j;
            }
            cout << endl;
            auto res = input(splitted[i]);
            edges.insert(edges.end(), make_move_iterator(res.begin()),
                         make_move_iterator(res.end()));
        }
    }
    void print() const {
        for (auto&& c : cities) {
            cout << c << " ";
        }
        cout << endl;
        for (auto&& [a, b] : edges) {
            cout << a << " " << b << endl;
        }
    }
};

class Solver {
    Timer timer;

   public:
    Solver(Timer&& timer) : timer(timer) {}

    ~Solver() {}
    void answer(const vector<Group>& G) {
        cout << "!" << endl;
        for (auto&& g : G) {
            g.print();
        }
    }
    auto getRoots(deque<vll>& q, map<ll,vector<pair<ll, vll>>> &waiting, map<ll, vvll>& substandards,
                  map<ll, set<ll>>& tree, ll lim) {
        map<ll, vector<pair<ll, vll>>> roots;
        set<ll> resolved;
        while (!q.empty()) {
            vll branch = q.front();q.pop_front();
            auto dfs = [&](auto dfs, ll u, ll pre) -> bool {
                branch.push_back(u);
                if (pre != -1) {
                    if (waiting.count(u)) {
                        return true;
                    }
                }
                if ((ll)branch.size() >= lim) {
                    return false;
                }
                if (tree.count(u) && tree[u].size() > 2) return true;
                bool ok = true;
                if(tree.count(u)){
                    for (auto&& v : tree[u]) {
                        if (pre == v) continue;
                        if (ok) ok &= dfs(dfs, v, u);
                    }
                }
                return ok;
            };
            ll leaf = branch.back();
            if(roots.count(leaf)){
                roots[leaf].emplace_back(leaf, branch);
            } else {
                branch.pop_back();
                if (dfs(dfs, leaf, -1)) {
                    auto c = branch.back();
                    if (waiting.count(c)) {
                        waiting[c].emplace_back(leaf, branch);
                        resolved.insert(c);
                    } else {
                        roots[c].emplace_back(leaf, branch);
                    }
                } else {
                    substandards[branch.back()].push_back(branch);
                }
            }
        }
        for (auto &&c : resolved){
            for (auto &&[leaf, path] : waiting[c]){
                roots[c].emplace_back(leaf, path);
            }
            waiting.erase(c);
        }
        return roots;
    }
    // Kruskal's algorithmを使って、全ての町の最小全域木を求める。
    // その後、各ノードの次数が1のものだけを取り出す。
    // 次数が1のノードを使って多始点BFSを行う。他の探索点と合流した場合、そこまでに見つかった経路をマージする。
    auto grouping(map<ll, set<ll>>& tree, map<ll, ll> mp, bool& mst) {
        map<ll, vvll> ans;
        ll lim = mp.rbegin()->first;
        vll leaves = getLeaves(tree);
        deque<vll> q;
        map<ll, vector<pair<ll, vll>>> waiting;
        map<ll, vvll> substandards;
        auto push = [&](const vll& family) {
            auto c = family.back();
            if (tree.count(c) && tree[c].size() > 1) {
                waiting[c].emplace_back(-1, family);
                return;
            }
            ll s = family.size();
            if (s >= lim){
                substandards[c].push_back(family);
                return;
            }
            q.push_back(family);
            if (mp.count(s)) {
                ans[c].push_back(family);
                decrease_key(mp, s);
            }
        };
        auto pop = [&](ll key) {
            if (ans.count(key) == 0) return;
            for (auto &&family : ans[key]){
                auto s = family.size();
                mp[s]++;
            }
            ans.erase(key);
        };
        for (auto&& leaf : leaves) {
            auto family = vll{leaf};
            push(family);
        }
        auto removePath = [&](const vll& path) {
            ll u = -1;
            for (auto&& v : path) {
                if (u != -1) {
                    if(tree.count(u)){
                        tree[u].erase(v);
                        if (tree[u].empty()) {
                            tree.erase(u);
                        }
                    } 
                    if(tree.count(v)) {
                        tree[v].erase(u);
                        if (tree[v].empty()) {
                            tree.erase(v);
                        }
                    } 
                }
                u = v;
            }
        };
        auto restorePath = [&](const vll& path) {
            ll u = -1;
            for (auto&& v : path) {
                if (u != -1) {
                    tree[u].emplace(v);
                    tree[v].emplace(u);
                }
                u = v;
            }
        };
        while (true) {
            auto roots = getRoots(q, waiting, substandards, tree, lim);
            for (auto&& [c, branches] : roots) {
                // const ll s = [&]() {
                //     ll s = 1;
                //     for (auto&& [leaf, branch] : branches) {
                //         s += branch.size() - 1;
                //     }
                //     return s;
                // }();
                // ここでcontinueすると、その枝が消えてしまう。
                // if (s > lim) continue;
                vll leaves;
                auto family = [&]() {
                    vll res;
                    for (auto&& [leaf, branch] : branches) {
                        removePath(branch);
                        res.insert(res.end(), branch.begin(), branch.end());
                        res.pop_back();
                        leaves.push_back(leaf);
                    }
                    res.push_back(c);
                    return res;
                }();
                for (auto&& leaf : leaves) {
                    pop(leaf);
                }
                push(family);
            }
            // 答えが見つかった順に返していく
            if (!ans.empty()) {
                for (auto &&[k, v] : waiting){
                    for (auto &&[_, path] : waiting[k]){
                        restorePath(path);
                    }
                }
                break;
            } 
            if (q.empty() || tree.size() == 0) {
                // if (!ans.empty()) {
                //     for (auto &&[k, v] : waiting){
                //         for (auto &&[_, path] : waiting[k]){
                //             restorePath(path);
                //         }
                //     }
                //     break;
                // } 
                if(substandards.size() > 0) {
                    bool ok = [&](){
                        for (auto &&[key, branches] : substandards){
                            for (auto &&branch : branches){
                                if((ll)branch.size() == lim) {
                                    ans[key].push_back(branch);
                                    removePath(branch);
                                    return true;
                                }
                            }
                        }
                        return false;
                    }();
                    if(!ok){
                        auto forceReturn = [&](){
                            mst = true;
                            map<ll, vvll> ans;
                            for (auto&& [key, branches] : substandards) {
                                vll family;
                                for (auto&& branch : branches) {
                                    auto it = mp.lower_bound(branch.size());
                                    if(it == mp.begin())continue;
                                    --it;
                                    ll s = it->first;
                                    family.insert(family.end(), branch.begin(), branch.begin()+s);
                                    removePath(family);
                                    ans[family.back()].push_back(family);
                                    return ans;
                                }
                            }
                            assert(false);
                            return ans;
                        };
                        ans = forceReturn();
                    }
                    break;
                } else {
                    auto forceReturn = [&](){
                        mst = true;
                        map<ll, vvll> ans;
                        for (auto&& [c, branches] : roots) {
                            vll family;
                            for (auto&& [leaf, branch] : branches) {
                                auto it = mp.lower_bound(branch.size());
                                if(it == mp.begin())continue;
                                --it;
                                ll s = it->first;
                                family.insert(family.end(), branch.begin(), branch.begin()+s);
                                removePath(family);
                                ans[family.back()].push_back(family);
                                return ans;
                            }
                        }
                        assert(false);
                        return ans;
                    };
                    ans = forceReturn();
                }
                break;
            }
        }
        return ans;
    }

    void solve() {
        map<ll, P> coords;
        rep(i, N) {
            auto&& [x1, x2, y1, y2] = R[i];
            coords[i] = {(x1 + x2) / 2, (y1 + y2) / 2};
        }
        set<P> gg;
        rep(i, M) { gg.emplace(G[i], i); }
        vector<Group> ans(M);
        map<ll, set<ll>> tree;
        bool mst = true;
        set<ll> used;
        [&]() {
            // while (timer.isIntime() && Q--)
            {
                vector<Group> now(M);
        
                while (!gg.empty()) {
                    if(mst || (ll)(tree.size() + used.size()) != N){
                        tree = getMinimumSpanningTree(coords);
                        // for (auto &&[u, vs] : tree){
                        //     for (auto &&v : vs){
                        //         if(u > v) continue;
                        //         cout << u << " " << v << endl;
                        //     }
                        // }
                        mst = false;
                    }
                    if (gg.rbegin()->first == 1) {
                        auto it = gg.begin();
                        auto c = coords.begin();
                        auto u = c->first;
                        assert(!used.count(u));
                        used.emplace(u);
                        now[it->second].cities = {u};
                        coords.erase(c);
                        gg.erase(it);
                        {
                            if(tree.count(u)){
                                for (auto &&v : tree[u]){
                                    tree[v].erase(u);
                                    if (tree[v].empty()) {
                                        tree.erase(v);
                                    }
                                }
                                tree.erase(u);
                            }
                        }
                    } else {
                        map<ll, ll> mp;
                        for (auto&& [s, i] : gg) {
                            if(s == 1) continue;
                            mp[s]++;
                        }
                        // cout << "tree: " << tree.size() << endl;
                        // cout << "used: " << used.size() << endl;
                        auto maps = grouping(tree, mp, mst);
                        for (auto&& [_, groups] : maps) {
                            for (auto&& group : groups) {
                                ll s = group.size();
                                auto g = Group{};
                                g.cities = group;
                                [&]() {
                                    repr(j, g.cities) {
                                        coords.erase(j);
                                        assert(!used.count(j));
                                        used.emplace(j);
                                    }
                                }();
                                g.query();
                                auto it = gg.lower_bound({s, 0});
                                assert(it != gg.end());
                                now[it->second] = g;
                                gg.erase(it);
                                {
                                    ll u = g.cities.back();
                                    if(tree.count(u)){
                                        for (auto &&v : tree[u]){
                                            tree[v].erase(u);
                                            if (tree[v].empty()) {
                                                tree.erase(v);
                                            }
                                        }
                                        tree.erase(u);
                                    }
                                }
                            }
                        }
                    }
                }
                ans = now;
            }
        }();
        // #ifdef _DEBUG
        //         cerr << "result: " << score << endl;
        // #endif
        answer(ans);
    }
};
#ifndef TIMELIMIT
constexpr ll msLimit = 1800;
#else
constexpr ll msLimit = TIMELIMIT;
#endif

int main() {
    Timer timer(msLimit);
    g_input();
    Solver solver(move(timer));
    solver.solve();
    return 0;
}
