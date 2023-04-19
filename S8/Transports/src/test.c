#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <time.h>

int init_can(int *p_s, struct sockaddr_can *p_addr, struct ifreq *p_ifr);
int close_can(int s);


int main()
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    // Pointers
    int *p_s = &s;
    struct sockaddr_can *p_addr = &addr;
    struct ifreq *p_ifr = &ifr;
    struct can_frame *p_frame = &frame;

    if(init_can(p_s, p_addr, p_ifr) != 0) printf("Erreur lors de l'initialisation du CAN\r");

    

}

int init_can(int *p_s, struct sockaddr_can *p_addr, struct ifreq *p_ifr)
{
    if ((*p_s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(p_ifr->ifr_name, "vcan0" );
    ioctl(*p_s, SIOCGIFINDEX, p_ifr);

    memset(p_addr, 0, sizeof(*p_addr));
    p_addr->can_family = AF_CAN;
    p_addr->can_ifindex = p_ifr->ifr_ifindex;

    if (bind(*p_s, (struct sockaddr *)p_addr, sizeof(*p_addr)) < 0) {
        perror("Bind");
        return 1;
    }

    return 0;
}

int close_can(int s)
{
    if (close(s) < 0) {
        perror("Close");
        return 1;
    }

    return 0;
}