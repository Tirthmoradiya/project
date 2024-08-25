#include <bits/stdc++.h>
using namespace std;

class Process
    {
    private:
        int pid;
        int arrival_time;
        int burst_time;
        int start_time;
        int completion_time;
        int turnaround_time;
        int waiting_time;
        int priority;

    public:
        Process()
        {
            pid = 0;
            arrival_time = 0;
            burst_time = 0;
            start_time = 0;
            completion_time = 0;
            turnaround_time = 0;
            waiting_time = 0;
            priority = 0;
        }

        Process(int pid, int arrival_time, int burst_time, int start_time, int completion_time,
                int turnaround_time, int waiting_time, int priority)
        {
            this->pid = pid;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
            this->start_time = start_time;
            this->completion_time = completion_time;
            this->turnaround_time = turnaround_time;
            this->waiting_time = waiting_time;
            this->priority = priority;
        }
        
        int get_pid() { return pid; }
        int get_arrival_time() { return arrival_time; }
        int get_burst_time() { return burst_time; }
        int get_start_time() { return start_time; }
        int get_completion_time() { return completion_time; }
        int get_turnaround_time() { return turnaround_time; }
        int get_waiting_time() { return waiting_time; }
        int get_priority() { return priority; }

        void set_pid(int pid) { this->pid = pid; }
        void set_arrival_time(int arrival_time) { this->arrival_time = arrival_time; }
        void set_burst_time(int burst_time) { this->burst_time = burst_time; }
        void set_start_time(int start_time) { this->start_time = start_time; }
        void set_completion_time(int completion_time) { this->completion_time = completion_time; }
        void set_turnaround_time(int turnaround_time) { this->turnaround_time = turnaround_time; }
        void set_waiting_time(int waiting_time) { this->waiting_time = waiting_time; }
        void set_priority(int priority) { this->priority = priority; }

        static bool compareArrival(Process p1, Process p2)
        {
            return p1.get_arrival_time() < p2.get_arrival_time();
        }

        static bool comparestart(Process p1, Process p2)
        {
            return p1.get_start_time() < p2.get_start_time();
        }

        static bool compareID(Process p1, Process p2)
        {
            return p1.get_pid() < p2.get_pid();
        }
    };

class SchedulingAlgorithm
    {
    public:
        SchedulingAlgorithm() {}
        virtual ~SchedulingAlgorithm() {}
        virtual void solve() = 0;
    };

class SchedulingUnits
    {
    private:
        float avg_turnaround_time;
        float avg_waiting_time;

    public:
        // constructor
        SchedulingUnits()
        {
            avg_turnaround_time = 0;
            avg_waiting_time = 0;
        }

        // getters
        float get_avg_turnaround_time() { return avg_turnaround_time; }
        float get_avg_waiting_time() { return avg_waiting_time; }

        // setters
        void set_avg_turnaround_time(float avg_turnaround_time)
        {
            this->avg_turnaround_time = avg_turnaround_time;
        }

        void set_avg_waiting_time(float avg_waiting_time)
        {
            this->avg_waiting_time = avg_waiting_time;
        }

        void display_scheduling_units()
        {
            cout << "Average Turnaround Time = " << get_avg_turnaround_time() << endl;
            cout << "Average Waiting Time = " << get_avg_waiting_time() << endl;
        }
    };

class Display
    {
        int n;
        Process *p;

    public:
        Display(int n, Process *p) : n(n), p(p) {}

        void display_solution()
        {
            cout << endl;
            cout << "|  Process ID\t|"
                      << " Arrival Time\t|"
                      << "  Burst Time\t|"
                      << "  Start Time\t|"
                      << "    Completion Time\t|"
                      << "    Turnaround Time\t|"
                      << " Waiting Time\t|"
                      << "\n"
                      << endl;

            for (int i = 0; i < n; i++)
            {
                cout << "|      P"<<p[i].get_pid() << "\t|"
                    << "       " << p[i].get_arrival_time() << "\t|"
                    << "       "  << p[i].get_burst_time() << "\t|"
                    << "       "  << p[i].get_start_time() << "\t|"
                    << "           "  << p[i].get_completion_time() << "\t\t|"
                    << "           "  << p[i].get_turnaround_time() << "\t\t|"
                    << "       "  << p[i].get_waiting_time() << "\t|"
                    << "\n"
                    << endl;
            }
        };
        void display_gantt_chart()
        {

        };

    };

