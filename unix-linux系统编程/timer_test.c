// Unix timer 

#include <ctime>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>


void unix_signal_call(int sig) {
    printf("sig is %d \n", sig);
}

// unix settimer and gettimmer
void unix_timer_test() {
    // which: ITIMER_REAL  ITIMER_VIRTUAL(SIGVTALRM signal) ITIMER_PROF
    // 
    struct itimerval val = {
        // 这个字段表示是否为循环定时器
        .it_interval = {
            .tv_sec = 6,
            .tv_usec = 0,
        },
        // 定时器到期时间
        .it_value = {
            .tv_sec = 10,
            .tv_usec = 0,
        }
    };


    setitimer(ITIMER_REAL, &val, NULL);
    // 或者， 两者操作的是同一个定时器
    alarm(10);


    sigset_t set;
    sigemptyset(&set);
    sigfillset(&set);
    struct sigaction action = {
        .sa_mask = set,
        .sa_flags = SA_RESTART,
        .sa_handler = unix_signal_call,
    };
    sigaction(SIGALRM, &action, NULL);

    sleep(20);
}


void timer_create_test() {
    int fd = timer_create(CLOCK_, struct sigevent *__restrict __evp, timer_t *__restrict __timerid)

    fd
}

int main() {
    unix_timer_test();
    return 1;
}