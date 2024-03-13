// standard header
#include <stdlib.h>

// dpdk header 
#include <rte_eal.h>
#include <rte_lcore.h>
#include <rte_launch.h>
#include <rte_common.h>


static int lcore_hello(__attribute__((unused)) void *arg) {
    unsigned lcore_id;
    lcore_id = rte_lcore_id();
    printf("hello from core %u\n", lcore_id);
    return 0;
}

// process in 
int main(int argc, char **argv) {
    // init eal environment, 
    // create thread 
    if (rte_eal_init(argc, argv) < 0) {
        rte_exit(EXIT_FAILURE, "Invalid EAL parameters\n");
    }
    // get the number of lcore
    unsigned lcore_id;
    // schedule for each worker thead
    RTE_LCORE_FOREACH_WORKER(lcore_id) {
        // set each worker thread to run lcore_hello
        rte_eal_remote_launch(lcore_hello, NULL, lcore_id);
    }
    // wait for all worker thread to finish
    rte_eal_mp_wait_lcore();
    // clean up the EAL
    rte_eal_cleanup();
    return 0;
}