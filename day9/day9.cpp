#include "../includes.h"

vector<int> readInput(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vector<int> nums;
    string line;

    while(getline(file, line))
    {
        for(char& c : line)
        {
            nums.push_back(c - '0');
        }
    }

    return nums;
}

int main()
{
    auto numArr = readInput("input.txt");




    return 0;
}
