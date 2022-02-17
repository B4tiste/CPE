/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */


#ifndef __SERVER_H__
#define __SERVER_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

// Structure de données pour les calculs : op, nb1, nb2
typedef struct calcul_cmd {
    char op;
    int nb1;
    int nb2;
} calcul_cmd;


/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd);
int recois_numeros_calcule(int socketfd);

#endif
