
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#include "sqlite/sqlite3.c"
#include <gtk/gtk.h>
#include "modules/html_generator.h"
#include "modules/html_generator.c"


//Chemin du repertoire de travail


//Prototypes des procédures lançant les différentes fenêtres du projet
static void launch(GtkApplication *app, gpointer user_data);
static void activate_menu(GtkApplication *app, gpointer user_data);
static void activate_Entreprise(GtkApplication *app, gpointer user_data);
static void activate_Blog(GtkApplication *app, gpointer user_data);
static void activate_Commerce(GtkApplication *app, gpointer user_data);
static void activate_Travel(GtkApplication *app, gpointer user_data);
static void activate_CV(GtkApplication *app, gpointer user_data);

//Protoypes des procédures créant les codes HTML


//Prototypes des fonctions créant les différentes fenêtres du projets.
GtkWidget *create_menu_window(GtkApplication *app);
GtkWidget *create_login_window(GtkApplication *app);
GtkWidget *create_form(GtkApplication *app, const char *form_title, const char *Website_Type, int num_elements);

//Les différentes fenêtres du projet
GtkWidget *login_window = NULL;
GtkWidget *menu_window = NULL;
GtkWidget *form_window= NULL;

GtkApplication *app;

sqlite3 *db;








// Fonction de rappel pour le bouton "OK" après avoir ajouté un site à la BDD
void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    //g_print("Réponse du bouton : %d\n", response_id);
    gtk_widget_destroy(GTK_WIDGET(dialog));  
        if (form_window != NULL) {
        gtk_widget_destroy(form_window);
        form_window = NULL;  
        activate_menu(app,NULL);
    }
}

//Sauvergarder le template de CV
void save_CV(GtkWidget *button, GtkWidget **entries) {
    const char *values[12];

    for (int i = 0; i < 12; i++) {
        if (GTK_IS_ENTRY(entries[i])) {
            const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entries[i]));
            values[i] = entry_text;
            g_print("Entry %d Text: %s \n", i, values[i]);
        } else {
            g_print("L'élément %d n'est pas un GtkEntry\n", i);
        }
    }
    free(entries);
    // Génération du code html/css:
    generate_CV(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
                                values[8], values[9], values[10], values[11]);
    // Ouvrir la base de données
    sqlite3 *db;
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        printf("BDD ouverte correctement \n");

        // Construction de la requête avec sqlite3_mprintf
        const char *insertQuery = sqlite3_mprintf(
            "INSERT INTO CV_Website ("
            "name, email, phone, linkedin, job_title, company, job_date, job_description, education, education_date, skills, download_link)"
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q');",
            values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
            values[8], values[9], values[10], values[11]);
        // Exécuter la requête préparée
        int result = sqlite3_exec(db, insertQuery, 0, 0, 0);
        if (result != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de l'insertion dans la table : %s\n", sqlite3_errmsg(db));
        } else {
            printf("Template de CV ajouté avec succès.\n");
            // Création d'une fenêtre de dialogue
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(form_window),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Site Successfully Registered");
            g_signal_connect_swapped(G_OBJECT(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
            gint result = gtk_dialog_run(GTK_DIALOG(dialog));

            // Ajout d'un message de débogage supplémentaire
            printf("Après l'insertion.\n");
        }
        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }
}

//Sauvergarder le site d'agence de voyage en BDD
void save_travel_website(GtkWidget *button, GtkWidget **entries) {
    const char *values[13];

    for (int i = 0; i < 13; i++) {
        if (GTK_IS_ENTRY(entries[i])) {
            const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entries[i]));
            values[i] = entry_text;
            g_print("Entry %d Text: %s \n", i, values[i]);
        } else {
            g_print("L'élément %d n'est pas un GtkEntry\n", i);
        }
    }
    free(entries);
    // Génération du code html/css:
    generate_Travel_Website(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
                                values[8], values[9], values[10], values[11], values[12]);
    // Ouvrir la base de données
    sqlite3 *db;
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        printf("BDD ouverte correctement \n");

        // Construction de la requête avec sqlite3_mprintf
        const char *insertQuery = sqlite3_mprintf(
            "INSERT INTO Travel_Website (name, slogan, about_us, header_title, header_description, destination_title,"
            "destination_image, destination_description, special_offer_title, special_offer_image, special_offer_description," 
            "contact_email, footer_text)"
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q');",
            values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
            values[8], values[9], values[10], values[11], values[12]);
        // Exécuter la requête préparée
        int result = sqlite3_exec(db, insertQuery, 0, 0, 0);
        if (result != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de l'insertion dans la table : %s\n", sqlite3_errmsg(db));
        } else {
            printf("Site d'agence de voyage ajoutée avec succès.\n");
            // Création d'une fenêtre de dialogue
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(form_window),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Site Successfully Registered");
            g_signal_connect_swapped(G_OBJECT(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
            gint result = gtk_dialog_run(GTK_DIALOG(dialog));

            // Ajout d'un message de débogage supplémentaire
            printf("Après l'insertion.\n");
        }
        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }
}

