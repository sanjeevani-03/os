#include<stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void fcfs(struct Process p[], int n){
    int current_time = 0;

    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1; j++){
            if(p[j].arrival_time > p[j+1].arrival_time){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1]=temp;
            }
        }
    }

    for(int i=0; i<n; i++){
        if(current_time< p[i].arrival_time){
            current_time = p[i].arrival_time;
        }

        current_time += p[i].burst_time;
        p[i].completion_time = current_time;
        p[i].turnaround_time = p[i].completion_time-p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time-p[i].burst_time;
    }
}

    int main(){
        int n;
        printf("Enter number of processes: ");
        scanf("%d", &n);

        struct Process p[n];

        for(int i=0; i<n; i++){
            p[i].pid = i+1;
            printf("Enter arrival time for the process %d:  ", p[i].pid);
            scanf("%d", &p[i].arrival_time);
            printf("enter burst time for the process %d: ", p[i].pid);
            scanf("%d", &p[i].burst_time);
        }

        fcfs(p, n);

        printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
        float total_tat =0, total_wt = 0;

        for(int i=0; i<n; i++){
            printf("%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
            total_tat +=p[i].turnaround_time;
            total_wt +=p[i].waiting_time;
        }

        printf("Avergae turn around time: %.2f\n", total_tat/n);
        printf("Average waiting time: %.2f\n", total_wt/n);

        return 0;
    }