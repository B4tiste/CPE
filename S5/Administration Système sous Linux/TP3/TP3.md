# Batiste Laloi
## TP 3

## Ex 1 Commandes de base

1. Mise à jour du système

    Détection des paquets pouvant être mis à jour :
    
    > sudo apt update

    Mise à jour des paquets :

    > sudo apt upgrade

2. Création de l'alias `maj`

    Création d'un alias :

    > alias maj='sudo apt update && sudo apt upgrade'

    On écrit cette ligne de code dans le fichier `.bashrc` pour que cet alias soit sauvegardé sur le disque

    > nano ~/.bashrc

3. Fichier `/var/log/dpkg.log`

    Afficher les 5 derniers paquets insatllés sur la machine

    > tail -n 5 dpkg.log

4. Afficher les paquets installés avec `apt install`

    > apt list --installed

5. Compter le nombre de paquets installés sur la machine

    ```console
    root@LAPTOP-I755TR12:~# dpkg --list | wc -l
    601
    root@LAPTOP-I755TR12:~# apt list --installed | wc -l
    597
    ```

    La faible différence est causée par le fait que dpkg compte les paquets installés avec autre chose que `apt install`

6. Combien de paquets sont disponibles au dans les dépôts Ubuntu

    > apt list | wc -l
    
    Sortie : 67 506

7. A quoi servent les paquets glances, tldr et hollywood ? Installez-les et testez-les

    > sudo apt install glances

    `glances` permet de connaître l'état du système

    > sudo apt install 

    `tldr` permet de simplifier les pages du manuel, et donne des exemples d'utilisation des commandes

    > sudo apt install hollywood

    `hollywood` permet d'afficher un faux terminal "Comme dans les films"

8. Quels paquets permettent de jouer au sudoku ?

    > sudo apt install gnome-sudoku

    `gnome-sudoku` permet de jouer au sudoku