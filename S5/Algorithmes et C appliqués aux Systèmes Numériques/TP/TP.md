# TP

# TP/TP6

# TP/TP6/src

## client.c
```c
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

#include "client.h"
#include "bmp.h"

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(int socketfd) {

 
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));


  // Demandez à l'utilisateur d'entrer un message
  char message[100];
  printf("Votre message (max 1000 caracteres): ");
  fgets(message, 1024, stdin);
  strcpy(data, "message: ");
  strcat(data, message);
  
  int write_status = write(socketfd, data, strlen(data));
  if ( write_status < 0 ) {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));


  // lire les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if ( read_status < 0 ) {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu: %s\n", data);
 
  return 0;
}

void analyse(char *pathname, char *data) {
  //compte de couleurs

  printf("Entrer le nombre de couleur souhaité : \n");
  int nb_couleurs=0;
  scanf("%i",&nb_couleurs);
  printf("Nombre : %i \n",nb_couleurs);

  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  strcpy(data, "couleurs: ");
  char temp_string[nb_couleurs];
  sprintf(temp_string, "%d,", nb_couleurs);
  if (cc->size < nb_couleurs) {
    sprintf(temp_string, "%d,", cc->size);
  }
  strcat(data, temp_string);
  
  //choisir 10 couleurs
  for (count = 1; count < (nb_couleurs+1) && cc->size - count >0; count++) {
    if(cc->compte_bit ==  BITS32) {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc24[cc->size-count].c.rouge,cc->cc.cc32[cc->size-count].c.vert,cc->cc.cc32[cc->size-count].c.bleu);
    }
    if(cc->compte_bit ==  BITS24) {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc32[cc->size-count].c.rouge,cc->cc.cc32[cc->size-count].c.vert,cc->cc.cc32[cc->size-count].c.bleu);
    }
    strcat(data, temp_string);
  }

  //enlever le dernier virgule
  data[strlen(data)-1] = '\0';
}

int envoie_couleurs(int socketfd, char *pathname) {
  char data[1024];
  memset(data, 0, sizeof(data));
  analyse(pathname, data);
  
  int write_status = write(socketfd, data, strlen(data));
  if ( write_status < 0 ) {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}


int main(int argc, char **argv) {
  int socketfd;
  int bind_status;

  struct sockaddr_in server_addr, client_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  //détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  //demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if ( connect_status < 0 ) {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }
  //envoie_recois_message(socketfd);
  envoie_couleurs(socketfd, argv[1]);

  close(socketfd);
}
```
## couleur.c
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#define _GNU_SOURCE //to avoid c99 related warnings
#include "couleur.h"
#include <stdio.h>
#include <stdlib.h>
#include <search.h>

//compter les couleurs distincts 
couleur_compteur* compte_couleur(couleur *c, int csize) {
   couleur_compteur *compteur;
   COMPTEBIT bc;
   int compteur_size = 0;
   int i = 0;

   if (c->compte_bit == BITS24) {
     bc = BITS24;
     compteur = calloc(1, sizeof(couleur_compteur));
     if (compteur == NULL) {
       perror("Erreur: allocation dynamique de memoire\n");
       return NULL;      
     }
     compteur->compte_bit = BITS24;
     compteur->cc.cc24 = calloc(csize, sizeof(couleur_compteur));
     if (compteur == NULL) {
       perror("Erreur: allocation dynamique de memoire\n");
       return NULL;      
     }
   }
   else if (c->compte_bit == BITS32) {
     bc = BITS32;
     compteur = calloc(1, sizeof(couleur_compteur));
     if (compteur == NULL) {
       perror("Erreur: allocation dynamique de memoire\n");
       return NULL;      
     }
     compteur->compte_bit = BITS32;
     compteur->cc.cc32 = calloc(csize, sizeof(couleur_compteur));
     if (compteur == NULL) {
       perror("Erreur: allocation dynamique de memoire\n");
       return NULL;      
     }
   }
   else {
     perror("compte du bits inconnu");
     return NULL;
   }

   /*
    * créer une table de hachage pour stocker les différentes couleurs et leur nombre
    */
   hcreate(csize);

   for (i=0; i < csize; i++) {
     ENTRY e, *es;
     char key[256];

     if (bc == BITS24) {
       sprintf(key, "%hd:%hd:%hd", c->c.c24[i].rouge, c->c.c24[i].vert, c->c.c24[i].bleu); 
     }
     else if (bc == BITS32) {
       sprintf(key, "%hd:%hd:%hd:%hd", c->c.c32[i].rouge, c->c.c32[i].vert, c->c.c32[i].bleu, c->c.c32[i].alpha); 
     }
     e.key = key;

     es = hsearch(e, FIND);
     if (es == NULL ) {
       compteur_size++;
       if (c->compte_bit == BITS24) {
         compteur->cc.cc24[compteur_size-1].c = c->c.c24[i];
         compteur->cc.cc24[compteur_size-1].compte = 1;
         e.data = (void *) &compteur->cc.cc24[compteur_size-1];
       }
       else {
         compteur->cc.cc32[compteur_size-1].c = c->c.c32[i];
         compteur->cc.cc32[compteur_size-1].compte = 1;
         e.data = (void *) &compteur->cc.cc32[compteur_size-1];
       } 
       es = hsearch(e, ENTER);
       if (es == NULL) {
         perror("Erreur: impossible d'inserer\n");
         return NULL;
       }
     }
     else {
       if (bc == BITS24) {
         couleur24_compteur *cc24 = (couleur24_compteur *) es->data;
         cc24->compte++;
       }
       else if (bc == BITS32) {
         couleur32_compteur *cc32 = (couleur32_compteur *) es->data;
         cc32->compte++;
       } 
     }
   }

   compteur->size = compteur_size;

   hdestroy();
   return compteur;
}

//afficher les couleurs
void print_couleur(couleur *c, int csize) {
   int i = 0;

   for (i=0; i < csize; i++) {
     if (c->compte_bit == BITS24) { // 3 octets (RGB)
       printf("%5x %5x %5x\n", c->c.c24[i].rouge, c->c.c24[i].vert, c->c.c24[i].bleu); 
     }
     else if (c->compte_bit == BITS32) { // 4 octets (RGBA)
       printf("%5x %5x %5x %5x\n", c->c.c32[i].rouge, c->c.c32[i].vert, c->c.c32[i].bleu, c->c.c32[i].alpha); 
     }
     else {
       return;
     }
   }
}

//afficher le compte de couleurs distincts
void print_couleur_compteur(couleur_compteur * ccompteur) {
   int i = 0;

   for (i=0; i < ccompteur->size; i++) {
     if (ccompteur->compte_bit == BITS24) {
       printf("%5hx %5hx %5hx: %10d\n", ccompteur->cc.cc24[i].c.rouge, ccompteur->cc.cc24[i].c.vert, ccompteur->cc.cc24[i].c.bleu, ccompteur->cc.cc24[i].compte); 
     }
     else if (ccompteur->compte_bit == BITS32) {
       printf("%5hx %5hx %5hx %5hx: %10d\n", ccompteur->cc.cc32[i].c.rouge, ccompteur->cc.cc32[i].c.vert, ccompteur->cc.cc32[i].c.bleu, ccompteur->cc.cc32[i].c.alpha, ccompteur->cc.cc32[i].compte); 
     }
   }

}

/*
 * fonction permettant de comparer deux couleurs
 */
static int compare_compteur (const void *ccp1, const void *ccp2, void *compte_bitp) {
  COMPTEBIT *bc = (COMPTEBIT *)compte_bitp;
  if (*bc == BITS24) {
    couleur24_compteur *cc241 = (couleur24_compteur *) ccp1;
    couleur24_compteur *cc242 = (couleur24_compteur *) ccp2;
    if (cc241->compte == cc242->compte) {
      return 0;
    }
    else if (cc241->compte > cc242->compte) {
      return 1;
    }
    return -1;
  }
  else if (*bc == BITS32) {
    couleur32_compteur *cc321 = (couleur32_compteur *) ccp1;
    couleur32_compteur *cc322 = (couleur32_compteur *) ccp2;
    if (cc321->compte == cc322->compte) {
      return 0;
    }
    else if (cc321->compte > cc322->compte) {
      return 1;
    }
    return -1;
  }
}

//trier le compte de couleurs distincts
void trier_couleur_compteur(couleur_compteur * ccompteur) {
  COMPTEBIT bc = ccompteur->compte_bit;
  if ( ccompteur->compte_bit == BITS24) {
    qsort_r(ccompteur->cc.cc24, ccompteur->size, sizeof(couleur24_compteur),
      compare_compteur, (void *) &bc);
  }
  else if ( ccompteur->compte_bit == BITS32) {
    qsort_r(ccompteur->cc.cc32, ccompteur->size, sizeof(couleur32_compteur),
      compare_compteur, (void *) &bc);
  }
}
```
## serveur.c
```c
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

#include "serveur.h"

