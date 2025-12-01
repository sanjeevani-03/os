#include<stdio.h>

int find_page (int frames[], int num_frames, int page){
    for(int i=0; i<num_frames; i++){
        if(frames[i]==page) return 1; 
    }
    return 0;
}

void print_frames(int frames[], int num_frames){
    printf("Frames: ");
    for(int i=0; i<num_frames; i++){
        if(frames[i]==-1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("\n");
}

int main(){
    int num_frames, num_pages;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);
    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    int pages[num_pages];
    printf("Enter page reference string: \n");
    for(int i=0; i<num_pages; i++){
        scanf("%d", &pages[i]);
    }

    int frames[num_frames];
    for(int i=0; i<num_frames; i++){
        frames[i] = -1; 
    }

    int page_faults = 0;
    int next_frame = 0;

    printf("\n");

    for(int i=0; i<num_pages; i++){
        printf("Page %d: ", pages[i]);

        if(!find_page(frames, num_frames, pages[i])){
            frames[next_frame] = pages[i];
            next_frame = (next_frame + 1) % num_frames;
            page_faults++;
            printf("Page Fault ");
        }else printf("Page Hit ");

        print_frames(frames, num_frames);
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    return 0;
}