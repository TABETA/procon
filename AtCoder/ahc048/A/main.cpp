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
using P = pair<ll,ll>;

// ---------------------------
// input values
// ---------------------------
ll N, K, H, T, D;
struct Color {
    double c, m, y;
    double error(const Color& their) const {
        double dc = this->c - their.c;
        double dm = this->m - their.m;
        double dy = this->y - their.y;
        return sqrt(dc * dc + dm * dm + dy * dy);
    }
};
vector<Color> Co;
vector<Color> Ct;
void g_input() {
    cin >> N >> K >> H >> T >> D;
    Co.resize(K);
    for (auto& c : Co) {
        cin >> c.c >> c.m >> c.y;
    }
    Ct.resize(H);
    for (auto& c : Ct) {
        cin >> c.c >> c.m >> c.y;
    }
}

// ---------------------------

class Solver {
    Timer timer;
    int actualV;  // 操作1の実行回数
    int actualH;
    int turn;
    double actualE;  // 実際の色誤差の累計


    // 階層的ウェル管理システム
    struct Well {
        vector<P> cells;
        Color color;  // ウェルの色
        int remaining;

        Well(const vector<P>& cells) : cells(cells), color(), remaining(0) {}

        // ウェルの容量（グラム数）
        int capacity() const { return cells.size(); }

    };
    // ウェル管理用
    vector<Well> wells;
    map<ll, vector<Well*>> wellMap;  // ウェルサイズごとのマップ

    // パレット仕切り状態（mixedColorStrategy用）
    vector<vector<int>> v;  // 縦仕切り N行×(N-1)列
    vector<vector<int>> h;  // 横仕切り (N-1)行×N列

    // 戦略統計用
    vll stCount;
    vector<double> totalErrors;

    // 最適化用: 事前計算された1:1混色結果
    struct PrecomputedPair {
        int tube1, tube2;
        Color mixedColor;  // 1:1の混色結果
    };
    vector<PrecomputedPair> precomputedPairs;

    // 色選択肢の構造体
    struct ColorOption {
        Color color;  // 選択可能な色
        int cost;     // 採用時のコスト（g単位）
        vector<int>
            tubes;  // 使用するチューブリスト（空=不正、1要素=単色、2要素以上=混色）
        vector<int> grams;  // 各チューブのグラム数（tubesと対応）

        ColorOption(const Color& c, int costVal) : color(c), cost(costVal) {}

        ColorOption(const Color& c, int costVal, const vector<int>& tubeList)
            : color(c), cost(costVal), tubes(tubeList) {
            // デフォルトでは各チューブ1gずつ
            grams.assign(tubes.size(), 1);
        }

        ColorOption(const Color& c, const vector<int>& tubeList,
                    const vector<int>& gramList)
            : color(c), tubes(tubeList), grams(gramList) {
            // コストは総グラム数
            cost = 0;
            for (int g : grams) cost += g;
        }

        // 目標色との誤差とスコアを計算
        double calculateError(const Color& target) const {
            return target.error(color);
        }

        // この色選択肢の総グラム数を計算
        int getTotalGrams() const {
            // 各チューブから使用するグラム数の合計
            int totalGrams = 0;
            for (int g : grams) {
                totalGrams += g;
            }
            return totalGrams;
        }

        // 絶対的なスコア計算（総スコア計算用）
        double calculateScore(const Color& target) const {
            double error = calculateError(target);
            int totalGrams = getTotalGrams();
            return D * totalGrams + round(error * 10000);
        }
    };

    // 事前計算された全ての色選択肢
    vector<ColorOption> allColorOptions;

   public:
    Solver(Timer&& timer)
        : timer(timer),
          actualV(0),
          actualH(0),
          turn(0),
          actualE(0.0),
          wells(),
          wellMap(),
          v(N, vector<int>(N - 1, 1)),  // 縦仕切りあり
          h(N - 1, vector<int>(N, 1)),  // 横仕切りあり
          stCount(2),
          totalErrors(2),
          precomputedPairs(),
          allColorOptions() {
        // ウェル割り当て戦略を初期化
        initializeWellAllocation();
    }

    ~Solver() {}

    double calcError(const Color& target, const Color& actual) {
        double dc = target.c - actual.c;
        double dm = target.m - actual.m;
        double dy = target.y - actual.y;
        return sqrt(dc * dc + dm * dm + dy * dy);
    }

