#include "../includes.h"

pair<vector<int>, vector<int>> readInput(const string& fileName)
{
    vector<int> left;
    vector<int> right;
    ifstream file(fileName);

    if (!file.is_open())
    {
        cerr << "Fail to open file" << endl;
    }
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        int l, r;
        ss >> l >> r;
   //     cout << l << " " << r << endl;
        left.push_back(l);
        right.push_back(r);
    }

    return {left, right};
}   

int getTotalDistance(vector<int> left, vector<int> right)
{
    // No point not sorting the lists
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int totalDistance = 0;
    assert(right.size() == left.size());
    for(int i = 0; i < left.size(); i++)
    {
        totalDistance += abs(left[i] - right[i]);
    }
    return totalDistance;
}

// For each number in left list, multiply it by how much that num appears in right
// then add up
int calculateSimilarity(vector<int> left, vector<int> right)
{
    int similarityScore = 0;
    unordered_map<int, int> rightFreq;
    for(auto& i : right)
    {
        rightFreq[i]++;
    }

    for(auto& i : left)
    {
        similarityScore += i * rightFreq[i];
    }
    
    return similarityScore;
}

int main()
{
    auto [list1, list2] = readInput("input.txt");
    int totalDistance = getTotalDistance(list1, list2);
    cout << "Total Distance: " << totalDistance << endl;
    int similarity = calculateSimilarity(list1, list2);
    cout << "Similarity Score: " << similarity << endl;
    return 0;
}


