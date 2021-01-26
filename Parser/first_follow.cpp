#include <bits/stdc++.h>
using namespace std;
vector<vector<string>> get_production(unordered_map<char, int> &non_term, int *num) //return the production vector
{
    int non = -1;
    string s;
    vector<vector<string>> production(100);
    getline(cin, s);
    while (s != "")
    {
        int non_index;
        char left = s[0];
        if (non_term.find(s[0]) == non_term.end()) //add if it is a new non terminal
        {
            non_term[s[0]] = ++non;
            non_index = non;
        }
        else
        {
            non_index = non_term[s[0]];
        }
        string right = s.substr(4, s.size() - 4); // "s : " total 4 spaces are blank
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

vector<char> find_first(char c, vector<vector<string>> production, vector<vector<char>> &First, unordered_map<char, int> umap)
{
    vector<char> res;
    if (umap.find(c) == umap.end())
    {
        res.push_back(c);
        return res;
    }
    int num = umap[c];
    if (First[num].size() != 0)
    {
        return First[num];
    }
    int n = production[num].size();
    for (int i = 0; i < n; ++i) // iterate through each production
    {
        string m = production[num][i];
        int right_size = m.size();
        for (int j = 0; j < right_size; ++j) // iterate through each charecter in production
        {
            if (umap.find(m[j]) == umap.end()) //if right side of production  is a terminal
            {
                if (find(res.begin(), res.end(), m[j]) == res.end())
                {
                    res.push_back(m[j]);
                }

                break;
            }
            else // Non terminal
            {
                vector<char> temp = find_first(m[j], production, First, umap); // finding first of  j th non terminal
                //cout << "called for first of " << m[j] << endl;
                int first_char = temp.size();
                int flag = 1;
                for (int k = 0; k < first_char; ++k)
                {
                    if (temp[k] == '#')
                    {
                        cout << "Epsilon found in first of " << m[j] << endl;
                        flag = 0;
                    }
                    if (find(res.begin(), res.end(), temp[k]) == res.end())
                    {
                        if (temp[k] != '#')
                        {
                            res.push_back(temp[k]);
                        }
                        else
                        {
                            if (j == right_size - 1)
                            {
                                res.push_back(temp[k]);
                            }
                        }
                    }
                }
                if (flag == 1)
                {
                    break;
                }
            }
        }
    }
    First[num] = res;
    return res;
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
    // for (auto x : non_terminals)
    // {
    //     cout << x << " ";
    // }
    // cout << endl;
    cout << "Terminals: ";
    getline(cin, s);
    vector<vector<char>> First(non + 1);
    terminals = split_string(s);
    // for (auto x : terminals)
    // {
    //     cout << x << " ";
    // }
    // cout << endl;
    // cout << "number of non term is : " << non << endl;
    for (auto x : non_terminals)
    {
        First[non_term[x]] = find_first(x, production, First, non_term);
    }
    cout << "-----First----- " << endl;
    for (auto x : non_terminals)
    {
        cout << x << ": ";
        for (auto y : First[non_term[x]])
        {
            cout << y << " ";
        }
        cout << endl;
    }
    return 0;
}

// E : TR
// F : (E)
// F : i
// R : #
// R : +TR
// T : FY
// Y : #
// Y : *FY

// E F R T Y

// ( ) i # + *