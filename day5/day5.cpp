#include "../includes.h"

void readInput(string inputFile, vector<pair<int, int>>& rules, vector<vector<int>>& updates)
{
    auto file = openFileSafe(inputFile);

    // First read rules in x|y format
    string line;
    while(getline(file, line))
    {
        int x, y;

        if (sscanf(line.c_str(), "%d|%d", &x, &y) == 2)
        {
            rules.emplace_back(x, y);
        }
        else
        {
            break; // We made it to the new line
        }
    }

    // Read updates into a vector
    while(getline(file, line))
    {
        vector<int> update;
        stringstream ss(line);
        int num;

        while(ss >> num)
        {
            update.push_back(num);
            ss.ignore(1); // ignore comma
        }
        updates.push_back(update);
    }
}

pair<int, int> isOrderedMiddleSum(vector<pair<int, int>>& rules, vector<vector<int>>& updates)
{
    int totalOrdered = 0;
    int totalUnordered = 0;
    // Every value in this map represents numbers known to be higher than the key. 
    unordered_map<int, unordered_set<int>> lessThan;
    for(auto& rule: rules)
    {
        lessThan[rule.first].insert(rule.second);
    }

    auto ruleCompare = [&lessThan](int a, int b)
    {
        // a < b if b exists in lessThan[a]
        return lessThan[a].contains(b);
    };

    for(auto& update : updates)
    {
        if (is_sorted(update.begin(), update.end(), ruleCompare))
        {
            // Sorted, add the middle number to the sum. 
            totalOrdered += update[update.size() / 2];
        }
        else
        {
            sort(update.begin(), update.end(), ruleCompare);
            totalUnordered += update[update.size() / 2];
        }
    }

    return {totalOrdered, totalUnordered};
}

int main()
{
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;
    readInput("input.txt", rules, updates);
    auto sums = isOrderedMiddleSum(rules, updates);

    cout << "Part 1 Sum: " << sums.first << endl;
    cout << "Part 2 Sum: " << sums.second << endl;

    return 0;
}