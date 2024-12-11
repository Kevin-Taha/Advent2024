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



int main()
{
    auto input = readInput("input.txt");


    return 0;
}