class FCFS : public SchedulingAlgorithm, SchedulingUnits, public Display
{
    int n;
    Process *p;

public:
    FCFS(int n, Process *p)
        : Display(n, p), n(n), p(p)
    {
        solve();
        display_solution();
        display_scheduling_units();
        display_gantt_chart();
    };

    void solve();
    void display_gantt_chart();
};

void FCFS::solve()
{
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    sort(p, p + n, Process::compareArrival);

    for (int i = 0; i < n; i++)
    {
        int maxStartTime = max(p[i - 1].get_completion_time(), p[i].get_arrival_time());

        int start_time = (i == 0) ? p[i].get_arrival_time() : maxStartTime;

        p[i].set_start_time(start_time);
        p[i].set_completion_time(p[i].get_start_time() + p[i].get_burst_time());
        p[i].set_turnaround_time(p[i].get_completion_time() - p[i].get_arrival_time());
        p[i].set_waiting_time(p[i].get_turnaround_time() - p[i].get_burst_time());

        total_turnaround_time += p[i].get_turnaround_time();
        total_waiting_time += p[i].get_waiting_time();
    }

    set_avg_turnaround_time((float)total_turnaround_time / n);
    set_avg_waiting_time((float)total_waiting_time / n);

    sort(p, p + n, Process::compareID);
}

void FCFS::display_gantt_chart()
{
    cout << "\n\nGantt Chart (FCFS):\n";
    cout << "\n";
    int total_time = p[n - 1].get_completion_time();
    for (int i = 0; i < (total_time-1)*2 + n+1; i++)
    {
        cout << "-";
    }
    cout << "\n|";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].get_burst_time(); j++)
        {
            cout << "P" << p[i].get_pid();
        }
        cout << "|";
    }
    cout << "\n";
    for (int i = 0; i < (total_time-1)*2 + n+1; i++)
    {
        cout << "-";
    }
    cout << "\n";
    int x=0;
    cout << "0";
    for (int i = 0; i < n; i++)
    {
        x+=p[i].get_burst_time();
        for (int j = 0; j < p[i].get_burst_time(); j++)
        {
            cout << "  ";
        }
        cout << x;
    }
    cout << "\n";
}


class SJF : public SchedulingAlgorithm, SchedulingUnits, public Display
{
    int n;
    Process *p;

public:
    SJF(int n, Process *p)
        : Display(n, p), n(n), p(p)
    {
        solve();
        display_solution();
        display_scheduling_units();
        display_gantt_chart();
    };

    void solve();
    void display_gantt_chart();
};

void SJF::solve()
{
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].get_arrival_time() <= current_time && is_completed[i] == 0)
            {
                if (p[i].get_burst_time() < mn)
                {
                    mn = p[i].get_burst_time();
                    idx = i;
                }
                if (p[i].get_burst_time() == mn)
                {
                    if (p[i].get_arrival_time() < p[idx].get_arrival_time())
                    {
                        mn = p[i].get_burst_time();
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1)
        {
            p[idx].set_start_time(current_time);
            p[idx].set_completion_time(p[idx].get_start_time() + p[idx].get_burst_time());
            p[idx].set_turnaround_time(p[idx].get_completion_time() - p[idx].get_arrival_time());
            p[idx].set_waiting_time(p[idx].get_turnaround_time() - p[idx].get_burst_time());

            total_turnaround_time += p[idx].get_turnaround_time();
            total_waiting_time += p[idx].get_waiting_time();

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].get_completion_time();
        }
        else
        {
            current_time++;
        }
    }

    set_avg_turnaround_time((float)total_turnaround_time / n);
    set_avg_waiting_time((float)total_waiting_time / n);
}
void SJF::display_gantt_chart()
{
    cout << "\n\nGantt Chart (SJF):\n\n";
    
    sort(p, p + n, Process::comparestart);
    
    int total_time = p[n - 1].get_completion_time();
    
    for (int i = 0; i < (total_time - 1) * 2 + n + 1; i++)
    {
        cout << "-";
    }
    cout << "\n|";
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].get_burst_time(); j++)
        {
            cout << "P" << p[i].get_pid();
        }
        cout << "|";
    }
    cout << "\n";
    
    for (int i = 0; i < (total_time - 1) * 2 + n + 1; i++)
    {
        cout << "-";
    }
    cout << "\n";
    
    int current_time = 0;
    cout << "0";
    
    for (int i = 0; i < n; i++)
    {
        current_time += p[i].get_burst_time();
        
        for (int j = 0; j < p[i].get_burst_time(); j++)
        {
            cout << "  ";
        }
        cout << current_time; 
    }
    cout << "\n";
}

