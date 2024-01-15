<<<<<<< HEAD
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void simplemap(ofstream &fout, int row, int column)
{
    // make and assignment 0
    int map[row][column];
    char lead[row][column];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            map[i][j] = 0;
            lead[i][j] = '*';
        }
    }

    // making path
    srand(time(NULL));
    int path = rand() % row;
    int sum = 0;
    int bucket = 0;
    for (int i = 0; i < path; i++)
    {
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[i][0] = bucket;
        }
        else
        {
            bucket -= 2;
            map[i][0] = bucket;
        }
        sum += bucket;
        lead[i][0] = '#';
    }

    for (int j = 0; j < column; j++)
    {
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[path][j] = bucket;
        }

        else
        {
            bucket -= 2;
            map[path][j] = bucket;
        }
        sum += bucket;
        lead[path][j] = '#';
    }

    for (int i = path + 1; i < row - 1; i++)
    {
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[i][column - 1] = bucket;
        }

        else
        {
            bucket -= 2;
            map[i][column - 1] = bucket;
        }
        sum += bucket;
        lead[i][column - 1] = '#';
    }
    map[row - 1][column - 1] = sum;
    lead[row - 1][column - 1] = '#';


    // making block
    int block = (rand() % 3) + 2;
    int freeCell = row * column - (row + column - 1);
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

    //ranbom assignment
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (lead[i][j] == '*')
            {
                bucket = rand() % 6;
                if (bucket <= 2)
                {
                    bucket -= 3;
                    map[i][j] = bucket;
                }

                else
                {
                    bucket -= 2;
                    map[i][j] = bucket;
                }
            }
        }
    }

    // print map
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            
            if (map[i][j]<0)
                fout << " ";
            else
                fout << "  ";
            fout << map[i][j];
        }
        fout << endl;
    }

    fout << endl;

    // // print lead
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < column; j++)
    //     {
    //         fout << lead[i][j] << " ";
    //     }
    //     fout << endl;
    // }
}

int main()
{
    string name;
    cout << "Enter map name"<< endl;
    cin >> name;
    ofstream fout;
    fout.open(name);
    cout << "Enter 1 for simple & 2 for complex"<< endl;
    int sc;
    cin >> sc;
    cout << "Enter row & column of map"<< endl;
    int row, column;
    cin >> row >> column;
    cout << "Enter range of blocks";
    int minblock, maxblock;
    cin >> minblock >> maxblock;
    if (sc == 1)
    {
        simplemap(fout, row, column);
    }
=======
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template <typename T>
void Swap(T *a, T *b);

template <typename T>
void FY(T* a, int n);

void simplemap(ofstream &fout, int row, int column)
{
    // make and assignment 0
    int map[row][column];
    char lead[row][column];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            map[i][j] = 0;
            lead[i][j] = '*';
        }
    }

    // making path
    srand(time(NULL));
    int path = rand() % row;
    int sum = 0;
    int bucket = 0;
    for (int i = 0; i < path; i++)
    {
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[i][0] = bucket;
        }
        else
        {
            bucket -= 2;
            map[i][0] = bucket;
        }
        sum += bucket;
        lead[i][0] = '#';
    }

    for (int j = 0; j < column; j++)
    {
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[path][j] = bucket;
        }

        else
        {
            bucket -= 2;
            map[path][j] = bucket;
        }
        sum += bucket;
        lead[path][j] = '#';
    }

    for (int i = path + 1; i < row - 1; i++)
    {
        bucket = rand() % 6;
        if (bucket <= 2)
        {
            bucket -= 3;
            map[i][column - 1] = bucket;
        }

        else
        {
            bucket -= 2;
            map[i][column - 1] = bucket;
        }
        sum += bucket;
        lead[i][column - 1] = '#';
    }
    map[row - 1][column - 1] = sum;
    lead[row - 1][column - 1] = '#';


    // making block
    int block = (rand() % 3) + 2;
    int freeCell = row * column - (row + column - 1);
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

    //ranbom assignment
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (lead[i][j] == '*')
            {
                bucket = rand() % 6;
                if (bucket <= 2)
                {
                    bucket -= 3;
                    map[i][j] = bucket;
                }

                else
                {
                    bucket -= 2;
                    map[i][j] = bucket;
                }
            }
        }
    }

    // print map
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            
            if (map[i][j]<0)
                fout << " ";
            else
                fout << "  ";
            fout << map[i][j];
        }
        fout << endl;
    }

    fout << endl;

    // // print lead
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < column; j++)
    //     {
    //         fout << lead[i][j] << " ";
    //     }
    //     fout << endl;
    // }
}

int main()
{
    string name;
    cout << "Enter map name"<< endl;
    cin >> name;
    ofstream fout;
    fout.open(name);
    cout << "Enter 1 for simple & 2 for complex"<< endl;
    int sc;
    cin >> sc;
    cout << "Enter row & column of map"<< endl;
    int row, column;
    cin >> row >> column;
    cout << "Enter range of blocks";
    int minblock, maxblock;
    cin >> minblock >> maxblock;
    if (sc == 1)
    {
        simplemap(fout, row, column);
    }
}

template <typename T>
void FY(T* a, int n)
{
    int index;
    for (int i = n - 1; i >= 1; i--)
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
>>>>>>> 95df49b (making path with FY (part 1))
}