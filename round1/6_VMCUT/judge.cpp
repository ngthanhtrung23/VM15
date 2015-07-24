#include "spoj.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int n, m;
vector<pii> edges;
int dh;

int t_dh;

int main() {
    spoj_init();

    // input the graph
    fscanf(spoj_p_in, "%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        pii edge;
        fscanf(spoj_p_in, "%d%d", &edge.first, &edge.second);
        edges.push_back(edge);
    }

    // check D(H)
    fscanf(spoj_p_out, "%d", &dh);
    fscanf(spoj_t_out, "%d", &t_dh);
    spoj_assert(dh == t_dh);

    // check the set H 
    int h_size;
    set<int> h;
    fscanf(spoj_t_out, "%d", &h_size);
    for (int i = 0; i < h_size; i++) {
        int vertex;
        fscanf(spoj_t_out, "%d", &vertex);
        
        // verify whether the user's vertex is correct 
        spoj_assert(1 <= vertex && vertex <= n);

        // no vertex appears twice in the list
        spoj_assert(h.find(vertex) == h.end());

        h.insert(vertex);
    }

    for (int i = 0; i < m; i++) {
        if ((h.find(edges[i].first) != h.end() && h.find(edges[i].second) == h.end()) ||
            (h.find(edges[i].second) != h.end() && h.find(edges[i].first) == h.end()))
            t_dh--;
    }
    // verify whether the set H corresponds to D(H)
    spoj_assert(t_dh == 0);

    fprintf(spoj_score, "1");

    return 0;
}
