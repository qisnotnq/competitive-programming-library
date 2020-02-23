#include <bits/stdc++.h>

#include "graph.cpp"
#include "range_query/segment_tree.cpp"

#ifdef DEBUG
#define PRINT(x)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#x<<" = "<<(x)<<endl;
#define PRINTA(a,first,last)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#a<<"["<<(first)<<", "<<(last)<<")"<<endl;\
    for (int i=(first);i<(last);++i){cout<<#a<<"["<<i<<"] = "<<(a)[i]<<endl;}
#define PRINTP(p)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#p<<" = ("<<(p.first)<<", "<<(p.second)<<")"<<endl;
#define PRINTI(a,i)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#a<<"["<<#i<<"] = "<<#a<<"["<<(i)<<"] = "<<(a)[i]<<endl;
#else
#define PRINT(x)
#define PRINTA(a,first,last)
#define PRINTP(p)
#define PRINTI(a,i)
#endif

#define FOR(i,a,b) for (int i=(a);i<(b);++i)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);--i)
#define REP(i,n) for (int i=0;i<(n);++i)
#define RREP(i,n) for (int i=(n)-1;i>=0;--i)
#define pb push_back
#define mp make_pair
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define MOD 1000000007

using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

template <class Graph>
struct heavy_light_decomposition {
    using Edge = typename Graph::edge_type;
    using Weight = typename Edge::weight_type;

    int n_vertices;
    int m_root;
    vector<int> sizes;
    vector<int> heavy_children;
    vector<int> branch_vertices;
    vector<int> pos;
    vector<int> pos_end;
    vector<int> depth;
    segment_tree<Weight> seg_tree;

    heavy_light_decomposition(const Graph &g, int root) : n_vertices(g.n_vertices()), m_root(root) , seg_tree(n_vertices, 0, [](Weight x, Weight y) { return x + y; }) {

        cout << "heavylieght called" << endl;
        sizes.resize(n_vertices);
        heavy_children.resize(n_vertices);
        branch_vertices.resize(n_vertices);
        pos.resize(n_vertices);
        pos_end.resize(n_vertices);
        depth.resize(n_vertices);

        function<void(int, int)> dfs = [&](int v, int parent) {

            printf("dfs(%d, %d) is called\n", v, parent);

            sizes[v] = 1;
            heavy_children[v] = -1;
            int child_size_max = -1;

            for (const Edge &e: g.edges_from(v)) {
                int child = e.to();

                if (child == parent) continue;
                
                dfs(child, v);

                sizes[v] += sizes[child];

                if (child_size_max < sizes[child]) {
                    child_size_max = sizes[child];
                    heavy_children[v] = child;
                }
            }

            return sizes[v];
        };

        dfs(root, -1);

        int cur_pos = n_vertices;

        function<void(int, int, int, int)> decompose = [&](int v, int parent, int bv, int ep) {
            printf("decompose(%d, parent=%d, branch_vertices=%d) is called\n", v, parent, bv);
            branch_vertices[v] = bv;
            pos[v] = --cur_pos;
            pos_end[v] = ep;
            if (heavy_children[v] != -1) {
                decompose(heavy_children[v], v, bv, ep);
            }
            for (const Edge &e: g.edges_from(v)) {
                int child = e.to();

                if (child != parent && child != heavy_children[v]) {
                    decompose(child, v, v, cur_pos);
                }
            }
        };

        decompose(root, n_vertices, n_vertices, n_vertices);

        REP(i, n_vertices) {
            printf("sizes[%d] = %d\n", i, sizes[i]);
        }

        REP(i, n_vertices) {
            printf("heavy_children[%d] = %d\n", i, heavy_children[i]);
        }

        REP(i, n_vertices) {
            printf("branch_vertices[%d] = %d\n", i, branch_vertices[i]);
        }

        REP(i, n_vertices) {
            printf("pos[%d] = %d\n", i, pos[i]);
        }

        REP(i, n_vertices) {
            printf("pos_end[%d] = %d\n", i, pos_end[i]);
        }
    }

    ~heavy_light_decomposition() {
        printf("~heavy_light_decomposition() is called\n");
    }

    void update(int v, Weight w) {
        printf("update vertex v = %d, pos[v] = %d\n", v, pos[v]);
        seg_tree.update(pos[v], w);
    }

    Weight query(int v) {
        Weight result = 0;
        do {
            printf("vertex %d to %d, segment [%d, %d)\n", v, branch_vertices[v], pos[v], pos_end[v]);
            result += seg_tree.query(pos[v], pos_end[v]);
        } while ((v = branch_vertices[v]) != n_vertices);
        return result;
    }
};
