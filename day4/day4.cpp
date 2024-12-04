#include "../includes.h"

vector<string> readCrossword(string inputFile)
{
    auto file = openFileSafe(inputFile);
    vector<string> out;

    string line;
    while(getline(file, line))
    {
        out.push_back(line);
    }

    return out;
}

bool searchDirection(vector<string>& crossWord, int i, int j, pair<int, int> direction)
{
    const string xmas = "XMAS";
    auto iter = xmas.begin();

    while(iter != xmas.end())
    {
        if (i < 0 || j < 0 || i >= crossWord.size() || j >= crossWord[0].length())
        {
            return false; // we went out of bounds.
        }

        if(crossWord[i][j] != *iter)
        {
            return false;
        }

        i += direction.first;
        j += direction.second;
        iter++;
    }

    return true;
}

// Recursive would be nice but would be difficult to handle maintaining the same direction. 
// Easier to just check in each relevant direction. 
int searchFrom(vector<string>& crossWord, int i, int j)
{
    int total = 0;

    // Search all 8 directions, pair represents {x, y} diff
    total += searchDirection(crossWord, i, j, pair{1, 0}); // right
    total += searchDirection(crossWord, i, j, pair{-1, 0}); // left
    total += searchDirection(crossWord, i, j, pair{0, 1}); // down
    total += searchDirection(crossWord, i, j, pair{0, -1}); // up

    total += searchDirection(crossWord, i, j, pair{-1, -1}); // left-up
    total += searchDirection(crossWord, i, j, pair{1, -1}); // right-up 
    total += searchDirection(crossWord, i, j, pair{-1, 1}); // left-down
    total += searchDirection(crossWord, i, j, pair{1, 1}); // right-down

    return total;
}

int countXmas(vector<string>& crossWord)
{
    int total = 0;

    // Find X characters and then traverse from there to count all XMAS instances. 
    for(int i = 0; i < crossWord.size(); i++)
    {
        for(int j = 0; j < crossWord[0].length(); j++)
        {
            if (crossWord[i][j] == 'X')
            {
                total += searchFrom(crossWord, i, j);
            }
        }
    }

    return total;
}

// Pt 2 Just find all 'A' characters and check diags. Format
// M.S      
// .A.
// M.S
// So opposite corners must contain both M and S. 
int countCrosses(vector<string>& crossWord)
{
    int total = 0;
    for(int i = 0; i < crossWord.size(); i++)
    {
        for(int j = 0; j < crossWord[0].length(); j++)
        {
            if (crossWord[i][j] == 'A')
            {
                // Need to not be at an edge
                if (i <= 0 || i >= crossWord.size() - 1 || j <= 0 || j >= crossWord[0].length() - 1)
                {
                    continue;
                }
                // Check that each diag contains an M and an S using unordered set comparison.
                unordered_set<char> upLeftDownRight {crossWord[i - 1][j - 1], crossWord[i + 1][j + 1]};
                unordered_set<char> upRightDownLeft {crossWord[i - 1][j + 1], crossWord[i + 1][j - 1]};
                if (upLeftDownRight == unordered_set{'M', 'S'} && upRightDownLeft == unordered_set{'M', 'S'})
                {
                    total++;
                }
            }
        }    
    }
    return total;
}

int main()
{
    auto crossword = readCrossword("input.txt");
    int total = countXmas(crossword);
    cout << "Total XMAS: " << total << endl;
    int totalCross = countCrosses(crossword);
    cout << "Total Cross: " << totalCross << endl;

    return 0;
}

