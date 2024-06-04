#include <rte_arp.h>
#include <rte_dev.h>
#include <rte_eal.h>
#include <rte_ether.h>
#include <rte_flow.h>
#include <rte_ip.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_ethdev.h>
#include <rte_common.h>
#include <rte_memcpy.h>
#include <rte_mempool.h>
#include <rte_mbuf_core.h>

#include <stdbool.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MBUF_SIZE 8191
#define CACHE_SIZE 128
#define PRIVATE_SIZE RTE_MBUF_PRIV_ALIGN*2
#define RECV_MBUF 1

const uint16_t g_dpdk_port = 0;
const struct rte_eth_conf g_eth_conf = {
    .rxmode = {

    },
    .txmode = {

    }
};

/*
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute
       valid_lft forever preferred_lft forever
2: ens160: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
    link/ether 00:0c:29:04:4d:d3 brd ff:ff:ff:ff:ff:ff
    altname enp3s0
    inet 192.168.121.171/24 brd 192.168.121.255 scope global dynamic noprefixroute ens160
       valid_lft 43186sec preferred_lft 43186sec
    inet6 fe80::e3a3:62d6:811:c372/64 scope link noprefixroute
       valid_lft forever preferred_lft forever
3: ens192: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
    link/ether 00:0c:29:04:4d:dd brd ff:ff:ff:ff:ff:ff
    altname enp11s0
    inet 192.168.121.181/24 brd 192.168.121.255 scope global dynamic noprefixroute ens192
       valid_lft 43186sec preferred_lft 43186sec
    inet6 fe80::4da7:a788:52da:5af5/64 scope link noprefixroute
       valid_lft forever preferred_lft forever
4: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 00:0c:29:04:4d:c9 brd ff:ff:ff:ff:ff:ff
    altname enp2s1
    inet 192.168.121.161/24 brd 192.168.121.255 scope global dynamic noprefixroute ens33
       valid_lft 43186sec preferred_lft 43186sec
    inet6 fe80::eecb:50cd:113e:4b03/64 scope link noprefixroute
       valid_lft forever preferred_lft forever
*/

// define local mac addr
static struct rte_ether_addr g_local_mac_addr = {
    .addr_bytes = {0},
};

// define broadcast mac addr
const struct rte_ether_addr g_broadcast_mac_addr = {
    .addr_bytes = {0xff, 0xff, 0xff, 0xff,0xff, 0xff},
};

// define arp request unknown mac addr
const struct rte_ether_addr g_unknown_mac_addr = {
    .addr_bytes = {0},
};

// define local ip addr
const rte_be32_t g_local_ip_addr = RTE_IPV4(192, 168, 121, 220);


// print_mac_addr print mac addr
void print_mac_addr(const struct rte_ether_addr *mac_addr) {
    printf("%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8 "",
           mac_addr->addr_bytes[0], mac_addr->addr_bytes[1], mac_addr->addr_bytes[2],
           mac_addr->addr_bytes[3], mac_addr->addr_bytes[4], mac_addr->addr_bytes[5]);
}

// get_print_addr_from_be get format ipv4addr 
int get_print_addr_from_be(rte_be32_t addr, char *format_addr) {
    // 0x101a8c0 -> 192.168.1.1
    sprintf(format_addr, "%02d.%02d.%02d.%02d", addr, addr >> 2, addr >> 4, addr >> 6);
    return 0;
}

// send_arp_msg
int send_arp_msg(struct rte_ether_addr src_mac_addr, rte_be32_t src_ip_addr,
    struct rte_ether_addr dst_mac_addr, rte_be32_t dst_ip_addr, 
    rte_be16_t op_code, uint8_t *msg) {
    if (msg == NULL)
        rte_exit(EXIT_FAILURE, "no free buffer");
    // offset arp header 
    struct rte_arp_hdr *arp_header = (struct rte_arp_hdr *)(msg + sizeof(struct rte_ether_hdr));
    arp_header->arp_data.arp_sha = src_mac_addr;
    arp_header->arp_data.arp_sip = rte_cpu_to_be_32(src_ip_addr);
    arp_header->arp_data.arp_tha = dst_mac_addr;
    arp_header->arp_data.arp_tip = rte_cpu_to_be_32(dst_ip_addr);
    arp_header->arp_hardware = rte_cpu_to_be_16(RTE_ARP_HRD_ETHER);
    arp_header->arp_protocol = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);
    arp_header->arp_opcode = rte_cpu_to_be_16(op_code);
    arp_header->arp_hlen = RTE_ETHER_ADDR_LEN;
    arp_header->arp_plen = sizeof(rte_be32_t);
    return 0;
}

