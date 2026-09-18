#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, arrival, burst;
    int completion, waiting, turnaround;
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

    sort(p.begin(), p.end(), [](Process a, Process b)
    {
        return a.arrival < b.arrival;
    });

    int time = 0;

    for(auto &x : p)
    {
        if(time < x.arrival)
            time = x.arrival;

        time += x.burst;

        x.completion = time;
        x.turnaround = x.completion - x.arrival;
        x.waiting = x.turnaround - x.burst;
    }

    double avg = 0;

    for(auto x : p)
    {
        cout << "P" << x.pid
             << " WT = " << x.waiting << endl;

        avg += x.waiting;
    }

    cout << "Average WT = " << avg / n << endl;

    return 0;
}