void plot(char *data) {

  //Extraire le compteur et les couleurs RGB 
  FILE *p = popen("gnuplot -persist", "w");
  printf("Plot");
  int count = 0;
  int n;
  char *saveptr = NULL;
  char *str = data;
  fprintf(p, "set xrange [-15:15]\n");
  fprintf(p, "set yrange [-15:15]\n");
  fprintf(p, "set style fill transparent solid 0.9 noborder\n");
  fprintf(p, "set title 'Top 30 colors'\n");
  fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
  char donnee = data[10] - '0';
  char donnee2 = data[11] - 48;
   printf("\n value : %c \n",donnee);
   printf("\n value : %c \n",donnee2);

char donne_real = donnee *10 + donnee2;
int donnee_INT=donne_real;

float valeur_cercle=(360/donnee_INT);

printf("\n valeur int : %i \n", donnee_INT);

  while(1) {
    char *token = strtok_r(str, ",", &saveptr);
    if (token == NULL) {
      break;
    }
    str=NULL;
    if (count == 0) {
      n = atoi(token);
    }
    else {
      // On divise 360° par notre nombre de couleur
      fprintf(p, "0 0 10 %f %f 0x%s\n", (count-1)*valeur_cercle, count*valeur_cercle, token+1);
    }
    count++;
  }
  fprintf(p, "e\n");
  printf("Plot: FIN\n");
  pclose(p);
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data) {
  int data_size = write (client_socket_fd, (void *) data, strlen(data));
      
  if (data_size < 0) {
    perror("erreur ecriture");
    return(EXIT_FAILURE);
  }
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd) {
  struct sockaddr_in client_addr;
  char data[1024];

  int client_addr_len = sizeof(client_addr);
 
  // nouvelle connection de client
  int client_socket_fd = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
  if (client_socket_fd < 0 ) {
    perror("accept");
    return(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  //lecture de données envoyées par un client
  int data_size = read (client_socket_fd, (void *) data, sizeof(data));
      
  if (data_size < 0) {
    perror("erreur lecture");
    return(EXIT_FAILURE);
  }
  
  /*
   * extraire le code des données envoyées par le client. 
   * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
   */
  printf ("Message recu: %s\n", data);
  char code[30];
  sscanf(data, "%s", code);

  //Si le message commence par le mot: 'message:' 
  if (strcmp(code, "message:") == 0) {
    renvoie_message(client_socket_fd, data);
  }
  else {
    plot(data);
  }

  //fermer le socket 
  close(socketfd);
}

int main() {

  // merci l'editeur texte !!
  //printf("Entrer le nombre de couleur souhaité : \n");
  //int nb_couleurs=0;
  //scanf("%i",&nb_couleurs);
  //printf("Nombre : %i \n",nb_couleurs);


  int socketfd;
  int bind_status;
  int client_addr_len;

  struct sockaddr_in server_addr, client_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  //détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (bind_status < 0 ) {
    perror("bind");
    return(EXIT_FAILURE);
  }
 
  // Écouter les messages envoyés par le client
  listen(socketfd, 10);

  //Lire et répondre au client
  recois_envoie_message(socketfd);

  return 0;
}
```
## client.h
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */
int envoie_recois_message(int socketfd);

#endif
```
## serveur.h
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */


#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd);

#endif
```
## couleur.h
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdint.h>

// Compte de bits (24 bits, 32 bits..)
typedef enum COMPTEBIT {BITS24, BITS32} COMPTEBIT; 

// Structure de données d'une couleur de 32 bits
#pragma pack(push, 1)
typedef struct {
  uint8_t bleu;
  uint8_t vert;
  uint8_t rouge;
  uint8_t alpha;
} couleur32;
#pragma pack(pop)

// Structure de données d'une couleur de 24 bits
#pragma pack(push, 1)
typedef struct {
  uint8_t bleu;
  uint8_t vert;
  uint8_t rouge;
} couleur24;
#pragma pack(pop)

// Structure de données d'un couleurs de 24/32 bits
typedef struct {
  COMPTEBIT compte_bit; 
  union {
    couleur24 *c24;
    couleur32 *c32;
  } c;
  int size;
} couleur;

// Structure de données de compteur de couleurs de 32 bits
typedef struct {
  couleur32 c;
  int compte;
}
couleur32_compteur;

// Structure de données de compteur de couleurs de 24 bits
typedef struct {
  couleur24 c;
  int compte;
}
couleur24_compteur;

// Structure de données de compteur de couleurs de 24/32 bits
typedef struct {
  COMPTEBIT compte_bit; 
  union {
    couleur24_compteur *cc24;
    couleur32_compteur *cc32;
  } cc;
  int size;
} couleur_compteur;

//compter les couleurs distincts 
couleur_compteur* compte_couleur(couleur *, int);

//afficher les couleurs
void print_couleur(couleur *, int);

//afficher le compte de couleurs distincts
void print_couleur_compteur(couleur_compteur *);

//trier le compte de couleurs distincts
void trier_couleur_compteur(couleur_compteur *);

#endif
```
## bmp.c
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 

#include "bmp.h"

/*
 * fonction d'analyse des couleurs dans l'image du format BMP
 * Il faut un argument : le chemin du fichier image
 */
couleur_compteur * analyse_bmp_image(char *nom_de_fichier) {

  couleur_compteur * cc = NULL;

  // l'ouverture du fichier pour la lecture
  int fd = open(nom_de_fichier, O_RDONLY);  
  printf("%s",nom_de_fichier);
  if (fd < 0) {
    perror("Erreur: open");
    return 0;
  }

  bmp_header bheader;
  bmp_info_header binfo_header;

  //la lecture de l'en-tête du fichier pour en connaître la taille et le type
  ssize_t compte = read(fd, &bheader, sizeof(bheader));
  if (compte < 0) {
    perror("Erreur: read");
    return(NULL);
  }

  // Vérifier l'en-tête pour voir si le fichier est une image de format BMP
  if (bheader.type != 0x4D42) {
    return(NULL);
  }

  /* Obtenir l'information indiquant si l'image utilise 3 (RGB) ou 4 (RGBA)
   * octets pour stocker une seule couleur
   */
  compte = read(fd, &binfo_header, sizeof(binfo_header));
  if (compte < 0) {
    perror("Erreur: read");
    return(NULL);
  }
  
  //Se positionner correctement pour commencer à lire les couleurs 
  off_t offset = lseek(fd, bheader.offset, SEEK_SET);
  if (offset != bheader.offset) {
    perror("Erreur: lseek");
    return(NULL);
  }

  // Lecture des couleurs de 4 octets
  if (binfo_header.compte_bit == 32) {
    couleur32 * c32 = calloc (binfo_header.taille_image/4, 4);
    read(fd, c32, binfo_header.taille_image);
    if (compte < 0) {
      perror("Erreur: read");
      return(NULL);
    }

    int ccsize;
    couleur c;
    c.compte_bit = BITS32;
    c.c.c32 = c32;
    cc = compte_couleur(&c, binfo_header.taille_image/4);
    trier_couleur_compteur(cc);
  }
  else if (binfo_header.compte_bit == 24) {
    // Lecture des couleurs de 3 octets
    couleur24 * c24 = calloc (binfo_header.taille_image/3, 3);
    read(fd, c24, binfo_header.taille_image);
    if (compte < 0) {
      perror("Erreur: read");
      return(NULL);
    }

    int ccsize;
    couleur c;
    c.compte_bit = BITS24;
    c.c.c24 = c24;
    cc = compte_couleur(&c, binfo_header.taille_image/3);
    trier_couleur_compteur(cc);
  }
 
  close(fd);

  return cc; 
}
```
## bmp.h
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __READ_BMP_H__
#define __READ_BMP_H__

#include <stdint.h>
#include "couleur.h"

//Reference: http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
//https://stackoverflow.com/questions/14279242/read-bitmap-file-into-structure

//Structure de données d'une image bmp (en-tête)
#pragma pack(push, 1)
typedef struct {
  uint16_t type;
  uint32_t file_size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
} bmp_header;
#pragma pack(pop)

//Structure de données d'une image bmp (en-tête): détails (taille etc.)
#pragma pack(push, 1)
typedef struct {
  uint32_t info_header_size;
  uint32_t largeur;
  uint32_t hauteur;
  uint16_t planes;
  uint16_t compte_bit;
  uint32_t compression;
  uint32_t taille_image;
  uint32_t xpixels_par_metre;
  uint32_t ypixels_par_metre;
  uint32_t couleurs_utilise;
  uint32_t couleurs_important;
} bmp_info_header;
#pragma pack(pop)

// analyse d'un fichier bmp (compter et trier)
couleur_compteur * analyse_bmp_image(char *);
#endif
```
# TP/TP6/src/images

# TP/TP3

## tri.c
```c
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// Fonctions de générations de nombres pseudos aléatoires
signed short hasard(signed short a, signed short b);
void srand(unsigned int seed);
int rand(void);

#define MAX 999
#define MIN 0

#define TAILLE 100

int main(int argc, char const *argv[])
{

    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL)); 
    
    int tbl[TAILLE];

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        tbl[i] = hasard(MIN, MAX);
    }

    printf("Tableau de base :\n");
    for (unsigned int i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }

    /*
    
    tri_à_bulles_optimisé(Tableau T)
    pour i allant de 0 à TAILLE - 1
        tableau_trié := vrai
        pour j allant de 0 à TAILLE - i - 1
            si T[j+1] < T[j]
                (T[j+1], T[j]) = (T[j], T[j+1])
                tableau_trié := faux
        si tableau_trié
            fin tri_à_bulles_optimisé

    */

   /* Bubble sort */

    int tmp = 0;
    
    for (unsigned int i = 0; i < TAILLE - 1; i++)
    {
        bool tri = true;

        // printf("a");
        
        for (unsigned int j = 0; j < TAILLE - i - 1; j++)
        {
            // printf("%d", tbl[j+1] < tbl[j]);

            if(tbl[j+1] < tbl[j])
            {
                // printf("a");
                tmp = tbl[j];
                tbl[j] = tbl[j+1];
                tbl[j+1] = tmp;

                tri = false;
            }
        }

        if(tri)
        {
            break;
        }
        
    }

    printf("\n\n");

    printf("Tableau apres le tri :\n");

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }
    
    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand()%(b - a + 1);

    return vrdm;
}```
## chercher.c
```c
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Fonctions de générations de nombres pseudos aléatoires
signed short hasard(signed short a, signed short b);
void srand(unsigned int seed);
int rand(void);

#define MAX 999
#define MIN 0

#define TAILLE 100


int main(int argc, char const *argv[])
{
    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL)); 

    int tbl[TAILLE];

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        tbl[i] = hasard(MIN, MAX);
    }

    for (size_t i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }

    int entier = 0;

    printf("Entrer l'entier a trouver dans le tableau : ");

    fflush(stdin);
    scanf("%d", &entier);

    bool present = false;

    // tbl[0] = 20;

    for (size_t i = 0; i < TAILLE; i++)
    {
        if(tbl[i] == entier)
        {
            printf("\nL'entier %d se trouve dans le tableau au rang [%d] !", entier, i);
            present = true;
        }
    }
    
    if (present == false)
    {
        printf("L'entier %d ne se trouve pas dans le tableau !", entier);
    }

    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand()%(b - a + 1);

    return vrdm;
}```
## grand_petit.c
```c
#include <stdio.h>
#include <time.h>

// Fonctions de générations de nombres pseudos aléatoires
signed short hasard(signed short a, signed short b);
void srand(unsigned int seed);
int rand(void);

#define MAX 999
#define MIN 0

#define TAILLE 100

int main(int argc, char const *argv[])
{
    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL)); 
    
    int tbl[TAILLE];

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        tbl[i] = hasard(MIN, MAX);
    }

    /* Minimum */

    int min = MAX + 1;

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        if(tbl[i] < min)
        {
            min = tbl[i];
        }
    }

    /* Maximum */

    int max = MIN + 1;

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        if(tbl[i] > max)
        {
            max = tbl[i];
        }
    }
    
    printf("Le minimum du tableau est : %i\n", min);
    printf("Le maximum du tableau est : %i\n", max);

    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand()%(b - a + 1);

    return vrdm;
}```
## chercher_phrase.c
```c
#include <stdio.h>

int compare(char *s1, char *s2);

int main(int argc, char const *argv[])
{
    // Creation d'un tableau de 10 phrases
    char tabPhrase[10][50] = {
        "Bonjour",
        "Au revoir",
        "Aujourd'hui",
        "Demain",
        "Nous sommes le 10",
        "Nous sommes le 11",
        "Nous sommes le 12",
        "Nous sommes le 13",
        "Nous sommes le 14",
        "Nous sommes le 15"
    };

    // creation de la chaine de caractere à chercher
    char phrase[50] = "Bonjour";

    // affiche chaque caractere de phrase
    int i;
    for (i = 0; i < 50; i++)
    {
        printf("%c", phrase[i]);
    }

    printf("\n");

    // Vérifie si la phrase est dans le tableau
    int trouve = 0;
    for (i = 0; i < 10; i++)
    {
        if (compare(tabPhrase[i], phrase) == 1)
        {
            trouve = 1;
        }
    }

    if (trouve == 1)
    {
        printf("La phrase est dans le tableau\n");
    }
    else
    {
        printf("La phrase n'est pas dans le tableau\n");
    }

    return 0;

}

// Compare deux chaines de caracteres sans utiliser strcmp, retourne 1 si elles sont egales, 0 sinon
int compare(char *s1, char *s2)
{
    int i;
    for (i = 0; i < 50; i++)
    {
        if (s1[i] != s2[i])
        {
            return 0;
        }
    }
    return 1;
}```
## octect.c
```c
#include <stdio.h>

int main()
{
// Pour chaque type, on créer un poiteur que l'ont passe dans un sizeof

    int unInt=11;
    int * unPointeurSurInt=&unInt;

    long int unLongInt=123456;
    int * unPointeurSurLongInt=&unLongInt;
    
    short unShort=11;
    int * unPointeurSurShort=&unShort;
    
    double unDouble=123456789;
    int * unPointeurSurDouble=&unDouble;

    long double unLongDouble=123456789;
    int * unPointeurSurLongDouble=&unLongDouble;

    float unFloat=3.14;
    int * unPointeurSurFloat=&unFloat;

    printf("Taille d'un int (pointé) : %li \n",sizeof(*unPointeurSurInt));
    printf("Taille d'un long int (pointé) : %li \n",sizeof(*unPointeurSurLongInt));
    printf("Taille d'un short (pointé) : %li \n",sizeof(*unPointeurSurShort));
    printf("Taille d'un double (pointé) : %li \n",sizeof(*unPointeurSurDouble));
    printf("Taille d'un long double (pointé) : %li \n",sizeof(*unPointeurSurLongDouble));
    printf("Taille d'un float (pointé) : %li \n",sizeof(*unPointeurSurFloat));
}```
## recherche_digotomique2.c
```c
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void srand(unsigned int seed);
int rand(void);

#define MAX 999

int main(int argc, char const *argv[])
{
    
    // Fill a table with random numbers
    int table[100]; // Table of 100 numbers
    srand(time(NULL)); // Initialize the random number generator
    for (int i = 0; i < 100; i++)
    {
        table[i] = rand() % MAX; // Fill the table with random numbers
    }

    // print the table
    printf("Table : \n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", table[i]);
    }
    printf("\n");

    // sort the table
    int temp;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (table[i] < table[j])
            {
                temp = table[i];
                table[i] = table[j];
                table[j] = temp;
            }
        }
    }

    // print the table
    printf("Table : \n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", table[i]);
    }
    printf("\n");

    // dichotomic search
    int search = 0; // number to search
    int left = 0;
    int right = 99;
    int middle;
    bool found = false;

    printf("Enter a number to search : ");
    fflush(stdin);
    scanf("%d", &search);

    while (left <= right && !found)
    {
        middle = (left + right) / 2;
        if (table[middle] == search)
        {
            found = true;
        }
        else if (table[middle] > search)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }

    if (found)
    {
        printf("%d is in the table\n", search);
    }
    else
    {
        printf("%d is not in the table\n", search);
    }


    return 0;
}
```
## couleur_compteur.c
```c
#include <stdio.h>
#include <time.h>

void srand(unsigned int seed);
int rand(void);

// Définition de la structure couleur : rouge, vert, bleu, alpha
typedef struct couleur {
    int rouge;
    int vert;
    int bleu;
    int alpha;
} couleur;

#define TAILLE 100
#define SAMPLE 8

int main(int argc, char const *argv[])
{
    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL));

    // Creer une palette de 8 couleurs et la remplir avec des valeurs héxadécimales aléatoires
    couleur tab_sample[SAMPLE];
    int i;
    for (i = 0; i < SAMPLE; i++)
    {
        tab_sample[i].rouge = rand() % 256;
        tab_sample[i].vert = rand() % 256;
        tab_sample[i].bleu = rand() % 256;
        tab_sample[i].alpha = rand() % 256;
    }

    // Creer un tableau de couleurs et le remplir avec des couleurs aléatoires tirées de la palette tab_sample
    couleur tab_couleur[TAILLE];

    int n = 0;
    for (i = 0; i < TAILLE; i++)
    {
        n = rand() % SAMPLE;
        tab_couleur[i].rouge = tab_sample[n].rouge;
        tab_couleur[i].vert = tab_sample[n].vert;
        tab_couleur[i].bleu = tab_sample[n].bleu;
        tab_couleur[i].alpha = tab_sample[n].alpha;
    }

    // Trouver les duplicatas de chaque couleurs
    int nb_couleur[TAILLE]; // Tableau qui donne le nombre de fois qu'une couleur apparait dans le tableau tab_couleur
    for (int i = 0; i < TAILLE; i++)
    {
        nb_couleur[i] = 0;
    }

    for (int i = 0; i < TAILLE; i++)
    {
        // Comparaison de la couleur i avec les autres couleurs du tableau tab_couleur
        for (int j = 0; j < TAILLE; j++)
        {
            if (tab_couleur[i].rouge == tab_couleur[j].rouge &&
                tab_couleur[i].vert == tab_couleur[j].vert && 
                tab_couleur[i].bleu == tab_couleur[j].bleu && 
                tab_couleur[i].alpha == tab_couleur[j].alpha)
            {
                // Si la couleur i est identique à la couleur j, on incrémente le nombre de fois qu'elle apparait
                nb_couleur[i]++;
            }
        }
    }


    // Création d'une struct pour stocker les couleurs et leur nombre de repetition
    typedef struct compteur {
        couleur clr;
        int nb;
        int checked; // 0 = non vérifié, 1 = vérifié
    } compteur;

    // Création d'un tableau de compteurs de couleurs
    compteur tab_compteur[TAILLE];

    // Initialisation de tab_compteur
    for (int i = 0; i < TAILLE; i++)
    {
        tab_compteur[i].clr = tab_couleur[i];
        tab_compteur[i].nb = nb_couleur[i];
        tab_compteur[i].checked = 0;
    }  
    
    // On met à 0 la valeur nb des couleurs déjà vu lors du scan de toutes les couleurs
    // Pour ne pas les afficher plusieurs fois
    // Une fois que la couleur est vérifiée, on met à la variable checked à 1 pour ne plus la vérifier
    for (int i = 0; i < TAILLE; i++)
    {
        if (tab_compteur[i].checked == 0)
        {
            tab_compteur[i].checked = 1;

            for (int j = 0; j < TAILLE; j++)
            {
                if (tab_compteur[j].checked == 0 &&
                    tab_compteur[i].clr.rouge == tab_compteur[j].clr.rouge &&
                    tab_compteur[i].clr.vert == tab_compteur[j].clr.vert && 
                    tab_compteur[i].clr.bleu == tab_compteur[j].clr.bleu && 
                    tab_compteur[i].clr.alpha == tab_compteur[j].clr.alpha)
                {
                    tab_compteur[j].checked = 1;
                    tab_compteur[j].nb = 0;
                }
            }
        }
    }

    printf("===========================\n");
    printf("Tableau des couleurs et le nombre de fois qu'elles apparaissent : \n");
    for (int i = 0; i < TAILLE; i++)
    {
        if (tab_compteur[i].nb != 0)
        {
            printf("0x%2.2x 0x%2.2x 0x%2.2x 0x%2.2x %d \n", tab_compteur[i].clr.rouge, tab_compteur[i].clr.vert, tab_compteur[i].clr.bleu, tab_compteur[i].clr.alpha, tab_compteur[i].nb);
        }
    }

    printf("===========================\n");

    return 0;
}
```
## recherche_digotomique.c
```c
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

// Fonctions de générations de nombres pseudos aléatoires
signed short hasard(signed short a, signed short b);
void srand(unsigned int seed);
int rand(void);

#define MAX 999
#define MIN 0

#define TAILLE 10

int main(int argc, char const *argv[])
{
    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL));

    int tbl[TAILLE];

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        tbl[i] = hasard(MIN, MAX);
    }

    int entier = 0;

    printf("\nEntrer l'entier a trouver dans le tableau : ");

    fflush(stdin);
    scanf("%d", &entier);

    /* Bubble sort */

    int tmp = 0;
    
    for (unsigned int i = 0; i < TAILLE - 1; i++)
    {
        bool tri = true;

        // printf("a");
        
        for (unsigned int j = 0; j < TAILLE - i - 1; j++)
        {
            // printf("%d", tbl[j+1] < tbl[j]);

            if(tbl[j+1] < tbl[j])
            {
                // printf("a");
                tmp = tbl[j];
                tbl[j] = tbl[j+1];
                tbl[j+1] = tmp;

                tri = false;
            }
        }

        if(tri)
        {
            break;
        }
        
    }

    // printf("a\n");

    /*
        //déclarations
        début, fin, mil : Entiers
        tbl : tableau d'entiers classé
        trouvé : Booléen
        
        //initialisation
        début ← 0 
        fin ← N
        trouvé ← faux
        Saisir val

        //Boucle de recherche
        // La condition début inférieur ou égal à fin permet d'éviter de faire
        // une boucle infinie si 'val' n'existe pas dans le tableau.
        Tant que trouvé != vrai et début <= fin:
            mil ← partie_entière((début + fin)/2)
            si t[mil] == val:
                trouvé ← vrai
            sinon:
                si val > t[mil]:
                    début ← mil+1
                sinon:
                    fin ← mil-1
        //Affichage du résultat
        Si trouvé == vrai:
            Afficher "La valeur ", val , " est au rang ", mil
        Sinon:
            Afficher "La valeur ", val , " n'est pas dans le tableau"
    */

    for (size_t i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }
    
    /* Dichotomie */

    int debut = 0, fin = tbl[TAILLE - 1], mil;
    bool present = false;

    // printf("a");

    while ((present != true) && (debut <= fin))
    {
        // printf("b");
        mil = floor((debut + fin) / 2);

        if (tbl[mil] == entier)
        {
            present = true;
            // printf("a");
        }
        else
        {
            if (entier > tbl[mil])
            {
                debut = mil + 1;
            }
            else
            {
                fin = mil - 1;
            }
        }
    }

    // printf("c");

    printf("%d", present);

    if(present)
    {
        printf("\nL'entier %d se trouve dans le tableau au rang [%d] !", entier, mil);
    }
    else
    {
        printf("L'entier %d ne se trouve pas dans le tableau !", entier);
    }

    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand() % (b - a + 1);

    return vrdm;
}```
## sizeof.c
```c
#include <stdio.h>

int main()
{
	//Affichage valeur int
	printf("Taille d'un entier : %ld\n", sizeof(int));
	printf("Taille d'un entier* : %ld\n", sizeof(int*));
	printf("Taille d'un entier** : %ld\n", sizeof(int**));

	//Affichage valeur char
	printf("Taille d'un caractere* : %ld\n", sizeof(char*));
	printf("Taille d'un caractere** : %ld\n", sizeof(char**));
	printf("Taille d'un caractere*** : %ld\n", sizeof(char***));

	//Affichage valeur float
	printf("Taille d'un float* : %ld\n", sizeof(float*));
	printf("Taille d'un float** : %ld\n", sizeof(float**));
	printf("Taille d'un float*** : %ld\n", sizeof(float***));
}
```
# TP/TP1

## binaire.c
```c
/*

#include <stdio.h>



int main(int argc, char const *argv[])
{

    int r, n = 0;
    long dec;

    int tbl_bin[16];

    printf("Entrer le nombre decimal a convertir en binaire : ");
    fflush(stdin);
    scanf("%i", &dec);

    if(dec > 65535)
    {
        printf("Ce nombre depasse la limite d'affichage sur 16 bits de 65535\n");
    }
    else
    {
        for (int n = 0; n < 16; n++)
        {
            r = dec % 2;
            dec = dec / 2;
            tbl_bin[n] = r;
        }

        for (int i = 16 - 1; i >= 0; i--)
        {
            if ((i + 1) % 4)
            {
                printf("%i", tbl_bin[i]);
            }
            else
            {
                printf(" %i", tbl_bin[i]);
            }
        }
    }

    return 0;
}
*/

#include <stdio.h>
#include <math.h>
// On initialise nos procédure
int puissance(int value, int power);

// Ce programme permet d'afficher un nombre décimal en binaire
int main(void) {
    int nb = 0;
    int i = 0;
    long lenght = 0;

    printf("Quelle valeur voulez-vous en binaire ?");
    fflush(stdin);
    scanf("%i",&nb);

    // la longueur nécessaire pour écrire un nombre en binaire correspond à se nombre à la puissance 2
    lenght = puissance(nb,2);
    // on crée un tableau de la taille nécessaire pour écrire le nombre en binaire
    int res[lenght];

    for(i = 0; nb > 0; i++) 
    {
        // 0 ou 1
        res[i] = nb%2;
        // on décrémente les puissances
        nb=nb/2;
    }
    // On affiche le resultat
    for(i = i-1;i >= 0; i--) 
    {
        printf("%d", res[i]);
    }
    printf("\n");
}

// Procédure retournant un nombre passé en paramète à la puissance, passée en paramètre
int puissance(int value, int power) {
    long result = 1;
    for(int i=0; i<power;i++) {
        result *= value;
    }
    return result;
}
```
## cercle.c
```c
#include <math.h>
#include <stdio.h>

float c_aire(float r);
float c_perim(float r);

int main(int argc, char const *argv[])
{

    float rayon = 0;

    printf("Entrer le rayon du cercle : ");
    fflush(stdin);
    scanf("%f", &rayon);

    // printf("%f\n", rayon);

    printf("Aire du cercle = %f\n", c_aire(rayon));
    printf("Perimetre du cercle = %f\n", c_perim(rayon));

    return 0;
}

float c_aire(float r)
{
    float aire = M_PI * pow(r, 2);
    // printf("R aire : %f \n",r);

    return aire;
}

float c_perim(float r)
{
    float perim = 2 * M_PI * r;

    return perim;
}```
## variables.c
```c
#include <stdio.h>

int main()
{
    char t1;
    short t2;
    int t3;
    long int t4;
    long long int t5;
    float t6;
    double t7;
    long double t8;

    unsigned char ut1;
    unsigned short ut2;
    unsigned int ut3;
    unsigned long int ut4;
    unsigned long long int ut5;
    
    fflush(stdin);

    printf("Entrez un char : \n");
    scanf("%c",&t1);
    printf("vous avez entré : %c \n",t1);

    printf("Entrez un short : \n");
    while(getchar()!='\n');
    scanf("%hd",&t2);
    printf("vous avez entré : %hd \n",t2);

    printf("Entrez un int : \n");
    while(getchar()!='\n');
    scanf("%i",&t3);
    printf("vous avez entré : %i \n",t3);

    printf("Entrez un long int : \n");
    while(getchar()!='\n');
    scanf("%ld",&t4);
    printf("vous avez entré : %ld \n",t4);

    printf("Entrez un long long int  : \n");
    while(getchar()!='\n');
    scanf("%lld",&t5);
    printf("vous avez entré : %lld \n",t5);

    printf("Entrez un float : \n");
    while(getchar()!='\n');
    scanf("%f",&t6);
    printf("vous avez entré : %f \n",t6);

    printf("Entrez un double : \n");
    while(getchar()!='\n');
    scanf("%lg",&t7);
    printf("vous avez entré : %lg \n",t7);

    printf("Entrez un long double : \n");
    while(getchar()!='\n');
    scanf("%Lg",&t8);
    printf("vous avez entré : %Lg \n",t8);

    printf("Entrez un unsigned char : \n");
    while(getchar()!='\n');
    scanf("%c",&ut1);
    printf("vous avez entré : %c \n",ut1);

    printf("Entrez un unsigned short : \n");
    while(getchar()!='\n');
    scanf("%hu",&ut2);
    printf("vous avez entré : %hu \n",ut2);

    printf("Entrez un unsigned int : \n");
    while(getchar()!='\n');
    scanf("%u",&ut3);
    printf("vous avez entré : %u \n",ut3);

    printf("Entrez un unsigned long int : \n");
    while(getchar()!='\n');
    scanf("%lu",&ut4);
    printf("vous avez entré : %lu \n",ut4);

    printf("Entrez un  unsigned long long int  : \n");
    while(getchar()!='\n');
    scanf("%llu",&ut5);
    printf("vous avez entré : %llu \n",ut5);



    return 0;
}
```
## operateur2.c
```c
#include <math.h>
#include <stdio.h>

// +, -, *, /, %, &, |

int main(int argc, char const *argv[])
{
    int a, b;
    char op;
    long int resultat;

    printf("Entrer la valeur de num1 : ");
    fflush(stdin);
    scanf("%i", &a);

    printf("\nEntrer la valeur de num1 : ");
    fflush(stdin);
    scanf("%i", &b);

    while (1)
    {

        printf("Entrer l'operateur choisis entre [+, -, *, /, %%, &, |] : ");
        fflush(stdin);
        while(getchar()!='\n'); //Clear le \n du précédent scanf
        scanf("%c", &op);

        switch (op)
        {
        case '+':
            // printf("%i", a + b);
            resultat = a + b;
            break;

        case '-':
            // printf("%i", a - b);
            resultat = a - b;
            break;

        case '*':
            // printf("%i", a * b);
            resultat = a * b;
            break;

        case '/':
            // printf("%i", a / b);
            resultat = a / b;
            break;

        case '%':
            // printf("%i", a % b);
            resultat = a % b;
            break;

        case '&':
            // printf("%i", a & b:);
            resultat = a & b;
            break;

        case '|':
            // printf("%i", a | b);
            resultat = a | b;
            break;

        default:
            printf("\nOperateur non disponible !\n");
            break;
        }

        printf("Le resultat de %i %c %i est : %ld \n\n", a, op, b, resultat);
    }

    return 0;
}
```
## sizeof_types.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{

    int a;
    /*
        char
        short
        int
        long int
        long long int
        float
        double
        long double
    */
    printf("Taille d'un char : %hu\n", sizeof(char));
    printf("Taille d'un short : %hu\n", sizeof(short));
    printf("Taille d'un int : %hu\n", sizeof(int));
    printf("Taille d'un long int : %hu\n", sizeof(long int));
    printf("Taille d'un long long int : %hu\n", sizeof(long long int));
    printf("Taille d'un float : %hu\n", sizeof(float));
    printf("Taille d'un double : %hu\n", sizeof(double));
    printf("Taille d'un long double : %hu\n", sizeof(long double));

    return 0;
}
```
## operateur.c
```c
#include <math.h>
#include <stdio.h>

