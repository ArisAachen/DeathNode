// standard heaer files
#include <netinet/in.h>
#include <rte_byteorder.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_mbuf_core.h>
#include <rte_mempool.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// dpdk header files
#include <rte_eal.h>
#include <rte_common.h>
#include <rte_ethdev.h>


#define NUM_MBUFS 8191
#define RX_RING_SIZE 1024
#define MBUF_CACHE_SIZE 250

static int port_init(uint16_t port, struct rte_mempool *mbuf_pool) {
    struct rte_eth_conf port_conf;
    const uint16_t rx_rings = 1, tx_rings = 1;
    int retval;
    uint16_t q;
    if (port >= rte_eth_dev_count_avail()) {
        return -1;
    }
    // configure the Ethernet device
    retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
    if (retval != 0) {
        return retval;
    }
    // allocate and set up 1 RX queue
    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(port, q, RX_RING_SIZE, rte_eth_dev_socket_id(port), NULL, mbuf_pool);
        if (retval < 0) {
            return retval;
        }
    }
    // allocate and set up 1 TX queue
    for (q = 0; q < tx_rings; q++) {
        retval = rte_eth_tx_queue_setup(port, q, RX_RING_SIZE, rte_eth_dev_socket_id(port), NULL);
        if (retval < 0) {
            return retval;
        }
    }
    // start the Ethernet device
    retval = rte_eth_dev_start(port);
    if (retval < 0) {
        return retval;
    }
    // enable RX in promiscuous mode for the Ethernet device
    rte_eth_promiscuous_enable(port);
    return 0;
}

// 
int main(int argc, char **argv) {
    // init dpdk environment
    if (rte_eal_init(argc, argv) < 0) {
        rte_exit(EXIT_FAILURE, "Invalid EAL parameters\n");
    }
    // check available ports
    unsigned nb_ports = rte_eth_dev_count_avail();
    if (nb_ports == 0) {
        rte_exit(EXIT_FAILURE, "No Ethernet ports - bye\n");
    }
    printf("There are %u ports available\n", nb_ports);
    // alloc memory for port information
    struct rte_mempool *mbuf_pool = rte_pktmbuf_pool_create("UDP_INPUT", NUM_MBUFS * nb_ports, MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mbuf_pool == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");
    }
    // init port
    uint16_t portid;
    RTE_ETH_FOREACH_DEV(portid) {
        if(port_init(portid, mbuf_pool) != 0)
            rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu16"\n", portid);
    }
    printf("all port init finished");
    // check icmp packet
    while (true) {
        // range all port 
        RTE_ETH_FOREACH_DEV(portid) {
            // receive packet
            struct rte_mbuf *bufs[RX_RING_SIZE];
            const uint16_t nb_rx = rte_eth_rx_burst(portid, 0, bufs, RX_RING_SIZE);
            if (nb_rx == 0) {
                continue;
            }
            // print packet information
            for (int i = 0; i < nb_rx; i++) {
                // check ethernet type 
                struct rte_ether_hdr *eth_hdr = rte_pktmbuf_mtod(bufs[i], struct rte_ether_hdr *);
                if (eth_hdr == NULL) 
                    continue;
                if (eth_hdr->ether_type == rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4)) {
                    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(bufs[1], struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));
                    if (ipv4_hdr == NULL)
                        continue;
                    printf("receive packet, protocol: %d\n", ipv4_hdr->next_proto_id);
                    if (ipv4_hdr->next_proto_id == IPPROTO_ICMP) {
                        printf("receive icmp packet\n");
                    }
                }
            }
        }
    }
    // clean dpdk environment
    rte_eal_cleanup();
    return 0;
}