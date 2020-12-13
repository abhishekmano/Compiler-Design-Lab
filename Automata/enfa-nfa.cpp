// CPP program to covert epsilon nfa to non epsilon nfa
#include <bits/stdc++.h>
using namespace std;

void print_vect(vector<vector<int>> arr, int a, int b)
{
    for (int i = 0; i < a; ++i)
    {
        for (int j = 0; j < b; ++j)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
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

unordered_set<int> split_Add(string s)
{
    int size = s.size();
    unordered_set<int> res;
    int start = 0;
    for (int i = 0; i < size; ++i)
    {
        if (s[i] == ',')
        {
            string sub = s.substr(start, i - start);
            start = i + 1;
            int temp = stoi(sub);
            res.insert(temp);
        }
    }
    string sub = s.substr(start, size - start);
    int temp = stoi(sub);
    res.insert(temp);
    return res;
}
int main()
{
    cout << "Enter the number of states: ";
    int n, m;
    cin >> n;
    cout << "Enter the number of input symbols: ";
    cin >> m;
    vector<vector<unordered_set<int>>> table(n, vector<unordered_set<int>>(m));
    print_header(m);
    for (int i = 0; i < n; ++i)
    {
        cout << i << "\t";
        for (int j = 0; j < m; ++j)
        {
            string s;
            cin >> s;
            unordered_set<int> to_states;
            if (s != "-")
                to_states = split_Add(s);
            table[i][j] = to_states;
        }
    }
    // for (auto x : table)
    // {
    //     for (auto y : x)
    //     {
    //         for (auto z : y)
    //         {
    //             cout << z << ",";
    //         }
    //         cout << "\t";
    //     }
    //     cout << endl;
    // }
    //print_vect(table, n, m);
    int start, last, temp, temp1;
    unordered_set<int> s, f;
    cout << "Enter the number of start states: ";
    cin >> start;
    cout << "Enter the start states: ";
    for (int i = 0; i < start; ++i)
    {
        cin >> temp;
        s.insert(temp);
    }
    cout << "Enter the number of final states: ";
    cin >> last;
    cout << "Enter the final states: ";
    for (int i = 0; i < last; ++i)
    {
        cin >> temp;
        f.insert(temp);
    }
    int epsilon;
    cout << "Enter the number of epsilon transition: ";
    cin >> epsilon;
    vector<pair<int, int>> eps;
    cout << "From\tTo" << endl;
    for (int i = 0; i < epsilon; ++i)
    {
        cin >> temp >> temp1;
        eps.push_back({temp, temp1});
    }

    queue<int> check;
    vector<unordered_set<int>> closures; // to store the set of states
    // cout << "Epsilon Closures are: \n";
    for (int i = 0; i < n; ++i)
    {
        vector<int> visited(n, 0);
        if (visited[i] != 1)
        {
            unordered_set<int> building;
            building.insert(i);
            //cout << i << ": ";
            visited[i] = 1;
            //cout << "{ " << i;
            for (auto x : eps)
            {
                if (x.first == i)
                {
                    check.push(x.second);
                }
            }
            while (!check.empty())
            {
                int c = check.front();
                check.pop();
                building.insert(c);
                visited[c] = 1;
                //cout << ", " << c;
                for (auto x : eps)
                {
                    if (x.first == c && visited[x.second] != 1)
                    {
                        check.push(x.second);
                    }
                }
            }
            closures.push_back(building);
        }
    }
    // for (int i = 0; i < n; ++i)
    // {
    //     cout << i << ":\t";
    //     for (auto x : closures[i])
    //     {
    //         cout << x << ",";
    //     }
    //     cout << endl;
    // }
    cout << endl;
    cout << "New NFA without epsilon transition\n";
    print_header(m);
    for (int i = 0; i < n; ++i)
    {
        cout << i << "\t";
        for (int j = 0; j < m; ++j)
        { // for the new state k where each transitions go
            unordered_set<int> check;
            for (auto x : closures[i])
            {
                for (auto y : table[x][j])
                {
                    if (check.find(y) == check.end())
                    {
                        check.insert(y);
                        for (auto z : closures[y])
                        {
                            if (check.find(z) == check.end())
                                check.insert(z);
                        }
                    }
                }
            }
            if (check.empty())
            {
                cout << "-";
            }
            else
            {
                for (auto x : check)
                {
                    cout << x << ",";
                }
            }

            cout << "\t";
        }
        cout << endl;
    }
    cout << "Start state is: ";
    for (int i = 0; i < n; ++i)
    {
        for (auto x : closures[i])
        {
            if (s.find(x) != f.end())
            {
                cout << i << " ";
                break;
            }
        }
    }
    cout << endl;
    cout << "Final state is: ";
    for (int i = 0; i < n; ++i)
    {
        for (auto x : closures[i])
        {
            if (f.find(x) != f.end())
            {
                cout << i << " ";
                break;
            }
        }
    }
    cout << endl;
    return 0;
}