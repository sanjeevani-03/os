#include<stdio.h>
#include<limits.h>

int find_page(int frames[], int num, int page){
    for(int i=0; i<num; i++){
        if(frames[i]==page) return i;
    }
    return -1;
}

void print_frames(int frames[], int num){
    printf("Frames: ");
    for(int i=0; i<num; i++){
        if(frames[i]==-1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("\n");
}

int find_lru(int frames[], int n, int last_used[], int current_time){
    int min_time = INT_MAX;
    int lru_index = -1;

    for(int i=0; i<n; i++){
        if(frames[i]==-1) return i;
        if(last_used[i] < min_time){
            min_time = last_used[i];
            lru_index=i;
        }
    }
    return lru_index;
}

int main(){
    int num_frames, num_pages;
    printf("ENter number of frames: ");
    scanf("%d", &num_frames);
    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    int pages[num_pages];
    printf("Enter page reference string: \n");
    for(int i=0; i<num_pages; i++){
        scanf("%d", &pages[i]);
    }

    int frames[num_frames];
    int last_used[num_frames];

    for(int i=0; i<num_frames; i++){
        frames[i] =-1;
        last_used[i] = -1;
    }

    int page_faults = 0;
    printf("\n");

    for(int i=0; i<num_pages; i++){
        printf("Page %d: ", pages[i]);
        int pos = find_page(frames, num_frames, pages[i]);
        if(pos==-1){
            int lru_index = find_lru(frames, num_frames, last_used, i);
            frames[lru_index] = pages[i];
            last_used[lru_index] = i;
            page_faults++;
            printf("Page Fault ");
        } else {
            last_used[pos] = i;
            printf("Page Hit ");
        }
        print_frames(frames, num_frames);
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}