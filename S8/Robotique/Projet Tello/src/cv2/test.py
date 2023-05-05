#!/usr/bin/env python3

import sys
import time
import cv2
import imutils
import numpy as np
import sklearn

# Fonction pour afficher la position du code QR et le rectangle qui l'entoure
def display(img, bbox):
    n = len(bbox)

    # Récupérer les coordonnées des angles en haut à gauche et en bas à droite
    pt1 = int(bbox[0][0][0]), int(bbox[0][0][1])    # angle en haut à gauche
    pt2 = int(bbox[0][2][0]), int(bbox[0][2][1])    # angle en bas à droite
    
    # Couleur du rectangle (rouge)
    color = (0, 0, 255)

    # Dessiner la diagonale du rectangle
    # cv2.line(img, pt1, pt2, color, 3)

    # Mettre un cercle au milieu de cette diagonale
    cv2.circle(img, (int((pt1[0]+pt2[0])/2), int((pt1[1]+pt2[1])/2)), 5, color, -1)

    # Afficher l'image avec le rectangle
    cv2.imshow("Results", img)

# Fonction principale
def main():
    # Ouvrir la caméra
    cap = cv2.VideoCapture(0)
    time.sleep(2.0)

    while True:
        # Lire les images de la caméra
        ret, frame = cap.read()
        cv2.imshow("frame", frame)
        key = cv2.waitKey(1) & 0xFF
        
        # Créer un objet QRCodeDetector
        qr_decoder = cv2.QRCodeDetector()
    
        # Détecter et décoder le code QR
        data, bbox, rectified_image = qr_decoder.detectAndDecode(frame)
        
        # Si un code QR est détecté
        if len(data)>0:
            # Afficher les données décodées
            print("Decoded Data : {}".format(data))
            
            # Afficher le rectangle autour du code QR
            display(frame, bbox)
            
            # Afficher l'image redressée du code QR
            rectified_image = np.uint8(rectified_image);
            cv2.imshow("Rectified QRCode", rectified_image);
        else:
            # Si aucun code QR n'est détecté, afficher l'image originale
            print("QR Code not detected")
            cv2.imshow("Results", frame)

# Appeler la fonction principale
main()
