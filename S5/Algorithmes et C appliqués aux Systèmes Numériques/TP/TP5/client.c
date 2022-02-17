/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <dirent.h>

#include "client.h"

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(int socketfd)
{

    char data[1024];
    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // Demandez à l'utilisateur d'entrer un message
    char message[1024];
    printf("Votre message (max 1000 caracteres): ");
    // while(getchar() != '\n');
    fgets(message, 1024, stdin);
    strcpy(data, "message: ");
    strcat(data, message);

    // Ecriture du message dans le socket
    int write_status = write(socketfd, data, strlen(data));

    if (write_status < 0)
    {
        perror("erreur ecriture");
        exit(EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lire les données de la socket
    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
        perror("erreur lecture");
        return -1;
    }

    printf("Message recu: %s\n", data);

    return 0;
}

int envoie_operateur_numeros(int socketfd)
{
    char data[1024];
    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // Demandez à l'utilisateur d'entrer un message
    char commande_str[1024];
    printf("Votre commande de calcul (max 1000 caracteres): ");
    // while(getchar() != '\n');
    fgets(commande_str, 1024, stdin);
    strcpy(data, "calcul: ");
    strcat(data, commande_str);

    // Ecriture du message dans le socket
    int write_status = write(socketfd, data, strlen(data));

    if (write_status < 0)
    {
        perror("erreur ecriture");
        exit(EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lire les données de la socket
    // Lecture réponse serveur
    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
        perror("erreur lecture");
        return -1;
    }

    printf("Resultat operation : %s\n", data);

    return 0;
}

int main()
{
    int socketfd;

    struct sockaddr_in server_addr;

    /*
     * Creation d'une socket
     */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // détails du serveur (adresse et port)
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // demande de connection au serveur
    int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_status < 0)
    {
        perror("connection serveur");
        exit(EXIT_FAILURE);
    }

    // envoie_recois_message(socketfd);
    // envoie_operateur_numeros(socketfd);

    // ====================== //

    // Récupération des notes

    int notes_etudiant[5][5];
    int cpt = 0;

    // Scanner tous les sous dossiers du dossier ./Etudiant et afficher le contenu de chaque sous dossier
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./Etudiant")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            cpt = 0;

            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                // printf("%s\n", ent->d_name);

                // Rentrer dans le sous dossier et lire le contenu
                DIR *dir_sous_dossier;
                struct dirent *ent_sous_dossier;

                char *path_sous_dossier = malloc(sizeof(char) * (strlen("./Etudiant/") + strlen(ent->d_name) + 1));

                strcpy(path_sous_dossier, "./Etudiant/");
                strcat(path_sous_dossier, ent->d_name);

                // printf("%s\n", path_sous_dossier);

                if ((dir_sous_dossier = opendir(path_sous_dossier)) != NULL)
                {
                    while ((ent_sous_dossier = readdir(dir_sous_dossier)) != NULL)
                    {
                        if (strcmp(ent_sous_dossier->d_name, ".") != 0 && strcmp(ent_sous_dossier->d_name, "..") != 0)
                        {
                            // printf("%s\n", ent_sous_dossier->d_name);

                            // Afficher le contenu de chaque fichier .txt present dans le sous dossier
                            char *path_fichier = malloc(sizeof(char) * (strlen(path_sous_dossier) + strlen(ent_sous_dossier->d_name) + 1));
                            strcpy(path_fichier, path_sous_dossier);
                            strcat(path_fichier, "/");
                            strcat(path_fichier, ent_sous_dossier->d_name);

                            // printf("%s\n", path_fichier);

                            FILE *fichier = fopen(path_fichier, "r");
                            if (fichier == NULL)
                            {
                                perror("fichier");
                                exit(EXIT_FAILURE);
                            }
                            else
                            {
                                char *contenu_fichier = malloc(sizeof(char) * 1024);
                                fgets(contenu_fichier, 1024, fichier);
                                fclose(fichier);

                                if ((strlen(contenu_fichier) > 0) && (contenu_fichier[strlen(contenu_fichier) - 1] == '\n'))
                                {
                                    contenu_fichier[strlen(contenu_fichier) - 1] = '\0';
                                }

                                // Variable contenu_fichier = note

                                // Enregistrer la note dans la matrice notes_etudiant
                                // printf("%s\n", contenu_fichier);

                                int note = atoi(contenu_fichier);
                                notes_etudiant[atoi(ent->d_name) - 1][cpt] = note;

                                cpt++; // Incrementer le compteur de notes

                                // printf("Note int = %d\n", note);
                                // printf("ent->d_name = %s\n", ent->d_name);

                                free(contenu_fichier);
                            }

                            free(path_fichier);
                        }
                    }
                    closedir(dir_sous_dossier);
                }
                else
                {
                    perror("erreur ouverture sous dossier");
                    exit(EXIT_FAILURE);
                }

                free(path_sous_dossier);
            }
        }
        closedir(dir);
    }
    else
    {
        perror("erreur ouverture dossier");
        exit(EXIT_FAILURE);
    }

    // Afficher la matrice notes_etudiant

    printf("\nNotes des etudiants :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Etudiant %d : ", i + 1);
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", notes_etudiant[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 5; i++)
    {
        int moyenne = 0;

        for (int j = 0; j < 5; j++)
        {
            // printf("%d ", notes_etudiant[i][j]);

            char data[1024];
            memset(data, 0, sizeof(data));

            char calc_str[1024];
            strcpy(calc_str, "+ ");

            // Convertir moyenne en char
            char moyenne_str[1024];
            sprintf(moyenne_str, "%d", moyenne);

            strcat(calc_str, moyenne_str);

            strcat(calc_str, " ");

            // Convertir notes_etudiant[i][j] en char
            char note_str[1024];
            sprintf(note_str, "%d", notes_etudiant[i][j]);

            strcat(calc_str, note_str);

            strcpy(data, "calcul: ");
            strcat(data, calc_str);

            // Ecriture du message dans le socket
            int write_status = write(socketfd, data, strlen(data));

            if (write_status < 0)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }

            memset(data, 0, sizeof(data));

            // Récupération des données dans le socket

            int read_status = read(socketfd, data, sizeof(data));
            if (read_status < 0)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            // TODO Envoyer SOMME / 5 au serveur

            printf("%s\n", data);

            
        }

        // printf("Moyenne : %0.2f", moyenne / 5.0);
    }

    close(socketfd);
}