void save_ecommerce(GtkWidget *button, GtkWidget **entries) {
    const char *values[18];

    for (int i = 0; i < 18; i++) {
        if (GTK_IS_ENTRY(entries[i])) {
            const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entries[i]));
            values[i] = entry_text;
            g_print("Entry %d Text: %s \n", i, values[i]);
        } else {
            g_print("L'élément %d n'est pas un GtkEntry\n", i);
        }
    }
    free(entries);

    // Génération du code html/css:
    generate_ECommerce_Site(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
                                values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15],
                                values[16], values[17]);

    // Ouvrir la base de données
    sqlite3 *db;
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        printf("BDD ouverte correctement \n");

        // Construction de la requête avec sqlite3_mprintf
        const char *insertQuery = sqlite3_mprintf(
                "INSERT INTO ECommerce_Website (site_name, site_description, "
                "header_title, header_description, "
                "product1_title, product1_description, product1_price, "
                "product2_title, product2_description, product2_price, "
                "product3_title, product3_description, product3_price, "
                "product4_title, product4_description, product4_price, "
                "contact_email, footer_text) "
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q');",
            values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
            values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15],
            values[16], values[17]);

        // Exécuter la requête préparée
        int result = sqlite3_exec(db, insertQuery, 0, 0, 0);
        if (result != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de l'insertion dans la table : %s\n", sqlite3_errmsg(db));
        } else {
            printf("Site d'e-commerce ajoutée avec succès.\n");

            // Création d'une fenêtre de dialogue
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(form_window),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Site Successfully Registered");
            g_signal_connect_swapped(G_OBJECT(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
            gint result = gtk_dialog_run(GTK_DIALOG(dialog));

            // Ajout d'un message de débogage supplémentaire
            printf("Après l'insertion.\n");
        }

        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }
}

void save_blog(GtkWidget *button, GtkWidget **entries) {
    const char *values[10];

    for (int i = 0; i < 10; i++) {
        if (GTK_IS_ENTRY(entries[i])) {
            const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entries[i]));
            values[i] = entry_text;
            g_print("Entry %d Text: %s \n", i, values[i]);
        } else {
            g_print("L'élément %d n'est pas un GtkEntry\n", i);
        }
    }
    free(entries);

    // Génération du code html/css:
    generate_Personal_Blog(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
                                values[8], values[9]);

    // Ouvrir la base de données
    sqlite3 *db;
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        printf("BDD ouverte correctement \n");

        // Construction de la requête avec sqlite3_mprintf
        const char *insertQuery = sqlite3_mprintf(
            "INSERT INTO Blog (blog_title, blog_description, "
            "article1_title, article1_date, article1_content, "
            "article2_title, article2_date, article2_content, "
            "about_me, contact_email) "
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q');",
            values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
            values[8], values[9]);

        // Exécuter la requête préparée
        int result = sqlite3_exec(db, insertQuery, 0, 0, 0);
        if (result != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de l'insertion dans la table : %s\n", sqlite3_errmsg(db));
        } else {
            printf("Blog ajouté avec succès.\n");

            // Création d'une fenêtre de dialogue
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(form_window),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Site Successfully Registered");
            g_signal_connect_swapped(G_OBJECT(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
            gint result = gtk_dialog_run(GTK_DIALOG(dialog));

            // Ajout d'un message de débogage supplémentaire
            printf("Après l'insertion.\n");
        }

        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }
}

void save_company_website(GtkWidget *button, GtkWidget **entries) {
    const char *values[16];

    for (int i = 0; i < 16; i++) {
        if (GTK_IS_ENTRY(entries[i])) {
            const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entries[i]));
            values[i] = entry_text;
            g_print("Entry %d Text: %s \n", i, values[i]);
        } else {
            g_print("L'élément %d n'est pas un GtkEntry\n", i);
        }
    }
    free(entries);

    // Génération du code html/css:
    generate_Company_Website(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
                                values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15]);

    // Ouvrir la base de données
    sqlite3 *db;
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        printf("BDD ouverte correctement \n");

        // Construction de la requête avec sqlite3_mprintf
        const char *insertQuery = sqlite3_mprintf(
            "INSERT INTO Entreprise_Website (name, about_us, slogan, contact, "
            "service1_name, service1_description, service2_name, service2_description, "
            "body_color, body_font_family, header_bg_color, header_text_color, "
            "a_text_color, footer_bg_color, footer_text_color, hero_bg_color) "
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q');",
            values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
            values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15]);

        // Exécuter la requête préparée
        int result = sqlite3_exec(db, insertQuery, 0, 0, 0);
        if (result != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de l'insertion dans la table : %s\n", sqlite3_errmsg(db));
        } else {
            printf("Entreprise ajoutée avec succès.\n");

            // Création d'une fenêtre de dialogue
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(form_window),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Site Successfully Registered");
            g_signal_connect_swapped(G_OBJECT(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
            gint result = gtk_dialog_run(GTK_DIALOG(dialog));

            // Ajout d'un message de débogage supplémentaire
            printf("Après l'insertion.\n");
        }

        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }
}

