#include "../includes.h"

// Maps directions to their translational matrix, and the next direction
static const unordered_map<char, pair<pair<int, int>, char>> arrowTransform = {
    {'<', {{0, -1}, '^'}},
    {'^', {{-1, 0}, '>'}},
    {'>', {{0,1}, 'v'}},
    {'v', {{1, 0}, '<'}}
};

constexpr bool isInBounds(int x, int y, vector<vector<char>>& arr)
{
    return (x >= 0 && y >= 0 && x < arr.size() && y < arr[0].size());
}

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

bool isLoop(vector<vector<char>>& guardMap, int startRow, int startCol, char startDir)
{
    int i = 0;
    set<tuple<int, int, char>> visited;
    pair<int, int> guardLoc {startRow, startCol};
    char curDir = startDir;
    auto guardDir = arrowTransform.at(startDir).first;
    while(isInBounds(guardLoc.first, guardLoc.second, guardMap))
    {
        int nextRow = guardLoc.first + guardDir.first;
        int nextCol = guardLoc.second + guardDir.second;
        if (!isInBounds(nextRow, nextCol, guardMap)) return false;

        if (guardMap[nextRow][nextCol] == '#')
        {
            curDir = arrowTransform.at(curDir).second;
            guardDir = arrowTransform.at(curDir).first;
        }
        else
        {
            guardLoc = {nextRow, nextCol};
        }

        if(visited.count({guardLoc.first, guardLoc.second, curDir}))
        {
            return true; 
        }

        visited.insert({guardLoc.first, guardLoc.second, curDir});
    }

    return false;
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
            if (pathLen == 0 || guardMap[guardLoc.first][guardLoc.second] == '.')
            {
                // Mark current spot as visited and then increment pathLen
                guardMap[guardLoc.first][guardLoc.second] = curDir;
                pathLen++;

                // Check if making the next space a wall creates a loop (PT 2)
                char prevChar = exchange(guardMap[nextRow][nextCol], '#');
                if(isLoop(guardMap, guardLoc.first, guardLoc.second, curDir))
                {
                    possibleLoops++;
                }
                //possibleLoops += isLoop(guardMap, guardLoc.first, guardLoc.second, curDir);
                guardMap[nextRow][nextCol] = prevChar;
            }

            guardLoc = {nextRow, nextCol};
        }

    } while (isInBounds(guardLoc.first, guardLoc.second, guardMap));
    
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