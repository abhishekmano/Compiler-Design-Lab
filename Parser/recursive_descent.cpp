#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> get_production(unordered_map<char, int> &non_term, int *num)
{
    int non = -1;
    string s;
    vector<vector<string>> production(100);
    getline(cin, s);
    while (s != "")
    {
        int non_index;
        char left = s[0];
        if (non_term.find(s[0]) == non_term.end())
        {
            non_term[s[0]] = ++non;
            non_index = non;
        }
        else
        {
            non_index = non_term[s[0]];
        }
        string right = s.substr(4, s.size() - 4);
        production[non].push_back(right);
        //cout << "right side " << right << endl;
        getline(cin, s);
    }
    *num = non;
    return production;
}

unordered_set<char> split_string(string s)
{
    int n = s.size();
    unordered_set<char> result;
    for (int i = 0; i < n; ++i)
    {
        if (s[i] != ' ')
        {
            result.insert(s[i]);
        }
    }
    return result;
}

int method(vector<vector<string>> production, unordered_map<char, int> non_term, string input, int count, string crnt_prod, char E)
{
    int success = 0;
    cout << "using production " << E << "-->" << crnt_prod << endl;
    //cout << "inspecting " << count << "th char in input" << endl;
    int size = crnt_prod.size();
    for (int i = 0; i < size; ++i)
    {
        if (non_term.find(crnt_prod[i]) == non_term.end()) //if it is a terminal do the matching
        {
            if (crnt_prod[i] != input[count + success])
            {
                if (crnt_prod[i] == '#')
                {
                    //cout << "epsilon found" << endl;
                    continue;
                }

                return -1;
            }
            else
            {
                cout << "matching index " << count << " of input =\"" << input[count] << "\" in " << input << " with " << crnt_prod[i] << " in " << E << "-->" << crnt_prod << endl;
                success++;
            }
        }
        else
        {
            int fount = 0;
            char temp = crnt_prod[i];
            int non_term_num = non_term[crnt_prod[i]];
            for (int j = 0; j < production[non_term_num].size(); ++j)
            {
                int res = method(production, non_term, input, count + success, production[non_term_num][j], temp);
                if (res == 0)
                {
                    fount = 1;
                    continue;
                }
                if (res != -1)
                {
                    fount = 1;
                    success += res;
                    //break;
                }
                else
                {
                    //contines loop
                }
            }
            if (fount == 0)
            {
                return -1;
            }
        }
    }

    return success;
}

bool recursive_descent(vector<vector<string>> production, unordered_map<char, int> non_term, char E, string input, int count)
{
    int size = input.size();
    bool res = false;
    int non_term_num = non_term[E];
    for (int i = 0; i < production[non_term_num].size(); ++i)
    {
        int ans = method(production, non_term, input, count, production[non_term_num][i], E);
        if (ans != -1)
        {
            if (ans >= size)
            {
                cout << "-----------------------------------------" << endl;
                cout << "Valid and parsing finished successfully" << endl;
                return true;
            }
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Invalid input" << endl;
    return false;
}

int main()
{
    int non = -1;
    string s;
    vector<vector<string>> production(100);
    cout << "Enter the productions in the form \"S : r\" " << endl;
    unordered_map<char, int> non_term;
    production = get_production(non_term, &non);
    unordered_set<char> terminals;
    unordered_set<char> non_terminals;
    cout << "Non-terminals: ";
    getline(cin, s);
    non_terminals = split_string(s);

    cout << "Terminals: ";
    getline(cin, s);
    terminals = split_string(s);

    char start;
    cout << "Enter the start symobl: ";
    cin >> start;
    cout << "Enter the Expression: ";
    cin >> s;
    bool val = recursive_descent(production, non_term, start, s, 0);

    return 0;
}