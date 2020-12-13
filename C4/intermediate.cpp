#include <bits/stdc++.h>
using namespace std;
int precedence(char a)
{
    if (a == '+' || a == '-')
    {
        return 0;
    }
    if (a == '(')
        return -1;
    return 1;
}
bool isop(char s)
{
    if (s == '+' || s == '-' || s == '*' || s == '/')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void print_star(int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << "*";
    }
    cout << endl;
}
string charint(char s)
{
    string res = "";
    if (s >= '1' && s <= '9')
    {
        res += 't';
        res += s;
        return res;
    }
    return res + s;
}
int main()
{
    string s;
    cout << "Enter the expression: ";
    getline(cin, s);
    vector<char> input;
    int len = s.size();
    int start = 0;
    while (s[start] != '=')
    {
        start++;
    }
    for (int i = start + 1; i < len; ++i)
    {
        if (s[i] == ' ')
            continue;
        input.push_back(s[i]);
    }
    // for (auto x : input)
    // {
    //     cout << x;
    // }
    char count = '1';
    stack<char> value;
    stack<char> op;
    for (int i = 0; i < input.size(); ++i)
    {
        //cout << input[i] << "current reading" << endl;
        //cout << isop(input[i]);
        if (isalpha(input[i]))
        {
            //cout << input[i] << " pushed into the stack" << endl;
            value.push(input[i]);
        }
        else if (input[i] == '(')
        {
            op.push(input[i]);
        }

        else if (isop(input[i]))
        {
            //cout << "operant found: " << input[i] << endl;
            while (!op.empty() && precedence(op.top()) >= precedence(input[i]))
            {
                char a1, a2, o1;
                a2 = value.top();
                value.pop();
                a1 = value.top();
                value.pop();
                o1 = op.top();
                op.pop();
                string b1, b2;
                b1 = charint(a1);
                b2 = charint(a2);
                cout << "t" << count << " = " << b1 << " " << o1 << " " << b2 << endl;
                value.push(count);
                count++;
            }
            op.push(input[i]);
        }
        else
        { // closing bracket present
            //cout << "closing bracket found " << endl;
            while (!op.empty() && op.top() != '(')
            {
                char a1, a2, o1;
                a2 = value.top();
                value.pop();
                a1 = value.top();
                value.pop();
                o1 = op.top();
                op.pop();
                string b1, b2;
                b1 = charint(a1);
                b2 = charint(a2);
                cout << "t" << count << " = " << b1 << " " << o1 << " " << b2 << endl;
                value.push(count);
                count++;
            }
            op.pop();
        }
    }
    while (!op.empty())
    {
        char a1, a2, o1;
        a2 = value.top();
        value.pop();
        a1 = value.top();
        value.pop();
        o1 = op.top();
        op.pop();
        string b1, b2;
        b1 = charint(a1);
        b2 = charint(a2);
        cout << "t" << count << " = " << b1 << " " << o1 << " " << b2 << endl;
        value.push(count);
        count++;
    }
    cout << s[0] << " = " << charint(count - 1) << endl;
    return 0;
}