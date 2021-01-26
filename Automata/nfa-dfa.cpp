//CPP program to convert NFA into DFA
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
set<int> split_Add(string s)
{
    int size = s.size();
    set<int> res;
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
void print(vector<vector<set<int>>> table)
{
    for (auto x : table)
    {
        for (auto y : x)
        {
            for (auto z : y)
            {
                cout << z << ",";
            }
            cout << "\t";
        }
        cout << endl;
    }
}
int main()
{
    cout << "Enter the number of states: ";
    int n, m;
    cin >> n;
    cout << "Enter the number of input symbols: ";
    cin >> m;
    vector<vector<set<int>>> table(n, vector<set<int>>(m));
    print_header(m);
    for (int i = 0; i < n; ++i)
    {
        cout << i << "\t";
        for (int j = 0; j < m; ++j)
        {
            string s;
            cin >> s;
            set<int> to_states;
            if (s != "-")
                to_states = split_Add(s);
            table[i][j] = to_states;
        }
    }
    //print(table);
    int start, last, temp, temp1;
    set<int> s, f;
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
    vector<vector<set<int>>> dfa; //states and transitions
    set<set<int>> present;        // keep track of states
    map<set<int>, int> state_num; //map state to a number
    queue<set<int>> elem;

    int dfa_state = 0;
    elem.push(s);
    present.insert(s);
    while (!elem.empty())
    {

        vector<set<int>> dfa_row;

        set<int> current = elem.front();
        state_num[current] = dfa_state;
        dfa_state++;
        dfa_row.push_back(current);
        elem.pop();
        for (int i = 0; i < m; ++i) //for each transition from this set of states
        {
            set<int> new_state;
            for (auto x : current)
            {
                for (auto y : table[x][i]) //for state x in current state set where i transition go
                {
                    new_state.insert(y);
                }
            }
            dfa_row.push_back(new_state);
            if (present.find(new_state) == present.end()) //check whther this newly created state already exist
            {
                present.insert(new_state);
                elem.push(new_state);
            }
        }
        dfa.push_back(dfa_row);
    }
    print_header(m);
    for (int i = 0; i < dfa_state; ++i)
    {
        for (int j = 0; j < m + 1; ++j)
        {
            cout << state_num[dfa[i][j]] << "\t";
        }
        cout << endl;
    }
    cout << "Final states are: ";
    for (auto x : present)
    {
        for (auto y : x)
        {
            if (f.find(y) != f.end())
            {
                cout << state_num[x] << " ";
                break;
            }
        }
    }
    cout << endl;
    return 0;
}