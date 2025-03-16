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
#include <atcoder/all>
using namespace atcoder;
using P = pair<ll, ll>;
ll N;
ll L;
map<ll,ll> mp;
double average_required_visits = 0;
struct Employee{
    ll a;
    ll b;
    ll t;
    ll T;
    ll i;
    ll score() const{
        return abs(t - T);
    }
};
vector<Employee> E;

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

auto get_random_key = [](map<ll,ll>& mp) -> ll {
    auto it = mp.begin();
    advance(it, rand() % mp.size());
    return it->first;
};

auto decrease_key = [](map<ll,ll>& mp, ll key) {
    mp[key]--;
    if(mp[key] == 0){
        mp.erase(key);
    }
};

// 重み付きランダム選択のための関数を追加
auto get_weighted_random_key = [](const map<ll,ll>& mp, const vector<Employee>& E) -> ll {
    vector<pair<ll,double>> weights;
    double total_weight = 0;
    
    // 各ノードの重みを計算
    for(const auto& [key, remaining] : mp) {
        // 残り必要回数が多いほど重みを大きくする
        double weight = remaining;
        weights.push_back({key, weight});
        total_weight += weight;
    }
    
    // ルーレット選択
    double r = (double)rand() / RAND_MAX * total_weight;
    double sum = 0;
    for(const auto& [key, weight] : weights) {
        sum += weight;
        if(r <= sum) {
            return key;
        }
    }
    return weights.back().first;
};

#include <random>  // 乱数生成器用のヘッダーを追加
map<ll, double> createNormalizedWeights(const map<ll, ll>& mp) {
    map<ll, double> normalized_mp;
    const double TOTAL_TRANSITIONS = 200.0;  // 合計遷移数
    double sum_weights = 0.0;
    
    // 各ノードの訪問回数を正規化
    for (const auto& [key, visits] : mp) {
        sum_weights += visits;
    }
    
    for (const auto& [key, visits] : mp) {
        double normalized_weight = (visits / sum_weights) * TOTAL_TRANSITIONS;
        normalized_mp[key] = std::max(0.1, normalized_weight);
    }
    
    return normalized_mp;
}

// 正規化された重みを用いた重み付きランダム選択
auto get_normalized_random_key = [](const map<ll, ll>& mp) -> ll {
    auto normalized_weights = createNormalizedWeights(mp);
    vector<pair<ll, double>> weights;
    double total_weight = 0.0;
    
    for (const auto& [key, weight] : normalized_weights) {
        weights.push_back({key, weight});
        total_weight += weight;
    }
    
    double r = (double)rand() / RAND_MAX * total_weight;
    double sum = 0.0;
    for (const auto& [key, weight] : weights) {
        sum += weight;
        if (r <= sum) {
            return key;
        }
    }
    
    return weights.back().first;
};

class Solver {
    Timer timer;
    std::mt19937 rng;  // 乱数生成器を追加

    // 次のノードを取得する関数
    ll getNextNode(ll pos, bool odd, const vector<Employee>& emp) const {
        return odd ? emp[pos].a : emp[pos].b;
    }

   public:
    Solver(Timer&& timer)
        : timer(timer), rng(std::random_device{}()) {}  // 乱数生成器の初期化を追加
    
    ~Solver() {}
    ll calcScore(const vector<Employee>& emp){
        ll r = 0;
        rep(i,N){
            r += emp[i].score();
        }
        return r;
    }

    ll calcScoreNormal(vector<Employee> emp) {
        ll cur = 0;
        rep(i, 500000) {
            emp[cur].t++;
            bool isOdd = (emp[cur].t % 2 == 1);
            if(isOdd) cur = emp[cur].a;
            else cur = emp[cur].b;
        }
        ll score = 0;
        rep(i, N) {
            score += abs(emp[i].t - emp[i].T);
        }
        return score;
    }

