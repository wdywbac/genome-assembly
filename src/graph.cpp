#include <iostream>
#include <stack>
#include "graph.h"

namespace genome {

    Edge::Edge(const Node &from, const Node &to)
            : m_from(from), m_to(to) {}

    bool Edge::operator==(const Edge &other) const
    {
        return m_from == other.m_from && m_to == other.m_to;
    }

    Graph::Graph(std::size_t k, const std::vector<std::string> &reads)
    {
        for (const auto &read : reads)
        {
            for (std::size_t j = 0; j < read.length() - k; j++)
            {
                std::string node = read.substr(j, k + 1);
                Edge edge(node.substr(0, k), node.substr(1, k));
                add_edge(edge);
            }
        }
    }

    void Graph::add_edge(Edge edge)
    {
        m_edges_out[edge.from()].push_back(edge.to());
        m_edges_in[edge.to()]++;
    }

    std::list<Node> Graph::find_euler_path()
    {
        std::list<Node> path;

        Node first;
        for (const auto & [from, out] : m_edges_out)
        {
            unsigned int deg_in = m_edges_in[from];
            unsigned int deg_out = out.size();
            if (deg_out > deg_in)
            {
                first = from;
                break;
            }
            else if ((deg_in - deg_out) % 2 == 1)
            {
                first = from;
            }
        }

        std::stack<Node> st;
        st.push(first);

        while (!st.empty())
        {
            std::list<Node>& temp = m_edges_out[st.top()];
            auto it = temp.begin();
            if (it != temp.end())
            {
                st.push(*it);
                temp.pop_front();
            }
            else
            {
                path.emplace_back(st.top());
                st.pop();
            }
        }

        path.reverse();
        return path;
    }

} // namespace genome