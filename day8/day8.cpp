#include "../includes.h"

vec2d<char> readFile(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vec2d<char> out;
    string line;
    while(getline(file, line))
    {
        vector<char> row {line.begin(), line.end()};
        out.push_back(row);
    }
    return out;
}

int countAntinodeLocs(vec2d<char>& antennas)
{
    int numUnique = 0;









    return numUnique;
}

int main()
{
    auto in = readFile("input.txt");
    auto numAntiLocs = countAntinodeLocs(in);
    cout << "Antinode Unique Locations "<< numAntiLocs << endl;

    return 0;
}