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

/*
    Documentation d'écriture dans le bus CAN :

    123# : Intéragir avec les lumières de la voiture :

    Trame      Action
    -----------------
    123 00 00  Tout éteindre
    123 00 01  Allumer les clignotants gauches
    123 00 02  Allumer les clignotants droits
    123 00 03  Allumer les warnings
    123 01 00  Feux de position
    123 02 00  Feu de route

    321# : Intéragir avec le volant et les pédales de la voiture

    Trame          Plage XX     Action
    -----------------------------------
    321 00 00 XX   01 - 64     Volant à gauche
    321 00 00 XX   FF - 9C     Volant à droite
    321 00 XX 00   00 - 64     Appui sur le frein
    321 XX 00 00   00 - 64     Appui sur l'accélérateur
*/

// === Définition des fonctions ===

// CAN bus
int init_can(int *p_s, struct sockaddr_can *p_addr, struct ifreq *p_ifr);
int close_can(int s);
int conf_can_id_and_data_size(struct can_frame *p_frame, int can_id, int data_size);
int inject_data(struct can_frame *p_frame, int data_size, int data[]);
int send_data_to_frame(int *p_s, struct can_frame *p_frame);

// Gestion des feux
int allumer_feux_de_route(int *p_s, struct can_frame *p_frame);
int allumer_feux_de_croisement(int *p_s, struct can_frame *p_frame);
int eteindre_feux(int *p_s, struct can_frame *p_frame);

// Gestion des clignotants
int allumer_clignotants_droits(int *p_s, struct can_frame *p_frame);
int allumer_clignotants_gauches(int *p_s, struct can_frame *p_frame);
int allumer_feux_de_detresse(int *p_s, struct can_frame *p_frame);
int eteindre_clignotants(int *p_s, struct can_frame *p_frame);

// Gestion de la vitesse
int set_accelerateur(int *p_s, struct can_frame *p_frame, int accelerateur_pourcentage);
int set_frein(int *p_s, struct can_frame *p_frame, int frein_pourcentage);

// Gestion de la direction
int set_direction(int *p_s, struct can_frame *p_frame, int direction_pourcentage);


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

    // Init can
    if(init_can(p_s, p_addr, p_ifr) != 0) printf("Erreur lors de l'initialisation du CAN\r");

	printf("CAN Sockets Demo\r\n");

    // Tests des feux
    // Allumer les feux de route
    if (allumer_feux_de_route(p_s, p_frame) != 0) printf("Erreur lors de l'allumage des feux de route\r");
    sleep(1);

    // Allumer les feux de croisement
    if (allumer_feux_de_croisement(p_s, p_frame) != 0) printf("Erreur lors de l'allumage des feux de croisement\r");
    sleep(1);

    // Eteindre les feux
    if (eteindre_feux(p_s, p_frame) != 0) printf("Erreur lors de l'extinction des feux\r");
    sleep(1);

    // Tests des clignotants
    // Allumer les clignotants droits
    if (allumer_clignotants_droits(p_s, p_frame) != 0) printf("Erreur lors de l'allumage des clignotants droits\r");
    sleep(1);

    // Allumer les clignotants gauches
    if (allumer_clignotants_gauches(p_s, p_frame) != 0) printf("Erreur lors de l'allumage des clignotants gauches\r");
    sleep(1);

    // Etteindre les clignotants
    if (eteindre_clignotants(p_s, p_frame) != 0) printf("Erreur lors de l'extinction des clignotants\r");
    sleep(1);

    // Allumer les feux de détresse
    if (allumer_feux_de_detresse(p_s, p_frame) != 0) printf("Erreur lors de l'allumage des feux de détresse\r");
    sleep(1);

    // Eteindre les clignotants
    if (eteindre_clignotants(p_s, p_frame) != 0) printf("Erreur lors de l'extinction des clignotants\r");
    sleep(1);

    // Tests de la direction
    // Volant à 50%
    if (set_direction(p_s, p_frame, 50) != 0) printf("Erreur lors du changement de direction\r");
    sleep(1);

    // Tests de la vitesse
    // Accélérateur à 50%
    if (set_accelerateur(p_s, p_frame, 50) != 0) printf("Erreur lors du changement de vitesse\r");
    sleep(5);

    // Accélérateur à 0%
    if (set_accelerateur(p_s, p_frame, 0) != 0) printf("Erreur lors du changement de vitesse\r");
    sleep(1);

    // Frein à 50%
    if (set_frein(p_s, p_frame, 50) != 0) printf("Erreur lors du changement de vitesse\r");
    sleep(2);

    // Frein à 0%
    if (set_frein(p_s, p_frame, 0) != 0) printf("Erreur lors du changement de vitesse\r");

    // Close can
    if(close_can(s) != 0) printf("Erreur lors de la fermeture du CAN\r");

	return 0;
}

