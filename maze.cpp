#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

// chronometer
class Stopwatch
{
public:
    void start()
    {
        startTime = std::chrono::high_resolution_clock::now();
    }

    void stop()
    {
        endTime = std::chrono::high_resolution_clock::now();
    }

    void reset()
    {
        startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
        endTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
    }

    double elapsedMilliseconds() const
    {
        return std::chrono::duration<double, std::milli>(endTime - startTime).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
};

template <typename T>
void Swap(T *a, T *b);

template <typename T>
void FY(vector<T> a);

void assignmentPath(vector<vector<char>> &lead, vector<vector<int>> &map, vector<char> move, int row, int column, int minValue, int maxValue);

void assignmentMap(vector<vector<char>> &lead, vector<vector<int>> &map, int row, int column, int minValue, int maxValue);

void simplemap(ofstream &fout, int row, int column);

void complexmap(ofstream &fout, int row, int column, int minblock, int maxblock, int minValue, int maxValue, int length);

bool dfs(int x, int y, int ROWS, int COLS, int length, char move, vector<vector<int>> &grid, vector<vector<char>> &moves);

bool isValidMove(int x, int y, int ROWS, int COLS, const vector<vector<int>> &map);

bool isValidMove(int x, int y, int ROWS, int COLS, vector<vector<char>> lead);

vector<char> moveArray(vector<vector<char>> &moves);

void makeBlock(vector<vector<int>> &map, vector<vector<char>> &lead, int pathLength, int minblock, int maxblock, int row, int column);

void Playground(ifstream &fin);

void printmap(vector<vector<int>> map, vector<vector<char>> lead);

void solveMaze(ifstream &fin);

int main()
{
    int command;
    cout << "1. Create a New Map\n"
         << "2. Playground\n"
         << "3. Solve a Maze\n"
         << "4. History\n"
         << "5. Leaderboard\n"
         << "6. Exit\n";
    cin >> command;
    if (command == 1)
    {
        system("cls");
        string name;
        cout << "Enter name" << endl;
        getline(cin, name);
        name = "Maps/" + name + ".txt";
        ofstream fout;
        fout.open(name);
        fout << name + ".txt\n";

        cout << "- 1.1 Easy\n"
             << "- 1.2 Hard\n";
        cin >> command;
        cout << "Enter row & column of map" << endl;
        if (command == 1)
        {
            int row, column;
            cin >> row >> column;
            fout << "Easy\n";
            fout << row + column - 2 << "\n";
            simplemap(fout, row, column);
        }
        if (command == 2)
        {
            int row, column;
            cin >> row >> column;
            cout << "Enter range of blocks" << endl;
            int minblock, maxblock;
            cin >> minblock >> maxblock;
            // exeption handling
            if (minblock > maxblock)
                swap(minblock, maxblock);

            if (minblock < 0 || maxblock < 0)
            {
                cerr << "invalid value!" << endl;
                cout << "Enter range of blocks" << endl;
                cin >> minblock >> maxblock;
            }

            cout << "Enter range of values of cells." << endl;
            int minValue, maxValue;
            cin >> minValue >> maxValue;
            // exeption handling
            if (minValue > maxValue)
                swap(minValue, maxValue);

            cout << "Enter length of path." << endl;
            int length;
            cin >> length;
            fout << "Hard\n";
            fout << length << "\n";
            complexmap(fout, row, column, minblock, maxblock, minValue, maxValue, length);
        }
    }

    else if (command == 2)
    {
        system("cls");
        int command;
        cout << "- 2.1 Choose from Existing Maps\n"
             << "- 2.2 Import a Custom Map\n";
        cin >> command;
        string name;
        if (command == 1)
        {
            int i = 0;
            cout << "Choose from mentioned names.\n";
            WIN32_FIND_DATA findFileData;
            HANDLE hFind = FindFirstFile("Maps/*", &findFileData);
            if (hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    i++;
                    std::cout << findFileData.cFileName << std::endl;
                } while (FindNextFile(hFind, &findFileData) != 0);
                FindClose(hFind);
            }
            else
            {
                std::cerr << "Unable to find files" << std::endl;
                return 1;
            }
            cin >> name;
            ifstream fin;
            fin.open("Maps/" + name);
            getline(fin, name);
            string level;
            fin >> level;
            int pathLength;
            fin >> pathLength;
            Playground(fin);
        }
        else if (command == 2)
        {
            cout << "Enter the adddress.\n";
            cin >> name;
            ifstream fin;
            fin.open(name);
            getline(fin, name);
            string level;
            fin >> level;
            int pathLength;
            fin >> pathLength;
            Playground(fin);
        }
        else
        {
            cerr << "Invalid command!\n";
        }
    }

