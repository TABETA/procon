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
ll N, K, H, T, D;
struct Color {
    double c, m, y;
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
    int actualV;      // 操作1の実行回数
    double actualE;   // 実際の色誤差の累計
    
   public:
    Solver(Timer&& timer) : timer(timer), actualV(0), actualE(0.0) {}

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
    
    // スコア計算関数
    double calculateCurrentScore(int colorIndex) {
        return 1.0 + D * (actualV - colorIndex) + round(10000.0 * actualE);
    }
    
    // 操作1: チューブkから重さwの絵の具を座標(i,j)に出す
    void operation1(int i, int j, int k) {
        cout << "1 " << i << " " << j << " " << k;
        cout << "\n";
        actualV++;  // 操作1回数を増加
    }
    
    // 操作2: 座標(i,j)から絵の具を画伯に渡す
    void operation2(int i, int j, const Color& targetColor, const Color& actualColor) {
        cout << "2 " << i << " " << j << "\n";
        auto e = calcError(targetColor, actualColor);
        actualE += e;
    }
    void debugOutput(int h) {
#ifdef _DEBUG
        double currentScore = calculateCurrentScore(h + 1);
        // 進捗ログ（100色ごとに中間結果を表示）
        if ((h + 1) % 100 == 0)
        {
            cerr << "Progress: " << (h + 1) << "/" << H 
                 << ", V=" << actualV << ", E=" << actualE 
                 << ", Current Score=" << currentScore << endl;
        }
#endif
    }
    // シンプル戦略: 全マス独立、各色ごとに最も近いチューブ1gを使用
    void simple(){
        // 初期仕切り: 全て出す（全マス独立）
        // v: 縦仕切り N行×(N-1)列 - マス(i,j)と(i,j+1)間
        vector<vector<int>> v(N, vector<int>(N - 1, 1));
        // h: 横仕切り (N-1)行×N列 - マス(i,j)と(i+1,j)間  
        vector<vector<int>> h(N - 1, vector<int>(N, 1));
        
        // 仕切り情報の出力
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
        // 各色ごとに処理（同じマスを再利用してH回必ず実行）
        for (int h = 0; h < H; h++) {
            // 固定のマス(0,0)を使用（操作2後は空になるので再利用可能）
            int i = 0, j = 0;
            
            // 目標色に最も近いチューブを選択
            int bestTube = findBestTube(Ct[h]);
            
            // 操作1: チューブから1g出す
            operation1(i, j, bestTube);

            // 操作2: 画伯に1g渡す（これでマスは空になる）
            // シンプル戦略では選択したチューブの色がそのまま提出される
            operation2(i, j, Ct[h], Co[bestTube]);
            debugOutput(h);   
        }
    }
    void solve() {
        simple();
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
