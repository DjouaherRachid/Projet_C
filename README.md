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

### Fonction main:
```
int main(int argc, char *argv[]) {
    // Obtenir le chemin du répertoire de travail
    _getcwd(currentDirectory, sizeof(currentDirectory));
    int status;
    // Initialiser GTK
    gtk_init(&argc, &argv);
    app = gtk_application_new("projet.c", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_menu), NULL);
    // Initialiser la base de données
    initializeDatabase();
    // Exécuter l'application GTK
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
```
La fonction procède tout d'abord à l'initialisation de l'application GTK en appelant la fonction callback "activate_menu", qui lance le menu principal de l'application.
En parallèle la base de donnée est initialisée grâce à l'appel de procédure initializeDatabase(); où les tables et les tuples des templates de site sont créés s'ils n'existent pas déjà.

### Les procédures activate:
En GTK (GIMP Toolkit), une fonction de rappel (callback function) fait référence à une fonction spécifique qui est appelée en réponse à un événement particulier. Les événements peuvent être déclenchés par l'utilisateur (comme le clic d'un bouton, une pression de touche, etc.) ou par le système lui-même.
Dans notre projet, les fonctions activate sont des fonctions de rappel servant à ouvrir les différentes fenêtres qui constituent les interfaces du projet.
Par exemple, au lancement de l'application, l'initialisation de l'application GTK appelle donc la procédure callback activate_menu, qui créée une fenêtre GTKWideget create_menu_window, qui constitue l'écran d'accueil de notre application.
```
static void activate_menu(GtkApplication *app, gpointer user_data) {
    menu_window = create_menu_window(app);

    gtk_widget_show_all(menu_window);
    g_signal_connect(menu_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre de connexion
    if (login_window != NULL) {
        gtk_widget_destroy(login_window);
        login_window = NULL;  
    }
    if (form_window!= NULL) {
        gtk_widget_destroy(form_window);
        form_window = NULL;  
    }

    gtk_main();
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}
```
A noter que les 3 fenêtres de notre projet, le menu (menu_window), l'écran de connexion (login_window) et le formulaire de personnalisation de site (form_window) sont définies comme variables globales et sont initialisées dans les fonctions create. Cela permet notamment de pouvoir les fermer dans les fonctions activate pour s'assurer qu'une seule fenêtre est ouverte à la fois.

### Les fenêtres create
Les différentes fenêtres sont définies dans notre projet comme des fonctions renvoyant des GTKWidget de type Window. C'est ici qu'est effectuée la mise en forme des diférentes fenêtres.
La fonction create_form est un peu particulière car la fenêtre qu'elle renvoie dépend du type de site modifié (blog, site d'agence de voyage etc.) entré en paramètres. Elle prendra la forme d'un nombre plus ou moins important de couples Labels/entries selon le nombre de paramètres modifiables du type de site. De même, le bouton "save" appelera la procédure save associée au type de site créé.

### Les procédures save
Les procédures save servent à enregistrer le site créé dans la base de donnée. Il y a une procédure save pour chaque type de site. Celles-ci récupérent les modifications dans les entries du formulaire et les ajoutent en tant que valeurs dans les champs des tables appropriées.
Elles font aussi appel aux fonctions generate afin de générer les fichiers html appropriés.

### Les procédures generate
Elles servent à générer les fichiers html correspondant aux sites créés. Elles utilisent la fonction fprint afin de créer le fichier hmtl en question en remplaçant certaines parties du code (textes ou code hexadécimal de couleur) par les paramètres entrés par l'utilisateur. Une fois le fichier html créé, celui-ci est ouvert sur navigateur grâce à une commande système.

## Structure de la base de données
La BDD contient 5 tables, une par type de site.
Voici la structure des différentes tables:
1 **Blog:**
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/bb32dc9d-cd0a-4896-a934-39958c4562df)
2 **CV en ligne:**
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/144c1dd1-549d-4b44-991e-5ef4e4dcd8f9)
3 **Site d'e-commerce:**
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/36a5f938-d2c7-47ee-8897-dfaca8088ed5)
4 **Site d'entreprise:**
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/ac3901cb-277d-43d7-8a52-59a169677930)
5 **Site d'agence de voyage:**
![image](https://github.com/DjouaherRachid/Projet_C/assets/152193959/7ea33af3-7dae-4a42-a5b7-5f3e770ccb0f)



