#include "../includes.h"

vec2d<char> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vec2d<char> res;

    string line;
    while(getline(file, line))
    {
        res.emplace_back(line.begin(), line.end());
    }

    return res;
}

uint64_t priceOfRegion(vec2d<char>& grid, int row, int col)
{




}

uint64_t totalFencePrice(vec2d<char>& grid)
{
    uint64_t totalPrice = 0;
    for(int row = 0; row < grid.size(); row++)
    {
        for(int col = 0; col < grid[0].size(); col++)
        {
            if(grid[row][col] != '0')
            {
                totalPrice += priceOfRegion(grid, row, col);
            }
        }
    }

    return totalPrice;
}

int main()
{
    auto input = readInput("input.txt");


    for(auto row : input)
    {
        printVector(row);
    }

    return 0;
}