    // 最も近いチューブを選択
    int findBestTube(const Color& target) {
        int bestIndex = 0;
        double bestE = 1e18;
        for (int k = 0; k < K; k++) {
            double e = calcError(target, Co[k]);
            if (chmin(bestE, e)) {
                bestIndex = k;
            }
        }
        return bestIndex;
    }

    // 2色の線形補間（グラム数指定）
    Color mixTwoColors(const Color& c1, int grams1, const Color& c2,
                       int grams2) {
        int totalGrams = grams1 + grams2;
        double ratio1 = (double)grams1 / totalGrams;
        double ratio2 = (double)grams2 / totalGrams;

        Color result;
        result.c = c1.c * ratio1 + c2.c * ratio2;
        result.m = c1.m * ratio1 + c2.m * ratio2;
        result.y = c1.y * ratio1 + c2.y * ratio2;
        return result;
    }

    // 2色混色の最適比率計算（三分探索）
    pair<double, double> findOptimalRatioTwoColors(const Color& target,
                                                   const Color& c1,
                                                   const Color& c2) {
        double left = 0.0, right = 1.0;

        // 三分探索で最適な ratio1 を求める
        for (int iter = 0; iter < 100; iter++) {
            double m1 = left + (right - left) / 3.0;
            double m2 = right - (right - left) / 3.0;

            // Convert ratios to gram amounts (assuming total 100 grams)
            double grams1_1 = m1 * 100.0;
            double grams2_1 = (1.0 - m1) * 100.0;
            double grams1_2 = m2 * 100.0;
            double grams2_2 = (1.0 - m2) * 100.0;

            Color mixed1 = mixTwoColors(c1, grams1_1, c2, grams2_1);
            Color mixed2 = mixTwoColors(c1, grams1_2, c2, grams2_2);

            double error1 = calcError(target, mixed1);
            double error2 = calcError(target, mixed2);

            if (error1 > error2) {
                left = m1;
            } else {
                right = m2;
            }
        }

        double optimalRatio1 = (left + right) / 2.0;
        double optimalRatio2 = 1.0 - optimalRatio1;
        return {optimalRatio1, optimalRatio2};
    }

    // 目標色に対する最適な2色組み合わせを探索
    struct TubePairResult {
        int tube1, tube2;
        double ratio1, ratio2;
        double error;
        Color resultColor;
    };
    // 最適化された2色組み合わせ探索
    // 1:1混色が純色より良い場合のみ三分探索を実行
    TubePairResult findBestTubePairOptimized(const Color& target) {
        TubePairResult best;
        best.error = 1e18;

        // まず純色での最良結果を取得
        int bestSingleTube = findBestTube(target);
        double bestSingleError = calcError(target, Co[bestSingleTube]);

        // 有望な組み合わせのみを収集
        vector<size_t> candidatePairs;
        candidatePairs.reserve(precomputedPairs.size());

        for (size_t i = 0; i < precomputedPairs.size(); i++) {
            const auto& pair = precomputedPairs[i];

            // 1:1混色での誤差
            double oneToOneError = calcError(target, pair.mixedColor);

            // 1:1混色が最良純色より良い場合のみ候補とする（条件を緩和）
            if (oneToOneError <
                bestSingleError * 0.98) {  // 2%以上の改善が見込める場合
                candidatePairs.push_back(i);
            }
        }

        // 候補が少ない場合は1:1混色の結果をそのまま使用
        if (candidatePairs.empty()) {
            return best;  // 空の結果（error = 1e18）
        }

        // 候補数が少ない場合は三分探索、多い場合は1:1のみ評価
        bool useFullSearch = candidatePairs.size() <= 10;  // 閾値調整可能

        for (size_t idx : candidatePairs) {
            const auto& pair = precomputedPairs[idx];

            double r1, r2, error;
            Color mixed;

            if (useFullSearch) {
                // 三分探索で最適比率を探索
                auto [opt_r1, opt_r2] = findOptimalRatioTwoColors(
                    target, Co[pair.tube1], Co[pair.tube2]);
                r1 = opt_r1;
                r2 = opt_r2;
                // Convert ratios to gram amounts (assuming total 100 grams)
                double grams1 = r1 * 100.0;
                double grams2 = r2 * 100.0;
                mixed = mixTwoColors(Co[pair.tube1], grams1, Co[pair.tube2],
                                     grams2);
                error = calcError(target, mixed);
            } else {
                // 1:1混色のみ評価（高速）
                r1 = r2 = 0.5;
                mixed = pair.mixedColor;
                error = calcError(target, mixed);
            }

            if (error < best.error) {
                best.tube1 = pair.tube1;
                best.tube2 = pair.tube2;
                best.ratio1 = r1;
                best.ratio2 = r2;
                best.error = error;
                best.resultColor = mixed;
            }
        }

        return best;
    }