class SRTF : public SchedulingAlgorithm, SchedulingUnits, public Display
{
    int n;
    Process *p;

public:
    SRTF(int n, Process *p)
        : Display(n, p), n(n), p(p)
    {
        solve();
        display_solution();
        display_scheduling_units();
        display_gantt_chart();
    };

    void solve();
};
void SRTF::solve()
{
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];

    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    for (int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].get_burst_time();
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].get_arrival_time() <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if (burst_remaining[i] == mn)
                {
                    if (p[i].get_arrival_time() < p[idx].get_arrival_time())
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            if (burst_remaining[idx] == p[idx].get_burst_time())
            {
                p[idx].set_start_time(current_time);
            }
            burst_remaining[idx] -= 1;
            current_time++;

            if (burst_remaining[idx] == 0)
            {
                p[idx].set_completion_time(current_time);
                p[idx].set_turnaround_time(p[idx].get_completion_time() - p[idx].get_arrival_time());
                p[idx].set_waiting_time(p[idx].get_turnaround_time() - p[idx].get_burst_time());

                total_turnaround_time += p[idx].get_turnaround_time();
                total_waiting_time += p[idx].get_waiting_time();

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }
    
    set_avg_turnaround_time((float)total_turnaround_time / n);
    set_avg_waiting_time((float)total_waiting_time / n);
}

class RR : public SchedulingAlgorithm, SchedulingUnits, public Display
{
    int n;
    Process *p;

public:
    RR(int n, Process *p)
        : Display(n, p), n(n), p(p)
    {
        solve();
        display_solution();
        display_scheduling_units();
    };

    void solve();
};
void RR::solve()
{

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];
    int idx;

    int tq;
    cout << "Enter time quantum: ";
    cin >> tq;

    for (int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].get_burst_time();
    }

    sort(p, p + n, Process::compareArrival);

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;

    while (completed != n)
    {
        idx = q.front();
        q.pop();

        if (burst_remaining[idx] == p[idx].get_burst_time())
        {
            p[idx].set_start_time(max(current_time, p[idx].get_arrival_time()));
            current_time = p[idx].get_start_time();
        }

        if (burst_remaining[idx] - tq > 0)
        {
            burst_remaining[idx] -= tq;
            current_time += tq;
        }
        else
        {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            p[idx].set_completion_time(current_time);
            p[idx].set_turnaround_time(p[idx].get_completion_time() - p[idx].get_arrival_time());
            p[idx].set_waiting_time(p[idx].get_turnaround_time() - p[idx].get_burst_time());

            total_turnaround_time += p[idx].get_turnaround_time();
            total_waiting_time += p[idx].get_waiting_time();
        }

        for (int i = 1; i < n; i++)
        {
            if (burst_remaining[i] > 0 && p[i].get_arrival_time() <= current_time && mark[i] == 0)
            {
                q.push(i);
                mark[i] = 1;
            }
        }
        if (burst_remaining[idx] > 0)
        {
            q.push(idx);
        }

        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0)
                {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    set_avg_turnaround_time((float)total_turnaround_time / n);
    set_avg_waiting_time((float)total_waiting_time / n);

    sort(p, p + n, Process::compareID);
}

class PRS : public SchedulingAlgorithm, SchedulingUnits, public Display
{
    int n;
    Process *p;

public:
    PRS(int n, Process *p)
        : Display(n, p), n(n), p(p)
    {
        solve();
        display_solution();
        display_scheduling_units();
    };

    void solve();
};