    ll calcScoreOptimized(vector<Employee> emp) {
        // より安全な実装に変更
        ll curr = 0;
        const ll total_steps = 500000;
        
        // すべてのノードの訪問回数をリセット
        rep(i, N) emp[i].t = 0;

        // サイクル検出のための訪問状態履歴
        vector<pair<ll, ll>> visited_states;
        map<pair<ll, ll>, ll> state_to_index;

        for (ll step = 0; step < total_steps; step++) {
            // 現在のノードの訪問回数を増加
            emp[curr].t++;
            
            // 現在の状態（ノード番号, 奇数フラグ）
            pair<ll, ll> state = {curr, emp[curr].t % 2};
            
            // 以前に同じ状態を訪問したかチェック
            if (state_to_index.count(state)) {
                // サイクルを検出
                ll cycle_start = state_to_index[state];
                ll cycle_length = step - cycle_start;
                
                // 安全チェック: サイクル長が有効か
                if (cycle_length <= 0) {
                    // 無効なサイクルの場合はシミュレーションを続行
                    bool isOdd = (emp[curr].t % 2 == 1);
                    curr = isOdd ? emp[curr].a : emp[curr].b;
                    continue;
                }
                
                ll remaining_steps = total_steps - step - 1;
                if (remaining_steps <= 0) break;
                
                // サイクルの各ノードでの訪問回数を計算
                vector<ll> visits_per_cycle(N, 0);
                ll temp_pos = curr;
                ll temp_visits = emp[temp_pos].t;
                
                // 1サイクル分の訪問回数を計算
                for (ll i = 0; i < cycle_length; i++) {
                    bool temp_isOdd = ((temp_visits + 1) % 2 == 1); // 次の訪問が奇数かどうか
                    temp_pos = temp_isOdd ? emp[temp_pos].a : emp[temp_pos].b;
                    
                    // インデックス範囲チェック
                    if (temp_pos < 0 || temp_pos >= N) {
                        // 無効なインデックスなら中断
                        goto simulate_normally;
                    }
                    
                    visits_per_cycle[temp_pos]++;
                    temp_visits++;
                }
                
                // 完全なサイクル数を計算
                ll full_cycles = remaining_steps / cycle_length;
                
                // サイクル分の訪問回数を一括加算
                rep(i, N) {
                    emp[i].t += visits_per_cycle[i] * full_cycles;
                }
                
                // 残りのステップを1つずつシミュレート
                ll extra_steps = remaining_steps % cycle_length;
                for (ll i = 0; i < extra_steps; i++) {
                    bool isOdd = (emp[curr].t % 2 == 1);
                    curr = isOdd ? emp[curr].a : emp[curr].b;
                    
                    // インデックス範囲チェック
                    if (curr < 0 || curr >= N) break;
                    
                    emp[curr].t++;
                }
                
                break;
            }
            
            simulate_normally:
            // 状態を記録
            state_to_index[state] = step;
            visited_states.push_back(state);
            
            // 次のノードに移動
            bool isOdd = (emp[curr].t % 2 == 1);
            curr = isOdd ? emp[curr].a : emp[curr].b;
            
            // インデックス範囲チェック
            if (curr < 0 || curr >= N) break;
        }
        
        // もしサイクル検出でエラーが発生した場合はナイーブな方法で再計算
        if (curr < 0 || curr >= N) {
            curr = 0;
            rep(i, N) emp[i].t = 0;
            
            for (ll step = 0; step < min(total_steps, 10000LL); step++) {
                emp[curr].t++;
                bool isOdd = (emp[curr].t % 2 == 1);
                curr = isOdd ? emp[curr].a : emp[curr].b;
                
                if (curr < 0 || curr >= N) break;
            }
        }
        
        // 最終スコアを計算
        ll score = 0;
        rep(i, N) {
            score += abs(emp[i].t - emp[i].T);
        }
        return score;
    }

    // 特定のノードについて両方の遷移先を同じにする関数を追加
    void setupDuplicateTransitions(vector<Employee>& emp, vector<ll>& targetNodes) {
        for (ll node : targetNodes) {
            // ノードのaとbを同じ値に設定
            emp[node].b = emp[node].a;
        }
    }

    // 最適化されたグラフ構築関数 - average_required_visitsをパラメータとして追加
    vector<Employee> buildOptimizedGraph(double average_required_visits) {
        vector<Employee> emp = E;
        map<ll, ll> mp_copy = mp;
        
        // 基本的なサイクル構造を構築（例えば0->1->2->...->0のような循環）
        for (ll i = 0; i < N-1; i++) {
            emp[i].a = i+1;
            decrease_key(mp_copy, i+1);
        }
        emp[N-1].a = 0; // 循環を完成させる
        decrease_key(mp_copy, 0);
        
        // 一部のノードについて、aとbを同じにする
        // 訪問頻度を増やしたいノード（必要回数の多いノード）を選択
        vector<ll> highFrequencyNodes;
        for (ll i = 0; i < N; i++) {
            if (E[i].T > average_required_visits) { // 平均以上の訪問が必要なノード
                highFrequencyNodes.push_back(i);
            }
        }
        
        // 選択したノードのaとbを同じにする
        setupDuplicateTransitions(emp, highFrequencyNodes);
        
        // 残りのノードはbの遷移先をランダムに設定
        for (ll i = 0; i < N; i++) {
            if (emp[i].a != emp[i].b) { // まだbが設定されていないノード
                emp[i].b = get_weighted_random_key(mp_copy, emp);
                decrease_key(mp_copy, emp[i].b);
            }
        }
        
        return emp;
    }

