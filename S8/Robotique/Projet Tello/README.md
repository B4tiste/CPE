# Rapport Projet Drone Tello

## Batiste LALOI, Raphael LARUE, Alexis LONCHAMBON

### Controle du drone à la manette

Le drone est controlé à la manette de la même manière que lors du TP en Ros1. Le code se trouve dans le noeud `control_node.py` du package `src/control`

Ce code contient aussi la gestion des modes de vol du drone, ainsi que la communication d'un booléen sur le topic `/qr` permettant au noeud `qr_code_cv2.py` du package `src/qr_code` de savoir si le drone est dans le mode de vol `QR Code` ou non (suivi de QR Code activé ou non).

### Suivi de QR Code

Voila comment le code fonctionne dans les grandes lignes :

- On récupère l'image du drone sur le topic `/image_raw` et on la convertit en image OpenCV
- On détecte les QR Code dans l'image
- Si on en détecte un, on vérifie son contenu
- Si le contenu est `start` et que le drone n'est pas en vol, on fait décoller le drone
- Si le contenu est `finish` et que le drone est en vol, on fait atterir le drone
- Si le contenu est `BITE` ou `red_block`, on affiche le QR Code et on calcule la position du QR Code par rapport au centre de l'image. Le drone se déplace alors en fonction de la position du QR Code dans l'image, avec une zone morte de 100px autour du centre de l'image permettant de ne pas faire bouger sans cesse le drone lorsqu'il est proche de son état stable.

### Vidéos

Vidéos de démonstration de la fonctionnalité de suivi de QR Code :

- Démonstration en personne : [Démo](https://youtu.be/PklBKns2mJU)
- Rendu visuel sur l'écran de l'ordinateur de la démo : [Vidéo Youtube](https://youtu.be/PklBKns2mJU)

Vidéo finale de démonstration du projet :
- Démonstration finale du projet (Activez les sous titres pour négliger le bruit du drone en vol) : [Démo Projet](https://youtu.be/Z6iEBzqYi7E)