#include <bits/stdc++.h>
using namespace std;

int main()
{
    string file;

    cout << "Enter filename: ";
    cin >> file;

    string cmd = "stat \"" + file + "\"";

    system(cmd.c_str());

    return 0;
}
