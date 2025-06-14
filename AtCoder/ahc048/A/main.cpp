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
using P = pair<ll, ll>;
struct Color {
    double c, m, y;
    double error(const Color& their) const {
        double dc = this->c - their.c;
        double dm = this->m - their.m;
        double dy = this->y - their.y;
        return sqrt(dc * dc + dm * dm + dy * dy);
    }
};
// 色選択肢の構造体
struct ColorOption {
    Color color;   // 選択可能な色
    int unitCost;  // 採用時のコスト（g単位）
    vector<int>
        tubes;  // 使用するチューブリスト（空=不正、1要素=単色、2要素以上=混色）
    vector<int> grams;  // 各チューブのグラム数（tubesと対応）

    ColorOption(const Color& c, int costVal) : color(c), unitCost(costVal) {}

    ColorOption(const Color& c, int costVal, const vector<int>& tubeList)
        : color(c), unitCost(costVal), tubes(tubeList) {
        // デフォルトでは各チューブ1gずつ
        grams.assign(tubes.size(), 1);
    }

    ColorOption(const Color& c, const vector<int>& tubeList,
                const vector<int>& gramList, int costVal)
        : color(c), unitCost(costVal), tubes(tubeList), grams(gramList) {}

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
    int getTotalCost() const {
        return getTotalGrams() * unitCost;
    }

    // 絶対的なスコア計算（総スコア計算用）
    double calculateScore(const Color& target) const {
#ifdef _DEBUG
        static ll scoreCalculations = 0;
        scoreCalculations++;
        if (scoreCalculations % 100000 == 0) {
            cerr << "Score calculations: " << scoreCalculations << endl;
        }
#endif
        double error = calculateError(target);
        int totalGrams = getTotalGrams();
        return unitCost * totalGrams + round(error * 10000);
    }
};

// k-d tree for fast nearest neighbor search in 3D color space
struct KDNode {
    Color color;
    int optionIndex;  // allColorOptions内のインデックス
    int axis;         // 分割軸 (0:C, 1:M, 2:Y)
    KDNode* left;
    KDNode* right;

    KDNode(const Color& c, int optIdx)
        : color(c),
          optionIndex(optIdx),
          axis(-1),
          left(nullptr),
          right(nullptr) {}
};

class KDTree {
   private:
    KDNode* root;

    struct ColorIndexPair {
        Color color;
        int optionIndex;

        ColorIndexPair(const Color& c, int idx)
            : color(c), optionIndex(idx) {}
    };

    KDNode* buildTree(vector<ColorIndexPair>& points, int depth = 0) {
        if (points.empty()) return nullptr;

        int axis = depth % 3;  // 0:C, 1:M, 2:Y

        // 現在の軸でソート
        sort(points.begin(), points.end(),
             [axis](const auto& a, const auto& b) {
                 if (axis == 0)
                     return a.color.c < b.color.c;
                 else if (axis == 1)
                     return a.color.m < b.color.m;
                 else
                     return a.color.y < b.color.y;
             });

        int median = points.size() / 2;
        KDNode* node =
            new KDNode(points[median].color, points[median].optionIndex);
        node->axis = axis;

        vector<ColorIndexPair> leftPoints(points.begin(),
                                          points.begin() + median);
        vector<ColorIndexPair> rightPoints(points.begin() + median + 1,
                                           points.end());

        node->left = buildTree(leftPoints, depth + 1);
        node->right = buildTree(rightPoints, depth + 1);

        return node;
    }

