#include <stdbool.h>
#include <stdio.h>

#include <rte_eal.h>
#include <rte_ip.h>
#include <rte_flow.h>
#include <rte_udp.h>
#include <rte_common.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_mbuf_core.h>
#include <rte_byteorder.h>

#define DPDK_QUEUE_SIZE 1
#define DPDK_MBUFS_SIZE 8191
#define DPDK_BUF_SIZE 1024
#define DPDK_DESC_COUNT 1024
#define DROP_DST_ADDR (192 << 24) + (168 << 16) + (121 << 8) + 200
#define DROP_DST_MASK 0xFFFFFFFF
#define DROP_PATTERN_COUNT 3

int main_loop(uint16_t port_id) {
    struct rte_mbuf *bufs[DPDK_BUF_SIZE];
    struct rte_ether_hdr *eth_hdr;
    struct rte_ipv4_hdr *ipv4_hdr;
    // receive all package
    while (true) {
        // get buf size from port 0
        for (uint16_t index = 0; index < DPDK_QUEUE_SIZE; index++) {
            uint16_t buf_count = rte_eth_rx_burst(port_id, index, bufs, DPDK_BUF_SIZE);
            if (buf_count == 0) {
                continue;
            }
            for (uint16_t buf_index = 0; buf_index < buf_count; buf_index++) {
                eth_hdr = rte_pktmbuf_mtod(bufs[buf_index], struct rte_ether_hdr *);
                if (eth_hdr == NULL) {
                    printf("eth_hdr is null\n");
                    continue;
                }
                if (eth_hdr->ether_type != rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4)) {
                    continue;
                }
                // get ether net proto 
                struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(bufs[buf_index], struct rte_ipv4_hdr*, sizeof(struct rte_ether_hdr));
                if (ipv4_hdr == NULL) {
                    continue;
                }
                // printf("receive packet, protocol: %d\n", ipv4_hdr->next_proto_id);
                if (ipv4_hdr->next_proto_id == IPPROTO_ICMP) {
                } else if (ipv4_hdr->next_proto_id == IPPROTO_UDP) {
                    struct rte_udp_hdr *udp_hdr = (struct rte_udp_hdr*)(ipv4_hdr + 1);
                    // check udp header
                    if (udp_hdr == NULL) {
                        printf("udp_hdr is null\n");
                        continue;
                    }
                    uint16_t dst_port = ntohs(udp_hdr->dst_port);
                    if (dst_port != 12345)
                        continue;
                    // get data length
                    uint16_t data_length = ntohs(udp_hdr->dgram_len);
                    *(char *)(udp_hdr + 1 + data_length) = '\0';
                    // get src addr
                    struct in_addr src_addr;
                    src_addr.s_addr = ipv4_hdr->src_addr;
                    // get dst addr
                    struct in_addr dst_addr;
                    dst_addr.s_addr = ipv4_hdr->dst_addr;
                    printf("recv: %s:%d -> %s:%d, data: %s \n", inet_ntoa(src_addr), ntohs(udp_hdr->src_port), inet_ntoa(dst_addr), 
                        ntohs(udp_hdr->dst_port), (char *)(udp_hdr + 1));
                }
                // check if protocol is ipv4
                rte_pktmbuf_free(bufs[buf_index]);
            }
        }
    }
    return 0;
}

