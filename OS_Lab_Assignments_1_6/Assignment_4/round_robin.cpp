#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, arrival, burst;
    int remaining, completion, waiting;
};

int main()
{
    int n, quantum;

    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }

    cin >> quantum;

    queue<int> q;
    vector<bool> added(n, false);

    int time = 0;
    int done = 0;

    while(done < n)
    {
        for(int i = 0; i < n; i++)
        {
            if(!added[i] && p[i].arrival <= time)
            {
                q.push(i);
                added[i] = true;
            }
        }

        if(q.empty())
        {
            time++;
            continue;
        }

        int i = q.front();
        q.pop();

        int run = min(quantum, p[i].remaining);

        cout << "P" << p[i].pid << " ";

        for(int t = 0; t < run; t++)
        {
            time++;
            p[i].remaining--;

            for(int j = 0; j < n; j++)
            {
                if(!added[j] && p[j].arrival <= time)
                {
                    q.push(j);
                    added[j] = true;
                }
            }

            if(p[i].remaining == 0)
                break;
        }

        if(p[i].remaining == 0)
        {
            p[i].completion = time;
            done++;
        }
        else
        {
            q.push(i);
        }
    }

    cout << endl;

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
