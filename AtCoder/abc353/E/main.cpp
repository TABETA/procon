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

/* debug */
#define debug(x) cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << endl;

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
template <typename element_type, typename array_type>
struct Trie {
    struct Node {
        Node(element_type val)
            : m_val(val),
              m_used(),
              m_descendantCount(),
              m_terminalCount(),
              m_children() {}
        Node() : Node(element_type{}) {}
        bool canTerminate() const { return m_terminalCount != 0; }
        bool hasChild(const element_type& val) const {
            return m_children.count(val) != 0;
        }
        Node* getChild(const element_type& val) const {
            if (!hasChild(val)) return nullptr;
            return &m_children[val];
        }
        int insert(const array_type& vals) { return insert(vals, 0); }
        size_t size() const { return m_descendantCount; }

       private:
        element_type m_val;
        int m_used;
        int m_descendantCount;
        int m_terminalCount;
        map<element_type, Node> m_children;
        int insert(const array_type& vals, int i) {
            ++m_used;
            if(i == (int)vals.size()){
                ++m_terminalCount;
                return m_used-1;
            }
            const element_type& val = vals[i];
            if(!m_children.count(val)){
                m_children[val] = Node(val);
            }
            ll cnt = m_children[val].insert(vals, i + 1);
            return (m_used-1)*(i!=0) + cnt;
        }
    };
    Node m_root;
    Trie() : m_root() {}
    int insert(const array_type& word) { return m_root.insert(word); }
    bool exists(const array_type& word, bool prefix = false) {
        Node* cur = &m_root;
        for (auto&& c : word) {
            auto next = cur->getChild(c);
            if (next == nullptr) {
                return false;
            }
        }
        return (prefix) ? true : cur->canTerminate();
    }
    bool startsWith(const array_type& prefix) { return exists(prefix, true); }
    size_t size() const { return m_root.size(); }
};

int main() {
    long long N;
    std::cin >> N;
    Trie<char, string> trie;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        CIN(string, s);
        ans += trie.insert(s);
    }
    cout << ans << endl;
    return 0;
}
