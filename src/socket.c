/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"

arp_t *create_arp(info_t *info, const uint8_t *dest_mac_addr)
{
    arp_t *arp = malloc(sizeof(arp_t));

    arp->hardware_type = htons(1);
    arp->protocol_type = htons(ETH_P_IP);
    arp->hardware_len = 6;
    arp->protocol_len = 4;
    arp->opcode = htons(1);
    memcpy(&arp->sender_mac_addr, info->my_mac_addr, sizeof(uint8_t) * 6);
    memcpy(&arp->target_mac_addr, dest_mac_addr, sizeof(uint8_t) * 6);
    inet_pton(AF_INET, info->sender_ip, arp->sender_ip_addr);
    inet_pton(AF_INET, info->target_ip, arp->target_ip_addr);
    return (arp);
}

ethernet_t *create_ethernet(info_t *info,
    const uint8_t *dest_mac_addr, arp_t *arp)
{
    ethernet_t *eth = malloc(sizeof(uint8_t) * 65535);
    memcpy(&eth->dest_mac_addr, dest_mac_addr, sizeof(uint8_t) * 6);
    memcpy(&eth->src_mac_addr, info->my_mac_addr, sizeof(uint8_t) * 6);
    memcpy(&eth->type, (uint8_t[2]){ETH_P_ARP / 256, ETH_P_ARP % 256},
    sizeof(uint8_t) * 2);
    memcpy((uint8_t *)eth + 14, arp, sizeof(uint8_t) * 28);
    return (eth);

}