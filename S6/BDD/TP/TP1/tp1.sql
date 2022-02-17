/*
 BASE DE DONNE DE L'APPLICATION
 
 FILM (NUMFILM, TITRE, GENRE, ANNEE, LONGUEUR, BUDGET, NB_SPECTATEUR_CUMULE, #REALISATEUR, SALAIRE_REAL)
 
 PERSONNE (NUMPERSONNE, PRENOM, NOM, DATENAIS, NATIONALITE, ADRESSE, CP, VILLE, TELEPHONE)
 
 ACTEUR (NUMACTEUR, #NUMPERSONNE, #AGENT, #SPECIALITE, TAILLE, POIDS)
 
 GENRE (NUMGENRE, LIBELLEGENRE)
 
 DISTRIBUTION (#NUMFILM, #NUMACTEUR, ROLE, SALAIRE)
 
 CINEMA (NUMCINEMA, NOM, ADRESSE, VILLE, TELEPHONE, COMPAGNIE)
 
 SALLE (#NUMCINEMA, NUMSALLE, TAILLE_ÉCRAN, NBPLACES)
 
 PROGRAMMATION (#NUMFILM, #[NUMCINEMA, NUMSALLE], DATE_DEB, DATE_FIN, HORAIRE, PRIX)
 */

-- 1 :

SELECT
    *
FROM
    personne
WHERE
    adresse LIKE '%Avenue%'

-- 2 :

UPDATE
    personne
SET
    telephone = 'N''a pas d''amis'
WHERE
    telephone IS NULL

-- 3 : Affichage des Noms et Prénoms des réalisateurs habitants dans une ville commençant par N

SELECT
    DISTINCT nom,
    prenom
FROM
    personne
    JOIN film ON numpersonne = realisateur
WHERE
    ville LIKE 'N%'

-- 4 : Afficher tous les films (TITRE, ANNEE, REALISATEUR) qui n’ont pas été réalisés par Spielberg

SELECT
    film.titre,
    film.annee,
    personne.nom,
    personne.prenom
FROM
    film
    JOIN personne ON personne.numpersonne = film.realisateur
WHERE
    personne.nom NOT LIKE 'Spielberg'

-- 5 : Afficher pour chaque réalisateur (nom, prénom) et chaque film (titre) son salaire à la minute de film

SELECT
    P.nom,
    P.prenom,
    F.titre,
    F.salaire_real / F.longueur
FROM
    film F
    JOIN personne P ON P.numpersonne = F.realisateur

-- 6 : Afficher pour chaque film, les nom et prénom des acteurs et leur salaire (afficher le titre du film par ordre alphabétique et le salaire par ordre décroissant)

SELECT
    F.titre,
    P.nom,
    P.prenom,
    D.salaire
FROM
    film F
    JOIN distribution D ON F.numfilm = D.numfilm
    JOIN acteur A ON D.numacteur = A.numacteur
    JOIN personne P ON P.numpersonne = A.numpersonne
ORDER BY
    F.titre,
    D.salaire DESC 
    
-- 7 : Quels sont les acteurs dramatiques (nom, prénom) qui ont joué dans un film de Spielberg.

SELECT
    P.nom,
    P.prenom
FROM
    personne P
    JOIN acteur A ON P.numpersonne = A.numpersonne
    JOIN genre G ON A.specialite = G.numgenre
    JOIN distribution D ON A.numacteur = D.numacteur
    JOIN film F ON D.numfilm = F.numfilm
    JOIN personne Pers ON F.realisateur = Pers.numpersonne
WHERE
    G.libellegenre = 'Drame'
    AND Pers.nom = 'Spielberg'

-- 8 : Quels sont les cinémas indépendants Bordelais, avec le film correspondant, qui passent un film
--      de Woody Allen à partir de 22 heures dans une salle d'au moins 100 places et d'écran de taille
--      supérieure à 30 m2

