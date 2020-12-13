#include <bits/stdc++.h>
using namespace std;
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
string last_3(stack<char> check)
{
    string res = "";
    for (int i = 0; i < 3; ++i)
    {
        res = check.top() + res;
        check.pop();
    }
    return res;
}

int main()
{
    vector<char> lhs = {'E'};
    unordered_set<string> rhs = {"E+E", "(E)", "i", "E*E"};
    cout << "Enter the string: ";
    string s;
    cin >> s;
    s += "$";
    int n = s.size(), count = 1, i = 0;
    stack<char> SR;
    char a, b, c;
    SR.push('$');
    cout << "----------------------------------------" << endl;
    cout << "STACK\t|\tINPUT\t|\tACTION\t|" << endl;
    cout << "----------------------------------------" << endl;
    while (true)
    {
        if (count >= 3)
        {
            string over = last_3(SR);
            //cout << "string found is " << over << endl;
            if (over == "$E$")
            {
                cout << "---------------------------------------" << endl;
                cout << "Parsing successfully finished, valid input" << endl;
                break;
            }
            if (rhs.find(over) != rhs.end())
            {
                SR.pop();
                SR.pop();
                SR.pop();
                SR.push('E');
                print_stack(SR);
                cout << "\t|\t";
                cout << s.substr(i, n - i) << "\t|Reduced E-->" << over << "|" << endl;
                // cout << "---------------------------------------" << endl;
                count -= 2;
                continue;
            }
        }
        if (SR.top() == 'i')
        {
            SR.pop();
            SR.push('E');
            print_stack(SR);
            cout << "\t|\t";
            cout << s.substr(i, n - i) << "\t|Reduced E-->i\t|" << endl;
            //cout << "---------------------------------------" << endl;
            continue;
        }
        if (i >= n)
        {
            cout << "---------------------------------------" << endl;
            cout << "Error--> Invalid Input" << endl;
            break;
        }
        SR.push(s[i]);
        print_stack(SR);
        cout << "\t|\t";
        cout << s.substr(i + 1, n - i) << "\t|\tShift\t|" << endl;
        //cout << "---------------------------------------" << endl;
        count++;
        i++;
    }
    return 0;
}