// send_eth_msg send ether msg
int send_eth_msg(struct rte_ether_addr src_mac_addr, struct rte_ether_addr dst_mac_addr,
    const rte_be16_t eth_type, uint8_t *msg) {
    if (msg == NULL)
        rte_exit(EXIT_FAILURE, "no free buffer \n");
    struct rte_ether_hdr *ether_hdr = (struct rte_ether_hdr *)msg;
    ether_hdr->src_addr = src_mac_addr;
    ether_hdr->dst_addr = dst_mac_addr;
    ether_hdr->ether_type = rte_cpu_to_be_16(eth_type);
    // print mac addr
    printf("send eth: ");
    print_mac_addr(&src_mac_addr);
    printf(" -> ");
    print_mac_addr(&dst_mac_addr);
    printf("\n");
    return 0;
}

int init_port(uint16_t port_id, struct rte_mempool *mempool) {
    // get device info 
    struct rte_eth_dev_info dev_info = {};
    if (rte_eth_dev_info_get(port_id, &dev_info) != 0) {
        rte_exit(EXIT_FAILURE, "get device info failed");
    }
    // bind memory to recv device
    struct rte_eth_conf dev_conf = g_eth_conf;
    if (rte_eth_dev_configure(port_id, 1, 1, &dev_conf) != 0) {
        rte_exit(EXIT_FAILURE, "config device failed");
    }
    // set device rx port config
    if (rte_eth_rx_queue_setup(port_id, 0, 512, rte_eth_dev_socket_id(port_id), 
        NULL, mempool) != 0) {
        rte_exit(EXIT_FAILURE, "config rx queue failed");
    }
    struct rte_eth_txconf tx_conf = dev_info.default_txconf;
    // set device tx port config
    if (rte_eth_tx_queue_setup(port_id, 0, 512, rte_eth_dev_socket_id(port_id), &tx_conf) != 0) {
        rte_exit(EXIT_FAILURE, "config tx queue failed");
    }
    // get device info 
    if (rte_eth_macaddr_get(g_dpdk_port, &g_local_mac_addr) != 0) {
        rte_exit(EXIT_FAILURE, "get device mac addr failed");
    }
    // enter promiscuous mode
    if (rte_eth_promiscuous_enable(port_id) != 0) {
        rte_exit(EXIT_FAILURE, "enter promiscuous failed");
    }
    // start device 
    if (rte_eth_dev_start(port_id) != 0) {
        rte_exit(EXIT_FAILURE, "start device failed");
    }
    print_mac_addr(&g_local_mac_addr);
    printf("init device success \n");
    return 0;
}