void PRS::solve()
{
    int choice;
    bool preemptive;
    cout << "Choose Priority Scheduling Algorithm: " << endl;
    cout << "1. Preemptive" << endl;
    cout << "2. Non-Preemptive" << endl;
    cout << "0. Exit" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        preemptive=true;
        break;
    case 2:
        preemptive=false;
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "Invalid Choice" << endl;
        break;
    }

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    int burst_remaining[100];
    for (int i = 0; i < n; i++)
    {
        burst_remaining[i] = p[i].get_burst_time();
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int idx = -1;
        int mx = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].get_arrival_time() <= current_time && is_completed[i] == 0)
            {
                if (p[i].get_priority() > mx)
                {
                    mx = p[i].get_priority();
                    idx = i;
                }
                if (p[i].get_priority() == mx)
                {
                    if (p[i].get_arrival_time() < p[idx].get_arrival_time())
                    {
                        mx = p[i].get_priority();
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            if (preemptive == true)
            {
                if (burst_remaining[idx] == p[idx].get_burst_time())
                {
                    p[idx].set_start_time(current_time);
                }
                burst_remaining[idx] -= 1;
                current_time++;

                if (burst_remaining[idx] == 0)
                {
                    p[idx].set_completion_time(current_time);
                    p[idx].set_turnaround_time(p[idx].get_completion_time() - p[idx].get_arrival_time());
                    p[idx].set_waiting_time(p[idx].get_turnaround_time() - p[idx].get_burst_time());

                    total_turnaround_time += p[idx].get_turnaround_time();
                    total_waiting_time += p[idx].get_waiting_time();

                    is_completed[idx] = 1;
                    completed++;
                }
            }
            else
            {
                p[idx].set_start_time(current_time);
                p[idx].set_completion_time(p[idx].get_start_time() + p[idx].get_burst_time());
                p[idx].set_turnaround_time(p[idx].get_completion_time() - p[idx].get_arrival_time());
                p[idx].set_waiting_time(p[idx].get_turnaround_time() - p[idx].get_burst_time());

                total_turnaround_time += p[idx].get_turnaround_time();
                total_waiting_time += p[idx].get_waiting_time();

                is_completed[idx] = 1;
                completed++;
                current_time = p[idx].get_completion_time();
            }
        }
        else
        {
            current_time++;
        }
    }

    set_avg_turnaround_time((float)total_turnaround_time / n);
    set_avg_waiting_time((float)total_waiting_time / n);
}

string scheduling_algo(int n)
{
    switch (n)
    {
    case 1:
        return "FCFS (First Come First Serve)";
    case 2:
        return "SJF (Shortest Job First)";
    case 3:
        return "SRTF (Shortest Remaining Time First)";
    case 4:
        return "RR (Round Robin)";
    case 5:
        return "Priority (Priority Scheduling)";
    default:
        return "Exit";
    }
}

int main()
{
    cout << endl << "Welcome to operating systems sheduling algorithms" << endl<<endl;
    cout << "1. " << scheduling_algo(1) << endl;
    cout << "2. " << scheduling_algo(2) << endl;
    cout << "3. " << scheduling_algo(3) << endl;
    cout << "4. " << scheduling_algo(4) << endl;
    cout << "5. " << scheduling_algo(5) << endl;
    cout << "0. " << scheduling_algo(0) << endl;

    int choice;
    cout << "Enter your choice of scheduler: ";
    cin >> choice;
    cout << endl << "You have chosen " << scheduling_algo(choice) << endl;

    if (choice>5 or choice<1)
    {
        cout << "Thanks for not choosing any algorithm. Exiting..." << endl;
        return 0;
    }

    int n;
    Process p[100];
    
    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        int arrival_time, burst_time;
        int priority = 0;
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> arrival_time;
        cout << "Enter burst time of process " << i + 1 << ":   ";
        cin >> burst_time;

        if (choice == 5)
        {
            cout << "Enter priority of the process " << i + 1 << ": ";
            cin >> priority;
        }
        cout << endl;

        p[i] = Process(i, arrival_time, burst_time, 0, 0, 0, 0, priority);
    }

    switch (choice)
    {
    case 0:
    {
        exit(0);
        break;
    }
    case 1:
    {
        FCFS fcfs(n, p);
        break;
    }
    case 2:
    {
        SJF sjf(n, p);
        break;
    }
    case 3:
    {
        SRTF srtf(n, p);
        break;
    }
    case 4:
    {
        RR rr(n, p);
        break;
    }
    case 5:
    {
        PRS PRS(n, p);
        break;
    }
    default:
    {
        cout << "Invalid choice" << endl;
        break;
    }
    }
    return 0;
}
