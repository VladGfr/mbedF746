# Projet d'Interfaçage Numérique avec la Carte DISCO-F746NG

## Description du Projet

Ce projet d'interfaçage numérique a pour objectif de concevoir et de réaliser un système électronique intégrant divers modules et capteurs en utilisant une carte de développement DISCO-F746NG. Les étapes principales du projet sont :
1. Choix des modules à interfacer.
2. Conception d'un PCB au format "shield" Arduino Uno pour accueillir ces modules.
3. Programmation de l'interfaçage sur la carte DISCO-F746NG, qui possède un affichage LCD et utilise la bibliothèque graphique open-source LVGL pour créer des interfaces graphiques.

## Modules Utilisés

### Récepteur FM Grove I2C

Le récepteur FM Grove I2C utilise le circuit intégré RDA5807M, un CI FM « tout-en-un » qui gère toutes les étapes de la réception à la sortie audio avec un minimum de composants externes.

#### Avantages du Module
- Évite l'ajout de composants supplémentaires (condensateurs, résistances, circuits de filtrage).
- Prise jack 3.5mm servant d’antenne pour la réception FM.

#### Communication
La communication avec le RDA5807M s'effectue via des trames I2C pour :
- La syntonisation sur une fréquence donnée (50-115MHz).
- La recherche automatique de stations.
- Le contrôle du volume.
- La lecture de la fréquence et du volume actuels.
- La lecture des données RDS (Nom de la station).

## Schéma et Typon de Raccordement

![Schéma](https://i.imgur.com/IrsIZG7.png)
![Typon](https://i.imgur.com/apLzDV2.png)

Les résistances de pull-up R2 et R3 ont été supprimées lors de l’assemblage de la carte car elles sont déjà présentes sur le module Grove.

## Description de la Liaison et Principe de Fonctionnement Software

### Utilisation de la Bibliothèque
Nous avons utilisé la bibliothèque [RDA5807M](https://github.com/star297/RDA5807M) compatible mbed pour simplifier l'interfaçage, bien que celle-ci présente quelques lacunes :
- **Manque de documentation** : Nécessitant un travail supplémentaire pour comprendre certaines fonctions.
- **Fonctions non implémentées** : Certaines fonctions déclarées dans le fichier header n'étaient pas implémentées.

### Ajouts et Modifications
Deux fonctions cruciales ont été ajoutées :
- `void SetThreshold(int threshold)` : Permet de régler le seuil de sensibilité pour la recherche automatique des stations.
- `bool verifCo()` : Vérifie la présence du module RDA5807M sur le bus I2C en renvoyant un booléen correspondant à l'ACK.

## Description du Fonctionnement de l'Application Réalisée

### Interface Utilisateur
L'application présente une interface de style vintage avec des affichages à segments rouges pour les caractères alphanumériques et des cadrans analogiques pour la fréquence et le volume.

#### Contrôles
- **Boutons < et >** : Modifient la fréquence par pas de 100kHz.
- **Boutons ◄ et ►** : Effectuent une recherche croissante ou décroissante des stations.
- **Boutons de volume** : Situés en haut à droite, permettent de varier le niveau de sortie du module. Le niveau est indiqué sur le cadran à aiguille en bas à gauche.
- **Pavé numérique** : Permet de saisir une fréquence radio précise (87.5-108 MHz).

![Interface de l'application](https://i.imgur.com/s1imZNx.png)

### Affichage des Données RDS
L'affichage sur 8 caractères en bas de l'écran montre l'identifiant de la station reçu via le protocole RDS. Notez qu'il n'y a pas de vérification de l'intégrité des données, ce qui peut entraîner des caractères incohérents en cas de mauvaise réception (par exemple, les deux « A » après « RTL2 »).

Des caractères « □□ », censés être des espaces, n'apparaissent pas correctement en raison d'un problème lors de la conversion du fichier TTF de la police de caractères en fichier C pour LVGL.

---

## Auteur

Nom : Vladimir G.
Organisation : IUT de Cachan 