    // 重さの整数化（最小2g、比率を保持）
    pair<int, int> calculateIntegerWeights(double ratio1, double ratio2,
                                           int minTotal = 2) {
        // 最小総重量を確保しつつ比率を維持
        double scale = max(minTotal / (ratio1 + ratio2), 1.0);

        int w1 = max(1, (int)round(ratio1 * scale));
        int w2 = max(1, (int)round(ratio2 * scale));

        return {w1, w2};
    }

    // スコア計算関数
    ll calculateCurrentScore() {
        return 1.0 + D * (actualV - actualH) + round(10000.0 * actualE);
    }

    // 操作タイプの定義
    enum class OperationType {
        TUBE_TO_CANVAS = 1,    // 操作1: チューブから絵の具を出す
        CANVAS_TO_PAINTER = 2, // 操作2: 絵の具を画伯に渡す
        DISPOSE = 3,           // 操作3: ウェルから 1g 絵具を廃棄
    };

    // 統一された操作関数
    void operation(OperationType type, Well* well, int k = -1,
                   const Color& targetColor = Color(),
                   const Color& actualColor = Color()) {
        auto [i, j] = well->cells[0];  // ウェルの最初のセルを使用
        switch (type) {
            case OperationType::TUBE_TO_CANVAS:
                // 操作1: チューブkから重さwの絵の具を座標(i,j)に出す
                cout << "1 " << i << " " << j << " " << k << "\n";
                actualV++;  // 操作1回数を増加
                well->remaining++;  // ウェルの残りを増加
                break;

            case OperationType::CANVAS_TO_PAINTER:
                // 操作2: 座標(i,j)から絵の具を画伯に渡す
                cout << "2 " << i << " " << j << "\n";
                well->remaining--;  // ウェルの残りを減少
                break;
            case OperationType::DISPOSE:
                // 操作3: 座標(i,j)から絵の具を廃棄する
                cout << "3 " << i << " " << j << "\n";
                well->remaining--;  // ウェルの残りを減少
                break;
        }

        ++turn;

        // 常にスコア計算を実行
#ifdef _DEBUG
        cerr << "Op: " << turn << ", " << calculateCurrentScore()
             << endl;
#endif
        if(type == OperationType::CANVAS_TO_PAINTER){
            auto e = calcError(targetColor, actualColor);
            actualE += e;
        }
    }
    void debugOutput() {
#ifdef _DEBUG
        double currentScore = calculateCurrentScore();
        // 進捗ログ（100色ごとに中間結果を表示）
        if ((turn) % 100 == 0) {
            cerr << "Progress: " << (turn) << "/" << H
                 << ", V=" << actualV << ", E=" << actualE
                 << ", Current Score=" << currentScore << endl;
        }
#endif
    }

    // 目標色に対する最適な色選択肢を選択（増分スコア比較版）
    const ColorOption& selectBestColorOption(const Color& target) {
        const ColorOption* bestOption = &allColorOptions[0];
        double bestScore = bestOption->calculateScore(target);

        for (size_t i = 1; i < allColorOptions.size(); i++) {
            double score = allColorOptions[i].calculateScore(target);
            // cerr << allColorOptions[i].getTotalGrams() << "g, ";
            // cerr << "score=" << score << ", error=" <<
            // allColorOptions[i].calculateError(target) << endl;
            if (score < bestScore) {
                bestScore = score;
                bestOption = &allColorOptions[i];
            }
        }

        return *bestOption;
    }

    // 統一された色戦略：全選択肢から最適なものを選択・実行
    void unifiedColorStrategy() {
        // 仕切り情報の出力（コンストラクタで既に初期化済み）
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N - 1; j++) {
                cout << v[i][j] << (j == N - 2 ? "\n" : " ");
            }
        }
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N; j++) {
                cout << h[i][j] << (j == N - 1 ? "\n" : " ");
            }
        }

        // 各色ごとに最適選択肢をリアルタイム選択・実行
        for (int colorIdx = 0; colorIdx < H; colorIdx++) {
            actualH = colorIdx;
            const ColorOption& bestOption = selectBestColorOption(Ct[colorIdx]);

            Well* well = wellMap[bestOption.tubes.size()][0];
            // 選択された戦略を実行
            for (int tube : bestOption.tubes) {
                operation(OperationType::TUBE_TO_CANVAS, well, tube);
            }
            operation(OperationType::CANVAS_TO_PAINTER, well, -1, Ct[colorIdx],
                      bestOption.color);
            while(well->remaining){
                operation(OperationType::DISPOSE, well);
            }

            // 統計更新
            ll st = bestOption.tubes.size();
            stCount[st]++;
            totalErrors[st] += bestOption.calculateError(Ct[colorIdx]);
#ifdef _DEBUG
            cerr << "Color " << colorIdx << ": " << st << " (tubes=";
            for (ll i = 0; i < st; i++) {
                cerr << bestOption.tubes[i];
                if (i < st - 1) cerr << ",";
            }
            cerr << ", cost=" << bestOption.cost
                 << "g, error=" << bestOption.calculateError(Ct[colorIdx])
                 << ", score=" << bestOption.calculateScore(Ct[colorIdx]) << ")"
                 << endl;
#endif
            debugOutput();
        }

