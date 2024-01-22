#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

template <typename T>
void Swap(T *a, T *b);

template <typename T>
void FY(vector<T> a);

void assignmentPath(vector<vector<char>> &lead, vector<vector<int>> &map, vector<char> move, int row, int column);

void assignmentMap(vector<vector<char>> &lead, vector<vector<int>> &map, int row, int column, int minValue, int maxValue);

void simplemap(ofstream &fout, int row, int column);

void complexmap(ofstream &fout, int row, int column, int minblock, int maxblock, int minValue, int maxValue, int length);

bool dfs(int x, int y, int ROWS, int COLS, int length, char move, vector<vector<int>> &grid, vector<vector<char>> &moves);

bool isValidMove(int x, int y, int ROWS, int COLS, const vector<vector<int>> &map);

vector<char> moveArray(vector<vector<char>> &moves);

void makeBlock(vector<vector<int>> &map, vector<vector<char>> &lead, int pathLength, int minblock, int maxblock, int row, int column)
{
    // making block
    int block;
    block = rand() % (maxblock - minblock) + minblock;
    int freeCell = row * column - (pathLength);
    int i = 0, j = 0;
    int zero;
    for (int k = 0; k < block; k++)
    {
        // zero=the cell that is going to be block
        zero = rand() % freeCell;
        int s = 0;
        for (int z = 0; z < zero; z++)
        {
            s++;
            i = s / column;
            j = s % column;
            if (lead[i][j] == '#')
                z--;
        }
        lead[i][j] = '#';
        freeCell--;
    }
}

int main()
{
    string name;
    cout << "Enter map name" << endl;
    getline(cin, name);
    name = "Maps/" + name + ".txt";
    ofstream fout;
    fout.open(name);
    cout << "Enter 1 for simple & 2 for complex" << endl;
    int sc;
    cin >> sc;
    cout << "Enter row & column of map" << endl;
    if (sc == 1)
    {
        int row, column;
        cin >> row >> column;
        simplemap(fout, row, column);
    }
    if (sc == 2)
    {
        int row, column;
        cin >> row >> column;
        cout << "Enter range of blocks" << endl;
        int minblock, maxblock;
        cin >> minblock >> maxblock;
        cout << "Enter range of values of cells." << endl;
        int minValue, maxValue;
        cin >> minValue >> maxValue;
        cout << "Enter length of path." << endl;
        int length;
        cin >> length;
        complexmap(fout, row, column, minblock, maxblock, minValue, maxValue, length);
    }
}

void simplemap(ofstream &fout, int row, int column)
{
    // make and assignment 0
    vector<vector<int>> map;
    vector<int> map1;
    vector<vector<char>> lead;
    vector<char> lead1;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            map1.push_back(0);
            lead1.push_back('*');
        }
        map.push_back(map1);
        lead.push_back(lead1);
    }

    // // making path
    vector<char> move;
    for (int i = 0; i < row - 1; i++)
    {
        move.push_back('D');
    }
    for (int i = 0; i < column - 1; i++)
    {
        move.push_back('R');
    }
    FY(move);
    assignmentPath(lead, map, move, row, column);

    // making block
    makeBlock(map, lead, row + column - 2, 2, 5, row, column);

    // ranbom assignment
    assignmentMap(lead, map, row, column, -3, 3);

    // print map
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {

            if (map[i][j] < 0)
                fout << " ";
            else
                fout << "  ";
            fout << map[i][j];
        }
        fout << endl;
    }
    fout << endl;
    // print lead
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            fout << lead[i][j] << " ";
        }
        fout << endl;
    }
}

void complexmap(ofstream &fout, int row, int column, int minblock, int maxblock, int minValue, int maxValue, int length)
{
    // make and assignment 0
    vector<vector<int>> map;
    vector<int> map1;
    vector<vector<char>> lead;
    vector<char> lead1;
    vector<vector<char>> moves;
    vector<char> moves1;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            map1.push_back(0);
            lead1.push_back('*');
            moves1.push_back(' ');
        }
        map.push_back(map1);
        lead.push_back(lead1);
        moves.push_back(moves1);
    }

    // finding path
    bool b= dfs(0, 0, row, column, length, ' ', map, moves);
    if (!b)
    {
        cerr << "invalid path!" << endl;
        cout << "Enter length of path." << endl;
        cin >> length;
        complexmap(fout, row, column, minblock, maxblock, minValue, maxValue, length);
        return;
    }

    // making an array to make a path.
    vector<char> move = moveArray(moves);

    // reset ghanges (just for control)
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            map[i][j] = 0;
            lead[i][j] = '*';
        }
    }

    // assignment map & lead
    assignmentPath(lead, map, move, row, column);

    // making blocks
    makeBlock(map, lead, length, minblock, maxblock, row, column);

    // ranbom assignment path
    assignmentMap(lead, map, row, column, minValue, maxValue);

    // print map
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {

            if (map[i][j] < 0)
                fout << " ";
            else
                fout << "  ";
            fout << map[i][j];
        }
        fout << endl;
    }
    fout << endl;
    // print lead
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            fout << lead[i][j] << " ";
        }
        fout << endl;
    }

}

