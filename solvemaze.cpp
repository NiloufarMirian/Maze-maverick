#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool dfsS(int x, int y, int ROWS, int COLS, int sum, int length, char move, vector<vector<int>> map, vector<vector<char>> &moves, vector<vector<char>> &lead);

bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<char>> moves);

int main()
{

    ifstream fin;
    fin.open("Maps/complex.txt");
    string name, level;
    getline(fin, name);
    fin >> level;
    int pathLength;
    fin >> pathLength;
    vector<vector<int>> map;
    vector<vector<char>> lead;
    vector<vector<char>> moves;

    string bucket;
    string sub;
    while (getline(fin, bucket))
    {

        vector<int> row;
        vector<char> move;
        vector<char> lead1;
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i] != ' ' && (int(bucket[i]) == 45 || (int(bucket[i]) > 47 && int(bucket[i]) < 58)))
            {
                sub = bucket.substr(i, bucket.find(' ', i) - i);
                row.push_back(stoi(sub));
                move.push_back(' ');
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
            moves.push_back(move);
            lead.push_back(lead1);
        }
    }

    // print map
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {

            if (map[i][j] < 0)
                cout << " ";
            else
                cout << "  ";
            cout << map[i][j];
        }

        cout << endl;
    }
    // print lead
    for (int i = 0; i < lead.size(); i++)
    {
        for (int j = 0; j < lead[0].size(); j++)
        {
            cout << lead[i][j] << " ";
        }
        cout << endl;
    }

    // print moves
    for (int i = 0; i < moves.size(); i++)
    {
        for (int j = 0; j < moves[0].size(); j++)
        {
            cout << moves[i][j] << " ";
        }
        cout << endl;
    }
    system("cls");

    if (dfsS(0, 0, map.size(), map[0].size(), map[map.size() - 1][map[0].size() - 1], pathLength, ' ', map, moves, lead))
    {
        // print map
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[0].size(); j++)
            {
                if (lead[i][j] == '#' && map[i][j] != 0)
                {
                    if (map[i][j] < 0)

                    cout << "\033[1;31m "<< map[i][j] <<"\033[0m";

                    else
                    cout << "\033[1;31m  "<< map[i][j] << "\033[0m";

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

        // print lead
        for (int i = 0; i < lead.size(); i++)
        {
            for (int j = 0; j < lead[0].size(); j++)
            {
                cout << lead[i][j] << " ";
            }
            cout << endl;
        }

        // print moves
        for (int i = 0; i < moves.size(); i++)
        {
            for (int j = 0; j < moves[0].size(); j++)
            {
                cout << moves[i][j] << " ";
            }
            cout << endl;
        }
    }
}

bool dfsS(int x, int y, int ROWS, int COLS, int sum, int length, char move, vector<vector<int>> map, vector<vector<char>> &moves, vector<vector<char>> &lead)
{
    if (x == ROWS - 1 && y == COLS - 1 && sum == 0 && length == 0)
    {
        lead[x][y] = '#';
        moves[x][y] = move;
        return true;
    }

    if (!(x == ROWS - 1 && y == COLS - 1) && length == 0)
    {
        return false;
    }

    if (x == ROWS - 1 && y == COLS - 1 && sum != 0 && length == 0)
    {
        return false;
    }

    if (!isValidMove(x, y, ROWS, COLS, lead))
    {
        return false;
    }
    sum -= map[x][y];
    moves[x][y] = move;
    lead[x][y] = '#';

    if (dfsS(x - 1, y, ROWS, COLS, sum, length - 1, 'D', map, moves, lead) ||
        dfsS(x, y - 1, ROWS, COLS, sum, length - 1, 'R', map, moves, lead) ||
        dfsS(x, y + 1, ROWS, COLS, sum, length - 1, 'L', map, moves, lead) ||
        dfsS(x + 1, y, ROWS, COLS, sum, length - 1, 'U', map, moves, lead))
    {
        return true;
    }

    lead[x][y] = '*';
    return false;
}

bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<char>> lead)
{
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && lead[x][y] != '#');
}
