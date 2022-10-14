#define CLE1 1
#define CLE2 2
#include "../tp4.h"

void ex1() {
    int my_semaphore;
    my_semaphore = sem_create(CLE, 0);
    printf("P1 : Sémaphore %d\n", my_semaphore);

    printf("P1 : Exécute T1 quand T2 est fini\n");
    for(int i = 0; i < 3; i++) {
        printf("-- T1 : étape %d\n", i+1);
        sleep(2);
    }
    printf("T1 : FIN\n\n");
    
    // Je pose un jeton dans le sémaphore, que P2 va pouvoir récupérer
    V(my_semaphore);
}

void RDV1(int sem) {
    printf("P1 : Je suis en RDV\n");
    P(sem);
    printf("P1 : Je sors du RDV\n");
    exit(0);
}

void ex2() {
    int sem1, sem2;
    sem1 = sem_create(CLE1, 0);
    sem2 = sem_create(CLE2, 0);
    printf("P1 : Sem1 %d - Sem2 %d\n", sem1, sem2);

    printf("P1 : Je suis prêt pour le rdv.\n");
    V(sem2);

    RDV1(sem1);

    printf("P1 : FIN\n");
}

int main(int argc, char *argv[]) {
    // ex1();
    ex2();
    return 0;
}
