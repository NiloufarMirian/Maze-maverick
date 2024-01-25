#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void printmap(vector<vector<int>> map, vector<vector<char>> lead);
bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<char>> lead);

int main()
{
    fstream fin;
    int command;
    // cout << "1 Choose from Existing Maps" << endl
    //      << "2 Import a Custom Map" << endl;
    // cin >> command;
    string name;
    // cin >> name;
    fin.open("Maps/complex.txt");
    // fin information
    getline(fin, name);
    string level;
    fin >> level;
    int pathLength;
    fin >> pathLength;
    // fin map
    vector<vector<int>> map;
    vector<vector<char>> lead;
    string bucket;
    string sub;
    while (getline(fin, bucket))
    {
        vector<int> row;
        vector<char> lead1;
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i] != ' ' && (int(bucket[i]) == 45 || (int(bucket[i]) > 47 && int(bucket[i]) < 58)))
            {
                sub = bucket.substr(i, bucket.find(' ', i) - i);
                row.push_back(stoi(sub));
                if (stoi(sub) != 0)
                    lead1.push_back('*');
                else
                    lead1.push_back('#');

                i += sub.size() - 1;
            }
        }
        if (!row.empty())
        {
            map.push_back(row);
            lead.push_back(lead1);
        }
    }
    int i = 0;
    int j = 0;
    lead[i][j] = '#';
    int sum=0;
    sum += map[i][j];
    printmap(map, lead);

    char ch;
    while (1)
    {
        if (_kbhit())
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up
                if (isValidMove(i - 1, j, map.size(), map[0].size(), lead))
                {
                    i--;
                    lead[i][j] = '#';
                    if (i==map.size()-1 && j==map[0].size()-1 && sum==map[i][j])
                    {
                        cout << "You won!";
                        return 0;
                    }
                    sum += map[i][j];
                    printmap(map, lead);
                }
                else
                    cout << "Invalid move!";
                break;
            case 80: // Down
                if (isValidMove(i + 1, j, map.size(), map[0].size(), lead))
                {
                    i++;
                    lead[i][j] = '#';
                    if (i==map.size()-1 && j==map[0].size()-1 && sum==map[i][j])
                    {
                        cout << "You won!";
                        return 0;
                    }
                    sum += map[i][j];
                    printmap(map, lead);
                }
                else
                    cout << "Invalid move!";
                break;
            case 75: // Left
                if (isValidMove(i, j - 1, map.size(), map[0].size(), lead))
                {
                    j--;
                    lead[i][j] = '#';
                    if (i==map.size()-1 && j==map[0].size()-1 && sum==map[i][j])
                    {
                        cout << "You won!";
                        return 0;
                    }
                    sum += map[i][j];
                    printmap(map, lead);
                }
                else
                    cout << "Invalid move!";
                break;
            case 77: // Right
                if (isValidMove(i, j + 1, map.size(), map[0].size(), lead))
                {
                    j++;
                    lead[i][j] = '#';
                    if (i==map.size()-1 && j==map[0].size()-1 && sum==map[i][j])
                    {
                        cout << "You won!";
                        return 0;
                    }
                    sum += map[i][j];
                    printmap(map, lead);
                }
                else
                    cout << "Invalid move!";
                break;
            case 13: // enter
                return 0;
            }
            

        }
    }
}

void printmap(vector<vector<int>> map, vector<vector<char>> lead)
{
    system("cls");
    // print map
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (lead[i][j] == '#' && map[i][j] != 0)
            {
                if (map[i][j] < 0)

                    cout << "\033[1;31m " << map[i][j] << "\033[0m";

                else
                    cout << "\033[1;31m  " << map[i][j] << "\033[0m";
            }
            else
            {
                if (map[i][j] < 0)
                    cout << " ";
                else
                    cout << "  ";
                cout << map[i][j];
            }
        }

        cout << endl;
    }
}

bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<char>> lead)
{
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && lead[x][y] != '#');
}

