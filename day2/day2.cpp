#include "../includes.h"

bool isReportSafe(vector<int>& report, bool dampenerActive);
int getNumSafeLevels(string inputFile, bool dampenerActive);

int main()
{
    int safeLevels = getNumSafeLevels("input.txt", false);
    cout << "Safe Levels: " << safeLevels << endl;

    // With dampener
    int safeLevelsDampener = getNumSafeLevels("input.txt", true);
    cout << "Safe Levels w/ Dampener " << safeLevelsDampener << endl;

    return 0;
}

int getNumSafeLevels(string inputFile, bool dampenerActive = false)
{
    int safeLevels = 0;
    
    // Read report as vector of levels
    auto file = openFileSafe(inputFile);
    string line;
    while(getline(file, line))
    {
        auto report = readLineIntoVector(line);
        if (isReportSafe(report, dampenerActive))
        {
            //printVector(report);
            safeLevels++;
        }
    }

    return safeLevels;
}

bool isReportSafe(vector<int>& report, bool dampenerActive = false)
{
    bool isIncreasing = (report.back() > report.front());

    for(int i = 1; i < report.size(); i++)
    {
        int diff = abs(report[i] - report[i - 1]);
        bool safe = ((report[i] > report[i - 1]) == isIncreasing) &&
            (diff >= 1 && diff <= 3);

        if (!safe)
        {
            if (dampenerActive)
            {
                // Try again with i - 1, or i removed. 
                vector<int> prevRemoved(report);
                prevRemoved.erase(prevRemoved.begin() + (i - 1));
                vector<int> currRemoved(report);
                currRemoved.erase(currRemoved.begin() + i);

                if(isReportSafe(prevRemoved, false) || isReportSafe(currRemoved, false)) return true;
            }
            return false;
        }
    }

    return true;
}
