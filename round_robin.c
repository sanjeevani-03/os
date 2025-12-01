#include<stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};

void round_robin(struct Process p[], int n, int time_quantum){
    int current_time  = 0;
    int completed = 0;

    while(completed<n){
        int done=1;
        for(int i=0; i<n; i++){
            if(p[i].remaining_time>0 && p[i].arrival_time <=current_time){
                done=0;
                if(p[i].remaining_time > time_quantum){
                    current_time+=time_quantum;
                    p[i].remaining_time = p[i].remaining_time - time_quantum;
                }
                else{
                    current_time+=p[i].remaining_time;
                    p[i].remaining_time = 0;
                    p[i].completion_time = current_time;
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    completed++;
                }
            }
        }
        if(done) current_time++;
    }
}

int main(){
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Process p[n];

    for(int i=0; i<n; i++){
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &p[i].arrival_time);    
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i+1;
        p[i].remaining_time = p[i].burst_time;
    }
    float total_tat=0, total_wt=0;
    round_robin(p, n, quantum);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        total_tat+=p[i].turnaround_time;
        total_wt+=p[i].waiting_time;
    }
    printf("Average Turnaroud time: %.2f\n", total_tat/n);
    printf("Average Waiting time: %.2f\n", total_wt/n);

    return 0;
}