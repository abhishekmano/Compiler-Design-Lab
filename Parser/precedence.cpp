#include <bits/stdc++.h>
using namespace std;
void set_precedence(unordered_map<char, int> &precedence)
{
    precedence['$'] = 0;
    precedence['('] = 0;
    // precedence['E'] = 2;
    precedence['+'] = 3;
    precedence['*'] = 4;
    precedence[')'] = 5;
    precedence['i'] = 5;
}
void print_stack(stack<char> check)
{
    string s = "";
    while (!check.empty())
    {
        s = check.top() + s;
        check.pop();
    }
    cout << s;
}
void print_string(string s, int n)
{
    int size = s.size();
    for (int i = n; i < size; ++i)
    {
        cout << s[i];
    }
}
int main()
{
    unordered_map<char, int> precedence;
    set_precedence(precedence);
    cout << "Enter the input: ";
    string s;
    stack<char> check;
    int ip = 0;
    check.push('$');
    cin >> s;
    s += "$";
    cout << "input is " << s << endl;
    cout << "Stack\t\tInput\t\tAction" << endl;
    while (true)
    {
        //cout << "in while loop" << endl;
        string action;
        if (s[ip] == '$' && check.top() == '$')
        {
            cout << "Finished parsing" << endl;
            break;
        }
        if (check.empty() || ip >= s.size())
        {
            cout << "Error" << endl;
            break;
        }
        int pref, flag = 0;
        if (s[ip] == ')')
        {
            pref = 1;
        }
        else
        {
            pref = precedence[s[ip]];
        }
        int pref2;
        if (check.top() != 'E')
        {
            pref2 = precedence[check.top()];
        }
        else
        {
            check.pop();
            pref2 = precedence[check.top()];
            if (check.top() == '$')
            {
                flag = 1;
            }
            check.push('E');
        }
        if (s[ip] == '(' || (pref >= pref2 && !(flag == 1 && s[ip] == '$'))) //Push into stack
        {
            //cout << "inside the shifft part" << endl;
            check.push(s[ip]);
            ip++;
            action = "Shift";
        }
        else
        {
            string temp = "";
            int flag = 1;
            while (check.top() == 'E' || pref <= precedence[check.top()])
            {
                if (check.top() != 'E' && pref == precedence[check.top()])
                {
                    //cout << "flag set to zero " << check.top() << endl;
                    flag = 0;
                }
                if (check.top() == '$')
                {
                    break;
                }
                char top = check.top();
                temp = top + temp;
                check.pop();
                if (top == 'i' || flag == 0)
                {
                    break;
                }
            }
            if (temp == "i")
            {
                action = "Reduce : E --> i";
                check.push('E');
            }
            else if (temp == "E+E")
            {
                action = "Reduce : E --> E + E ";
                check.push('E');
            }
            else if (temp == "E*E")
            {
                action = "Reduce : E --> E * E ";
                check.push('E');
            }
            else if (temp == "(E)")
            {
                action = "Reduce : E --> ( E ) ";
                check.push('E');
            }
            else if (temp == "E")
            {
            }
            else
            {
                cout << "unexpected  condition " << temp << endl;
                return 0;
            }
        }
        //cout << "endl of loop" << endl;
        print_stack(check);
        //cout << "stack printing finished " << endl;
        cout << "\t\t";
        print_string(s, ip);
        cout << "\t\t";
        cout << action << endl;
    }

    return 0;
}