//Fonction qui créée le formulaire de personnalisation du template de site d'entreprise
GtkWidget *create_form(GtkApplication *app, const char *form_title, const char *Website_Type, int num_elements) {
    //le int type servira à définir le type de template pour attribuer la fonction callback appropriée au bouton enregistré
    int type;
    GtkWidget *custom_form = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(custom_form), form_title);
    gtk_window_set_default_size(GTK_WINDOW(custom_form), 1280, 720);
    g_signal_connect(custom_form, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(custom_form), grid);

    // Ajouter le libellé du titre
    GtkWidget *titleLabel = gtk_label_new(form_title);
    PangoFontDescription *titleFontDesc = pango_font_description_from_string("Sans Bold 18");
    gtk_widget_override_font(titleLabel, titleFontDesc);
    gtk_widget_set_halign(titleLabel, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(grid), titleLabel, 0, 0, 2, 1);
    pango_font_description_free(titleFontDesc);

    const char **parameters;
    const char **default_texts;

    //On définit les paramètres et les entrées par défaut selon le type de site:
    if (strcmp(Website_Type, "Entreprise") == 0) {
        parameters = (const char *[]){
        "Name", "About Us", "Slogan", "Contact",
        "Service 1 Name", "Service 1 Description",
        "Service 2 Name", "Service 2 Description",
        "Body Color", "Body Font Family",
        "Header BG Color", "Header Text Color",
        "A Text Color", "Footer BG Color",
        "Footer Text Color", "Hero BG Color"
    };
        default_texts = (const char *[]){
        "Nom de l'Entreprise", "Une brève description de l'entreprise et de son histoire", 
        "Un slogan pour l'entreprise", "Adresse, numéro de téléphone, formulaire de contact, etc.", 
        "Service 1", "Description du service 1", 
        "Service 2", "Description du service 2", 
        "#000000", "Arial, sans-serif", 
        "#333", "#fff", "#fff", "#333", "#fff", "#f4f4f4"
    };
    type=1;
    }
    if (strcmp(Website_Type, "Blog") == 0) {
        parameters = (const char *[]){
        "Blog Title", "Blog Description",
        "Article 1 Title", "Article 1 Date", "Article 1 Content",
        "Article 2 Title", "Article 2 Date", "Article 2 Content",
        "About Me", "Contact Email"
        };
        default_texts = (const char *[]){
        "Titre du blog", "Description du blog",
        "Titre de l'article 1", "2024-01-01", "Contenu de l'article 1...",
        "Titre de l'article 2", "2024-01-02", "Contenu de l'article 2...",
        "À propos de moi", "contact@monblog.com"
        };
        type=2;
        }
    if (strcmp(Website_Type, "ECommerce") == 0) {
        parameters = (const char *[]) {
        "site_title", "site_description",
        "welcome_title", "welcome_message",
        "product1_name", "product1_description", "product1_price",
        "product2_name", "product2_description", "product2_price",
        "product3_name", "product3_description", "product3_price",
        "product4_name", "product4_description", "product4_price",
        "contact_email", "footer_text"
    };
        default_texts = (const char *[]) {
        "Mon Site E-Commerce", "Description de mon site e-commerce",
        "Bienvenue sur Mon Site E-Commerce", "Découvrez nos produits de qualité.",
        "Produit 1", "Description du produit 1", "$19.99",
        "Produit 2", "Description du produit 2", "$29.99",
        "Produit 3", "Description du produit 3", "$24.99",
        "Produit 4", "Description du produit 4", "$39.99",
        "contact@monsite.com", "© 2024 Mon Site E-Commerce. Tous droits réservés."
    };
    type=3;
    }
    if (strcmp(Website_Type, "Travel_Agency") == 0){
        parameters = (const char *[]){
        "name", "slogan", "about_us", "header_title", "header_description",
        "destination_title", "destination_image", "destination_description",
        "special_offer_title", "special_offer_image", "special_offer_description",
        "contact_email", "footer_text"
    };
        default_texts = (const char *[]){
        "'Nom de l''Agence'", "'Votre prochaine aventure commence ici.'",
        "'Découvrez des destinations extraordinaires et vivez des expériences inoubliables.'", "'Explorez le Monde'",
        "'Découvrez des destinations extraordinaires et vivez des expériences inoubliables.'", "'Tokyo, Japon'", "'tokyo.jpg'",
        "'Explorez la modernité et la tradition dans la capitale du Japon.'", "'Voyage tout compris à Bali'", "'bali.jpg'",
        "'Profitez de plages paradisiaques et d''une expérience culturelle unique.'", "'info@agencedevoyage.com'",
        "'&copy; 2024 Agence de Voyage. Tous droits réservés.'"
    };
    type=4;
    }
    if (strcmp(Website_Type, "CV") == 0){
        parameters = (const char *[]){
        "name", "email", "phone", "linkedin", "job_title", "company", "job_date",
        "job_description", "education", "education_date", "skills", "download_link"
    };

        default_texts = (const char *[]){
        "Nom Prénom", "email@example.com", "+123456789", "linkedin.com/in/nom",
        "Titre du poste", "Nom de l'entreprise", "Date du travail", "Description du travail",
        "Nom de l'école", "Date d'obtention", "Compétences clés", "lien_de_téléchargement.pdf"
    };
    type=5;
    }

    // Créer un tableau de widgets pour stocker les zones de texte
    GtkWidget **entries = malloc(num_elements * sizeof(GtkWidget *));

    for (int i = 0; i < num_elements; i++) {
        GtkWidget *label = gtk_label_new(parameters[i]);
        GtkWidget *entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(entry), default_texts[i]);

        printf("Nombre d'éléments dans parameters : %d\n", num_elements);
        printf("%s",default_texts[i]);

        PangoFontDescription *font_desc = pango_font_description_from_string("Sans Bold 14");
        gtk_widget_override_font(label, font_desc);
        gtk_widget_override_font(entry, font_desc);
        pango_font_description_free(font_desc);

        int vertical_spacing = 10;
        gtk_widget_set_margin_bottom(label, vertical_spacing);
        gtk_widget_set_margin_bottom(entry, vertical_spacing);

        // Multiplier par 3 la largeur des GtkEntry
        gtk_widget_set_size_request(entry, 3 * gtk_widget_get_allocated_width(entry), -1);

        // Ajouter les widgets au GtkGrid avec les ajustements de taille de police et d'espace vertical
        gtk_grid_attach(GTK_GRID(grid), label, 0, i + 1, 1, 1); // Incrémenter i de 1 pour laisser de l'espace pour le titre
        gtk_grid_attach(GTK_GRID(grid), entry, 1, i + 1, 1, 1);

        // Stocker les entrées dans le tableau entries
        entries[i] = entry;
    }

    // Ajouter le bouton "Enregistrer" à la fin
    GtkWidget *submit_button = gtk_button_new_with_label("Save");
    GtkWidget *cancel_button = gtk_button_new_with_label("Cancel");

    switch(type){
    case 1:
        g_signal_connect(submit_button, "clicked", G_CALLBACK(save_company_website), entries);
    break;
    case 2:
        g_signal_connect(submit_button, "clicked", G_CALLBACK(save_blog), entries);
    break;
    case 3:
        g_signal_connect(submit_button, "clicked", G_CALLBACK(save_ecommerce), entries);
    break;
    case 4:
        g_signal_connect(submit_button, "clicked", G_CALLBACK(save_travel_website), entries);
    break;
    case 5:
        g_signal_connect(submit_button, "clicked", G_CALLBACK(save_CV), entries);
    break;
    }

    g_signal_connect(cancel_button, "clicked", G_CALLBACK(activate_menu), NULL);

    // Ajouter de l'espace vertical entre le dernier champ et le bouton
    int vertical_spacing_button = 20;
    gtk_widget_set_margin_bottom(submit_button, vertical_spacing_button);
    gtk_widget_set_margin_bottom(cancel_button, vertical_spacing_button);

    // Ajouter les boutons au GtkGrid
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, num_elements + 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cancel_button, 1, num_elements + 1, 1, 1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    return custom_form;
}

