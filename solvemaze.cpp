#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool dfsS(int x, int y, int ROWS, int COLS, int sum, int length, int move, vector<vector<int>> map, vector<vector<char>> &moves);

bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<int>> map, vector<vector<char>> moves);

int main()
{
    ifstream fin;
    fin.open("Maps/complex.txt");
    vector<vector<int>> map;
    string bucket;
    string sub;
    while (getline(fin, bucket))
    {
        vector<int> row;
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i] != ' ' && (int(bucket[i]) == 45 
            || (int(bucket[i]) > 47 && int(bucket[i]) < 58)))
            {
                sub = bucket.substr(i, bucket.find(' ', i) - i);
                row.push_back(stoi(sub));
                i += sub.size()-1;
            }
        }
        if (!row.empty())
            map.push_back(row);
    }
}

bool dfsS(int x, int y, int ROWS, int COLS, int sum, int length, int move, vector<vector<int>> map, vector<vector<char>> &moves)
{
    if (x == ROWS - 1 && y == COLS - 1 && sum == map[x][y] && length == 0)
    {
        moves[x][y] = move;
        return true;
    }

    if (!(x == ROWS - 1 && y == COLS - 1) && length == 0)
    {
        return false;
    }

    if (x == ROWS - 1 && y == COLS - 1 && sum != map[x][y] && length == 0)
    {
        return false;
    }

    if (!isValidMove(x, y, ROWS, COLS, map, moves))
    {
        return false;
    }
    sum -= map[x][y];
    moves[x][y] = move;

    if (dfsS(x - 1, y, ROWS, COLS, sum, length - 1, 'D', map, moves) ||
        dfsS(x, y - 1, ROWS, COLS, sum, length - 1, 'R', map, moves) ||
        dfsS(x, y + 1, ROWS, COLS, sum, length - 1, 'L', map, moves) ||
        dfsS(x + 1, y, ROWS, COLS, sum, length - 1, 'U', map, moves))
    {
        return true;
    }

    moves[x][y] = ' ';
    return false;
}


bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<int>> map, vector<vector<char>> moves)
{
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && map[x][y] != 0 && moves[x][y] == ' ');
}
