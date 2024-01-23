# Générateur de sites web
[![Last Commit](https://img.shields.io/github/last-commit/votre-utilisateur/votre-projet.svg)]([https://github.com/votre-utilisateur/votre-projet/commits/main](https://github.com/DjouaherRachid/Projet_C.git))
[![Langage: C](https://img.shields.io/badge/Langage-C-blue.svg)](https://fr.wikipedia.org/wiki/C_(langage))
[![Plateforme: Windows](https://img.shields.io/badge/Plateforme-Windows-brightgreen.svg)](https://www.microsoft.com/en-us/windows)

##Introduction
Dans le cadre de ce projet, nous avons réalisé une application permettant de générer graphiquement des sites web. 
L'utilisateur accède à plusieurs templates de sites grâce à une interface graphique et peut modifier certains paramètres (textes, couleurs) afin de personnaliser le site en devenir.
Les paramètres modifiés par l'utilisateur sont ensuite utilisés pour générer un code html/CSS créant une nouvelle page à partir du template sélectioné. 
L'utilisateur peut ensuite revenir sur ses sites générés et y apporter des modifications grâce à une gestion de base de données.

##Architecture du Projet
Le projet est structuré comme suit:
C:.
│   DataBase.db
│   main.c
│
├───modules
│       curlfunc.c
│       html_generator.c
│       html_generator.h
│
├───sqlite
│       shell.c
│       sqlite3.c
│       sqlite3.def
│       sqlite3.dll
│       sqlite3.h
│       sqlite3ext.h
│
└───Website_Templates
        Blog.html
        CV.html
        E-commerce.html
        Entreprise.html
        Travel.html

->DataBase.db: C'estune base de données SQLite contenant les templates de site et les sites créés par l'utilisateur
->main.c: C'est le fichier source principal du programme en langage C. Il contient la fonction main et est responsable de l'intégration des différentes fonctionnalités du programme.
->modules/: Ce répertoire contient des fichiers sources et des en-têtes (headers) associés à des modules spécifiques du programme.
  ->curlfunc.c: Un module qui peut contenir des fonctions liées à l'utilisation de cURL, qui est une bibliothèque populaire pour effectuer des requêtes HTTP.
  ->html_generator.c et html_generator.h: Un module pour la génération des fichiers HTML qui contiennent des fonctions pour créer différentes pages HTML à partir des modèles fournis.
  ->sqlite/: Ce répertoire contient les fichiers associés à la bibliothèque SQLite. Certains fichiers comme sqlite3.c, sqlite3.h, et sqlite3.dll sont des fichiers nécessaires pour utiliser SQLite dans le                 projet.
Website_Templates/: Ce répertoire contient des modèles HTML pré-établis pour différentes pages web, telles que le blog, le CV, un site e-commerce, une page d'entreprise, et une page de voyage.

##Bibliothèques et dépendances
###GTK3
GTK3 (GIMP Toolkit 3) est une bibliothèque graphique open-source utilisée pour la création d'interfaces utilisateur (UI) graphiques.
Il est indispensable de l'installer afin de correctement exécuter le programme.
Il faut pour cela suivre les instructions spécifiées sur ce site:
https://www.gtk.org/docs/installations/windows
###Sqlite3
SQLite est une bibliothèque en langage C qui implémente un petit moteur de base de données SQL rapide, autonome, de haute fiabilité et complet.
Les fichiers .c et /h de la bibliothèques sont intégrés dans le dossier sqlite du projet
###Curl
##Configuration de l'environnement de développement
##Documentation du code source
##Structure de la base de données