#ifdef _DEBUG
        // 最終統計の出力
        cerr << "\n=== UNIFIED COLOR STRATEGY STATISTICS ===" << endl;
        cerr << "Simple strategy used: " << stCount[0] << " times" << endl;
        cerr << "Mixed strategy used: " << stCount[1] << " times" << endl;
        if (stCount[0] > 0) {
            cerr << "Average simple error: " << (totalErrors[0] / stCount[0])
                 << endl;
        }
        if (stCount[1] > 0) {
            cerr << "Average mixed error: " << (totalErrors[1] / stCount[1])
                 << endl;
        }
        cerr << "Total operations: " << actualV << endl;
        cerr << "Total color error: " << actualE << endl;
        cerr << "Final score: " << (ll)calculateCurrentScore() << endl;
        cerr << "=============================" << endl;
#endif
    }
    // すべての色選択肢の事前計算
    void precomputeAllColorOptions() {
        allColorOptions.clear();
        allColorOptions.reserve(K + K * (K - 1) / 2);

        // シンプル戦略の選択肢を追加（各チューブ1gずつ）
        for (int tube = 0; tube < K; tube++) {
            ColorOption option(Co[tube], 1, {tube});
            allColorOptions.push_back(option);
        }
        // return;

        // 2色混色戦略の選択肢を追加（1:1固定、2g使用）
        for (int i = 0; i < K; i++) {
            for (int j = i + 1; j < K; j++) {
                Color mixedColor =
                    mixTwoColors(Co[i], 1, Co[j], 1);  // 1g:1g混合
                vector<int> tubes = {i, j};
                vector<int> grams = {1, 1};
                ColorOption option(mixedColor, tubes, grams);
                allColorOptions.push_back(option);
            }
        }

#ifdef _DEBUG
        cerr << "Precomputed " << allColorOptions.size() << " color options ("
             << K << " simple + " << (K * (K - 1) / 2) << " mixed)" << endl;
#endif
    }

    // ウェル割り当て戦略: サイズ1,2,3,4...のウェルを(0,0)から順番に割り当て
    void initializeWellAllocation() {
        int x = 0, y = 0;
        size_t wellSize = 1;
        int dx = 1;
        vector<P> path;
        while (y < N) {
            path.emplace_back(y, x);
            int nx = x + dx;
            if(nx < 0 || N <= nx) {
                nx = x;
                dx *= -1; // 方向を反転
                ++y; // 次の行へ
                if (y >= N) break; // 範囲外チェック
            }
            if(path.size() == wellSize) {
                createWell(path);
                wellSize++;
                path.clear();
            }
            x = nx;
        }
        for (auto &&well : wells){
            wellMap[well.capacity()].push_back(&well);
        }
    }
    
    // 指定位置・サイズのウェルを作成（バリアを設定）
    void createWell(const vector<P>& path) {
        ll n = path.size();
        rep(i,n-1){
            auto [r1, c1] = path[i];
            auto [r2, c2] = path[i + 1];
            if(r1 == r2) {
                // 縦の仕切りを除去
                if (c1 > c2) swap(c1, c2);  // 左右を正規化
                v[r1][c1] = 0;  // 縦仕切りを除去
            } else {
                // 横の仕切りを除去
                if (r1 > r2) swap(r1, r2);  // 上下を正規化
                h[r1][c1] = 0;  // 縦仕切りを除去
            }
        }
        wells.emplace_back(path);
    }
    
    void solve() {
        // 全色選択肢の事前計算を実行
        precomputeAllColorOptions();

        // 統一戦略: 全選択肢から最適なものを選択
        unifiedColorStrategy();
    }
};
#ifndef TIMELIMIT
constexpr ll msLimit = 2800;
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
