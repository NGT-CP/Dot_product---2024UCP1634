#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    string input;

    while(1)
    {
        cout << "MyShell> ";
        getline(cin, input);

        if(input == "exit")
            break;

        stringstream ss(input);

        vector<string> words;
        string x;

        while(ss >> x)
            words.push_back(x);

        if(words.empty())
            continue;

        vector<char*> args;

        for(auto &s : words)
            args.push_back(s.data());

        args.push_back(NULL);

        if(fork() == 0)
        {
            execvp(args[0], args.data());
            exit(1);
        }

        wait(NULL);
    }

    return 0;
}
