#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, arrival, burst, priority;
    int remaining, completion, waiting;
};

int main()
{
    int n;
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        cin >> p[i].arrival
            >> p[i].burst
            >> p[i].priority;

        p[i].remaining = p[i].burst;
    }

    int time = 0;
    int done = 0;

    while(done < n)
    {
        int best = -1;

        for(int i = 0; i < n; i++)
        {
            if(p[i].arrival <= time &&
               p[i].remaining > 0)
            {
                if(best == -1 ||
                   p[i].priority < p[best].priority)
                    best = i;
            }
        }

        if(best == -1)
        {
            time++;
            continue;
        }

        p[best].remaining--;
        time++;

        if(p[best].remaining == 0)
        {
            p[best].completion = time;
            done++;
        }
    }

    double avg = 0;

    for(auto &x : p)
    {
        int tat = x.completion - x.arrival;
        x.waiting = tat - x.burst;

        cout << "P" << x.pid
             << " WT = " << x.waiting << endl;

        avg += x.waiting;
    }

    cout << "Average WT = " << avg / n << endl;
}