    else if (command == 3)
    {
        system("cls");
        int command;
        cout << "- 3.1 Choose from Existing Maps\n"
             << "- 3.2 Import a Custom Map\n";
        cin >> command;
        string name;
        if (command == 1)
        {
            int i = 0;
            cout << "Choose from mentioned names.\n";
            WIN32_FIND_DATA findFileData;
            HANDLE hFind = FindFirstFile("Maps/*", &findFileData);
            if (hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    i++;
                    std::cout << findFileData.cFileName << std::endl;
                } while (FindNextFile(hFind, &findFileData) != 0);
                FindClose(hFind);
            }
            else
            {
                std::cerr << "Unable to find files" << std::endl;
                return 1;
            }
            cin >> name;
            ifstream fin;
            fin.open("Maps/" + name);
            getline(fin, name);
            solveMaze(fin);
        }
        else if (command == 2)
        {
            cout << "Enter the adddress.\n";
            cin >> name;
            ifstream fin;
            fin.open(name);
            getline(fin, name);

            solveMaze(fin);
        }
        else
        {
            cerr << "Invalid command!\n";
        }
    }
}

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
    assignmentPath(lead, map, move, row, column, -3, 3);

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
    if (!dfs(0, 0, row, column, length, ' ', map, moves))
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
    assignmentPath(lead, map, move, row, column, minValue, maxValue);

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

void assignmentPath(vector<vector<char>> &lead, vector<vector<int>> &map, vector<char> move, int row, int column, int minValue, int maxValue)
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
        int bucket;
        if (minValue < 0 && maxValue > 0)
        {
            bucket = rand() % (maxValue - minValue);
            if (bucket <= (-1 * minValue - 1))
            {
                bucket += minValue;
                map[n][m] = bucket;
            }

            else
            {
                bucket += (minValue + 1);
                map[n][m] = bucket;
            }
        }
        else
        {
            bucket = rand() % (maxValue - minValue) + minValue;
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
                    bucket = rand() % (maxValue - minValue) + minValue;
                    map[i][j] = bucket;
                }
            }
        }
    }
}

void Playground(ifstream &fin)
{
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
    int sum = 0;
    sum += map[i][j];
    printmap(map, lead);
    Stopwatch stopwatch;
    stopwatch.start();

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
                    if (i == map.size() - 1 && j == map[0].size() - 1 && sum == map[i][j])
                    {
                        cout << "You won!\n";
                        stopwatch.stop();
                        cout << "Spent time: " << stopwatch.elapsedMilliseconds() / 1000 << " seconds" << std::endl;

                        //date
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        // print various components of tm structure.
                        cout << "Year:" << 1900 + ltm->tm_year << endl;
                        cout << "Month: " << 1 + ltm->tm_mon << endl;
                        cout << "Day: " << ltm->tm_mday << endl;

                        return;
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
                    if (i == map.size() - 1 && j == map[0].size() - 1 && sum == map[i][j])
                    {
                        cout << "You won!\n";
                        stopwatch.stop();
                        cout << "Spent time: " << stopwatch.elapsedMilliseconds() / 1000 << " seconds" << std::endl;

                        return;
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
                    if (i == map.size() - 1 && j == map[0].size() - 1 && sum == map[i][j])
                    {
                        cout << "You won!\n";
                        stopwatch.stop();
                        cout << "Spent time: " << stopwatch.elapsedMilliseconds() / 1000 << " seconds" << std::endl;
                        return;
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
                    if (i == map.size() - 1 && j == map[0].size() - 1 && sum == map[i][j])
                    {
                        cout << "You won!\n";
                        stopwatch.stop();
                        cout << "Spent time: " << stopwatch.elapsedMilliseconds() / 1000 << " seconds" << std::endl;

                        return;
                    }
                    sum += map[i][j];
                    printmap(map, lead);
                }
                else
                    cout << "Invalid move!";
                break;
            case 13: // enter
                return;
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

void solveMaze(ifstream &fin)
{
    string level;
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
    else
    {
        cout << "Not oath found!";
    }
}
