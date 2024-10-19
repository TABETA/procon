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

class Solver {
    class Result {
       public:
        void add(vs opes) {
            for (auto&& ope : opes) {
                add(ope);
            }
        }
        void add(string ope) {
            --cnt;
            operations.emplace_back(ope);
        }
        void write() const {
            ostringstream oss;
            for (auto&& line : operations) {
                oss << line << '\n';
            }
            cout << oss.str() << flush;
        }
        bool valid() const { return cnt >= 0; }
        ll getScore() const { return score; }
        ll getCount() const { return cnt; }
        Result(ll limit) : score(0), cnt(limit), operations() {}
        Result(ll limit, ll score) : score(score), cnt(limit), operations() {}
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
        vs operations;
    };    
    ll limit;
    ll N;
    ll M;
    ll V;
    vs S;
    vs T;
    Result ans;
    Timer timer;
    ll tried;
    struct Hand {
        Hand()
            : offset_x(0),
              offset_y(0),
              children(),
              isPicked(false) {}
        Hand(int ox, int oy)
            : offset_x(ox),
              offset_y(oy),
              children(),
              isPicked(false) {}
        int offset_x;
        int offset_y;
        vector<Hand> children;
        bool isPicked;
        bool tryPickOrDrop(int x, int y, ll N, const vs& T, vs& S, ll& M, string& s) {
            int nx = x + offset_x;
            int ny = y + offset_y;
            if (children.size() > 0) {
                bool res = false;
                s += ".";
                for (auto it = children.begin(); it != children.end(); ++it) {
                    bool now = it->tryPickOrDrop(nx, ny, N, T, S, M, s);
                    res |= now;
                }
                return res;
            } else {
                if(nx < 0 || nx >= N || ny < 0 || ny >= N) {
                    s += ".";
                    return false;
                }
                if (T[ny][nx] != '1' && S[ny][nx] == '1' && !isPicked) {
                    S[ny][nx] = '0';
                    isPicked = true;
                    s += "P";
                    return true;
                }
                if (T[ny][nx] == '1' && S[ny][nx] != '1' && isPicked) {
                    S[ny][nx] = '1';
                    isPicked = false;
                    --M;
                    s += "P";
                    return true;
                }
                s += ".";
                return false;
            }
        }
    };
    struct Arm {
        ll N;
        ll W;
        int x;
        int y;
        Hand root;
        Arm(ll N): N(N), W(1), x{}, y{}, root() {
            root.children.emplace_back(Hand(1, 0));++W;
            root.children[0].children.emplace_back(Hand(1, 0));++W;
            root.children[0].children.emplace_back(Hand(0, 1));++W;
            root.children[0].children.emplace_back(Hand(-1, 0));++W;
        }
        Arm(const Arm& arm)
            : N(arm.N),
              W(arm.W),
              x(arm.x),
              y(arm.y),
              root(arm.root) {}
        void write() {
            cout << W << '\n';
            cout << 0 << " " << 1 << '\n';
            cout << 1 << " " << 1 << '\n';
            cout << 1 << " " << 1 << '\n';
            cout << 1 << " " << 1 << '\n';
            cout << x << " " << y << '\n';
        }
        vs setup() {
            vs ret;
            ret.emplace_back("...RR.....");
            ret.emplace_back("....R.....");
            return ret;
        }
        bool tryPickOrDrop(const vs& T, vs& S, ll& M, string& s) {
            return root.tryPickOrDrop(x, y, N, T, S, M, s);
        }
        string getOperation(char moveDirection){
            string ret = "";
            ret += moveDirection;
            reps(i, 1, W) { ret += '.'; }
            rep(i, W) { ret += '.'; }
            return ret;
        }
        auto next_adjacents() {
            vector<pair<Arm, string>> ret;
            for (auto&& adj : {
                    pair<P, char>{P{y - 1, x}, 'U'},
                    pair<P, char>{P{y + 1, x}, 'D'},
                    pair<P, char>{P{y, x - 1}, 'L'},
                    pair<P, char>{P{y, x + 1}, 'R'},
                }) {
                auto [p, d] = adj;
                auto [ny, nx] = p;
                if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                Arm next(*this);
                next.x = nx;
                next.y = ny;
                ret.emplace_back(next, getOperation(d));
            }
            return ret;
        }
    };
   public:
    Solver(ll N, ll M, ll V, vs&& S, vs&& T, Timer&& timer)
        : limit(1e5),
          N(N),
          M(M),
          V(V),
          S(S),
          T(T),
          ans(limit, linf),
          timer(timer),
          tried(0) {}
    ~Solver() {}
    void write() const {
        // #ifdef ONLINE_JUDGE
        ans.write();
        // #endif
        debug("# tried: %lld\n", tried);
        debug("# score: %lld\n", ans.getScore());
    }
    void solve() {
        // while (timer.isIntime()) {
        Arm cur(N);
        cur.write();
        Result now(limit);
        now.add(cur.setup());
        rep(i, N) {
            rep(j, N) {
                if (S[i][j] == '1' && T[i][j] == '1') {
                    --M;
                }
            }
        }
        while (M > 0) {
            auto [next, opes] = pick(cur);
            now.add(opes);
            cur = next;
        }
        debug("# score of %lld: %lld with %lld at %lld.\n", tried,
              now.getScore(), now.getCount(), timer.getMilliSeconds());
        if (now.valid() && ans > now) {
            ans = move(now);
        }
        // ++tried;
        // }
    }
    ll getScore() const { return ans.getScore(); }

   private:
    pair<Arm, vs> pick(Arm cur) {
        queue<pair<Arm, vs>> Q;
        Q.push(pair<Arm, vs>{cur, vs{}});
        vector used(N, vector(N, false));
        used[cur.y][cur.x] = true;
        while (!Q.empty()) {
            auto a = Q.front();Q.pop();
            auto& [p, opes] = a;
            string s = "";
            if(p.tryPickOrDrop(T, S, M, s)) {
                ll n = opes.size()-1;
                if(n<0){
                    opes.emplace_back(cur.getOperation('.'));
                    n++;
                }
                ll u = opes[n].size();
                ll l = u-s.size();
                rep(i,s.size()) {
                    opes[n][l+i] = s[i];
                }
                return a;
            }
            for (auto&& adj : p.next_adjacents()) {
                auto [arm, ope] = adj;
                if (used[arm.y][arm.x]) continue;
                used[arm.y][arm.x] = true;
                auto nopes = opes;
                nopes.emplace_back(ope);
                Q.emplace(arm, nopes);
            }
        }
        vs opes;
        opes.emplace_back("..RR......");
        opes.emplace_back("..R.......");
        cur.root.children[0].children[0].offset_x = -1;
        cur.root.children[0].children[0].offset_y = 0;
        cur.root.children[0].children[1].offset_x = -1;
        cur.root.children[0].children[1].offset_y = 0;
        pair<Arm, vs> ret(cur, opes);
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
    CIN(ll, N);
    CIN(ll, M);
    CIN(ll, V);
    vs S(N);
    rep(i, N) { cin >> S[i]; }
    vs T(N);
    rep(i, N) { cin >> T[i]; }
    Solver solver(N, M, V, move(S), move(T), move(timer));
    solver.solve();
    solver.write();
    return 0;
}
