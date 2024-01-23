# Générateur de sites web
[![Last Commit](https://img.shields.io/github/last-commit/votre-utilisateur/votre-projet.svg)](https://github.com/votre-utilisateur/votre-projet/commits/main)
[![Langage: C](https://img.shields.io/badge/Langage-C-blue.svg)](https://fr.wikipedia.org/wiki/C_(langage))
[![Plateforme: Windows](https://img.shields.io/badge/Plateforme-Windows-brightgreen.svg)](https://www.microsoft.com/en-us/windows)

## Introduction
Dans le cadre de ce projet, nous avons réalisé une application permettant de générer graphiquement des sites web.  
L'utilisateur accède à plusieurs templates de sites grâce à une interface graphique et peut modifier certains paramètres (textes, couleurs) afin de personnaliser le site en devenir.  
Les paramètres modifiés par l'utilisateur sont ensuite utilisés pour générer un code html/CSS créant une nouvelle page à partir du template sélectioné.   
L'utilisateur peut ensuite revenir sur ses sites générés et y apporter des modifications grâce à une gestion de base de données.

## Architecture du Projet
Le projet est structuré comme suit:  
-> DataBase.db: C'est une base de données SQLite contenant les templates de site et les sites créés par l'utilisateur  
-> main.c: C'est le fichier source principal du programme en langage C. Il contient la fonction main et est responsable de l'intégration des différentes fonctionnalités du programme.  
-> modules/: Ce répertoire contient des fichiers sources et des en-têtes (headers) associés à des modules spécifiques du programme.  
-> curlfunc.c: Un module qui peut contenir des fonctions liées à l'utilisation de cURL, qui est une bibliothèque populaire pour effectuer des requêtes HTTP.  
-> html_generator.c et html_generator.h: Un module pour la génération des fichiers HTML qui contient des fonctions pour créer différentes pages HTML à partir des modèles fournis.  
-> sqlite/: Ce répertoire contient les fichiers associés à la bibliothèque SQLite. Certains fichiers comme sqlite3.c, sqlite3.h, et sqlite3.dll sont des fichiers nécessaires pour utiliser SQLite dans le projet.  
-> Website_Templates/: Ce répertoire contient des modèles HTML pré-établis pour différentes pages web, telles que le blog, le CV, un site e-commerce, une page d'entreprise, et une page de voyage.

## Bibliothèques et dépendances
### GTK3
GTK3 (GIMP Toolkit 3) est une bibliothèque graphique open-source utilisée pour la création d'interfaces utilisateur (UI) graphiques.  
Il est indispensable de l'installer afin de correctement exécuter le programme.  
Il faut pour cela suivre les instructions spécifiées sur ce site:  
https://www.gtk.org/docs/installations/windows  
### Sqlite3
SQLite est une bibliothèque en langage C qui implémente un petit moteur de base de données SQL rapide, autonome, de haute fiabilité et complet.  
Les fichiers .c et /h de la bibliothèque sont intégrés dans le dossier sqlite du projet.  
### Curl
## Configuration de l'environnement de développement
Ce projet a été développé sur l'IDE virtual studio code et a été pensé pour être exécuté grâce à celui-ci.
Pour l'exécuter vous aurez besoin d'un compilateur C tel que gcc.
Sur une machine linux, la compilation et l'exécution sont censées pouvoir se réaliser grâce à la commande suivante: 
```
gcc $(pkg-config gtk+-3.0 --cflags) "${file}" -o "${fileDirname}/${fileBasenameNoExtension}.exe" -lsqlite3 $(pkg-config gtk+-3.0 --libs)
```
Sur windows, sur vscode,il suffit d'installer l'extension Microsoft C/C++ puis d'ajouter le chemin de votre compilateur ainsi que les include path nécessaires (gtk-3.0,glib-2.0,/mingw64/include/**,mingw64/lib/**,atk-1.0) dans la configuration:
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/dfac1ff7-59d4-4f71-9a53-c6a24ed899af)
Lancer une première compilation devrait générer un dossier .vscode. Dans celui, il faut modifier le fichier tasks.json afin d'ajouter tous les paramètres de la compilation par ligne de commande:
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/f033c23e-5456-451a-8519-682f5cddf736)
## Documentation du code source
## Structure de la base de données
