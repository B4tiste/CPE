#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#define CLE 1

// Création ou récupération d'un sémaphore 
// Initialisation de la valeur du sémaphore
int sem_create(key_t cle, int init_val) {
    int sem_id;
    union semun { 
        int val; 
        struct semid_ds *buf; 
        ushort *array; 
    } arg_ctl;

    sem_id = semget(cle, 1, IPC_CREAT|IPC_EXCL|0666);

    // Si la création du sémaphore a échoué, on tente de récupérer l'existant
    if (sem_id == -1) {
        sem_id = semget(cle, 1, 0666);
        if (sem_id == -1) {
            perror("Erreur semget()");
            exit(1);
        }
    } else {
        arg_ctl.val = init_val;
        if (semctl(sem_id, 0, SETVAL, arg_ctl) == -1) {
            perror("Erreur initialisation sémaphore"); 
            exit(1);
        }
    }

    return(sem_id);
}

// Opération V
void P(int sem_id) {
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = -1;
    sempar.sem_flg = 0;
    if (semop(sem_id, &sempar, 1) == -1)
        perror("Erreur operation P");
} 

void V(int sem_id){
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = 1;
    sempar.sem_flg = 0;
    if (semop(sem_id, &sempar, 1) == -1)
        perror("Erreur opération V");
} 

void sem_delete(int sem_id){
    if (semctl(sem_id, 0, IPC_RMID, 0) == -1)
        perror("Erreur dans destruction sémaphore");
}
