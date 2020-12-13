#include <bits/stdc++.h>
using namespace std;
string beautify(string s) // to remove unneccessery space , () etc in the loop
{
    string new_s = "";
    int n = s.size();
    int flag = 0;
    for (int i = 0; i < n; ++i)
    {
        if (s[i] != ' ')
        {
            new_s += s[i];
        }
    }
    return new_s;
}
void print_star()
{
    cout << "***************************************************************" << endl;
}
bool is_id(string s, int i)
{
    if (!isalpha(s[i]))
    {
        return false;
    }
    if (i == 0)
    {
        if (!isalnum(s[i + 1]))
        {
            return true;
        }
    }
    else if (i == s.size() - 1)
    {
        if (!isalnum(s[i - 1]))
        {
            return true;
        }
    }
    else
    {
        if (!isalnum(s[i - 1]) && !isalnum(s[i + 1]))
        {
            return true;
        }
    }
    return false;
}
vector<string> constant(vector<string> lines, unordered_map<char, int> values)
{
    vector<string> result;
    int n = lines.size();
    for (int i = 0; i < n; ++i)
    {
        int len = lines[i].size();
        if (regex_match(lines[i], regex("[a-zA-Z]=[0-9]*;")))
        {
            //cout << "true" << endl;
            char variable = lines[i][0];
            string data = lines[i].substr(2, n - 1);
            int cons = stoi(data);
            //cout << "variale is: " << variable << " value: " << cons << endl;
            values[variable] = cons;
        }
        else
        {
            string append = "";
            for (int j = 0; j < len; ++j)
            {
                if (is_id(lines[i], j))
                {
                    if (values.find(lines[i][j]) != values.end())
                    {
                        int cons = values[lines[i][j]];
                        string s = to_string(cons);
                        append += s;
                        //cout << "variable found and appending " << s << endl;
                    }
                    else
                    {
                        append += lines[i][j];
                        // cout << "variable found but not value and appending " << lines[i][j] << endl;
                    }
                }
                else
                {
                    append += lines[i][j];
                    //cout << "variable not found and appending " << lines[i][j] << endl;
                }
            }
            result.push_back(append);
            //cout << append << endl;
        }
    }
    return result;
}
int main()
{
    vector<string> lines;
    string s, temp;
    ifstream file("constant.c");
    print_star();
    cout << "\t\t"
         << "Reading from constant.c" << endl;
    print_star();
    while (getline(file, s))
    {
        cout << "\t\t" << s << endl;
        s = beautify(s);
        lines.push_back(s);
    }
    unordered_map<char, int> values;
    vector<string> result = constant(lines, values);
    print_star();
    cout << "Result after constant propagation and deadcode elimination" << endl;
    print_star();
    for (auto x : result)
    {
        cout << "\t\t" << x << endl;
    }
    print_star();

    return 0;
}