//Sert à remplir l'onglet "Load Page"
void fill_load_page_grid(GtkWidget *grid) {
    // Variables pour stocker le résultat de la requête
    sqlite3_stmt *stmt;
    const char *query;
    
    // Nom de la table et les colonnes dont nous avons besoin
    const char *table_names[] = {"Entreprise_Website", "Blog", "ECommerce_Website", "Travel_Website", "CV_Website"};
    const char *column_names[] = {"name", "blog_title", "site_name", "name", "name"};

    for (int i = 0; i < G_N_ELEMENTS(table_names); i++) {
        // Construction de la requête SQL
        query = g_strdup_printf("SELECT id, %s FROM %s;", column_names[i], table_names[i]);

        // Préparation et exécution de la requête SQL
        sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

        // Libération de la mémoire de la requête
        g_free((gpointer)query);

        // Variable pour stocker le résultat de sqlite3_step
        int result;

        // Créer des étiquettes pour le nom de la table
        GtkWidget *table_label = gtk_label_new(table_names[i]);
        gtk_grid_attach(GTK_GRID(grid), table_label, 0, i, 1, 1);

        // Exécute la requête
        while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
            // Récupère l'ID et le nom de la ligne
            int id = sqlite3_column_int(stmt, 0);
            const char *name = (const char *)sqlite3_column_text(stmt, 1);

            // Crée une étiquette pour le nom de la ligne
            GtkWidget *name_label = gtk_label_new(name);
            gtk_grid_attach(GTK_GRID(grid), name_label, 1, i, 1, 1);

            // Crée un bouton "Sélectionner" pour chaque ligne
            GtkWidget *select_button = gtk_button_new_with_label("Sélectionner");
            gtk_grid_attach(GTK_GRID(grid), select_button, 2, i, 1, 1);

            // Connecte le signal "clicked" à une fonction de rappel pour gérer la sélection
            g_signal_connect(select_button, "clicked", G_CALLBACK(activate_Blog), GINT_TO_POINTER(id));
        }

        // Libère la mémoire du résultat de la requête
        sqlite3_finalize(stmt);
    }
}

