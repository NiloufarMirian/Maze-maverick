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
    // cin >> name; 
    fin.open("Maps/name.txt"); 
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
        map.push_back(row); 
    } 
    // system("cls"); 
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
}
