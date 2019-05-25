/*
** EPITECH PROJECT, 2019
** arp
** File description:
** main
*/

#include "../include/my.h"

void do_magic(struct sockaddr_ll *origin, info_t *info)
{
   arp_t *arp = create_arp(info, BROADCAST);
   ethernet_t *eth = create_ethernet(info, BROADCAST, arp);
   origin->sll_ifindex = if_nametoindex(info->interface);
   sendto(info->socket, eth, 42, 0,(const struct sockaddr *)origin, sizeof(*origin));
   victim_mac_address(info, origin);
}

void do_all(char **av, info_t *info)
{
   struct ifreq me;
   info->sender_ip = strdup(av[1]);
   info->target_ip = strdup(av[2]);
   info->interface = strdup(av[3]);
   info->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
   info->my_mac_addr = malloc(sizeof(int) * 6);
   memset(&me, 0, sizeof(me));
   strncpy(me.ifr_name, info->interface, IFNAMSIZ);
   ioctl(info->socket, SIOCGIFHWADDR, &me);
   memcpy(info->my_mac_addr, me.ifr_hwaddr.sa_data, sizeof(int) * 6);
}

void print_cast(char **av)
{
    struct ifreq me;
    int i = 0;
    info_t *info = malloc(sizeof(info_t));
    info->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    info->sender_ip = strdup(av[1]);
    info->target_ip = strdup(av[2]);
    info->interface = strdup(av[3]);
    info->my_mac_addr = malloc(sizeof(int) * 6);
    memset(&me, 0, sizeof(me));
    strncpy(me.ifr_name, info->interface, IFNAMSIZ);
    ioctl(info->socket, SIOCGIFHWADDR, &me);
    memcpy(info->my_mac_addr, me.ifr_hwaddr.sa_data, sizeof(int) * 6);
    arp_t *arp = create_arp(info, BROADCAST);
    while( i < 6) { 
        printf("%02x ", (unsigned char) BROADCAST[1]);
        i++;
    }
    printf("%02x ", (unsigned char) arp->hardware_type);
}

int main(int ac, char **av)
{
   info_t *info = malloc(sizeof(info_t));
   struct sockaddr_ll origin;
   if (ac < 4 || ac > 6)
       exit(84);
   if (ac == 5) {
       if (!strcmp(av[4], "--printBroadcast"))
           print_cast(av);
       else
           exit(84);
   }
   if (ac == 6) {
       if (!strcmp(av[4], "--printSpoof"))
           exit(0);
       else
           exit(84);
   }
   do_all(av, info);
   memset(&origin, 0, sizeof(origin));
   do_magic(&origin, info);
   return (0);
}