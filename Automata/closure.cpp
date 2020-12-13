// CPP program to find the epsilon closure of all states
#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "Enter the number of states: ";
    int n, m;
    cin >> n;
    int start, last, temp, temp1;
    int epsilon;
    cout << "Enter the number of epsilon transition: ";
    cin >> epsilon;
    vector<pair<int, int>> eps;
    cout << "From\tTo" << endl;
    for (int i = 0; i < epsilon; ++i)
    {
        cin >> temp >> temp1;
        if (temp >= n || temp < 0 || temp1 >= n || temp1 < 0)
        {
            cout << "incorrect input: program forced to terminate" << endl;
            return 0;
        }
        eps.push_back({temp, temp1});
    }

    queue<int> check;
    cout << "Epsilon Closures are: \n";
    for (int i = 0; i < n; ++i)
    {
        vector<int> visited(n, 0);
        if (visited[i] != 1)
        {
            cout << i << ": ";
            visited[i] = 1;
            cout << "{ " << i;
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
                visited[c] = 1;
                cout << ", " << c;
                for (auto x : eps)
                {
                    if (x.first == c && visited[x.second] != 1)
                    {
                        check.push(x.second);
                    }
                }
            }
            cout << " }" << endl;
        }
    }

    return 0;
}