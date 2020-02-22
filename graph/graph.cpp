#ifndef GRAPH_CPP
#define GRAPH_CPP

#include <iostream> // std::ostream
#include <vector> // std::vector

struct edge {
    typedef size_t weight_type;

    size_t m_to;

    edge(size_t to) : m_to(to) { }

    inline size_t to() const { return m_to; }

    inline weight_type weight() const { return 1; }

    friend std::ostream& operator<<(std::ostream &os, const edge &e) {
        os << "{ to: " << e.m_to << " }";
        return os;
    }
};

template <typename Weight>
struct weighted_edge : public edge {
    typedef Weight weight_type;

    weight_type m_weight;

    weighted_edge(size_t to, weight_type weight) : edge(to), m_weight(weight) { }

    inline weight_type weight() const { return m_weight; }

    friend std::ostream& operator<<(std::ostream &os, const weighted_edge &e) {
        os << "{ to: " << e.m_to << ", weight = " << e.m_weight << " }";
        return os;
    }
};

template <class Edge>
struct graph {
    typedef Edge edge_type;

    size_t m_n_vertices;
    std::vector<std::vector<edge_type>> m_edges;

    graph(size_t n_vertices) : m_n_vertices(n_vertices), m_edges(n_vertices) { }

    inline size_t n_vertices() const { return m_n_vertices; }

    inline void make_edge(size_t from, size_t to, typename edge_type::weight_type weight) {
        m_edges[from].emplace_back(edge_type(to, weight));
    }

    inline void make_edge(size_t from, size_t to) {
        m_edges[from].emplace_back(edge(to));
    }

    inline void make_edge(size_t from, const edge_type &e) {
        m_edges[from].emplace_back(e);
    }

    inline std::vector<edge_type> edges_from(size_t v) const {
        return m_edges[v];
    }
};

#endif // GRAPH_CPP