//Cette fonction sert à créer une box contenant un label titre et un bouton "select" pour chaque template dans le menu
GtkWidget *create_template_widget(const char *template_name) {
    GtkWidget *template_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *label = gtk_label_new(template_name);
    PangoFontDescription *font_desc = pango_font_description_from_string("Sans 16");
    gtk_widget_override_font(label, font_desc);

    GtkWidget *button = gtk_button_new_with_label("Select");

    //Cliquer sur le bouton ouvre le formulaire de personnalisation du site d'entreprise si on 
    if (strcmp(template_name, "Site d'Entreprise") == 0) 
    g_signal_connect(button, "clicked", G_CALLBACK(activate_Entreprise), NULL);

    if (strcmp(template_name, "Blog Personnel") == 0) 
    g_signal_connect(button, "clicked", G_CALLBACK(activate_Blog), NULL);
    
    if (strcmp(template_name, "Site d'e-commerce") == 0) 
    g_signal_connect(button, "clicked", G_CALLBACK(activate_Commerce), NULL);
    
    if (strcmp(template_name, "Agence de Voyage") == 0) 
    g_signal_connect(button, "clicked", G_CALLBACK(activate_Travel), NULL);

    if (strcmp(template_name, "Template de CV en Ligne") == 0) 
    g_signal_connect(button, "clicked", G_CALLBACK(activate_CV), NULL);

    gtk_box_pack_start(GTK_BOX(template_box), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(template_box), button, FALSE, FALSE, 0);

    int spacing = 50;
    gtk_widget_set_margin_right(button, spacing);
    gtk_widget_set_margin_left(button, spacing);
    gtk_widget_set_margin_bottom(button, 100);

    return template_box;
}

GtkWidget *create_menu_window(GtkApplication *app) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Main menu");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    GtkWidget *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_LEFT);

    const char *tab_labels[] = {"Create page from template",  "Load page"};

    for (int i = 0; i < G_N_ELEMENTS(tab_labels); i++) {
        GtkWidget *page = gtk_grid_new();
        GtkWidget *label = gtk_label_new(tab_labels[i]);

        PangoFontDescription *tab_font_desc = pango_font_description_from_string("Sans 10");
        gtk_widget_override_font(label, tab_font_desc);

        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, label);

        switch (i) {
        
            case 0:
                // Créer le titre "Create a page from template"
                GtkWidget *template_label = gtk_label_new("Create a page from template");
                PangoFontDescription *template_font_desc = pango_font_description_from_string("Sans 24");
                gtk_widget_override_font(template_label, template_font_desc);

                // Centrer horizontalement le titre
                GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
                gtk_widget_set_hexpand(title_box, TRUE);
                gtk_widget_set_halign(title_box, GTK_ALIGN_CENTER);

                gtk_box_pack_start(GTK_BOX(title_box), template_label, FALSE, FALSE, 0);

                GtkWidget *spacer = gtk_label_new("");  
                gtk_widget_set_vexpand(spacer, TRUE);
                gtk_box_pack_start(GTK_BOX(title_box), spacer, FALSE, FALSE, 50);

                // Ajouter le titre centré à la grille
                gtk_grid_attach(GTK_GRID(page), title_box, 0, 0, 1, 1);

                // Ajouter le conteneur des templates à la grille
                GtkWidget *templates_box = gtk_grid_new();
                gtk_grid_set_row_homogeneous(GTK_GRID(templates_box), TRUE);

                // Tableau de noms de templates
                const char *template_names[] = {"Site d'Entreprise", "Blog Personnel", "Site d'e-commerce", "Agence de Voyage", "Template de CV en Ligne"};

                // Ajouter les widgets de templates au conteneur avec une boucle
                for (int j = 0; j < G_N_ELEMENTS(template_names); j++) {
                    GtkWidget *template = create_template_widget(template_names[j]);
                    gtk_grid_attach(GTK_GRID(templates_box), template, j % 3, j / 3, 1, 1);
                }

                // Centrer la templates_box
                gtk_widget_set_hexpand(templates_box, TRUE);
                gtk_widget_set_halign(templates_box, GTK_ALIGN_CENTER);
                gtk_widget_set_vexpand(templates_box, TRUE);
                gtk_widget_set_valign(templates_box, GTK_ALIGN_CENTER);
                gtk_grid_attach(GTK_GRID(page), templates_box, 0, 0, 1, 1);
                break;

            case 1: // "Load page"
            {
                GtkWidget *template_label = gtk_label_new("Load created page from database");
                PangoFontDescription *template_font_desc = pango_font_description_from_string("Sans 24");
                gtk_widget_override_font(template_label, template_font_desc);

                // Centrer horizontalement le titre
                GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
                gtk_widget_set_hexpand(title_box, TRUE);
                gtk_widget_set_halign(title_box, GTK_ALIGN_CENTER);

                gtk_box_pack_start(GTK_BOX(title_box), template_label, FALSE, FALSE, 0);
                // Créer la grille pour l'onglet Load Page
                GtkWidget *load_page_grid = gtk_grid_new();
                gtk_grid_set_row_homogeneous(GTK_GRID(load_page_grid), TRUE);

                // Ajouter une barre de défilement
                GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
                gtk_container_add(GTK_CONTAINER(scrolled_window), load_page_grid);
                gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

                // Ajouter la barre de défilement à la grille principale
                gtk_grid_attach(GTK_GRID(page), title_box, 0, 0, 1, 1);  // Ajout du titre à la grille principale
                gtk_grid_attach(GTK_GRID(page), scrolled_window, 0, 1, 1, 1);  // Ajout de la barre de défilement

                // Définir l'expansion de l'onglet Load Page pour qu'il prenne autant d'espace que les autres onglets
                gtk_widget_set_hexpand(scrolled_window, TRUE);
                gtk_widget_set_vexpand(scrolled_window, TRUE);

                // Appeler une fonction pour remplir la grille avec les données de la BDD
                fill_load_page_grid(load_page_grid);
            }
            break;
            default:
            break;
        }
    }

    GtkWidget *boxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(boxLeft), notebook, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(main_box), boxLeft);

    // Centrer la fenêtre
    gtk_widget_show_all(window);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    return window;
}   

