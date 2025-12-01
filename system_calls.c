#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

int main(){
    pid_t pid;
    int status, fd;
    char buffer[100];
    char write_data[] = "Hello, World!";

    printf("Process related system calls \n");
    printf("parent process id: %d\n", getpid());

    pid=fork();

    if(pid<0){
        perror("Fork failed");
        exit(1);
    } else if (pid==0){
        printf("child process id: %d\n", getpid());
        printf("child's parent process id: %d\n", getppid());
        exit(0);
    }
    else{
        printf("Parent created child with id: %d\n", pid);
        wait(&status);
        printf("Child process terminated\n");
    }

    printf("\n File related system calls\n");

    fd = open("testfile.txt", O_CREAT | O_WRONLY, 0644);

    if(fd < 0) {
        perror("Failed to open file");
        exit(1);
    }
    printf("File opened successfully\n");

    ssize_t bytes_written = write(fd, write_data, strlen(write_data));
    printf("%ld bytes written to file\n", bytes_written);

    close(fd);
    printf("file closed!\n");

    fd = open("testfile.txt", O_RDONLY);
    if(fd<0){
        perror("failed to open");
        exit(1);
    }
    printf("file opened for reading\n");
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer)-1);
    buffer[bytes_read]='\0';
    printf("read %ld bytes from file\n", bytes_read);
    close(fd);
    printf("file closed!\n");

    return 0;
}