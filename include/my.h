/*
** EPITECH PROJECT, 2019
** arp
** File description:
** my
*/


#ifndef MY_H_
#define MY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <sys/socket.h>
#include <net/ethernet.h> 
#include <stdint.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <linux/types.h>
#define BROADCAST (uint8_t[6]){0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

   typedef struct ethernet_header_s
    {
        uint8_t dest_mac_addr[6];
        uint8_t src_mac_addr[6];
        uint16_t type;
    }ethernet_t;

    typedef struct arp_header_s
    {
        uint16_t hardware_type;
        uint16_t protocol_type;
        uint8_t hardware_len;
        uint8_t protocol_len;
        uint16_t opcode;
        uint8_t sender_mac_addr[6];
        uint8_t sender_ip_addr[4];
        uint8_t target_mac_addr[6];
        uint8_t target_ip_addr[4];
    }arp_t;

typedef struct info_s
    {
        char *target_ip;
        char *sender_ip;
        char *interface;
        int *my_mac_addr;
        int *victim_mac_addr;
        int socket;
    }info_t;

void do_magic(struct sockaddr_ll *origin, info_t *info);
void do_all(char **av, info_t *info);
arp_t *create_arp(info_t *info, const uint8_t *dest_mac_addr);
ethernet_t *create_ethernet(info_t *info,
    const uint8_t *dest_mac_addr, arp_t *arp);
void spoof_victim(struct sockaddr_ll *origin, uint8_t *victim_mac_addr,
    info_t *info);
void victim_mac_address(info_t *info, struct sockaddr_ll *origin);
struct all_t *create_arpp(info_t *info, const uint8_t *dest_mac_addr);


#endif /* !MY_H_ */