// recv_dev_buffer read buffer from pool 
void recv_dev_buffer(uint16_t port_id, struct rte_mempool *pool) {
    // recv buffer from pool
    struct rte_mbuf *recv_mbufs[RECV_MBUF];
    while (true) {
        uint16_t pkt_count = rte_eth_rx_burst(g_dpdk_port, 0, recv_mbufs, RECV_MBUF);
        if (pkt_count < 0) {
            rte_exit(EXIT_FAILURE, "read buf failed");
        }
        // parse packet
        for (int index = 0; index < pkt_count; index++) {
            struct rte_mbuf *recv_mbuf = recv_mbufs[index];
            struct rte_ether_hdr *eth_hdr = (struct rte_ether_hdr *)rte_pktmbuf_mtod(recv_mbuf, struct rte_ether_hdr*);
            // check if addr is broadcast or local
            if (memcmp(&eth_hdr->dst_addr, &g_local_mac_addr, RTE_ETHER_ADDR_LEN) != 0 &&
                memcmp(&eth_hdr->dst_addr, &g_broadcast_mac_addr, RTE_ETHER_ADDR_LEN) != 0) {
                continue;
            }
            // get protocol
            uint16_t protocol = rte_be_to_cpu_16(eth_hdr->ether_type);
            // check if is ip protocol
            if (protocol == RTE_ETHER_TYPE_IPV4) {
                // parse addr
                struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(recv_mbuf, struct rte_ipv4_hdr*, 
                    sizeof(struct rte_ipv4_hdr));
                if (ipv4_hdr == NULL)
                    continue;
                // get src addr and dst addr
                char src_addr_format[32] = {0};
                struct in_addr src_addr = {
                    .s_addr = ipv4_hdr->src_addr,
                };
                char dst_addr_format[32] = {0};
                struct in_addr dst_addr = {
                    .s_addr = ipv4_hdr->dst_addr,
                };
                inet_ntop(AF_INET, &src_addr, src_addr_format, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &dst_addr, dst_addr_format, INET_ADDRSTRLEN);
                // printf("ipv4: %s -> %s \n", src_addr_format, dst_addr_format);
                // check if proto is udp
                if (ipv4_hdr->next_proto_id == IPPROTO_UDP) {
                    

                } else if (ipv4_hdr->next_proto_id == IPPROTO_TCP) {

                }

            } else if (protocol == RTE_ETHER_TYPE_ARP) {
                // parse arp message
                struct rte_arp_hdr *arp_header = rte_pktmbuf_mtod_offset(recv_mbuf, struct rte_arp_hdr*, 
                    sizeof(struct rte_ether_hdr));
                if (arp_header == NULL)
                    continue;
                // get arp request ip 
                rte_be32_t src_ip_addr = rte_be_to_cpu_32(arp_header->arp_data.arp_sip);
                rte_be32_t dst_ip_addr = rte_be_to_cpu_32(arp_header->arp_data.arp_tip);
                // check if is arp request
                if (rte_be_to_cpu_16(arp_header->arp_opcode) == RTE_ARP_OP_REQUEST && 
                    dst_ip_addr == g_local_ip_addr) {
                    printf("recv arp request \n");
                    struct rte_mbuf *send_mbuf = rte_pktmbuf_alloc(pool);
                    // notice: dont use rte_pktmbuf_mtod_offset to add arp header
                    // because this func use mbuf->buf_addr, when send packet, this member not set yet
                    // but when recv packet, member will be set
                    uint8_t *msg = rte_pktmbuf_mtod(send_mbuf, uint8_t *);
                    // build ether message
                    if (send_eth_msg(g_local_mac_addr, arp_header->arp_data.arp_sha, 
                        RTE_ETHER_TYPE_ARP, msg) != 0)
                        rte_exit(EXIT_FAILURE, "create send ether msg failed \n");
                    // build arp message
                    if (send_arp_msg(g_local_mac_addr, g_local_ip_addr, 
                        arp_header->arp_data.arp_sha, src_ip_addr, 
                        RTE_ARP_OP_REPLY, msg) != 0)
                        rte_exit(EXIT_FAILURE, "create arp reply msg failed \n");
                    // set arp length
                    uint16_t total_length = sizeof(struct rte_ether_hdr) + sizeof(struct rte_arp_hdr);
                    send_mbuf->pkt_len = total_length;
                    send_mbuf->data_len = total_length;
                    // send eth tx burst
                    if (rte_eth_tx_burst(g_dpdk_port, 0, &send_mbuf, 1) == 0)
                        rte_exit(EXIT_FAILURE, "send arp reply failed \n");
                    // free memory
                    rte_pktmbuf_free(send_mbuf);
                    printf("send arp response success \n");
                }
                
            }
            rte_pktmbuf_free(recv_mbuf);
        }
    }
}


int main(int argc, char **argv) {
    // int dpdk env
    if (rte_eal_init(argc, argv) == -1) {
        rte_exit(EXIT_FAILURE, "init dpdk env failed\n");
    }
    // check if has at least device
    if (rte_eth_dev_count_avail() <= 0) {
        rte_exit(EXIT_FAILURE, "need at least one device");
    }
    // create dpdk mempool
    struct rte_mempool *mempool = rte_pktmbuf_pool_create("arp_pool", MBUF_SIZE, CACHE_SIZE, 
        0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mempool == NULL) {
        rte_exit(EXIT_FAILURE, "create memory pool failed");
    }
    // init dpdk port
    if (init_port(g_dpdk_port, mempool) != 0) {
        rte_exit(EXIT_FAILURE, "init port failed");
    }
    // recv buffer 
    recv_dev_buffer(g_dpdk_port, mempool);
    // clean dpdk
    rte_eal_cleanup();
}