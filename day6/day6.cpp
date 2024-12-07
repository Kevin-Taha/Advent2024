#include "../includes.h"

// Maps directions to their translational matrix, and the next direction
static const unordered_map<char, pair<pair<int, int>, char>> arrowTransform = {
    {'<', {{0, -1}, '^'}},
    {'^', {{-1, 0}, '>'}},
    {'>', {{0,1}, 'v'}},
    {'v', {{1, 0}, '<'}}
};

vector<vector<char>> readMap(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vector<vector<char>> guardMap;

    string line;
    while(getline(file, line))
    {
        guardMap.emplace_back(line.begin(), line.end());
    }

    return guardMap;
}

pair<int, int> getGuardLoc(vector<vector<char>>& guardMap)
{
    pair<int, int> guardLoc;
    for(int i = 0; i < guardMap.size(); i++)
    {
        for(int j = 0; j < guardMap[0].size(); j++)
        {
            auto it = arrowTransform.find(guardMap[i][j]);
            if (it != arrowTransform.end())
            {
                return {i, j};
            }
        }
    }
    return {0,0};
}

int countGuardPath(vector<vector<char>>& guardMap)
{
    int pathLen = 0;
    int possibleLoops = 0;

    // First find initial position and direction of guard. 
    pair<int, int> guardLoc = getGuardLoc(guardMap);
    char curDir = guardMap[guardLoc.first][guardLoc.second];
    pair<int, int> guardDir = arrowTransform.at(curDir).first;

    do
    {
        // Get next tile
        int nextRow = guardLoc.first + guardDir.first;
        int nextCol = guardLoc.second + guardDir.second;

        //cout << "next row " << nextRow << " " << "Col: " << nextCol << endl;
        if (guardMap[nextRow][nextCol] == '#')
        {
            // Change direction
            curDir = arrowTransform.at(curDir).second;
            guardDir = arrowTransform.at(curDir).first;
            //cout << "change dir " << curDir << "  Transform  " << guardDir.first << " " << guardDir.second << endl; 
        }
        else
        {
            // If the spot we're leaving from hasn't been visited, mark it and inc pathLen
            if (guardMap[guardLoc.first][guardLoc.second] == '.')
            {
                // Mark current spot as visited and then increment pathLen
                guardMap[guardLoc.first][guardLoc.second] = curDir;
                pathLen++;
            }

            guardLoc = {nextRow, nextCol};
        }

    } while (guardLoc.first >= 0 && guardLoc.first < guardMap.size() && guardLoc.second >= 0 && guardLoc.second < guardMap[0].size());
    
    cout << "Possible obstruction loops: " << possibleLoops << endl;
    return pathLen;
}

int main()
{
    auto guardMap = readMap("input.txt");
    auto guardPathCount = countGuardPath(guardMap);
    cout << "Guard path: " << guardPathCount << endl;

    return 0;   
}