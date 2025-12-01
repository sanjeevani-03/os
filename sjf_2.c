#include<stdio.h>
#include<limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int completed;
};

void sjf(struct Process p[], int n){
    int completed = 0;
    int current_time=0;

    while(completed < n){
        int min_burst = INT_MAX;
        int min_index = -1;

        for(int i=0; i<n; i++){
            if(p[i].arrival_time <= current_time && !p[i].completed){
                if(p[i].burst_time < min_burst){
                    min_burst = p[i].burst_time;
                    min_index = i;
                }
            }
        }

        if(min_index==-1) {
            current_time++;
            continue;
        }
            current_time+=p[min_index].burst_time;
            p[min_index].completion_time = current_time;
            p[min_index].turnaround_time = p[min_index].completion_time-p[min_index].arrival_time;
            p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time;
            p[min_index].completed = 1;
            completed++;
    }
}

int main(){
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i=0; i<n; i++){
        p[i].pid = i+1;
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);    
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }

    sjf(p, n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;

    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
    }

    printf("Average Turn aourn time: %.2f\n", total_tat/n);
    printf("Average waiting time: %.2f\n", total_wt/n);

    return 0;
}