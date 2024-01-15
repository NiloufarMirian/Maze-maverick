#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template <typename T>
void Swap(T *a, T *b);

template <typename T>
void FY(T *a, int n);

// void assignmentPath(char** lead, int** map, char move[], int moveSize, int row, int column);

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

    // // making path
    char move[row + column - 2];
    for (int i = 0; i < row - 1; i++)
    {
        move[i] = 'D';
    }
    for (int i = 0; i < column - 1; i++)
    {
        move[i + row - 1] = 'R';
    }
    FY(move, row + column - 2);
    // //assignmentPath(lead,map,move,row+column-2,row, column);
    // row
    int n = 0;
    // column
    int m = 0;
    int moveSize = row + column - 2 ;
    int bucket = 0;
    int sum = 0;
    srand(time(NULL));
    for (int i = 0; i < moveSize; i++)
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
        if (move[i] == 'R')
        {
            m++;
        }
        else if (move[i] == 'D')
        {
            n++;
        }
    }
    lead[n][m] = '#';
    map[n][m] = sum;

    

    // making block
    int block = rand() % 3 + 2;
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

    // ranbom assignment
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

    // // print map
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < column; j++)
    //     {

    //         if (map[i][j] < 0)
    //             fout << " ";
    //         else
    //             fout << "  ";
    //         fout << map[i][j];
    //     }
    //     fout << endl;
    // }

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

int main()
{
    string name;
    cout << "Enter map name" << endl;
    cin >> name;
    ofstream fout;
    fout.open(name);
    cout << "Enter 1 for simple & 2 for complex" << endl;
    int sc;
    cin >> sc;
    cout << "Enter row & column of map" << endl;
    int row, column;
    cin >> row >> column;
    // cout << "Enter range of blocks";
    // int minblock, maxblock;
    // cin >> minblock >> maxblock;
    if (sc == 1)
    {
        simplemap(fout, row, column);
    }
}

template <typename T>
void FY(T *a, int n)
{
    srand(time(NULL));
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
}

// void assignmentPath(char** lead, int** map, char move[], int moveSize, int row, int column)
// {
// //row
// int n=0;
// //column
// int m=0;
// int bucket=0;
// int sum=0;
// srand(time(NULL));
// for (int i=0; i<moveSize; i++)
// {
//     lead[n][m]='#';
//     bucket=rand()%6;
//     if (bucket <= 2)
//     {
//         bucket -= 3;
//         map[m][n] = bucket;
//     }
//     else
//     {
//         bucket -= 2;
//         lead[m][n] = bucket;
//     }
//     sum += bucket;
//     if (move[i]=='R')
//     {
//         m++;
//     }
//     else if (move[i]=='D')
//     {
//         n++;
//     }
// }
// lead[m][n]='#';
// map[m][n]=sum;
// }