    void searchNearest(KDNode* node, const Color& target, double& bestScore,
                       KDNode*& bestNode,
                       const vector<ColorOption>& allColorOptions,
                       int D, int depth = 0) {
        if (!node) return;

        // このノードのスコアを計算
        const ColorOption& option = allColorOptions[node->optionIndex];
        double score = option.calculateScore(target);

        if (score < bestScore) {
            bestScore = score;
            bestNode = node;
        }

        // 非常に良いスコアが見つかった場合の早期終了
        if (bestScore < D) {  // 閾値を調整
            return;
        }

        // 現在のノードの分割軸での距離
        double axisDist;
        if (node->axis == 0)
            axisDist = target.c - node->color.c;
        else if (node->axis == 1)
            axisDist = target.m - node->color.m;
        else
            axisDist = target.y - node->color.y;

        // まず近い側を探索
        KDNode* nearSide = (axisDist < 0) ? node->left : node->right;
        KDNode* farSide = (axisDist < 0) ? node->right : node->left;

        searchNearest(nearSide, target, bestScore, bestNode, allColorOptions, D,
                      depth + 1);

        // 遠い側のプルーニング判定を大幅に改善
        double axisDistSq = axisDist * axisDist;
        // 3次元ユークリッド距離の下界を計算
        double minPossibleColorError = sqrt(axisDistSq) * 10000;
        // この部分木の最小コストを推定（世代情報から）
        double minPossibleCost = D;  // 最低でもD（1世代）
        double lowerBound = minPossibleColorError + minPossibleCost;

        if (lowerBound < bestScore) {
            searchNearest(farSide, target, bestScore, bestNode, allColorOptions, D, depth + 1);
        }
    }

    void deleteTree(KDNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

   public:
    KDTree() : root(nullptr) {}

    ~KDTree() { deleteTree(root); }

    void build(const vector<ColorOption>& allColorOptions) {
        // 既存のrootを削除
        if (root) {
            deleteTree(root);
            root = nullptr;
        }

        vector<ColorIndexPair> points;
        points.reserve(allColorOptions.size());

        for (size_t opt = 0; opt < allColorOptions.size(); opt++) {
            points.emplace_back(allColorOptions[opt].color, opt);
        }

        if (!points.empty()) {
            root = buildTree(points);
        }
    }

    const ColorOption* findBestOption(
        const Color& target, const vector<ColorOption>& allColorOptions,
        int D) {
        if (!root) return nullptr;

        // より良い初期bestScoreを設定するため、複数の候補を事前チェック
        double bestScore = 1e18;
        KDNode* bestNode = nullptr;

        // ルートノードから開始
        const ColorOption& rootOption = allColorOptions[root->optionIndex];
        double rootScore = rootOption.calculateScore(target);
        bestScore = rootScore;
        bestNode = root;
        searchNearest(root, target, bestScore, bestNode, allColorOptions, D, 0);

        if (bestNode) {
            return &allColorOptions[bestNode->optionIndex];
        }
        return nullptr;
    }
};

// ---------------------------
// input values
// ---------------------------
ll N, K, H, T, D;
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

    // 事前計算された全ての色選択肢（フラット構造）
    vector<ColorOption> allColorOptions;
    
    // 単色オプション専用コンテナ（高速フォールバック用）
    vector<ColorOption> singleColorOptions;

    // k-d tree for fast color option search
    std::unique_ptr<KDTree> colorKDTree;

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
          stCount(21),
          totalErrors(21),
          precomputedPairs(),
          allColorOptions(),
          singleColorOptions(),
          colorKDTree(nullptr) {
        // ウェル割り当て戦略を初期化
        initializeWellAllocation();
    }

    ~Solver() { 
        // スマートポインタが自動的にメモリを解放
    }

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

    // スコア計算関数
    ll calculateCurrentScore() {
        return 1.0 + D * (actualV - actualH) + round(10000.0 * actualE);
    }

    // 操作タイプの定義
    enum class OperationType {
        TUBE_TO_CANVAS = 1,     // 操作1: チューブから絵の具を出す
        CANVAS_TO_PAINTER = 2,  // 操作2: 絵の具を画伯に渡す
        DISPOSE = 3,            // 操作3: ウェルから 1g 絵具を廃棄
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
                actualV++;          // 操作1回数を増加
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
        // cerr << "Op: " << turn << ", " << calculateCurrentScore() << endl;
#endif
        if (type == OperationType::CANVAS_TO_PAINTER) {
            auto e = calcError(targetColor, actualColor);
            actualE += e;
        }
    }
    void debugOutput() {
#ifdef _DEBUG
        double currentScore = calculateCurrentScore();
        // 進捗ログ（100色ごとに中間結果を表示）
        if ((turn) % 100 == 0) {
            cerr << "Progress: " << (turn) << "/" << H << ", V=" << actualV
                 << ", E=" << actualE << ", Current Score=" << currentScore
                 << endl;
        }
#endif
    }