// Code des fonction (// TODO)
int allumer_feux_de_route(int *p_s, struct can_frame *p_frame)
{
    // Init can
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 02 00 to create this frame : 123#0200
    int data[2] = {0x02, 0x00};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int allumer_feux_de_croisement(int *p_s, struct can_frame *p_frame)
{
    // Init can
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 01 00 to create this frame : 123#0100
    int data[2] = {0x01, 0x00};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int eteindre_feux(int *p_s, struct can_frame *p_frame)
{
    // Init CAN
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 00 00 to create this frame : 123#0000
    int data[2] = {0x00, 0x00};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int allumer_clignotants_droits(int *p_s, struct can_frame *p_frame)
{
    // Init can
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 00 02 to create this frame : 123#0002
    int data[2] = {0x00, 0x02};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int allumer_clignotants_gauches(int *p_s, struct can_frame *p_frame)
{
    // Init can
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 00 01 to create this frame : 123#0001
    int data[2] = {0x00, 0x01};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int allumer_feux_de_detresse(int *p_s, struct can_frame *p_frame)
{
    // Init can
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 00 03 to create this frame : 123#0004
    int data[2] = {0x00, 0x03};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int eteindre_clignotants(int *p_s, struct can_frame *p_frame)
{
    // Init can
    if (conf_can_id_and_data_size(p_frame, 0x123, 2) != 0) return 1;

    // We want to send 00 00 to create this frame : 123#0000
    int data[2] = {0x00, 0x00};
    if (inject_data(p_frame, 2, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int set_accelerateur(int *p_s, struct can_frame *p_frame, int accelerateur_pourcentage)
{
    // Check if the percentage value is within the valid range (0-100)
    if (accelerateur_pourcentage < 0 || accelerateur_pourcentage > 100) {
        printf("Invalid accelerateur_pourcentage value, must be between 0 and 100.\r");
        return 1;
    }

    // Initialize the CAN frame
    if (conf_can_id_and_data_size(p_frame, 0x321, 3) != 0) return 1;

    // We want to send XX 00 00 to create this frame : 321#XX0000
    int data[3] = {accelerateur_pourcentage, 0x00, 0x00};

    if (inject_data(p_frame, 3, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}

int set_frein(int *p_s, struct can_frame *p_frame, int frein_pourcentage)
{
    // Check if the percentage value is within the valid range (0-100)
    if (frein_pourcentage < 0 || frein_pourcentage > 100) {
        printf("Invalid frein_pourcentage value, must be between 0 and 100.\r");
        return 1;
    }

    // Initialize the CAN frame
    if (conf_can_id_and_data_size(p_frame, 0x321, 3) != 0) return 1;

    // We want to send 00 XX 00 to create this frame : 321#00XX00
    int data[3] = {0x00, frein_pourcentage, 0x00};

    if (inject_data(p_frame, 3, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
}


int set_direction(int *p_s, struct can_frame *p_frame, int direction_pourcentage)
{
    // Check if the percentage value is within the valid range (-100-100)
    if (direction_pourcentage < -100 || direction_pourcentage > 100) {
        printf("Invalid direction_pourcentage value, must be between -100 and 100.\r");
        return 1;
    }

    /*
        Range :
        Left : 0x01 to 0x64
        Right : 0xFF to 0x9C (In a decrescent order)
    */

    // Initialize the CAN frame
    if (conf_can_id_and_data_size(p_frame, 0x321, 3) != 0) return 1;

    // We want to send 00 00 XX to create this frame : 321#0000XX
    int data[3] = {0x00, 0x00, direction_pourcentage};
    if (inject_data(p_frame, 3, data) != 0) return 1;

    // Send data to the can
    if (send_data_to_frame(p_s, p_frame) != 0) return 1;

    return 0;
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

int conf_can_id_and_data_size(struct can_frame *p_frame, int can_id, int data_size)
{
    p_frame->can_id = can_id;
    p_frame->can_dlc = data_size;

    return 0;
}

// Function to put an array of data in the frame depending on the size of the array
int inject_data(struct can_frame *p_frame, int data_size, int data[])
{
    int i;

    for (i = 0; i < data_size; i++) {
        p_frame->data[i] = data[i];
    }

    return 0;
}

int send_data_to_frame(int *p_s, struct can_frame *p_frame)
{
    if (write(*p_s, p_frame, sizeof(*p_frame)) != sizeof(*p_frame)) {
        perror("Write");
        return 1;
    }

    return 0;
}