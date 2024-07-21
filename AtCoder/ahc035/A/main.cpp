#include <bits/stdc++.h>
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
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
/* define short */
#define CIN(type, name) type name; cin >> name;
#define all(obj) (obj).begin(), (obj).end()

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i,n) for(ll i=n-1;i>=0;i--)
#define rrepd(i,n) for(ll i=n;i>=1;i--)
#define repr(i, n) for(auto&& i: n)

// clang-format on
int N, M, T;
int seed_count;

auto seeding(const vvll& X) {
    static int t = 1;
    using Tp = tuple<ll,ll,ll,ll,ll,ll,ll,ll,ll,ll,ll,ll,ll,ll,ll, int>;
    deque<Tp> XX;
    rep(i,X.size()){
        XX.emplace_back(
            X[i][0], 
            X[i][1], 
            X[i][2], 
            X[i][3], 
            X[i][4], 
            X[i][5], 
            X[i][6], 
            X[i][7], 
            X[i][8], 
            X[i][9], 
            X[i][10], 
            X[i][11], 
            X[i][12], 
            X[i][13], 
            X[i][14], 
            i
        );
    }
    auto cmp = [](Tp l, Tp r){
        auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
        auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
        auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
        auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
        return sum1 > sum2;
    };
    ranges::sort(XX, cmp);
    while(XX.size() > N*N){
        XX.pop_back();
    }
        vvll A(N,vll(N));
    bool omo = false;
    rep(i,N){
        rep(j,N){
            if(omo){
                switch(t){
                    case 1:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l2+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r2+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 2:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l6+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r6+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 3:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 4:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 5:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 6:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 7:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 8:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 9:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 10:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    default:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                }
            } else {
                switch(t){
                    case 1:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l3+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r3+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 2:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l7+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r7+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 3:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 4:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 5:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 6:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 7:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 8:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 9:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    case 10:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                    default:
                        ranges::sort(XX, [](Tp l, Tp r){
                            auto [l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15, il] = l;
                            auto [r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15, ir] = r;
                            auto sum1 = l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12+l13+l14+l15;
                            auto sum2 = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15;
                            return sum1 > sum2;
                        });
                        break;
                }
            }
            A[i][j] = get<15>(XX.front()); XX.pop_front();
            omo = !omo;
        }
        omo = !omo;
    }
    ++t;
    return A;
}

auto output(const vvll& A){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j];
            if (j < N - 1) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    }
    cout.flush();
}
auto repair(vvll& A){
    set<ll> remain;
    rep(i,seed_count){
        remain.emplace(i);
    }
    set<ll*> viols;
    rep(i,N){
        rep(j,N){
            if(remain.count(A[i][j])){
                remain.erase(A[i][j]);
            } else {
                viols.emplace(&A[i][j]);
            }
        }
    }
    random_device rd;
    mt19937 g(rd());
    for (ll* v : viols)
    {
        auto it = remain.begin();
        advance(it, g() % remain.size());
        *v = *it;
        remain.erase(it);
    }
    return A;
}
int main() {
    cin >> N >> M >> T;
    seed_count = 2 * N * (N - 1);
    vvll X(seed_count, vll(M, 0));
    for (int i = 0; i < seed_count; i++) {
        for (int j = 0; j < M; j++) {
            cin >> X[i][j];
        }
    }
    for (int t = 0; t < T; t++) {
        auto A = seeding(X);
        output(repair(A));
        for (int i = 0; i < seed_count; i++) {
            for (int j = 0; j < M; j++) {
                cin >> X[i][j];
            }
        }
    }
    return 0;
}