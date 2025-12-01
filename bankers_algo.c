#include<stdio.h>
#include<stdbool.h>

int main(){
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int max[n][m], allocation[n][m], need[n][m], available[m];

    printf("Enter maximum resource matrix:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocation matrix:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter available resources:\n");
    for(int j=0; j<m; j++){
        scanf("%d", &available[j]);
    }

    printf("\nNeed Matrix:\n");
    for(int i=0; i<n; i++){
        printf("Process %d: ", i);
        for(int j=0; j<m; j++){
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    bool finished[n];
    int safe_sequence[n];
    int work[m];

    for(int i=0; i<n; i++) finished[i] = false;
    for(int j=0; j<m; j++) work[j] = available[j];

    int count=0;

    while(count<n){
        bool found = false;

        for(int i=0; i<n; i++){
            if(!finished[i]){
                bool can_allocate = true;
                for(int j=0; j<m;j++){
                    if(need[i][j] > work[j]){
                        can_allocate = false;
                        break;
                    }
                }

                if(can_allocate){
                    for(int j=0; j<m; j++){
                        work[j]+=allocation[i][j];
                    }

                    safe_sequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if(!found){
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for(int i=0; i<n; i++){
        printf("P%d ", safe_sequence[i]);
    }

    printf("\n");

    return 0;
}