# Projet : TurtleBot Rangeur d'Espace avec Commandes Vocales

![Image](./image/sujet.png)

```mermaid
graph TD;
    A[Utilisateur] -->|Commandes Vocales| B[Module Speech to Text]
    B -->|Texte Interprété| C[Contrôleur Principal]
    C -->|Instructions de Navigation| D[Module de Navigation]
    C -->|Instructions de Préhension| E[Module de Préhension]
    D -->|Données de Cartographie| F[Capteurs LIDAR/Ultrasoniques]
    D -->|Détection d'Obstacles| G[Caméra et Vision par Ordinateur]
    G -->|Identification d'Objets| C
    E -->|Manipulation d'Objets| H[Bras Robotique/Mécanisme de Préhension]
    C -->|Feedback| I[Interface Utilisateur]
    I -->|Visualisation et Contrôle| A

    style A fill:#f9f,stroke:#333,stroke-width:2px
    style B fill:#bbf,stroke:#333,stroke-width:2px
    style C fill:#fb4,stroke:#333,stroke-width:2px
    style D fill:#f96,stroke:#333,stroke-width:2px
    style E fill:#9f6,stroke:#333,stroke-width:2px
    style F fill:#6cf,stroke:#333,stroke-width:2px
    style G fill:#fc6,stroke:#333,stroke-width:2px
    style H fill:#ff6,stroke:#333,stroke-width:2px
    style I fill:#6f9,stroke:#333,stroke-width:2px

```

## Objectif Global
Développer un système logiciel pour un TurtleBot qui navigue dans un espace, identifie, trie, et range des objets dispersés (balles, objets en plastique, etc.) dans une zone de stockage définie, avec la possibilité de recevoir des instructions vocales.

### 1. Navigation et Cartographie
- **Cartographie de l'Espace** : Création d'une carte de la zone à ranger avec des capteurs.
- **Navigation Autonome** : Algorithme pour le déplacement autonome du TurtleBot.

### 2. Détection et Tri d'Objets
- **Reconnaissance d'Objets** : Identification des objets au sol via vision par ordinateur.
- **Classification des Objets** : Catégorisation automatique des objets détectés.
- **Système de Tri** : Mécanisme pour le tri et la séparation des objets.

### 3. Rangement des Objets
- **Manipulation d'Objets** : Utilisation d'un bras robotique pour la collecte et le transport.
- **Dépôt dans Zone de Stockage** : Placement des objets dans une zone prédéfinie.

### 4. Commandes Vocales (Speech to Text)
- **Intégration STT** : Système de reconnaissance vocale pour recevoir des instructions spécifiques.
- **Traitement des Instructions Vocales** : Interprétation et exécution des commandes vocales.
- **Feedback Vocal** : Réponses vocales pour confirmer les actions ou demandes.

### 5. Interface Utilisateur
- **Contrôle et Suivi** : Interface pour le démarrage, l'arrêt, et le suivi du robot.
- **Feedback Visuel** : Retransmission vidéo en direct pour surveillance.

### 6. Sécurité et Fiabilité
- **Gestion des Erreurs et Obstacles** : Système de réponse aux imprévus.
- **Tests de Sécurité** : Vérifications pour la sûreté du robot.

### 7. Documentation Technique
- **Guide d'Utilisation** : Instructions pour l'opération et la maintenance.
- **Rapport de Projet** : Analyse des méthodes, algorithmes, et résultats obtenus.

## Objectif prioritaire

Le robot doit pouvoir se mouvoir de manière autonome dans un espace, pour prendre des objets et les déplacer dans un espace de stockage. L'utilisation de ROS2 est primordial

Fonctionnalités a assurer en priorité :
- Déplacement autonome
- Déplacement du bras
- Detection, Ramassage, dépôt et tri d'items au sol
- Possibilité de travailler avec une différenciation des objets et des zones de stockage

```mermaid
graph TD;
    A[ROS2 Core] -->|Gestion de Tâches| B[Module de Déplacement Autonome]
    A -->|Contrôle du Bras| C[Module de Manipulation du Bras]
    B -->|Navigation| D[Capteurs de Navigation]
    C -->|Préhension/Dépôt| E[Bras Robotique]
    A -->|Traitement Visuel| F[Module de Vision par Ordinateur]
    F -->|Détection d'Objets| G[Caméra]
    F -->|Tri et Identification| H[Algorithme de Tri]
    E -->|Ramassage des Objets| I[Zone de Ramassage]
    E -->|Dépôt des Objets| J[Zone de Stockage Différenciée]

    style A fill:#f96,stroke:#333,stroke-width:2px
    style B fill:#6cf,stroke:#333,stroke-width:2px
    style C fill:#fc6,stroke:#333,stroke-width:2px
    style D fill:#f9f,stroke:#333,stroke-width:2px
    style E fill:#ff6,stroke:#333,stroke-width:2px
    style F fill:#bbf,stroke:#333,stroke-width:2px
    style G fill:#9f6,stroke:#333,stroke-width:2px
    style H fill:#fb4,stroke:#333,stroke-width:2px
    style I fill:#6f9,stroke:#333,stroke-width:2px
    style J fill:#f66,stroke:#333,stroke-width:2px
```