#pragma once

#include <list>
#include <map>
#include <string_view>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

namespace genome
{

// one possible starting point
//

    using Node = std::string;

    class Edge
    {
    public:
        Edge(const Node &from, const Node &to);

        const auto &from() const { return m_from; }
        const auto &to() const { return m_to; }

        bool operator==(const Edge &other) const;

    private:
        Node m_from;
        Node m_to;
    };

    class Graph
    {
    public:
        Graph(std::size_t k, const std::vector<std::string>& reads);

        void add_edge(Edge edge);

        std::list<Node> find_euler_path();

    private:
        std::map<Node, std::list<Node>> m_edges_out;

        std::map<Node, unsigned int> m_edges_in;
    };

} // namespace genome