//Fenêtre de connexion
GtkWidget *create_login_window(GtkApplication *app) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Interface de Connexion");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *username_label = gtk_label_new("Username:");
    GtkWidget *username_entry = gtk_entry_new();

    GtkWidget *password_label = gtk_label_new("Password:");
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    GtkWidget *connect_button = gtk_button_new_with_label("Connexion");
    g_signal_connect(connect_button, "clicked", G_CALLBACK(activate_menu), NULL);

    // Ajuster la taille de la police pour les étiquettes et les entrées
    PangoFontDescription *font_desc = pango_font_description_from_string("Sans Bold 14");
    gtk_widget_override_font(username_label, font_desc);
    gtk_widget_override_font(username_entry, font_desc);
    gtk_widget_override_font(password_label, font_desc);
    gtk_widget_override_font(password_entry, font_desc);
    gtk_widget_override_font(connect_button, font_desc);
    pango_font_description_free(font_desc);

    // Ajouter de l'espace vertical entre les widgets
    int vertical_spacing = 50;
    gtk_widget_set_margin_bottom(username_label, vertical_spacing);
    gtk_widget_set_margin_bottom(username_entry, vertical_spacing);
    gtk_widget_set_margin_bottom(password_label, vertical_spacing);
    gtk_widget_set_margin_bottom(password_entry, vertical_spacing);
    gtk_widget_set_margin_bottom(connect_button, vertical_spacing);

    // Ajouter les widgets au GtkGrid avec les ajustements de taille de police et d'espace vertical
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), connect_button, 1, 2, 1, 1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    return window;
}