    // 訪問回数バランス最適化関数
    vector<Employee> optimizeVisitBalance(vector<Employee> emp) {
        // 現在の各ノードの状態を評価
        vector<Employee> best_emp = emp;
        ll best_score = calcScoreOptimized(best_emp);
        
        const int MAX_ITERATIONS = 50; // 最適化の最大反復回数
        
        for (int iter = 0; iter < MAX_ITERATIONS && timer.isIntime(); iter++) {
            // 現在の訪問回数を計算
            vector<Employee> curr_emp = best_emp;
            calcScoreOptimized(curr_emp); // 訪問回数(t)を更新
            
            // 各ノードの過不足を計算
            vector<pair<ll, ll>> diff_nodes; // (t-T, ノード番号)
            rep(i, N) {
                diff_nodes.push_back({curr_emp[i].t - curr_emp[i].T, i});
            }
            
            // 訪問過多のノードと訪問不足のノードでソート
            sort(diff_nodes.begin(), diff_nodes.end());
            
            // 最も不足しているノードと最も過剰なノードを特定
            ll most_deficit_node = diff_nodes.front().second;
            ll most_excess_node = diff_nodes.back().second;
            
            if (diff_nodes.front().first >= 0 || diff_nodes.back().first <= 0) {
                // すべてのノードが過剰か、すべてのノードが不足している場合は最適化終了
                break;
            }
            
            // 遷移の再調整試行
            for (ll i = 0; i < N && timer.isIntime(); i++) {
                // ノードiのaかbが過剰ノードを指している場合、不足ノードに変更
                if (curr_emp[i].a == most_excess_node) {
                    curr_emp[i].a = most_deficit_node;
                } else if (curr_emp[i].b == most_excess_node) {
                    curr_emp[i].b = most_deficit_node;
                }
            }
            
            // スコアが改善したかチェック
            ll new_score = calcScoreOptimized(curr_emp);
            if (new_score > best_score) {
                best_emp = curr_emp;
                best_score = new_score;
            } else {
                // 改善がなかった場合は別のアプローチを試す
                // ランダムな遷移の変更
                ll random_node = rand() % N;
                if (rand() % 2 == 0) {
                    curr_emp[random_node].a = most_deficit_node;
                } else {
                    curr_emp[random_node].b = most_deficit_node;
                }
                
                new_score = calcScoreOptimized(curr_emp);
                if (new_score > best_score) {
                    best_emp = curr_emp;
                    best_score = new_score;
                }
            }
        }
        
        return best_emp;
    }

    void solve() {
        vector<Employee> ans(N);
        ll score = 0;
        [&](){
            
            while(timer.isIntime()){
                // 通常のランダムグラフ生成
                vector<ll> rem;
                rep(i, N) {
                    rem.push_back(i);
                }
                std::shuffle(rem.begin() + 1, rem.end(), rng);

                vector<Employee> now = E;
                map<ll, ll> mp_copy = mp;
                
                bool success = [&]() -> bool { // 戻り値の型を明示
                    for(int i = 0; i < N-1; i++) {
                        ll retry = 3;
                        while(rem[i] == rem[i+1]){
                            if(--retry == 0) return false;
                            if(!timer.isIntime()) return false;
                            std::shuffle(rem.begin() + i + 1, rem.end(), rng);
                        }
                        now[rem[i]].a = rem[i+1];
                        decrease_key(mp_copy, rem[i+1]);
                    }
                    return true; // 成功したらtrueを返す
                }();
                if(!success) continue; // 失敗したら次のループへ（修正）
                // 最後の頂点のaはランダム選択（正規化された重み使用）
                decrease_key(mp_copy, now[N-1].a = get_normalized_random_key(mp_copy));
                
                // 残りのエッジを追加（正規化された重み使用）
                for(int i = 0; i < N; i++) {
                    if(!timer.isIntime()) return;
                    decrease_key(mp_copy, now[rem[i]].b = get_normalized_random_key(mp_copy));
                }
    
                // 最適化されたシミュレーションでスコア計算
                ll new_score = calcScoreOptimized(now);
                if(chmax(score, new_score)){
                    ans = now;
#ifdef _DEBUG                
                    cerr << "score: " << score << endl;
#endif
                }
                
                // バランス最適化の適用（一定確率で）
                if (rand() % 10 == 0 && timer.isIntime()) { // 10%の確率
                    vector<Employee> balanced = optimizeVisitBalance(now);
                    new_score = calcScoreOptimized(balanced);
                    if(chmax(score, new_score)){
                        ans = balanced;
#ifdef _DEBUG                
                        cerr << "Balanced score: " << score << endl;
#endif
                    }
                }
                
                // 最適化されたグラフも試す
                if (rand() % 5 == 0) { // 20%の確率で最適化グラフを試す
                    vector<Employee> optimized = buildOptimizedGraph(average_required_visits); // パラメータを渡す
                    ll new_score = calcScoreOptimized(optimized);
                    if(chmax(score, new_score)){
                        ans = optimized;
                    }
                }
            }
            
            // 最終解に対するバランス最適化
            if (timer.isIntime()) {
                vector<Employee> final_balanced = optimizeVisitBalance(ans);
                ll final_score = calcScoreOptimized(final_balanced);
                if(chmax(score, final_score)){
                    ans = final_balanced;
#ifdef _DEBUG                
                        cerr << "Final balanced score: " << score << endl;
#endif
                }
            }
            
            return; // ラムダ関数の終了
        }();
#ifdef _DEBUG                
        cerr << "result: " << score << endl;
#endif
        rep(i,N){
            printf("%lld %lld\n", ans[i].a, ans[i].b);
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
    cin >> N >> L;
    E.resize(N);
    rep(i, N) {
        ll T;
        cin >> T;
        E[i].T = T;
        mp[i] = T;
        average_required_visits += T;
    }
    average_required_visits /= N;
    Solver solver(move(timer));
    solver.solve();
    return 0;
}
