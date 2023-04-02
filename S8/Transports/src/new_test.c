#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

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
    321 XX 00 00   01 - 64     Volant à gauche
    321 XX 00 00   FF - 9C     Volant à droite
    321 00 XX 00   00 - 64     Appui sur le frein
    321 00 00 XX   00 - 64     Appui sur l'accélérateur<
*/

// === Définition des fonctions ===

// Init CAN bus

// Gestion des feux
/**
 * Permet de d'allumer ou d'éteindre les phares
 * @param etat : true pour allumer, false pour éteindre
 * @return void
 */
void set_feux_de_route(bool etat);
void set_feux_de_croisement(bool etat);

// Gestion des clignotants
/**
 * Permet d'allumer ou d'éteindre les clignotants
 * @param etat : true pour allumer, false pour éteindre
 * @return void
*/
void toggle_clignotant_droit(bool etat);
void toggle_clignotant_gauche(bool etat);

// Gestion de la vitesse
/**
 * Permet de régler la vitesse de la voiture
 * @param vitesse : la vitesse à laquelle on veut que la voiture roule
 * @return void
 */
void set_vitesse(int vitesse_pourcentage);

// Gestion de la direction
/**
 * Permet de régler la direction de la voiture
 * @param direction : la direction à laquelle on veut que la voiture tourne
 * @return void
 */
void set_direction(int direction_pourcentage);


int main()
{
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Demo\r\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "vcan0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	frame.can_id = 0x123;
	frame.can_dlc = 2;
	// We want to send 00 01 to create this frame : 123#0001
    frame.data[0] = 0x00;
    frame.data[1] = 0x00;

	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}

// Code des fonction (// TODO)
void set_feux_de_route(bool etat)
{
    // TODO
}

void set_feux_de_croisement(bool etat)
{
    // TODO
}

void toggle_clignotant_droit(bool etat)
{
    // TODO
}

void toggle_clignotant_gauche(bool etat)
{
    // TODO
}

void set_vitesse(int vitesse_pourcentage)
{
    // TODO
}

void set_direction(int direction_pourcentage)
{
    // TODO
}