// port init
int port_int(uint16_t port_id, struct rte_mempool *pool) {
    // check if port is valid
    if (!rte_eth_dev_is_valid_port(port_id)) {
        rte_exit(EXIT_FAILURE, "port %d is invalid\n", port_id);
    }
	// init port config
	struct rte_eth_conf conf = {
		.txmode = {
			.offloads =
				RTE_ETH_TX_OFFLOAD_VLAN_INSERT |
				RTE_ETH_TX_OFFLOAD_UDP_CKSUM   |
				RTE_ETH_TX_OFFLOAD_TCP_CKSUM   |
				RTE_ETH_TX_OFFLOAD_TCP_TSO,
		},
	};
    // get device info 
    struct rte_eth_dev_info info;
    if (rte_eth_dev_info_get(port_id, &info) != 0) {
        rte_exit(EXIT_FAILURE, "Cannot get device info\n");
    }
    // configure the Ethernet device
    if (rte_eth_dev_configure(port_id, DPDK_QUEUE_SIZE, DPDK_QUEUE_SIZE, &conf) != 0) {
        rte_exit(EXIT_FAILURE, "Cannot configure device\n");
    }
    // set rx tx queue
    for (uint16_t index = 0; index < DPDK_QUEUE_SIZE; index++) {
        if(rte_eth_rx_queue_setup(port_id, index, DPDK_DESC_COUNT, 
            rte_eth_dev_socket_id(port_id), NULL, pool) != 0) {
            rte_exit(EXIT_FAILURE, "Cannot setup rx queue\n");
        } 
        if (rte_eth_tx_queue_setup(port_id, index, DPDK_DESC_COUNT, rte_eth_dev_socket_id(port_id), NULL) != 0) {
            rte_exit(EXIT_FAILURE, "Cannot setup tx queue\n");
        }
    }
    // start device 
    if (rte_eth_dev_start(port_id) != 0) {
        rte_exit(EXIT_FAILURE, "Cannot start device\n");
    }
    // enable promiscuous mode
    if (rte_eth_promiscuous_enable(port_id) != 0) {
        rte_exit(EXIT_FAILURE, "Cannot enable promiscuous mode\n");
    }
    // init port success
    printf("init port %d success\n", port_id);
    return 0;
}

// set flow filter
int set_flow_filter(uint16_t port_id) {
    // set ingress attribute 
    struct rte_flow_attr flow_attr;
    flow_attr.ingress = 1;
    // set target item 
    struct rte_flow_item ipv4_rule_item[DROP_PATTERN_COUNT];
    struct rte_flow_item_ipv4 ipv4_flow_dst_addr;
    struct rte_flow_item_ipv4 ipv4_flow_dst_mask;
    ipv4_flow_dst_addr.hdr.dst_addr = htonl(DROP_DST_ADDR);
    ipv4_flow_dst_mask.hdr.dst_addr = htonl(DROP_DST_MASK);
    ipv4_rule_item[0].type = RTE_FLOW_ITEM_TYPE_ETH;
    ipv4_rule_item[1].type = RTE_FLOW_ITEM_TYPE_IPV4;
    ipv4_rule_item[1].spec = &ipv4_flow_dst_addr;
    ipv4_rule_item[1].mask = &ipv4_flow_dst_mask;
    ipv4_rule_item[2].type = RTE_FLOW_ITEM_TYPE_END;
    // set flow action
    struct rte_flow_action flow_action[DROP_PATTERN_COUNT];
    flow_action[0].type = RTE_FLOW_ACTION_TYPE_DROP;
    flow_action[1].type = RTE_FLOW_ACTION_TYPE_END;
    // check if rule is valid
    struct rte_flow_error flow_error;
    if (rte_flow_validate(port_id, &flow_attr, ipv4_rule_item, flow_action, &flow_error) == 0) {
        rte_exit(EXIT_FAILURE, "check flow rule invalid\n");
    }
    // set rule 
    if (rte_flow_create(port_id, &flow_attr, ipv4_rule_item, flow_action, &flow_error) != 0) {
        rte_exit(EXIT_FAILURE, "set flow rule failed\n");
    }
    printf("set flow rule success\n");
    return 0;
}

// set flow action 
int main(int argc, char **argv) {
    // init dpdk enviroment
    if (rte_eal_init(argc, argv) < 0) {
        rte_exit(EXIT_FAILURE, "init dpdk enviroment failed\n");
    }
    // check device count 
    uint16_t device_count = rte_eth_dev_count_avail();
    if (device_count == 0) {
        rte_exit(EXIT_FAILURE, "no device found\n");
    } else if (device_count != 1) {
        rte_exit(EXIT_FAILURE, "only support one device\n");
    }
    // create mempool
    struct rte_mempool *pool = rte_pktmbuf_pool_create("pool", DPDK_MBUFS_SIZE, 128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (pool == NULL) {
        rte_exit(EXIT_FAILURE, "create mempool failed\n");
    }
    uint16_t port_id;
    RTE_ETH_FOREACH_DEV(port_id) {
        // port init
        port_int(port_id, pool);
        // set flow filter
        set_flow_filter(port_id);
        // start main loop
        main_loop(port_id);
    }

    // clean dpdk enviroment
    rte_eal_cleanup();
    return 0;
}