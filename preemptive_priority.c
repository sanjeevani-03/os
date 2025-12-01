#include<stdio.h>
#include<limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;    
    int waiting_time;
    int completed;
};

void preemptive_priority(struct Process p[], int n){
    int completed = 0;
    int current_time = 0;
    int prev_process = -1;

    while(completed < n){
        int highest_priority = INT_MAX;
        int selected_index = -1;

        for(int i=0; i<n; i++){
            if(p[i].arrival_time <=current_time && !p[i].completed){
                if(p[i].priority < highest_priority){
                    highest_priority = p[i].priority;
                    selected_index = i;
                }
            }
        }

        if(selected_index==-1){
            current_time++;
            continue;
        }   

        if(prev_process != selected_index && prev_process !=-1){
            printf("Time %d:Process %d\n", current_time, p[selected_index].pid);
        }
        p[selected_index].remaining_time--;
        current_time++;
        prev_process = selected_index;

        if(p[selected_index].remaining_time == 0){
            p[selected_index].completion_time = current_time;
            p[selected_index].turnaround_time = p[selected_index].completion_time - p[selected_index].arrival_time;
            p[selected_index].waiting_time = p[selected_index].turnaround_time - p[selected_index].burst_time;
            p[selected_index].completed = 1;
            completed++;
        }
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
        printf("Enter priority for process %d : ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = 0;
    }

    preemptive_priority(p, n);

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;

    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
    }

    printf("Average Turnaround Time: %.2f\n", total_tat/n);
    printf("Average Waiting Time: %.2f\n", total_wt/n);

    return 0;
}