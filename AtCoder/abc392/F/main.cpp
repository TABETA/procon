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
#define all(obj) (obj).begin(), (obj).end()
#define YESNO(bool) if(bool){cout<<"YES"<<endl;}else{cout<<"NO"<<endl;}
#define yesno(bool) if(bool){cout<<"yes"<<endl;}else{cout<<"no"<<endl;}
#define YesNo(bool) if(bool){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i,n) for(ll i=n-1;i>=0;i--)
#define rrepd(i,n) for(ll i=n;i>=1;i--)
#define repr(i, n) for(auto&& i: n)

/* debug */
#define debug(x) cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << endl;

/* func */
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
template<typename T>
pair<T,T> operator+(const pair<T,T>& lhs, const pair<T,T> rhs){
    return pair<T,T>{lhs.first+rhs.first, lhs.second+rhs.second};
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
class Treap {
   private:
    struct Node {
        int val, size, priority;
        Node *left, *right;
        Node(int v)
            : val(v),
              size(1),
              priority(rand()),
              left(nullptr),
              right(nullptr) {}
    };

    Node* root;

    int getSize(Node* t) { return t ? t->size : 0; }

    void update(Node* t) {
        if (t) t->size = 1 + getSize(t->left) + getSize(t->right);
    }

    void split(Node* t, int k, Node*& l, Node*& r) {
        if (!t) {
            l = r = nullptr;
        } else if (getSize(t->left) >= k) {
            split(t->left, k, l, t->left);
            r = t;
            update(r);
        } else {
            split(t->right, k - getSize(t->left) - 1, t->right, r);
            l = t;
            update(l);
        }
    }

    Node* merge(Node* l, Node* r) {
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            l->right = merge(l->right, r);
            update(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            update(r);
            return r;
        }
    }

    void insert(Node*& t, int pos, int val) {
        Node *l, *r;
        split(t, pos, l, r);
        Node* newNode = new Node(val);
        t = merge(merge(l, newNode), r);
    }

    void erase(Node*& t, int pos) {
        Node *l, *r, *m;
        split(t, pos, l, r);
        split(r, 1, m, r);
        delete m;
        t = merge(l, r);
    }

    int get(Node* t, int pos) {
        if (!t) throw out_of_range("Index out of range");
        int leftSize = getSize(t->left);
        if (pos < leftSize)
            return get(t->left, pos);
        else if (pos == leftSize)
            return t->val;
        else
            return get(t->right, pos - leftSize - 1);
    }

    void print(Node* t) {
        if (!t) return;
        print(t->left);
        cout << t->val << " ";
        print(t->right);
    }

    void clear(Node* t) {
        if (!t) return;
        clear(t->left);
        clear(t->right);
        delete t;
    }

   public:
    Treap() : root(nullptr) {
        srand(time(nullptr));  // 乱数初期化（必要に応じて一度だけ）
    }

    ~Treap() { clear(root); }

    void insert(int pos, int val) { insert(root, pos, val); }

    void erase(int pos) { erase(root, pos); }

    int get(int pos) { return get(root, pos); }

    void print() {
        print(root);
        cout << endl;
    }

    int size() { return getSize(root); }
};

void solveByTreap(){
    long long N;
    std::cin >> N;
    std::vector<long long> P(N);
    Treap t;
    for (int i = 0; i < N; i++) {
        std::cin >> P[i];
        t.insert(P[i] - 1, i + 1);
    }
    t.print();
    cout << endl;
}
#include <atcoder/all>
using namespace atcoder;
void solve(){
    long long N;
    std::cin >> N;
    std::vector<long long> P(N);
    fenwick_tree<long long> t(N+1);
    vll ans(N);
    for (int i = 0; i < N; i++) {
        std::cin >> P[i];
        P[i]--;
        t.add(i, 1);
    }
    repd(i,N){
        auto f = [&](int wj){
            return t.sum(0,wj) <= P[i];
        };
        auto binary_search = [&](auto f, ll ac, ll wa) -> ll {
            while (abs(ac - wa) > 1) {
                ll wj = (ac + wa) / 2;
                if (f(wj))
                    ac = wj;
                else
                    wa = wj;
            }
            return ac;
        };
        ll j = binary_search(f, 0, N+1);
        ans[j] = i+1;
        t.add(j, -1);
    }
    cout << ans << endl;
}
int main() {
    solve();
    return 0;
}