int main()
{
    int a = 16, b = 3;

    printf("%i\n", a + b);
    printf("%i\n", a - b);
    printf("%i\n", a * b);
    printf("%i\n", a / b);
    printf("%i\n", a & b);
    printf("%i\n", a && b);
    printf("%i\n", a || b);
    // printf("%i", a ! b);

    return 0;
}
```
## helloworld.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("Hello World");
    return 0;
}
```
## conditions.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{

    for (int i = 0; i <= 1000; i++)
    {
        if ((i % 2 == 0) && (i % 15 == 0))
        {
            printf("%i\n", i);
        }
        else if ((i % 103 == 0) || (i % 107 == 0))
        {
            printf("%i\n", i);
        }
        else if((i%7 == 0 || i%5 == 0) && (i%3 != 0))
        {
            printf("%i\n", i);
        }
    }

    

    return 0;
}
```
## boucle.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{

    int compter;

    printf("Entrer la taille du triangle (min 5) : ");
    fflush(stdin);
    scanf("%i", &compter);

    if (compter < 4)
    {
        printf("Taille de triangle trop petite...");
    }
    else
    {

        for (int i = 0; i < compter; i++)
        {

            if (i == 0)
            {
                printf("*");
            }

            else if (i < compter - 1)
            {
                printf("* ");

                for (int j = 0; j < i - 1; j++)
                {
                    printf("# ");
                }

                printf("*");
            }

            else
            {
                for (int j = 0; j < compter; j++)
                {
                    printf("* ");
                }
            }

            printf("\n");
        }
    }

    return 0;
}```
# TP/TP2

