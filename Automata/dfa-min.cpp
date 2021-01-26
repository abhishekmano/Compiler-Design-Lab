//CPP code to minimize dfa
#include <bits/stdc++.h>
using namespace std;
void print_header(int m)
{
    cout << "State";
    for (int j = 0; j < m; ++j)
    {
        char ch = char(int('a') + j);
        cout << "\t" << ch;
    }
    cout << endl;
}

vector<vector<int>> input_dfa(int *row, int *column)
{
    int n, m;
    cout << "Enter the number of states: ";
    cin >> n;
    cout << "Enter the number of alphabets: ";
    cin >> m;
    vector<vector<int>> dfa(n, vector<int>(m, 0));
    print_header(m);
    for (int i = 0; i < n; ++i)
    {
        cout << i << "\t";
        for (int j = 0; j < m; ++j)
        {
            cin >> dfa[i][j];
        }
    }
    *row = n;
    *column = m;

    return dfa;
}
int main()
{
    int n, m;
    vector<vector<int>> dfa = input_dfa(&n, &m);
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int s, last, temp;
    cout << "Enter the start state: ";
    cin >> s;
    set<int> f;
    cout << "Enter the number of final states: ";
    cin >> last;
    cout << "Enter the final states: ";
    for (int i = 0; i < last; ++i)
    {
        cin >> temp;
        f.insert(temp);
    }
    //differentiate final and non finale
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (f.find(i) != f.end() && f.find(j) == f.end())
            {
                matrix[i][j] = 1;
            }
            if (f.find(i) == f.end() && f.find(j) != f.end())
            {
                matrix[i][j] = 1;
            }
        }
    }
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = 0; k < m; ++k) //for each production
                {
                    if (matrix[i][j] != 1) //skip if already marked
                        if (matrix[dfa[i][k]][dfa[j][k]] == 1)
                        {
                            matrix[i][j] = 1;
                            flag = 1;
                            break;
                        }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i > j)
            {
                cout << "x"
                     << " ";
            }
            else
            {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    int num_state = 0;
    vector<int> visited(n, 0);
    vector<set<int>> minimised;
    unordered_map<int, int> mapping;
    for (int i = 0; i < n; ++i)
    {
        set<int> new_state;
        if (visited[i] != 1)
        {
            new_state.insert(i);
            mapping[i] = num_state;
            for (int j = i + 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    new_state.insert(j);
                    mapping[j] = num_state;
                    visited[j] = 1;
                }
            }
            minimised.push_back(new_state);
            num_state++;
        }
    }
    cout << "number of states is: " << num_state << endl;

    print_header(m);
    for (auto x : minimised)
    {
        for (auto y : x)
        {
            cout << mapping[y] << "\t";
            for (int j = 0; j < m; ++j)
            {
                cout << mapping[dfa[y][j]] << "\t";
            }
            break;
        }
        cout << endl;
    }
    cout << "Final states are: ";
    for (auto x : minimised)
    {
        for (auto y : x)
        {
            if (f.find(y) != f.end())
            {
                cout << mapping[y] << " ";
                break;
            }
        }
    }
    cout << endl;
    return 0;
}