# Rendu Batiste LALOI

Identification des ID des trames vcan0 permettant de faire des actions sur la voiture :

Utilisation de la commande `cansend vcan0 123#[trame]`

* 123 : Intéragir avec les lumières de la voiture :

| Trame | Action |
| --- | --- |
| 123 00 00 | Tout éteindre |
| 123 00 01 | Allumer les clignotants gauches |
| 123 00 02 | Allumer les clignotants droits |
| 123 00 03 | Allumer les warnings |
| 123 01 00 | Feux de position |
| 123 02 00 | Feu de route |

* 321 : Intéragir avec le volant et les pédales de la voiture

| Trame | Plage XX | Action |
| --- | --- | --- |
| 321 XX 00 00 | 01 - 64 | Volant à gauche |
| 321 XX 00 00 | FF - 9C | Volant à droite |
| 321 00 XX 00 | 00 - 64 | Appui sur le frein |
| 321 00 00 XX | 00 - 64 | Appui sur l'accélérateur |