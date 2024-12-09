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
    unordered_map<char, vector<pair<int, int>>> mp;
    vec2d<bool> antiNodes (antennas.size(), vector<bool>(antennas[0].size(), false));

    for(int i = 0; i < antennas.size(); i++)
    {
        for(int j = 0; j < antennas[0].size(); j++)
        {
            char loc = antennas[i][j];
            if (loc != '.')
            {
                auto& sameFreq = mp[loc];
                
                // First compute the antinodes with all other existing antennas of the same frequency
                for(auto& other : sameFreq)
                {
                    // Direction vector from new antenna to other  
                    pair<int, int> diffVec {other.first - i, other.second - j};
                    // First antinode is other + distance
                    pair<int, int> posAntinode{other.first + diffVec.first, other.second + diffVec.second};
                    // Second antinode is new antenna - distance
                    pair<int, int> newAntinode{i - diffVec.first, j - diffVec.second};

                    for(auto [antiRow, antiCol] : {posAntinode, newAntinode})
                    {
                        // If row, col is not already an antinode, mark it
                        if (isInBounds(antiRow, antiCol, antiNodes) && !antiNodes[antiRow][antiCol])
                        {
                            numUnique++;
                            antiNodes[antiRow][antiCol] = true;
                        }
                    }
                }

                // add new antenna to list
                sameFreq.emplace_back(i, j);
            }
        }
    }

    return numUnique;
}

// Part  2
int countAntinodeResonantFreq(vec2d<char>& antennas)
{
    int numUnique = 0;
    unordered_map<char, vector<pair<int, int>>> mp;
    vec2d<bool> antiNodes (antennas.size(), vector<bool>(antennas[0].size(), false));

    for(int i = 0; i < antennas.size(); i++)
    {
        for(int j = 0; j < antennas[0].size(); j++)
        {
            char loc = antennas[i][j];
            if (loc != '.')
            {
                auto& sameFreq = mp[loc];
                
                // First compute the antinodes with all other existing antennas of the same frequency
                for(auto& other : sameFreq)
                {
                    // Direction vector from new antenna to other  
                    pair<int, int> diffVec {other.first - i, other.second - j};

                    vector<pair<int, int>> candidates;
                    // Get all antinodes candidates starting at other antenna (keep adding distance)
                    int start = other.first;
                    int end = other.second;
                    while(isInBounds(start, end, antiNodes))
                    {
                        candidates.emplace_back(start, end);
                        start += diffVec.first;
                        end += diffVec.second;
                    }
                    
                    // Get all antinodes candidates starting at new antenna (sub distance)
                    start = i;
                    end = j;
                    while(isInBounds(start, end, antiNodes))
                    {
                        candidates.emplace_back(start, end);
                        start -= diffVec.first;
                        end -= diffVec.second;
                    }

                    for(auto [antiRow, antiCol] : candidates)
                    {
                        // If row, col is not already an antinode, mark it
                        if (isInBounds(antiRow, antiCol, antiNodes) && !antiNodes[antiRow][antiCol])
                        {
                            numUnique++;
                            antiNodes[antiRow][antiCol] = true;
                        }
                    }
                }

                // add new antenna to list
                sameFreq.emplace_back(i, j);
            }
        }
    }

    return numUnique;
}

int main()
{
    auto in = readFile("input.txt");
    auto numAntiLocs = countAntinodeLocs(in);
    cout << "Antinode Unique Locations "<< numAntiLocs << endl;

    auto numAntiPt2 = countAntinodeResonantFreq(in);
    cout << "Antinode Unique Locs w/ Resonant Freqs " << numAntiPt2;

    return 0;
}