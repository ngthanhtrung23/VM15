#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a); i <= (b); ++i)
using namespace std;

const int MN = 211;
int n, m;
int eu[MN*MN], ev[MN*MN];
int cur[MN], best[MN];
int curCut, bestCut;

int main() {
    cin >> n >> m;
    FOR(i,1,m) {
        cin >> eu[i] >> ev[i];
    }
    bestCut = 0;
    FOR(turn,1,10001110 / n / n) {
        FOR(i,1,n) cur[i] = rand() % 2;

        curCut = 0;
        FOR(i,1,m)
            if (cur[eu[i]] != cur[ev[i]]) ++curCut;

        if (curCut > bestCut) {
            bestCut = curCut;
            FOR(i,1,n) best[i] = cur[i];
        }
    }
    cout << bestCut << endl;
    int cnt = 0; FOR(i,1,n) if (best[i]) ++cnt;
    cout << cnt << endl;
    FOR(i,1,n) if (best[i]) cout << i << ' '; cout << endl;
}
