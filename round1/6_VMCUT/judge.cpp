#include <spoj.h>
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int n, m;
vector<pii> edges;
int dh;

int t_dh;

int main() {
    spoj_init();

    fscanf(spoj_p_in, "%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        pii edge;
        fscanf(spoj_p_in, "%d%d", &edge.first, &edge.second);
        edges.push_back(edge);
    }

    fscanf(spoj_p_out, "%d", &dh);
    fscanf(spoj_t_out, "%d", &t_dh);
    spoj_assert(dh == t_dh);

    int h_size;
    set<int> h;
    fscanf(spoj_t_out, "%d", &h_size);
    for (int i = 0; i < h_size; i++) {
        int vertex;
        fscanf(spoj_t_out, "%d", &vertex);
        
        spoj_assert(1 <= vertex && vertex <= n);
        spoj_assert(h.find(vertex) == h.end());

        h.insert(vertex);
    }

    for (int i = 0; i < m; i++) {
        if ((h.find(edges[i].first) != h.end() && h.find(edges[i].second) == h.end()) ||
            (h.find(edges[i].second) != h.end() && h.find(edges[i].first) == h.end()))
            t_dh--;
    }
    spoj_assert(t_dh == 0);

    return 0;
}