    // 目標色に対する最適な色選択肢を選択（k-d tree使用による高速化版 + ターン制限考慮）
    const ColorOption& selectBestColorOption(const Color& target) {
        // 残りターン数を計算
        int remainingTurns = T - turn;
        int remainingColors = H - actualH;
        
        // 通常の最適選択肢を取得
        const ColorOption* bestOption = colorKDTree->findBestOption(target, allColorOptions, D);
        // 選択した色オプションに必要なターン数を計算
        int requiredTurns = bestOption->tubes.size();  // チューブからキャンバスへの操作数
        requiredTurns += 1;  // キャンバスから画伯への操作
        requiredTurns += bestOption->getTotalGrams() - 1;  // 廃棄操作数（1g使用、残りを廃棄）
        
        // 残りの色処理に必要な最小ターン数を見積もり（各色最低2ターン：単色選択+画伯への受け渡し）
        int minTurnsForRemainingColors = (remainingColors - 1) * 2;
        
        // ターン制限チェック：現在の選択肢 + 残りの色の最小コストがターン制限を超える場合
        if (requiredTurns + minTurnsForRemainingColors > remainingTurns) {
            // 事前に準備された単色オプションから最適なものを選択
            double bestScore = 1e18;
            
            for (const auto& option : singleColorOptions) {
                double score = option.calculateScore(target);
                if (score < bestScore) {
                    bestScore = score;
                    bestOption = &option;
                }
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
            while (well->remaining) {
                operation(OperationType::DISPOSE, well);
            }

#ifdef _DEBUG
            // 統計更新
            ll st = bestOption.tubes.size() - 1;  // 0-based indexing
            if (st < (ll)stCount.size()) {
                stCount[st]++;
                totalErrors[st] += bestOption.calculateError(Ct[colorIdx]);
            }
            cerr << "Color " << colorIdx << ": " << (st + 1) << " (tubes=";
            for (ll i = 0; i < (ll)bestOption.tubes.size(); i++) {
                cerr << bestOption.tubes[i];
                if (i < (ll)bestOption.tubes.size() - 1) cerr << ",";
            }
            cerr << ", cost="
                 << bestOption.getTotalGrams() * bestOption.unitCost
                 << ", error=" << bestOption.calculateError(Ct[colorIdx])
                 << ", score=" << bestOption.calculateScore(Ct[colorIdx]) << ")"
                 << endl;
                 debugOutput();
#endif
        }

#ifdef _DEBUG
        // 最終統計の出力
        cerr << "\n=== UNIFIED COLOR STRATEGY STATISTICS ===" << endl;
        for (size_t i = 0; i < stCount.size(); i++) {
            if (stCount[i] > 0) {
                cerr << (i + 1) << "-color strategy used: " << stCount[i] << " times";
                if (totalErrors[i] > 0) {
                    cerr << ", average error: " << (totalErrors[i] / stCount[i]);
                }
                cerr << endl;
            }
        }
        cerr << "Total operations: " << actualV << endl;
        cerr << "Total color error: " << actualE << endl;
        cerr << "Final score: " << (ll)calculateCurrentScore() << endl;
        cerr << "=============================" << endl;
#endif
    }
    // すべての色選択肢の事前計算（ビット演算による効率的な組み合わせ生成）
    void precomputeAllColorOptions() {
        constexpr double worstScore = 17321;
        constexpr double costThreshold = worstScore/2;  // コストの閾値
        constexpr int MAX_OPTIONS = 50000;  // 最大選択肢数
        allColorOptions.clear();
        singleColorOptions.clear();

        // ビットマスクで全ての組み合わせを効率的に生成
        vector<ColorOption> all;
        
        // ビット数（popcount）ごとにマスクを分類
        vector<vector<int>> masksByPopcount(K + 1);
        for (int mask = 1; mask < (1 << K); mask++) {
            int popcount = __builtin_popcount(mask);
            masksByPopcount[popcount].push_back(mask);
        }
        
        // ビット数が少ない順（1色、2色、3色...）に処理
        for (int popcnt = 1; popcnt <= K && all.size() < MAX_OPTIONS; popcnt++) {
            for (int mask : masksByPopcount[popcnt]) {
                if (all.size() >= MAX_OPTIONS) break;
                
                vector<int> tubes;
                
                // ビットが立っているチューブを収集
                for (int tube = 0; tube < K; tube++) {
                    if (mask & (1 << tube)) {
                        tubes.push_back(tube);
                    }
                }
                
                // 混色計算（等量混合）
                Color mixedColor;
                mixedColor.c = mixedColor.m = mixedColor.y = 0.0;
                
                for (int tube : tubes) {
                    mixedColor.c += Co[tube].c;
                    mixedColor.m += Co[tube].m;
                    mixedColor.y += Co[tube].y;
                }
                
                // 平均を取る
                int tubeCount = tubes.size();
                mixedColor.c /= tubeCount;
                mixedColor.m /= tubeCount;
                mixedColor.y /= tubeCount;
                
                // 各チューブ1gずつ使用
                vector<int> grams(tubeCount, 1);
                ColorOption newOption(mixedColor, tubes, grams, D);
                
                // コスト閾値チェック
                if(newOption.getTotalCost() > costThreshold && popcnt > 1) {
                    continue;
                }
                all.push_back(newOption);
                
                // 単色の場合は単色オプションにも追加
                if (tubeCount == 1) {
                    singleColorOptions.push_back(newOption);
                }
            }
        }


        // 重複する色を除去（同じ色でコストが最も低いもののみを残す）
        removeDuplicateColors(all);

        // フラットな構造に格納
        allColorOptions = std::move(all);

        // k-d treeを構築
        colorKDTree = std::make_unique<KDTree>();
        colorKDTree->build(allColorOptions);

    }

private:
    // 重複する色を除去する関数
    void removeDuplicateColors(vector<ColorOption>& options) {
        map<tuple<int, int, int>, vector<ColorOption*>> colorGroups;
        
        // 色を離散化してグループ分け
        for (auto& option : options) {
            // 色を整数に離散化（精度を保ちつつグループ化）
            int discreteC = (int)round(option.color.c * 1000);
            int discreteM = (int)round(option.color.m * 1000);
            int discreteY = (int)round(option.color.y * 1000);
            
            auto key = make_tuple(discreteC, discreteM, discreteY);
            colorGroups[key].push_back(&option);
        }
        
        // 各グループで最もコストの低いオプションのみを残す
        vector<ColorOption> filteredOptions;
        for (auto& [key, group] : colorGroups) {
            // グループ内で最もコストの低いオプションを見つける
            ColorOption* bestOption = group[0];
            int minCost = bestOption->getTotalCost();
            
            for (auto* option : group) {
                int cost = option->getTotalCost();
                if (cost < minCost) {
                    minCost = cost;
                    bestOption = option;
                }
            }
            
            filteredOptions.push_back(*bestOption);
        }
        
#ifdef _DEBUG
        cerr << "Color deduplication: " << options.size() << " -> " << filteredOptions.size() 
             << " (" << (options.size() - filteredOptions.size()) << " duplicates removed)" << endl;
#endif
        
        options = std::move(filteredOptions);
    }

public:

    // ウェル割り当て戦略: サイズ1,2,3,4...のウェルを(0,0)から順番に割り当て
    void initializeWellAllocation() {
        int x = 0, y = 0;
        size_t wellSize = 1;
        int dx = 1;
        vector<P> path;
        while (y < N) {
            path.emplace_back(y, x);
            int nx = x + dx;
            if (nx < 0 || N <= nx) {
                nx = x;
                dx *= -1;           // 方向を反転
                ++y;                // 次の行へ
                if (y >= N) break;  // 範囲外チェック
            }
            if (path.size() == wellSize) {
                createWell(path);
                wellSize++;
                path.clear();
            }
            x = nx;
        }
        for (auto&& well : wells) {
            wellMap[well.capacity()].push_back(&well);
        }
    }

    // 指定位置・サイズのウェルを作成（バリアを設定）
    void createWell(const vector<P>& path) {
        ll n = path.size();
        rep(i, n - 1) {
            auto [r1, c1] = path[i];
            auto [r2, c2] = path[i + 1];
            if (r1 == r2) {
                // 縦の仕切りを除去
                if (c1 > c2) swap(c1, c2);  // 左右を正規化
                v[r1][c1] = 0;              // 縦仕切りを除去
            } else {
                // 横の仕切りを除去
                if (r1 > r2) swap(r1, r2);  // 上下を正規化
                h[r1][c1] = 0;              // 縦仕切りを除去
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
    Solver solver(std::move(timer));
    solver.solve();
    return 0;
}
