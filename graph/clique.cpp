#include <vector> // std::vector


// Time complexity is O(N^2 * 2^N),
// where N is the number of vertices of graph g.
template <class AdjancencyMatrix>
std::vector<size_t> maximum_clique(const AdjancencyMatrix &g) {

    size_t N = g.size();

    std::vector<size_t> result;

    for (size_t bit = 1; bit < (1 << N); ++bit) {
        std::vector<size_t> s;
        for (size_t v = 0; v < N; ++v) {
            if (bit & (1 << v)) {
                s.push_back(v);
            }
        }
        bool is_clique = true;
        for (size_t i = 0; i < s.size(); ++i) {
            size_t u = s[i];
            for (size_t j = i + 1; j < s.size(); ++j) {
                size_t v = s[j];
                if (!g[u][v]) {
                    is_clique = false;
                    goto label;
                }
            }
        }
        label:
        if (is_clique && result.size() < s.size()) {
            result = s;
        }
    }
    
    return result; 
}