static void activate_Entreprise(GtkApplication *app, gpointer user_data) {
    form_window = create_form(app,"Créez votre propre site d'entreprise","Entreprise",16);

    gtk_widget_show_all(form_window);
    g_signal_connect(form_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre du menu
    if (menu_window != NULL) {
        gtk_widget_destroy(menu_window);
        menu_window = NULL;  
    }

    gtk_main();
}

static void activate_Blog(GtkApplication *app, gpointer user_data){
    form_window = create_form(app,"Créez votre propre blog personnel","Blog",10);

    gtk_widget_show_all(form_window);
    g_signal_connect(form_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre du menu
    if (menu_window != NULL) {
        gtk_widget_destroy(menu_window);
        menu_window = NULL;  
    }

    gtk_main();
}

static void activate_Commerce(GtkApplication *app, gpointer user_data){
    form_window = create_form(app,"Créez votre propre site d'e-commerce","ECommerce",18);

    gtk_widget_show_all(form_window);
    g_signal_connect(form_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre du menu
    if (menu_window != NULL) {
        gtk_widget_destroy(menu_window);
        menu_window = NULL;  
    }

    gtk_main();
}


static void activate_Travel(GtkApplication *app, gpointer user_data){
    form_window = create_form(app,"Créez votre propre site d'agence de voyage","Travel_Agency",13);

    gtk_widget_show_all(form_window);
    g_signal_connect(form_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre du menu
    if (menu_window != NULL) {
        gtk_widget_destroy(menu_window);
        menu_window = NULL;  
    }

    gtk_main();
}

static void activate_CV(GtkApplication *app, gpointer user_data){
    form_window = create_form(app,"Créez un CV personnalisé","CV",12);

    gtk_widget_show_all(form_window);
    g_signal_connect(form_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre du menu
    if (menu_window != NULL) {
        gtk_widget_destroy(menu_window);
        menu_window = NULL;  
    }

    gtk_main();
}

//Procédure censée se lancer lorsque l'utilisateur appuie sur connexion et ouvrant le menu
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

//Procédure se lançant au démarrage de l'application
static void launch(GtkApplication *app, gpointer user_data) {
    login_window = create_login_window(app);

    gtk_widget_show_all(login_window);

    gtk_main();

    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

//Fonction callback pour le test select permettant de voir l'état de la BDD (à supprimer)
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void initializeDatabase() {
    int status;
    char *errMsg = 0;

    //Table entreprise et template
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        const char *createTableEntreprise =
            "CREATE TABLE IF NOT EXISTS Entreprise_Website ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT,"
            "about_us TEXT,"
            "slogan TEXT,"
            "contact TEXT,"
            "service1_name TEXT,"
            "service1_description TEXT," 
            "service2_name TEXT,"
            "service2_description TEXT," 
            "body_color TEXT,"
            "body_font_family TEXT,"
            "header_bg_color TEXT,"
            "header_text_color TEXT,"
            "a_text_color TEXT,"
            "footer_bg_color TEXT,"
            "footer_text_color TEXT,"
            "hero_bg_color TEXT"
            ");";

        if (sqlite3_exec(db, createTableEntreprise, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la création de la table : %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Table Entreprise_Website créée avec succès.\n");
            // Ajouter le template à la table uniquement si elle est vide (et que le template n'existe donc pas déjà)
            const char *insertTemplateEntreprise =
                "INSERT INTO Entreprise_Website (name, about_us, slogan, contact, "
                "service1_name, service1_description, service2_name, service2_description, "
                "body_color, body_font_family, header_bg_color, header_text_color, "
                "a_text_color, footer_bg_color, footer_text_color, hero_bg_color) "
                "SELECT 'Nom de l''Entreprise', 'Une brève description de l''entreprise et de son histoire', "
                "'Un slogan pour l''entreprise', 'Adresse, numéro de téléphone, formulaire de contact, etc.', "
                "'Service 1', 'Description du service 1', 'Service 2', 'Description du service 2', "
                "'#f4f4f4', 'Arial, sans-serif', '#333', '#fff', '#fff', '#333', '#fff', '#f4f4f4' "
                "WHERE NOT EXISTS (SELECT 1 FROM Entreprise_Website LIMIT 1)";

            if (sqlite3_exec(db, insertTemplateEntreprise, 0, 0, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de l'insertion du tuple : %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("Template de l'entreprise ajouté avec succès.\n");
            }
        }
        
        const char *createTableBlog =
            "CREATE TABLE IF NOT EXISTS Blog ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "blog_title TEXT,"
            "blog_description TEXT,"
            "article1_title TEXT,"
            "article1_date TEXT,"
            "article1_content TEXT,"
            "article2_title TEXT,"
            "article2_date TEXT,"
            "article2_content TEXT,"
            "about_me TEXT,"
            "contact_email TEXT"
            ");";

        if (sqlite3_exec(db, createTableBlog, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la création de la table : %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Table Blog créée avec succès.\n");
        }

        // Ajouter le template à la table uniquement si elle est vide (et que le template n'existe donc pas déjà)
            const char *insertTemplateBlog =
                "INSERT INTO Blog (blog_title, blog_description, "
                "article1_title, article1_date, article1_content, "
                "article2_title, article2_date, article2_content, "
                "about_me, contact_email) "
                "SELECT "
                "'Titre du blog', 'Description du blog', "
                "'Titre de l''article 1', '2024-01-01', 'Contenu de l''article 1...', "
                "'Titre de l''article 2', '2024-01-02', 'Contenu de l''article 2...', "
                "'À propos de moi', 'contact@monblog.com' "
                "WHERE NOT EXISTS (SELECT 1 FROM Blog LIMIT 1)";

            if (sqlite3_exec(db, insertTemplateBlog, 0, 0, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de l'insertion du tuple : %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("Template du blog ajouté avec succès.\n");
            } 

         const char *createTableCommerce =
            "CREATE TABLE IF NOT EXISTS ECommerce_Website ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "site_name TEXT,"
            "site_description TEXT,"
            "header_title TEXT,"
            "header_description TEXT,"
            "product1_title TEXT,"
            "product1_description TEXT,"
            "product1_price TEXT,"
            "product2_title TEXT,"
            "product2_description TEXT,"
            "product2_price TEXT,"
            "product3_title TEXT,"
            "product3_description TEXT,"
            "product3_price TEXT,"
            "product4_title TEXT,"
            "product4_description TEXT,"
            "product4_price TEXT,"
            "contact_email TEXT,"
            "footer_text TEXT);"
        ;

        if (sqlite3_exec(db, createTableCommerce, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la création de la table : %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Table Commerce créée avec succès.\n");
        }

        const char *insertTemplateECommerceSite =
                "INSERT INTO ECommerce_Website (site_name, site_description, "
                "header_title, header_description, "
                "product1_title, product1_description, product1_price, "
                "product2_title, product2_description, product2_price, "
                "product3_title, product3_description, product3_price, "
                "product4_title, product4_description, product4_price, "
                "contact_email, footer_text) "
                "SELECT "
                "'Nom du site', 'Description du site', "
                "'Titre de l''en-tête', 'Description de l''en-tête', "
                "'Produit 1', 'Description du produit 1', '$19.99', "
                "'Produit 2', 'Description du produit 2', '$29.99', "
                "'Produit 3', 'Description du produit 3', '$24.99', "
                "'Produit 4', 'Description du produit 4', '$39.99', "
                "'contact@monsite.com', '© 2024 Mon Site d''E-commerce. Tous droits réservés.' "
                "WHERE NOT EXISTS (SELECT 1 FROM ECommerce_Website LIMIT 1)";

            if (sqlite3_exec(db, insertTemplateECommerceSite, 0, 0, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de l'insertion du tuple : %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("Template du site d'e-commerce ajouté avec succès.\n");
            } 

        const char *createTableTravel =
            "CREATE TABLE IF NOT EXISTS Travel_Website ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT,"
            "slogan TEXT,"
            "about_us TEXT,"
            "header_title TEXT,"
            "header_description TEXT,"
            "destination_title TEXT,"
            "destination_image TEXT,"
            "destination_description TEXT,"
            "special_offer_title TEXT,"
            "special_offer_image TEXT,"
            "special_offer_description TEXT,"
            "contact_email TEXT,"
            "footer_text TEXT"
            ");"
        ;


        if (sqlite3_exec(db, createTableTravel, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la création de la table Travel_Website : %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Table Commerce créée avec succès.\n");
        }

            const char *insertTemplateTravel =
            "INSERT INTO Travel_Website (name, slogan, about_us, header_title, header_description, destination_title,"
            "destination_image, destination_description, special_offer_title, special_offer_image, special_offer_description," 
            "contact_email, footer_text)"
            "SELECT "
            "'Nom de l''Agence', 'Votre prochaine aventure commence ici.', "
            "'Découvrez des destinations extraordinaires et vivez des expériences inoubliables.', 'Explorez le Monde',"
            "'Découvrez des destinations extraordinaires et vivez des expériences inoubliables.', 'Tokyo, Japon', 'tokyo.jpg',"
            "'Explorez la modernité et la tradition dans la capitale du Japon.', 'Voyage tout compris à Bali', 'bali.jpg',"
            "'Profitez de plages paradisiaques et d''une expérience culturelle unique.', 'info@agencedevoyage.com', "
            "'&copy; 2024 Agence de Voyage. Tous droits réservés.'"
            "WHERE NOT EXISTS (SELECT 1 FROM Travel_Website LIMIT 1);"
            ;

            if (sqlite3_exec(db, insertTemplateTravel, 0, 0, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de l'insertion du tuple template travel: %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("Template du site de l'agence de voyage ajouté avec succès.\n");
            } 

    const char *createTableCV =
        "CREATE TABLE IF NOT EXISTS CV_Website ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "email TEXT,"
        "phone TEXT,"
        "linkedin TEXT,"
        "job_title TEXT,"
        "company TEXT,"
        "job_date TEXT,"
        "job_description TEXT,"
        "education TEXT,"
        "education_date TEXT,"
        "skills TEXT,"
        "download_link TEXT"
        ");";

        if (sqlite3_exec(db, createTableCV, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la création de la table CV_Website : %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Table Commerce créée avec succès.\n");
        }

        const char *insertTemplateCV =
            "INSERT INTO CV_Website ("
            "name, email, phone, linkedin, job_title, company, job_date, job_description, education, education_date, skills, download_link)"
            "SELECT "
            "'Nom Prénom', 'email@example.com', '+123456789', 'linkedin.com/in/nom', 'Titre du poste', 'Nom de l''entreprise', 'Date du travail', 'Description du travail', 'Nom de l''école', 'Date d''obtention', 'Compétences clés', 'lien_de_téléchargement.pdf'"
            "WHERE NOT EXISTS (SELECT 1 FROM CV_Website LIMIT 1);";


            if (sqlite3_exec(db, insertTemplateCV, 0, 0, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de l'insertion du tuple template travel: %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("Template du CVajouté avec succès.\n");
            } 

        
    //test pour voir l'état de la BDD (à supprimer)
    const char *selectQuery = "SELECT * FROM CV_Website";

    int rc;
    rc = sqlite3_exec(db, selectQuery, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erreur lors de la sélection des données : %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    //fin du test

        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }
}


void openFileInBrowser(const char *filePath) {
    ShellExecute(NULL, "open", filePath, NULL, NULL, SW_SHOWNORMAL);
}

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
