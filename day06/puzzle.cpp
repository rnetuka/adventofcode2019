//
// Created by rnetuka on 06.12.19.
//

#include <algorithm>
#include <string>
#include <vector>

#include "graph.h"

using namespace std;


pair<int, int> steps_to_intersection(const vector<string>& a, const vector<string>& b) {
    for (int i = 0; i < a.size(); i++)
        if (auto it = find(b.begin(), b.end(), a[i]); it != b.end()) {
            int j = distance(b.begin(), it);
            return { i , j };
        }
    return { -1, -1 };
}

int orbit_count_checksum()
{
    int checksum = 0;

    for (auto& object : orbit_map.nodes())
        checksum += orbit_map.parents_of(object).size();

    return checksum;
}

int steps_required_to_reach_santa()
{
    vector<string> my_parents = orbit_map.parents_of("YOU");
    vector<string> santas_parents = orbit_map.parents_of("SAN");

    auto [i, j] = steps_to_intersection(my_parents, santas_parents);
    return i + j;
}