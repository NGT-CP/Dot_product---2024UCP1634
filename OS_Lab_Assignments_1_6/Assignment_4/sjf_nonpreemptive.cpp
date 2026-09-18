#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, arrival, burst;
    int completion, waiting, turnaround;
    bool done = false;
};

int main()
{
    int n;
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cin >> p[i].arrival >> p[i].burst;
    }

    int time = 0;
    int done = 0;

    while(done < n)
    {
        int best = -1;

        for(int i = 0; i < n; i++)
        {
            if(!p[i].done && p[i].arrival <= time)
            {
                if(best == -1 ||
                   p[i].burst < p[best].burst)
                    best = i;
            }
        }

        if(best == -1)
        {
            time++;
            continue;
        }

        time += p[best].burst;

        p[best].completion = time;
        p[best].turnaround = time - p[best].arrival;
        p[best].waiting = p[best].turnaround - p[best].burst;

        p[best].done = true;
        done++;
    }

    double avg = 0;

    for(auto x : p)
    {
        cout << "P" << x.pid
             << " WT = " << x.waiting << endl;

        avg += x.waiting;
    }

    cout << "Average WT = " << avg / n << endl;
}