vector<char> moveArray(vector<vector<char>> &moves)
{
    vector<char> result;
    int i = moves.size() - 1;
    int j = moves[0].size() - 1;
    while (!(i == 0 && j == 0))
    {
        result.push_back(moves[i][j]);

        switch (moves[i][j])
        {
        case 'L':
            j--;
            break;
        case 'R':
            j++;
            break;
        case 'U':
            i--;
            break;
        case 'D':
            i++;
            break;
        default:
            break;
        }
    }
    return result;
}

bool dfs(int x, int y, int ROWS, int COLS, int length, char move, vector<vector<int>> &map, vector<vector<char>> &moves)
{
    if (x == ROWS - 1 && y == COLS - 1 && length == 0)
    {
        moves[x][y] = move;
        map[x][y] = 1;

        return true;
    }
    if (!(x == ROWS - 1 && y == COLS - 1) && length == 0)
    {
        return false;
        map[x][y] = 0;
    }
    
    if (!isValidMove(x, y, ROWS, COLS, map))
    {
        return false;
    }

    map[x][y] = 1;
    moves[x][y] = move;

    srand(time(0));
    int random = rand() % 4;
    switch (random)
    {
    case 0:
        if (dfs(x + 1, y, ROWS, COLS, length - 1, 'U', map, moves) || dfs(x - 1, y, ROWS, COLS, length - 1, 'D', map, moves) ||
            dfs(x, y + 1, ROWS, COLS, length - 1, 'L', map, moves) || dfs(x, y - 1, ROWS, COLS, length - 1, 'R', map, moves))
        {
            return true;
        }
        break;
    case 1:
        if (dfs(x, y + 1, ROWS, COLS, length - 1, 'L', map, moves) || dfs(x, y - 1, ROWS, COLS, length - 1, 'R', map, moves) ||
            dfs(x + 1, y, ROWS, COLS, length - 1, 'U', map, moves) || dfs(x - 1, y, ROWS, COLS, length - 1, 'D', map, moves))
        {
            return true;
        }
        break;
    case 2:
        if (dfs(x, y - 1, ROWS, COLS, length - 1, 'R', map, moves) || dfs(x, y + 1, ROWS, COLS, length - 1, 'L', map, moves) ||
            dfs(x - 1, y, ROWS, COLS, length - 1, 'D', map, moves) || dfs(x + 1, y, ROWS, COLS, length - 1, 'U', map, moves))
        {
            return true;
        }
        break;
    case 3:
        if (dfs(x - 1, y, ROWS, COLS, length - 1, 'D', map, moves) || dfs(x, y - 1, ROWS, COLS, length - 1, 'R', map, moves) ||
            dfs(x, y + 1, ROWS, COLS, length - 1, 'L', map, moves) || dfs(x + 1, y, ROWS, COLS, length - 1, 'U', map, moves))
        {
            return true;
        }
        break;
    }

    map[x][y] = 0;
    return false;
}

bool isValidMove(int x, int y, int ROWS, int COLS, const vector<vector<int>> &map)
{
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && map[x][y] == 0);
}

template <typename T>
void FY(vector<T> a)
{
    srand(time(0));
    int index;
    for (int i = a.size() - 1; i >= 1; i--)
    {
        index = rand() % (i + 1);
        Swap(&a[index], &a[i]);
    }
}

template <typename T>
void Swap(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

void assignmentPath(vector<vector<char>> &lead, vector<vector<int>> &map, vector<char> move, int row, int column)
{
    // row
    int n = 0;
    // column
    int m = 0;
    int bucket = 0;
    int sum = 0;
    int len = move.size();
    srand(time(0));
    for (int i = 0; i < len; i++)
    {
        lead[n][m] = '#';
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[n][m] = bucket;
        }
        else
        {
            bucket -= 2;
            map[n][m] = bucket;
        }
        sum += bucket;
        switch (move[len - i - 1])
        {
        case 'L':
            m++;
            break;
        case 'R':
            m--;
            break;
        case 'U':
            n++;
            break;
        case 'D':
            n--;
            break;
        default:
            break;
        }
    }
    lead[n][m] = '#';
    map[n][m] = sum;
}

void assignmentMap(vector<vector<char>> &lead, vector<vector<int>> &map, int row, int column, int minValue, int maxValue)
{
    srand(time(0));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (lead[i][j] == '*')
            {
                int bucket;
                if (minValue < 0 && maxValue > 0)
                {
                    bucket = rand() % (maxValue - minValue);
                    if (bucket <= (-1 * minValue - 1))
                    {
                        bucket += minValue;
                        map[i][j] = bucket;
                    }

                    else
                    {
                        bucket += (minValue + 1);
                        map[i][j] = bucket;
                    }
                }
                else 
                {
                    bucket = rand() % (maxValue - minValue)+minValue;
                    map[i][j] = bucket;
                }
            }
        }
    }
}
