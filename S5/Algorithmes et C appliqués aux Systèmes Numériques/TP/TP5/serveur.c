/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "serveur.h"

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{
    int data_size = write(client_socket_fd, (void *)data, strlen(data));

    if (data_size < 0)
    {
        perror("erreur ecriture");
        return (EXIT_FAILURE);
    }
    return (0);
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd)
{
    struct sockaddr_in client_addr;
    char data[1024];

    unsigned int client_addr_len = sizeof(client_addr);

    // nouvelle connection de client
    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
        perror("accept");
        return (EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lecture de données envoyées par un client
    int data_size = read(client_socket_fd, (void *)data, sizeof(data));

    if (data_size < 0)
    {
        perror("erreur lecture");
        return (EXIT_FAILURE);
    }

    /*
     * extraire le code des données envoyées par le client.
     * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
     */
    printf("Message recu: %s\n", data);
    char code[10];
    sscanf(data, "%s:", code);

    // Si le message commence par le mot: 'message:'
    if (strcmp(code, "message:") == 0)
    {
        // Demander et répondre au client
        memset(data, 0, sizeof(data)); // Clear data
        printf("Veuillez entrer votre message de reponse: "); 
        scanf("%s", data); // Récupérer le message de l'utilisateur
        printf("Vous avez entre: %s\n", data); // Afficher le message de l'utilisateur
        renvoie_message(client_socket_fd, data); // Envoyer le message au client
    }

    // fermer le socket
    close(socketfd);
    return (0);
}

int recois_numeros_calcule(int socketfd)
{
    struct sockaddr_in client_addr;
    char data[1024];

    unsigned int client_addr_len = sizeof(client_addr);

    // nouvelle connection de client
    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
        // printf("a\n");
        perror("accept");
        return (EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lecture de données envoyées par un client
    int data_size = read(client_socket_fd, (void *)data, sizeof(data));

    if (data_size < 0)
    {
        perror("erreur lecture");
        return (EXIT_FAILURE);
    }

    /*
     * extraire le code des données envoyées par le client.
     * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
     */
    printf("Message recu: %s\n", data);
    char code[10];
    sscanf(data, "%s:", code);
    printf("code: %s\n", code);

    // printf("%s", code);

    // Si le message commence par le mot: 'message:'
    if (strcmp(code, "calcul:") == 0)
    {
        // printf("a");

        // Demander et répondre au client
        // memset(data, 0, sizeof(data)); // Clear data
        
        calcul_cmd cmd;

        // Recuperation de l'operateur
        char *p = strtok(data, ": ");
        p = strtok(NULL, ": ");
        cmd.op = *p;

        // Recuperation de nb1 et nb2
        p = strtok(NULL, " ");
        cmd.nb1 = atoi(p);

        p = strtok(NULL, " ");
        cmd.nb2 = atoi(p);

        memset(data, 0, sizeof(data));

        printf("Operateur : %c %d %d\n", cmd.op, cmd.nb1, cmd.nb2);

        switch (cmd.op)
        {
            case '+':
                sprintf(data, "resultat: %d", cmd.nb1 + cmd.nb2);
                break; 
            break; 

            case '-':
                sprintf(data, "resultat: %d", cmd.nb1 - cmd.nb2);
                break;
            
            case 'x':
                sprintf(data, "resultat: %d", cmd.nb1 * cmd.nb2);
                break;

            case '/':
                sprintf(data, "resultat: %d", cmd.nb1 / cmd.nb2);
                break;

            default:
                perror("Operateur inconnu");
                return -1;
            break;
        }

        renvoie_message(client_socket_fd, data); // Envoyer le message au client
    }

    // fermer le socket
    close(socketfd);
    return (0);
}

int main()
{

    int socketfd;
    int bind_status;

    struct sockaddr_in server_addr;

    /*
     * Creation d'une socket
     */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Unable to open a socket");
        return -1;
    }

    int option = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // détails du serveur (adresse et port)
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Relier l'adresse à la socket
    bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status < 0)
    {
        perror("bind");
        return (EXIT_FAILURE);
    }

    // listen(socketfd, 30);

    // Lire et répondre au client
    // recois_envoie_message(socketfd);

    // ====================== //

    // Récupération des notes 

    for(int j = 0; j<5; j++)
    {
        // Écouter les messages envoyés par le client
        listen(socketfd, 1);

        // Lire et répondre au client
        // recois_envoie_message(socketfd);
        recois_numeros_calcule(socketfd);

        // memset(data, 0, sizeof(data));

        // sleep(1);

        /*
        * Creation d'un nouveau socket
        */
        /*
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd < 0)
        {
            perror("Unable to open a socket");
            return -1;
        }

        int option = 1;
        setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        // détails du serveur (adresse et port)
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        // Relier l'adresse à la socket
        bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (bind_status < 0)
        {
            perror("bind");
            return (EXIT_FAILURE);
        }
        */
    }

    // close(socketfd);

    return 0;
}
