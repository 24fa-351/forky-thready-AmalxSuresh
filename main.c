#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void pattern_one(int things);
void pattern_two(int things, int level);
int random_time();

int main(int argc, char *argv[]) {
    srand(time(0));
    int things, pattern_number;
    
    sscanf(argv[1], "%d", &things);
    sscanf(argv[2], "%d", &pattern_number);

    
    printf("this is things - %d, and this is pattern number - %d\n", things, pattern_number);
    fflush(stdout);
    if(pattern_number == 1) {
        pattern_one(things);
    }
    else if(pattern_number == 2) {
        pattern_two(things, 0);
    }

}

int random_time() {
    int random_time;
    random_time = (rand() % 8) + 1;
    return random_time;
}
void pattern_one(int things) {
    for(int i = 0; i < things; i++) {
        pid_t pid = fork();

        if(pid < 0) {
            printf("error\n");
            fflush(stdout);
            exit(1);
        }
        else if(pid == 0) {
            printf("Parent: created CHILD: %d, PID: %d\n", i, getpid());
            fflush(stdout);
            printf("Process %d (pid: %d) created: will sleep for %d seconds\n", i, getpid(), random_time());
            fflush(stdout);
            if(i == things - 1) {
                printf("*** Pattern 1 - All processes created ***\n");\
                fflush(stdout);
            }
            sleep(random_time());
            printf("Process %d is ending, PID: %d\n", i, getpid());
            fflush(stdout);
            if(i == things - 1) {
                printf("*** Pattern 1 - All children have exited ***\n");
                fflush(stdout);
            }
            exit(0);
        }
    }
}

void pattern_two(int things, int level) {
    if(level >= things) {
        return;
    }
    pid_t pid = fork();
    if(pid < 0) {
        printf("error\n");
        fflush(stdout);
        exit(1);
    }
    else if(pid == 0) {
        printf("Child: %d, PID: %d, starting\n", level, getpid());
        fflush(stdout);
        printf("Child %d (pid: %d) created: will sleep for %d seconds\n", level, getpid(), random_time());
        fflush(stdout);
        sleep(random_time());
        pattern_two(things, level + 1);
        printf("Child %d is ending, PID: %d\n", level, getpid());
        fflush(stdout);
        exit(0);

    }
    else {
        wait(NULL);
        printf("Child %d (pid %d), waiting for child %d (pid %d)\n", level, getppid(), level + 1, getpid());
        fflush(stdout);

    }
}