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
    using weight_type = Weight;

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
    using edge_type = Edge;

    const size_t m_n_vertices;
    std::vector<std::vector<edge_type>> m_edges;

    graph(size_t n_vertices) : m_n_vertices(n_vertices), m_edges(n_vertices) { }

    inline size_t n_vertices() const { return m_n_vertices; }

    inline void add_edge(size_t from, size_t to, typename edge_type::weight_type weight) {
        m_edges[from].emplace_back(to, weight);
    }

    inline void add_edge(size_t from, size_t to) {
        m_edges[from].push_back(to);
    }

    inline void add_edge(size_t from, const edge_type &e) {
        m_edges[from].emplace_back(e);
    }

    inline void add_biedge(size_t v0, size_t v1, typename edge_type::weight_type weight) {
        m_edges[v0].emplace_back(v1, weight);
        m_edges[v1].emplace_back(v0, weight);
    }

    inline void add_biedge(size_t v0, size_t v1) {
        m_edges[v0].push_back(v1);
        m_edges[v1].push_back(v0);
    }

    inline std::vector<edge_type> edges_from(size_t v) const {
        return m_edges[v];
    }
};

#endif // GRAPH_CPP
