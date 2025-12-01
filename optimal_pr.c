#include<stdio.h>
#include<limits.h>

int find_page(int frames[], int num_frames, int page){
    for(int i=0; i<num_frames; i++){
        if(frames[i]==page) return i;
    }
    return -1;
}

int print_frames(int frames[], int num_frames){
    printf("Frames: ");
    for(int i=0; i<num_frames; i++){
        if(frames[i]==-1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("\n");
}

int find_optimal(int frames[], int num_frames, int pages[], int num_pages, int current_index){
    int farthest = current_index;
    int index=-1;

    for(int i=0; i<num_frames; i++){
        if(frames[i]==-1) return i;
        int j;
        for(j=current_index; j<num_pages; j++){
            if(frames[i]==pages[j]){
                if(j>farthest){
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if(j==num_pages){
            return i;
        }
    }

    return (index==-1) ? 0 : index;
}

int main(){
    int num_Frames, num_pages;

    printf("Enter number of frames: ");
    scanf("%d", &num_Frames);
    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    int pages[num_pages], frames[num_Frames];

    printf("Enter page reference string: \n");
    for(int i=0; i<num_pages; i++){
        scanf("%d", &pages[i]);
    }

    for(int i=0; i<num_Frames; i++){
        frames[i]=-1;
    }

    int page_Faults = 0;

    printf("\n");

    for(int i=0; i<num_pages; i++){
        printf("Page %d:", pages[i]);

        if(find_page(frames, num_Frames, pages[i])==-1){
            int replace_index = find_optimal(frames, num_Frames, pages, num_pages, i+1);
            frames[replace_index] = pages[i];
            page_Faults++;
            printf("Page Fault ");
        } else {
            printf("Page Hit ");
        }
        print_frames(frames, num_Frames);
    }
    printf("Total Page Faults: %d\n", page_Faults);

    return 0;
}