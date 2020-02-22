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
    vector<int> head;
    vector<int> pos;
    vector<int> depth;
    segment_tree<Weight> st;

    heavy_light_decomposition(const Graph &g, int root) : n_vertices(g.n_vertices()), m_root(root) {

        cout << "heavylieght called" << endl;
        sizes.resize(n_vertices);
        heavy_children.resize(n_vertices);
        head.resize(n_vertices);
        pos.resize(n_vertices);
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

        function<void(int, int, int)> decompose = [&](int v, int parent, int h) {
            printf("decompose(%d, parent=%d, head=%d) is called\n", v, parent, h);
            head[v] = h;
            pos[v] = --cur_pos;
            if (heavy_children[v] != -1) {
                decompose(heavy_children[v], v, v);
            }
            for (const Edge &e: g.edges_from(v)) {
                int child = e.to();

                if (child != parent && child != heavy_children[v]) {
                    decompose(child, v, child);
                }
            }
        };

        decompose(root, n_vertices, n_vertices);

        REP(i, n_vertices) {
            printf("sizes[%d] = %d\n", i, sizes[i]);
        }

        REP(i, n_vertices) {
            printf("heavy_children[%d] = %d\n", i, heavy_children[i]);
        }

        REP(i, n_vertices) {
            printf("head[%d] = %d\n", i, head[i]);
        }

        REP(i, n_vertices) {
            printf("pos[%d] = %d\n", i, pos[i]);
        }
    }
};