## couleurs.c
```c
#include <stdio.h>

// struct couleur_rgba : rouge, vert, bleu, alpha
typedef struct couleur_rgba {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
} couleur_rgba;

int main(int argc, char const *argv[])
{
    // tableau de valeurs RGBA de 10 couleurs
    couleur_rgba tab_couleur[10] = {
        {0x00, 0x00, 0x00, 0xFF},
        {0xFF, 0x00, 0x00, 0xFF},
        {0x00, 0xFF, 0x00, 0xFF},
        {0x00, 0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x00, 0xFF},
        {0x00, 0xFF, 0xFF, 0xFF},
        {0xFF, 0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF},
        {0x80, 0x80, 0x80, 0xFF},
        {0xC0, 0xC0, 0xC0, 0xFF}
    }; 
    

    // affichage du tableau
    for (int i = 0; i < 10; i++) {
        printf("%d %d %d %d\n", tab_couleur[i].rouge, tab_couleur[i].vert, tab_couleur[i].bleu, tab_couleur[i].alpha);
    }

    return 0;
}
```
## etudiant2.c
```c
#include <stdio.h>

// structure etudiant : 
// nom, prenom, addresse, noteC, noteOS
struct etudiant {
    char nom[20];
    char prenom[20];
    char addresse[30];
    float noteC;
    float noteOS;
};

int main(int argc, char const *argv[])
{
    // creer un tableau de 5 etudiants
    struct etudiant etudiants[5];

    // remplir le tableau
    for (int i = 0; i < 5; i++)
    {
        printf("Etudiant %d\n", i+1);
        printf("Nom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].nom);
        printf("Prenom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].prenom);
        printf("Addresse : ");
        fflush(stdin);
        scanf("%s", etudiants[i].addresse);
        printf("Note C : ");
        fflush(stdin);
        scanf("%f", &etudiants[i].noteC);
        printf("Note OS : ");
        fflush(stdin);
        scanf("%f", &etudiants[i].noteOS);
    }

    // afficher les informations de chaque etudiant
    for (int i = 0; i < 5; i++)
    {
        printf("Etudiant %d\n", i+1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Addresse : %s\n", etudiants[i].addresse);
        printf("Note C : %f\n", etudiants[i].noteC);
        printf("Note OS : %f\n", etudiants[i].noteOS);
    }

    return 0;
}
```
## chaine.c
```c
#include <stdio.h>
// #include <string.h>

int nombre_de_char(char tbl[], int taille, char c);
int str_cpy(char tbl[], int taille);

#define TAILLE 20

int main(int argc, char const *argv[])
{
    int mode = 0;

    char string[] = "Batiste"; //Taille du tableau calculée automatiquement

    // Calcul du nombre de caractere dans la string, sans '\0'
    int cpt = 0;
    for (int i = 0; string[i] != '\0'; i++)
        cpt++;
    int l_string = cpt;

    // Affichage de la string
    printf("Tableau : %s\n", string);

    // Calcule le nombre de fois qu'apparait un caractere dans la string

    printf("Entrer le char a rechercher dans le tableau : ");

    char ch;
    fflush(stdin);
    scanf("%c", &ch);

    printf("Le charactere %c apparait %d fois dans la string [ %s ]", ch, nombre_de_char(string, l_string, ch), string);

    // Copie d'une chaine de caractere dans une autre

    char s1[100], s2[100], i;

    printf("\nEntrer la string 1 : ");
    fflush(stdin);
    scanf("%s", &s1);

    printf("string s1 : %s\n", s1);

    // On tourne dans le tableau donné jusqu'à trouver '\0'
    for (i = 0; s1[i] != '\0'; ++i) {
        // On copie chaque valeur de s1 dans s2
        s2[i] = s1[i];
    }

    // On ajoute le caractere de fin de chaine a la fin de s2
    s2[i] = '\0';

    printf("String s2 : %s\n", s2);

    // Concatenation de deux chaines

    char t1[100], t2[100];

    printf("Entrer s1 : ");
    fflush(stdin);
    scanf("%s", t1);

    printf("Entrer s2 : ");
    fflush(stdin);
    scanf("%s", t2);

    // Concatenation

    int st1 = 0, st2 = 0, x, y;

    // Calcul des tailles de tableau
    for (int i = 0; t1[i] != '\0'; i++)
        st1++;
    for (int i = 0; t2[i] != '\0'; i++)
        st2++;

    printf("l1 : %i | l2 : %i\n", st1, st2);

    char t3[st1 + st2 + 1];

    for (x = 0; x < st1; x++)
    {
        t3[x] = t1[x];
    }

    for (y = 0; y < st2; y++, x++)
    {
        t3[x] = t2[y];
    }

    t3[x] = '\0';
    
    printf("\nt3 : %s\n", t3);

    return 0;
}

int nombre_de_char(char tbl[], int taille, char c)
{
    int cpt = 0;

    for (size_t i = 0; i < taille; i++)
    {
        if (tbl[i] == c)
        {
            cpt++;
        }
    }

    return cpt;
}
```
## bits.c
```c
#include <stdio.h>

#define TAILLE 24

int main(int argc, char const *argv[])
{

    int r, n = 0;
    int dec = 65535;

    int tbl_bin[TAILLE];

    long mask = 0b00010000000000000001;

    printf("%i\n", dec & mask);

    for (int n = 0; n < TAILLE; n++)
    {
        r = dec % 2;
        dec = dec / 2;
        tbl_bin[n] = r;
    }

    for (int i = TAILLE - 1; i >= 0; i--)
    {
        if ((i + 1) % 4)
        {
            printf("%i", tbl_bin[i]);
        }
        else
        {
            printf(" %i", tbl_bin[i]);
        }
    }


    return 0;
}
```
## etudiant.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char tab_etu[5][5][30];
    //[i][j][k]

    int i, j;

    // [Nom] [Prenom] [Adresse] [note1] [note2]

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            switch (j)
            {
            case 0:
                printf("Nom de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 1:
                printf("Prenom de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 2:
                printf("Addresse de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 3:
                printf("Note 1 de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 4:
                printf("Note 2 de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            default:
                break;

            }
        }

        printf("\n");
    }

    int x, y;

    for (x = 0; x < 5; x++)
    {
        for (y = 0; y < 5; y++)
        {
            printf("%s ", tab_etu[x][y]);
        }

        printf("\n");
    }

    return 0;
}
```
## puissance.c
```c
#include <stdio.h>

int puissance(int x, int y);

int main(int argc, char const *argv[])
{
    int a, b;

    printf("== Calcul de a puissance b ==\n");

    printf("Entrer 'a' : ");
    fflush(stdin);
    scanf("%i", &a);

    printf("Entrer 'b' : ");
    fflush(stdin);
    scanf("%i", &b);

    printf("Resulat de %i^%i = %i", a, b, puissance(a, b));

    return 0;
}

int puissance(int x, int y)
{
    int res = 1;

    for (int i = 0; i < y; i++)
    {
        res *= x;
    }

    return res;
}```
## fibonacci.c
```c
#include <stdio.h>
#include <math.h>

void fibonacci(int x);

int main(int argc, char const *argv[])
{

    int n;

    printf("Entrer N : ");
    fflush(stdin);
    scanf("%i", &n);

    fibonacci(n);

    return 0;
}

void fibonacci(int x)
{
    int suivant;
    int u0 = 1;
    int u1 = 1;

    for (int i = 0; i < x; i++)
    {
        if (i <= 1)
        {
            suivant = i;
        }
        else
        {
            suivant = u0 + u1;
            u0 = u1;
            u1 = suivant;
        }
        printf("%d ", suivant);
    }
}```
## tableauptr.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
       


    return 0;
}```
# TP/TP5

## client.c
```c
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

#include <time.h>

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

    // char* path = "./etudiant";

    int **tab_notes = malloc(5 * sizeof(int*));

    for (int i = 0; i < 5; i++)
    {
        tab_notes[i] = malloc(5 * sizeof(int));
    }

    tab_notes = parse_notes();

    // Afficher la matrice notes_etudiant

    printf("\nNotes des etudiants :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Etudiant %d : ", i + 1);
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", tab_notes[i][j]);
        }
        printf("\n");
    }


    float *tab_moyennes = malloc(6 * sizeof(float));

    tab_moyennes = calcul_moyennes(tab_notes);

    // Afficher la matrice moyennes_etudiant
    for (int i = 0; i < 5; i++)
    {
        printf("Moyenne de l'etudiant %d : %0.2f\n", i + 1, tab_moyennes[i]);
    }
    free(tab_notes);

    char data[1024];
    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    char commande_str[1024];

    strcpy(data, "calcul: ");

    strcpy(commande_str, "+ ");

    char *moyenne_str = malloc(10 * sizeof(char));
    sprintf(moyenne_str, "%0.2f", tab_moyennes[5]);
    strcat(commande_str, moyenne_str);
    strcat(commande_str, " 5");
    strcat(data, commande_str);

    free(moyenne_str);

    printf("Commande : %s\n", commande_str);

    // Ecriture du message dans le socket
    int write_status = write(socketfd, data, strlen(commande_str));

    if (write_status < 0)
    {
        perror("erreur ecriture");
        exit(EXIT_FAILURE);
    }

    free(tab_moyennes);


    close(socketfd);
}

float *calcul_moyennes(int **notes)
{
    float *tab_moyennes = malloc(sizeof(float) * 6);

    for (int i = 0; i < 5; i++)
    {
        float somme = 0;
        for (int j = 0; j < 5; j++)
        {
            somme += notes[i][j];
        }
        tab_moyennes[i] = somme / 5;
    }

    // Faire la moyenne des moyennes des etudiants et la mettre dans la siexieme case du tableau
    float somme = 0;
    for (int i = 0; i < 5; i++)
    {
        somme += tab_moyennes[i];
    }
    tab_moyennes[5] = somme;

    return tab_moyennes;
}

int **parse_notes(void)
{
    // ====================== //

    // Récupération des notes

    int **notes_etudiant = malloc(sizeof(int *) * 5);

    for (int i = 0; i < 5; i++)
    {
        notes_etudiant[i] = malloc(sizeof(int) * 5);
    }

    int cpt = 0;

    // Scanner tous les sous dossiers du dossier ./etudiant et afficher le contenu de chaque sous dossier
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./etudiant")) != NULL)
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

                char *path_sous_dossier = malloc(sizeof(char) * (strlen("./etudiant/") + strlen(ent->d_name) + 1));

                strcpy(path_sous_dossier, "./etudiant/");
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

    //Renvoyer la matrice notes_etudiant
    return notes_etudiant;
}```
## serveur.c
```c
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

#define TAILLE 25

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

    printf("aa");

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

        printf("Vous avez entre: %d %c %d\n", cmd.nb1, cmd.op, cmd.nb2); // Afficher le message de l'utilisateur

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
                sprintf(data, "resultat: %0.2f", (float)cmd.nb1/cmd.nb2);
                break;

            default:
                perror("Operateur inconnu");
                return -1;
            break;
        }

        renvoie_message(client_socket_fd, data); // Envoyer le message au client
    }

    // fermer le socket
    // close(socketfd);
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

    // Code de base pour 5.4 et 5.5
    listen(socketfd, 30);

    // Lire et répondre au client
    // recois_envoie_message(socketfd);
    recois_numeros_calcule(socketfd);

    // close(socketfd);

    // ====================== //




    return 0;
}
```
## client.h
```c
/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

// Structure de données pour les calculs
typedef struct {
    char op;
    int nb1;
    int nb2;
} calcul_cmd;

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */
int envoie_recois_message(int socketfd);
int envoie_operateur_numeros(int socketfd);
int **parse_notes(void);
float *calcul_moyennes(int **notes);

#endif
```
## serveur.h
```c
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
```
## test.c
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Tableau de 5 notes de 5 etudiants

    int **tab_notes = malloc(5 * sizeof(int *));

    return 0;
}
```
## repertoire.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "lib/repertoire.h"

/*

*/

int main()
{

    int choix = 0;
    
    char *path = "..";

    printf("\n Path : %s\n", path);
    printf("\n\t Choix de la fonction a executer : \n");
    printf("\t1 - lire_dossier(PATH)\n");
    printf("\t2 - lire_dossier_recursif('PATH')\n");
    printf("\t3 - lire_dossier_iteratif('PATH')\n");
    fflush(stdin);
    scanf("%d", &choix);

    printf("\n\n");

    switch(choix)
    {
        case 1:
            lire_dossier(path);
            break;

        case 2:
            lire_dossier_recursif(path);
            break;
        case 3:
            lire_dossier_iteratif(path);
            break;
        default:
            printf("\n Choix invalide");
            break;
    }

    return 0;
}

// Fonction lire_dossier permettant d'afficher le contenu d'un dossier
void lire_dossier(char *chemin)
{
    DIR *rep;
    struct dirent *ent;
    rep = opendir(chemin);
    if (rep == NULL)
    {
        printf("Erreur d'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

    printf("Contenu du dossier %s : \n", chemin);

    while ((ent = readdir(rep)) != NULL)
    {
        printf("%s\n", ent->d_name);
    }
    closedir(rep);
}

// Fonction lire_dossier_recursif permettant d'afficher le contenu de sous-dossier de façon récursive
void lire_dossier_recursif(char *chemin)
{
    DIR *rep;
    struct dirent *ent;
    struct stat buf;
    rep = opendir(chemin);
    if (rep == NULL)
    {
        printf("Erreur d'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

    printf("Contenu du dossier %s : \n", chemin);

    while ((ent = readdir(rep)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        {
            char *chemin_fichier = malloc(sizeof(char) * (strlen(chemin) + strlen(ent->d_name) + 2));
            strcpy(chemin_fichier, chemin);
            strcat(chemin_fichier, "/");
            strcat(chemin_fichier, ent->d_name);
            stat(chemin_fichier, &buf);
            if (S_ISDIR(buf.st_mode))
            {
                lire_dossier_recursif(chemin_fichier);
            }
            else
            {
                printf("%s\n", chemin_fichier);
            }
            free(chemin_fichier);
        }
    }
    closedir(rep);
}

// Fonction lire_dossier_iteratif permettant d'afficher le contenu de sous-dossier sans récursivité
void lire_dossier_iteratif(char *chemin)
{
    DIR *rep;
    struct dirent *ent;
    struct stat buf;

    char chemins[100][100];

    strcpy(chemins[0], chemin);

    printf("Contenu du dossier %s : \n", chemin);

    // Tant que chemins[0] n'est pas vide, afficher le contenu de chemins[0]
    // if chemins[0] est vide, alors on décale le tableau de 1 case vers la gauche
    // et on affiche le contenu de chemins[0]
    while (strcmp(chemins[0], "") != 0)
    {
        printf("\n\t## Scan du dossier %s ##\n", chemins[0]);

        rep = opendir(chemins[0]);
        if (rep == NULL)
        {
            printf("Erreur d'ouverture du dossier %s", chemins[0]);
            exit(EXIT_FAILURE);
        }
        int i = 0;
        while ((ent = readdir(rep)) != NULL)
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                char *chemin_fichier = malloc(sizeof(char) * (strlen(chemins[0]) + strlen(ent->d_name) + 2));
                strcpy(chemin_fichier, chemins[0]);
                strcat(chemin_fichier, "/");
                strcat(chemin_fichier, ent->d_name);
                stat(chemin_fichier, &buf);
                if (S_ISDIR(buf.st_mode))
                {
                    strcpy(chemins[i + 1], chemin_fichier);
                    i++;
                    printf("%s DOSSIER\n", chemin_fichier);
                }
                else
                {
                    printf("%s\n", chemin_fichier);
                }
                free(chemin_fichier);
            }
        }
        closedir(rep);
        strcpy(chemins[0], chemins[1]);
        for (int j = 1; j < 10; j++)
        {
            strcpy(chemins[j], chemins[j + 1]);
        }
    }
}```
# TP/TP5/lib

## repertoire.h
```c
void lire_dossier(char *chemin);
void lire_dossier_recursif(char *chemin);
void lire_dossier_iteratif(char *chemin);```
# TP/TP5/etudiant

# TP/TP5/etudiant/4

# TP/TP5/etudiant/1

# TP/TP5/etudiant/3

# TP/TP5/etudiant/5

# TP/TP5/etudiant/2

# TP/TP5/test

# TP/TP4

# TP/TP4/4.5

## factorielle.c
```c
#include <stdio.h>
#include <math.h>

int factorielle(int num);

int main(int argc, char const *argv[])
{

    int n;

    printf("Entrer un nombre : ");
    fflush(stdin);
    scanf("%d", &n);

    printf("%d", factorielle(n));  


    return 0;
}

int factorielle(int num)
{
    if (num == 0)
    {
        return 1;
    }
    else
    {
        return num * factorielle(num - 1);
    }
}```
# TP/TP4/4.4

## operator.h
```c

// Prototype de fonction
int somme (int a, int b);
int soustraction (int a, int b);
int multiplication (int a, int b);
int division (int a, int b);
int modulo (int a, int b);
int et (int a, int b);
int ou (int a, int b);
int negation (int a);```
## operator.c
```c
#include <math.h>
#include <stdbool.h>
#include "operator.h"

// somme, différence, produit, quotient, modulo, 'et', ou et négation

// fonction somme
// somme de deux entiers
int somme(int a, int b)
{
    return a + b;
}

// fonction soustraction
// soustraction de deux entiers
int soustraction(int a, int b)
{
    return a - b;
}

// fonction multiplication
// multiplication de deux entiers
int multiplication(int a, int b)
{
    return a * b;
}

// fonction division
// division de deux entiers
int division(int a, int b)
{
    return a / b;
}

// fonction modulo
// modulo de deux entiers
int modulo(int a, int b)
{
    return a % b;
}

// fonction et
// et de deux entiers
int et(int a, int b)
{
    return a & b;
}

// fonction ou
// ou de deux entiers
int ou(int a, int b)
{
    return a | b;
}

// fonction negation
// negation d'un entier
int negation(int a)
{
    return ~a;
}

```
## calcule.c
```c
#include <stdio.h>
#include <stdlib.h>
#include "operator.h"

/*
    pour compiler : 
    gcc -Wall -c ./calcule.c ./operator.c
    gcc -o calcule ./calcule.o ./operator.o
*/


/*
    Utilisation du programme :
    $ calcul [operateur] [nombre1] [nombre2]
    [operateur] : +, -, x, /, %, &, |, ~
    Exemple :
        > calcul + 2 3
        > 5
*/

int main(int argc, char const *argv[])
{
    int nb1 = atoi(argv[2]), nb2 = atoi(argv[3]);
    char operateur = *argv[1];

    long int resultat;
    
    // printf("%d\n", argc);

    // afficher le contenu de argv
    // for (int i = 0; i < argc; i++)
    // {
        // printf("argv[%d] = %s\n", i, argv[i]);
    // }

    printf("\n");

    switch (operateur)
        {
        case '+':
            resultat = somme(nb1, nb2);
            break;
        case '-':
            resultat = soustraction(nb1, nb2);
            break;
        // case '*':
        case 'x': // Utilisation d'un char 'x' pour '*' sur Windows
            resultat = multiplication(nb1, nb2);
            break;
        case '/':
            resultat = division(nb1, nb2);
            break;
        case '%':
            resultat = modulo(nb1, nb2);
            break;
        case '&':
            resultat = et(nb1, nb2);
            break;
        case '|':
            resultat = ou(nb1, nb2);
            break;
        case '~':
            resultat = negation(nb1);
            break;
        default:
            printf("\nErreur : operateur non reconnu\n");
            break;
        }

        printf("Le resultat de %i %c %i est : %ld \n\n", nb1, operateur, nb2, resultat);
    
    return 0;
}```
# TP/TP4/4.6

## chercherfichier.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBR_LIGNE 1000
#define TAILLE_LIGNE 200

/*
    Utilisation du programme :
    ./chercherfichier [MOT_A_CHERCHER] [NOM_FICHIER]
*/

int main(int argc, char const *argv[])
{
    
    // récupération de chaque ligne du fichier argv[2]
    FILE *fichier = NULL;
    char ligne[TAILLE_LIGNE]; // tableau de caractères pour stocker une ligne du fichier
    int i = 0;
    
    fichier = fopen(argv[2], "r"); // ouverture en lecture du fichier argv[2]
    
    if (fichier != NULL) // vérification de l'existance ou non du fichier
    {
        // tant qu'on a pas atteint la fin du fichier
        while (fgets(ligne, TAILLE_LIGNE, fichier) != NULL)
        {
            // trouver le nombre d'occurence du mot argv[1] dans ligne
            int nbr_occurence = 0;
            const char *mot = argv[1];
            char *ptr = strstr(ligne, mot);
            while (ptr != NULL)
            {
                nbr_occurence++;
                ptr = strstr(ptr + 1, mot);
            }
            
            if(nbr_occurence != 0)
            {
                printf("Ligne %d: %d fois\n", i + 1, nbr_occurence);
            }

            i++;
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier chercherfichier.c\n");
    }    
    
    return 0;
}
```
## fichier.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

#define TAILLE_MAX 1000

// Fonction qui lit un fichier et renvoie le contenu dans un tableau
char *lire_fichier(char *nom_de_fichier)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];
    char tab_chaine[100][TAILLE_MAX];

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    int i = 0;

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        strcpy(tab_chaine[i], chaine);
        i++;
    }

    fclose(fichier);
    return tab_chaine;
}

// Fonction qui ecrit message dans un fichier
int ecrire_dans_fichier(char *nom_de_fichier, char *message)
{
    FILE *fichier;
    fichier = fopen(nom_de_fichier, "a");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }
    fprintf(fichier, "%s\n", message);
    fclose(fichier);
    return 0;
}

// Fonction qui chercher une chaine dans un fichier et qui affiche le nombre de fois qu'elle apparait dans chaque ligne
int chercher_dans_fichier(char *nom_de_fichier, char *chaine_a_chercher)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];
    char tab_chaine[100][TAILLE_MAX];
    int i = 0;
    int j = 0;
    int k = 0;
    int nb_occurence = 0;

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        strcpy(tab_chaine[i], chaine);
        i++;
    }

    for (j = 0; j < i; j++)
    {
        for (k = 0; k < strlen(tab_chaine[j]); k++)
        {
            if (tab_chaine[j][k] == chaine_a_chercher[0])
            {
                if (strstr(tab_chaine[j], chaine_a_chercher) != NULL)
                {
                    nb_occurence++;
                }
            }
        }
    }

    printf("La chaine %s apparait %d fois dans le fichier %s\n", chaine_a_chercher, nb_occurence, nom_de_fichier);
    fclose(fichier);
    return 1;
}```
## fichier.h
```c
char *lire_fichier(char *nom_de_fichier);
int ecrire_dans_fichier(char *nom_de_fichier, char *message);
int chercher_dans_fichier(char *nom_de_fichier, char *mot_a_chercher);```
# TP/TP4/4.2

## fichier.c
```c
#include <stdio.h>
#include "fichier.h"

#define TAILLE_MAX 1000


int lire_fichier(char *nom_de_fichier)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        printf("%s", chaine);
    }

    fclose(fichier);
    return 1;
}


int ecrire_dans_fichier(char *nom_de_fichier, char *message)
{
    FILE *fichier;
    fichier = fopen(nom_de_fichier, "a");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }
    fprintf(fichier, "%s\n", message);
    fclose(fichier);
    return 0;
}```
## main.c
```c
#include <stdio.h>
#include "fichier.h"

/*
    pour compiler : 
    gcc -Wall -c ./fichier.c ./main.c
    gcc -o main ./fichier.o ./main.o
*/

int main(int argc, char const *argv[])
{
    

    // afficher le contenu du fichier avant modification
    printf("Fichier avant modification : \n");
    lire_fichier("fichier.txt");

    printf("\n");

    // demander à l'utilisateur d'entrer une chaine de caractère
    char str[100];
    printf("Enter a string: ");
    fflush(stdin);
    scanf("%s", str);

    // ecrire la chaine str dans le fichier fichier.txt 
    ecrire_dans_fichier("fichier.txt", str);

    // afficher le contenu du fichier apres modification
    printf("Fichier apres modification : \n");
    lire_fichier("fichier.txt");

    return 0;
}```
## fichier.h
```c
int lire_fichier(char *nom_de_fichier);
int ecrire_dans_fichier(char *nom_de_fichier, char *message);```
# TP/TP4/4.3

## fichier.c
```c
#include <stdio.h>
#include "fichier.h"

#define TAILLE_MAX 1000

int lire_fichier(char *nom_de_fichier)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        printf("%s", chaine);
    }

    fclose(fichier);
    return 1;
}

int ecrire_dans_fichier(char *nom_de_fichier, char *message)
{
    FILE *fichier;
    fichier = fopen(nom_de_fichier, "a");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }
    fprintf(fichier, "%s\n", message);
    fclose(fichier);
    return 0;
}```
## fichier.h
```c
int lire_fichier(char *nom_de_fichier);
int ecrire_dans_fichier(char *nom_de_fichier, char *message);```
## etudiant_bd.c
```c
#include <stdio.h>
#include "fichier.h"
#include <string.h>

/*
    Pour compiler
    gcc -Wall -c ./fichier.c ./etudiant_bd.c
    gcc -o etudiant_bd ./fichier.o ./etudiant_bd.o
*/

// structure etudiant : 
// nom, prenom, addresse, noteC, noteOS
struct etudiant {
    char nom[20];
    char prenom[20];
    char addresse[30];
    char noteC;
    char noteOS;
};

int main(int argc, char const *argv[])
{
    
    // creer un tableau de 5 etudiants
    struct etudiant etudiants[5];

    // remplir le tableau
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("Etudiant %d\n", i+1);
        printf("Nom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].nom);
        printf("Prenom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].prenom);
        printf("Addresse : ");
        fflush(stdin);
        scanf("%s", etudiants[i].addresse);
        printf("Note C : ");
        fflush(stdin);
        scanf("%c", &etudiants[i].noteC);
        printf("Note OS : ");
        fflush(stdin);
        scanf("%c", &etudiants[i].noteOS);
    }

    for (i = 0; i < 5; i++)
    {
        // concatener les champs nom, prenom, addresse, noteC, noteOS
        char string_final[100];
        strcpy(string_final, etudiants[i].nom);
        strcat(string_final, ", ");
        strcat(string_final, etudiants[i].prenom);
        strcat(string_final, ", ");
        strcat(string_final, etudiants[i].addresse);
        strcat(string_final, ", ");
        strcat(string_final, &etudiants[i].noteC);
        strcat(string_final, ", ");
        strcat(string_final, &etudiants[i].noteOS);
    
        // ecrire dans un fichier
        ecrire_dans_fichier("etudiant_bd.txt", string_final);

    }
    
    // afficher le contenu d'un fichier
    lire_fichier("etudiant_bd.txt");

    return 0;
}
```
# TP/TP4/4.7

## liste.c
```c
#include <stdio.h>
#include "liste.h"

int main()
{
// On declare un structure qui va contenir les couleurs (la liste) ainsi que sa tete vide
  struct liste_couleurs liste;
  liste.tete = NULL;
  // Puis un tableau de 10 couleurs
  struct Couleur tab_couleur[10];

    tab_couleur[0].r=0x10;
    tab_couleur[0].g=0x20;
    tab_couleur[0].b=0x30;
    tab_couleur[0].a=0xe2;

    tab_couleur[1].r=0xf5;
    tab_couleur[1].g=0x15;
    tab_couleur[1].b=0x25;
    tab_couleur[1].a=0xa1;

    tab_couleur[2].r=0x32;
    tab_couleur[2].g=0xc4;
    tab_couleur[2].b=0x88;
    tab_couleur[2].a=0xf1;

    tab_couleur[3].r=0x90;
    tab_couleur[3].g=0x70;
    tab_couleur[3].b=0x50;
    tab_couleur[3].a=0xd5;

    tab_couleur[4].r=0x87;
    tab_couleur[4].g=0x67;
    tab_couleur[4].b=0x16;
    tab_couleur[4].a=0xba;

    tab_couleur[5].r=0x29;
    tab_couleur[5].g=0xd4;
    tab_couleur[5].b=0x16;
    tab_couleur[5].a=0xbc;

    tab_couleur[6].r=0x31;
    tab_couleur[6].g=0xbe;
    tab_couleur[6].b=0x51;
    tab_couleur[6].a=0x77;

    tab_couleur[7].r=0x44;
    tab_couleur[7].g=0x67;
    tab_couleur[7].b=0x82;
    tab_couleur[7].a=0x7e;

    tab_couleur[8].r=0xc7;
    tab_couleur[8].g=0x67;
    tab_couleur[8].b=0x1f;
    tab_couleur[8].a=0x8a;

    tab_couleur[9].r=0x81;
    tab_couleur[9].g=0x37;
    tab_couleur[9].b=0x26;
    tab_couleur[9].a=0xba;

    insertion(&tab_couleur[0],&liste);
    insertion(&tab_couleur[1],&liste);
    insertion(&tab_couleur[2],&liste);
    insertion(&tab_couleur[3],&liste);
    insertion(&tab_couleur[4],&liste);
    insertion(&tab_couleur[5],&liste);
    insertion(&tab_couleur[6],&liste);
    insertion(&tab_couleur[7],&liste);
    insertion(&tab_couleur[8],&liste);
    insertion(&tab_couleur[9],&liste);
    parcours(&liste);
}

void insertion (struct Couleur *couleur, struct liste_couleurs *liste)
{
    //Si la tete de liste est vide, on lui assigne la premiere couleurs
   if(liste->tete == NULL)
   {
       liste->tete = couleur;
       liste->tete->suivant = NULL;
   }
   else
   {
       // Sinon on parcours jusqu'a trouver un element "suivant" vide, dans lequel on assigne alors la couleur
       struct Couleur *iter = liste->tete;
        while(iter->suivant != NULL)
        {

            iter = iter->suivant;
        }
        iter->suivant = couleur;
        couleur->suivant = NULL;
   }
}   
// Tant qu'un élément n'est pas vide, on l'affiche et on accede au suivant.          
void parcours (struct liste_couleurs *liste)
{
    printf("[ rouge : %x | vert : %x | bleu : %x | alpha : %x ]\n",liste->tete->r,liste->tete->g,liste->tete->b,liste->tete->a);
    struct Couleur *iter = liste->tete;
    
    while(iter->suivant != NULL)
        {
            printf("[ rouge : %x | vert : %x | bleu : %x | alpha : %x ]\n",iter->suivant->r,iter->suivant->g,iter->suivant->b,iter->suivant->a);
            iter = iter->suivant;
        }
   
}
//gcc liste.c -o liste -Wall -Wextra -g



```
## liste.h
```c
struct Couleur {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        struct Couleur *suivant; 
    };

struct liste_couleurs{
        struct Couleur *tete;
};

void insertion (struct Couleur *, struct liste_couleurs *);                
void parcours (struct liste_couleurs *);










































//gcc -c -Wall -Wextra -g main.c
//gcc -c -Wall -Wextra -g fonction.c 
//gcc fonction.o main.o -o main 
//./main
//CFLAGS=-Wall -Wextra -g
//all:main 
//main: main.o fonction.o
//main.o fonction.h main.c 
//make
```
# TP/TP4/4.1

## operator.h
```c

// Prototype de fonction
int somme (int a, int b);
int soustraction (int a, int b);
int multiplication (int a, int b);
int division (int a, int b);
int modulo (int a, int b);
int et (int a, int b);
int ou (int a, int b);
int negation (int a);```
## main.c
```c
#include <stdio.h>
#include "operator.h"

/*
    pour compiler : 
    gcc -Wall -c ./operator.c ./main.c
    gcc -o main ./operator.o ./main.o
*/

int main(int argc, char const *argv[])
{

    // demander deux nombres et un operateur
    int nb1, nb2;
    char op;
    long int resultat;

    printf("a");

    printf("Entrer la valeur de num1 : ");
    fflush(stdin);
    scanf("%i", &nb1);

    printf("\nEntrer la valeur de num1 : ");
    fflush(stdin);
    scanf("%i", &nb2);

    while (1)
    {
        printf("Entrer l'operateur choisis entre [+, -, *, /, %%, &, |, ~] : ");
        fflush(stdin);
        scanf("%c", &op);

        switch (op)
        {
        case '+':
            resultat = somme(nb1, nb2);
            break;
        case '-':
            resultat = soustraction(nb1, nb2);
            break;
        case '*':
            resultat = multiplication(nb1, nb2);
            break;
        case '/':
            resultat = division(nb1, nb2);
            break;
        case '%':
            resultat = modulo(nb1, nb2);
            break;
        case '&':
            resultat = et(nb1, nb2);
            break;
        case '|':
            resultat = ou(nb1, nb2);
            break;
        case '~':
            resultat = negation(nb1);
            break;
        default:
            printf("\nErreur : operateur non reconnu\n");
            break;
        }


        printf("Le resultat de %i %c %i est : %ld \n\n", nb1, op, nb2, resultat);
    }

    return 0;
}
```
## operator.c
```c
#include <math.h>
#include <stdbool.h>
#include "operator.h"

// somme, différence, produit, quotient, modulo, 'et', ou et négation

// fonction somme
// somme de deux entiers
int somme(int a, int b)
{
    return a + b;
}

// fonction soustraction
// soustraction de deux entiers
int soustraction(int a, int b)
{
    return a - b;
}

// fonction multiplication
// multiplication de deux entiers
int multiplication(int a, int b)
{
    return a * b;
}

// fonction division
// division de deux entiers
int division(int a, int b)
{
    return a / b;
}

// fonction modulo
// modulo de deux entiers
int modulo(int a, int b)
{
    return a % b;
}

// fonction et
// et de deux entiers
int et(int a, int b)
{
    return a & b;
}

// fonction ou
// ou de deux entiers
int ou(int a, int b)
{
    return a | b;
}

// fonction negation
// negation d'un entier
int negation(int a)
{
    return ~a;
}

```
