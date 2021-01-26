// Cpp program for a lexical analyzer
#include <bits/stdc++.h>
using namespace std;
vector<string> split_vect(vector<string> s) //function to seperate each token and remove extra spaces
{
    vector<string> words;
    for (auto x : s)
    {
        int n = x.size();
        int j = 0;
        for (int i = 0; i < n; ++i)
        {
            if (x[i] == ' ' || x[i] == '\t')
            {
                if (i != j)
                {
                    words.push_back(x.substr(j, i - j));
                    j = i + 1;
                }
                else
                {
                    j++;
                }
            }
            if (x[i] == '{' || x[i] == '}' || x[i] == '(' || x[i] == ')' || x[i] == ',' || x[i] == ';')
            {
                if (i != j)
                {
                    words.push_back(x.substr(j, i - j));
                    j = i;
                }
                string samp = "";
                samp += x[i];

                if (i + 1 != n)
                {
                    words.push_back(samp);
                    j = i + 1;
                }
            }
        }
        words.push_back(x.substr(j, n - j));
    }
    return words;
}

bool is_key(string s) //function to check whether passed string is keyword
{
    if (s == "if" || s == "else" || s == "int" || s == "for" || s == "bool" || s == "string" || s == "float" || s == "return" || s == "printf")
        return true;
    else
        return false;
}

bool is_id(string s)
{
    int size = s.size();
    if (!isalpha(s[0]))
    {
        return false;
    }
    else
    {
        for (int i = 1; i < size; ++i)
        {
            if (!isalnum(s[i]))
            {
                return false;
            }
        }
    }
    return true;
}

bool is_bop(string s)
{
    if (s == "+" || s == "-" || s == "*" || s == "/" || s == "&&" || s == "||" || s == "=")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_uop(string s)
{
    if (s == "++" || s == "--" || s == "!")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_par(string s)
{
    if (s == "{" || s == "}" || s == "(" || s == ")")
    {
        return true;
    }
    return false;
}

bool is_relop(string s)
{
    if (s == " < " || s == ">" || s == ">=" || s == "<=" || s == "==")
    {
        return true;
    }
    return false;
}

bool is_num(string s) //function to check whether the token is literal
{
    int n = s.size();
    if (n == 0)
        return false;
    if (s[0] == '"' && s[n - 1] == '"' && n - 1 != 0)
        return true;
    for (int i = 0; i < n; ++i)
    {
        if (!isdigit(s[i]))
        {
            if (s[i] != '.')
                return false;
            else
            {
                for (int j = i + 1; j < n; ++j)
                {
                    if (!isdigit(s[j]))
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return true;
}

bool is_sup(string s)
{
    if (s == "," || s == ";")
        return true;
    return false;
}
int main()
{
    // int n;
    // cout << "Number of lines :";
    // cin >> n;
    // string s;
    // getline(cin, s);
    // vector<string> lines;
    // for (int i = 0; i < n; ++i)
    // {
    //     getline(cin, s);
    //     lines.push_back(s);
    // }
    vector<string> lines;
    string s;
    ifstream file("input.c");
    cout << "Reading from input.c" << endl;
    while (getline(file, s))
    {
        cout << s << endl;
        lines.push_back(s);
    }
    vector<string> words;
    words = split_vect(lines);
    vector<string> tokens;
    for (auto x : words)
    {
        if (is_key(x))
        {
            tokens.push_back("< " + x + " , " + "keyword" + " >");
        }
        else if (is_id(x))
        {
            tokens.push_back("< " + x + " , " + "identifier" + " >");
        }
        else if (is_par(x))
        {
            tokens.push_back("< " + x + " , " + "paranthesis" + " >");
        }
        else if (is_bop(x))
        {
            tokens.push_back("< " + x + " , " + "operator_b" + " >");
        }
        else if (is_uop(x))
        {
            tokens.push_back("< " + x + " , " + "operator_u" + " >");
        }
        else if (is_relop(x))
        {
            tokens.push_back("< " + x + " , " + "relop" + " >");
        }
        else if (is_sup(x))
        {
            tokens.push_back("< " + x + " , " + "seperator" + " >");
        }
        else if (is_num(x))
        {
            tokens.push_back("< " + x + " , " + "literal" + " >");
        }
        else
        {
            tokens.push_back("< " + x + " , " + "no_idea" + " >");
            cout << "un identified tocken " << x << " program forced to quit" << endl;
            return 0;
        }
    }
    for (auto x : tokens)
    {
        cout << x << endl;
        ;
    }
    cout << endl;
    return 0;
}