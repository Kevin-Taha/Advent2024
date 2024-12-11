#include "../includes.h"

vec2d<int> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vec2d<int> out;

    string line;
    while(getline(file, line))
    {
        vector<int> nums;
        for(char& c : line)
        {
            nums.push_back(c - '0');
        }
        out.push_back(nums);
    }

    return out;
}

vector<pair<int, int>> getValidAdjacentSpaces(vec2d<int> grid, int row, int col)
{
    vector<pair<int, int>> adjacent;
    int currentVal = grid[row][col];

                      //                up               down                   left                 right  
    for(auto& dir : {pair<int, int>{-1, 0}, pair<int, int>{1, 0}, pair<int, int>{0, -1}, pair<int, int>{0, 1}})
    {
        auto candidate = pair<int, int>{row + dir.first, col + dir.second};
        if(isInBounds(candidate.first, candidate.second, grid) &&
            grid[candidate.first][candidate.second] == currentVal + 1)
        {
            adjacent.push_back(candidate);
        }
    }
    return adjacent;
}

int walkTrail(vec2d<int>& grid, int row, int col, vec2d<bool>& peaksVisited, bool distinctTrails)
{
    // Base case: made it to peak
    if (grid[row][col] == 9 && !peaksVisited[row][col])
    {
        if (!distinctTrails)
        {
            peaksVisited[row][col] = true;
        }

        return 1;
    }
    auto adjacent = getValidAdjacentSpaces(grid, row, col);

    // Base case: Nowhere else to go 
    if (adjacent.empty())
    {
        return 0;
    }

    int peakSum = 0;
    for(auto& [adjRow, adjCol] : adjacent)
    {
        peakSum += walkTrail(grid, adjRow, adjCol, peaksVisited, distinctTrails);
    }

    return peakSum;
}

int sumScores(vec2d<int>& grid, bool distinctTrails)
{
    int scoreSum = 0;

    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[0].size(); j++)
        {
            if(grid[i][j] == 0)
            {
                vec2d<bool> peaksVisited(grid.size(), vector<bool>(grid[0].size(), false));
                scoreSum += walkTrail(grid, i, j, peaksVisited, distinctTrails);
            }
        }
    }

    return scoreSum;
}

int main()
{
    auto input = readInput("input.txt");
    auto score = sumScores(input, false);
    cout << "Pt 1 Score Sum: " << score << endl;

    auto score2 = sumScores(input, true);
    cout << "Pt 2 Score Sum: " << score2 << endl;

    return 0;
}