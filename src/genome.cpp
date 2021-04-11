#include <map>
#include <graph.h>
#include "genome.h"

namespace genome
{

    std::string assembly(size_t k, const std::vector<std::string> & reads)
    {
        if (k == 0 || reads.empty())
        {
            return "";
        }
        Graph f(k, reads);
//        f.create_graph(k, reads);
        std::list<std::string> res = f.find_euler_path();
        std::string ans = res.front();
        res.pop_front();
        while (!res.empty())
        {
            ans += res.front().back();
            res.pop_front();
        }
        return ans;
    }

}