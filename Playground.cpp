#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main()
{
    fstream fin;
    int command;
    // cout << "1 Choose from Existing Maps" << endl
    //      << "2 Import a Custom Map";
    // cin >> command;
    string name;
    cin >> name;
    fin.open(name);
    vector<vector<int>> map;
    vector<int> row;
    string bucket;
    string sub;
    while (getline(fin, bucket))
    {
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i] != ' ')
            {
                sub = bucket.substr(i, bucket.find(' ', i) - i);
                row.push_back(stoi(sub));
                i = bucket.find(' ', i);
            }
        }
        map.push_back(row);
    }
    // system("cls");
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < row.size(); j++)
        {

            if (map[i][j] < 0)
                cout << " ";
            else
                cout << "  ";
            cout << map[i][j];
        }
        cout << endl;
    }
}