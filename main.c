#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#include "sqlite/sqlite3.c"
#include <gtk/gtk.h>

//Prototypes des procédures lançant les différentes fenêtres du projet
static void launch(GtkApplication *app, gpointer user_data);
static void activate_menu(GtkApplication *app, gpointer user_data);
static void activate_Entreprise(GtkApplication *app, gpointer user_data);

GtkWidget *create_menu_window(GtkApplication *app);
GtkWidget *create_login_window(GtkApplication *app);
GtkWidget *create_Entreprise_form(GtkApplication *app);

GtkWidget *login_window = NULL;
GtkWidget *menu_window = NULL;
GtkWidget *entreprise_form= NULL;

GtkApplication *app;

sqlite3 *db;

//Les procédures qui générent les sites
void generate_Entreprise_Website(const char *name, const char *about, const char *slogan, const char *contact,
                  const char *service1_name, const char *service1_description,
                  const char *service2_name, const char *service2_description,
                  const char *body_color, const char *body_font_family,
                  const char *header_bg_color, const char *header_text_color,
                  const char *a_text_color, const char *footer_bg_color,
                  const char *footer_text_color, const char *hero_bg_color) {

    FILE *file = fopen("Generated.html", "w");

    if (file != NULL) {
        fprintf(file, "<!DOCTYPE html>\n"
                      "<html lang=\"en\">\n"
                      "<head>\n"
                      "<meta charset=\"UTF-8\">\n"
                      "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                      "<title>%s</title>\n"
                      "<style>\n"
                      "body {\n"
                      "    font-family: %s;\n"
                      "    margin: 0;\n"
                      "    padding: 0;\n"
                      "    box-sizing: border-box;\n"
                      "    color: %s;\n"
                      "}\n"
                      "header {\n"
                      "    background-color: %s;\n"
                      "    color: %s;\n"
                      "    padding: 10px;\n"
                      "    text-align: center;\n"
                      "}\n"
                      "nav ul {\n"
                      "    list-style: none;\n"
                      "    margin: 0;\n"
                      "    padding: 0;\n"
                      "}\n"
                      "nav li {\n"
                      "    display: inline;\n"
                      "    margin-right: 20px;\n"
                      "}\n"
                      "a {\n"
                      "    text-decoration: none;\n"
                      "    color: %s;\n"
                      "}\n"
                      "#hero {\n"
                      "    background-color: %s;\n"
                      "    padding: 50px;\n"
                      "    text-align: center;\n"
                      "}\n"
                      "#services, #about, #contact {\n"
                      "    padding: 50px;\n"
                      "}\n"
                      ".service {\n"
                      "    margin-bottom: 20px;\n"
                      "}\n"
                      "footer {\n"
                      "    background-color: %s;\n"
                      "    color: %s;\n"
                      "    text-align: center;\n"
                      "    padding: 10px;\n"
                      "    position: fixed;\n"
                      "    bottom: 0;\n"
                      "    width: 100%%;\n"
                      "}\n"
                      "</style>\n"
                      "</head>\n"
                      "<body>\n"
                      "<header>\n"
                      "    <h1>%s</h1>\n"
                      "    <nav>\n"
                      "        <ul>\n"
                      "            <li><a href=\"#services\">Nos Services</a></li>\n"
                      "            <li><a href=\"#about\">À Propos</a></li>\n"
                      "            <li><a href=\"#contact\">Contact</a></li>\n"
                      "        </ul>\n"
                      "    </nav>\n"
                      "</header>\n"
                      "<section id=\"hero\">\n"
                      "    <h2>%s</h2>\n"
                      "</section>\n"
                      "<section id=\"services\">\n"
                      "    <h2>Nos Services</h2>\n"
                      "    <div class=\"service\">\n"
                      "        <h3>%s</h3>\n"
                      "        <p>%s</p>\n"
                      "    </div>\n"
                      "    <div class=\"service\">\n"
                      "        <h3>%s</h3>\n"
                      "        <p>%s</p>\n"
                      "    </div>\n"
                      "</section>\n"
                      "<section id=\"about\">\n"
                      "    <h2>À Propos de Nous</h2>\n"
                      "    <p>%s</p>\n"
                      "</section>\n"
                      "<section id=\"contact\">\n"
                      "    <h2>Contactez-nous</h2>\n"
                      "    <p>%s</p>\n"
                      "</section>\n"
                      "<footer>\n"
                      "    <p>&copy; 2024 %s. Tous droits réservés.</p>\n"
                      "</footer>\n"
                      "</body>\n"
                      "</html>\n", name, body_font_family, body_color, header_bg_color, header_text_color,
                      a_text_color, hero_bg_color, footer_bg_color, footer_text_color, name, slogan,
                      service1_name, service1_description, service2_name, service2_description,
                      about, contact, name);

        fclose(file);
        printf("Fichier HTML généré avec succès : %s\n", "Generated.html");
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier HTML de sortie.\n");
    }
}

// Fonction de rappel pour le bouton "OK" après avoir ajouté un site à la BDD
void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    g_print("Réponse du bouton : %d\n", response_id);
    gtk_widget_destroy(GTK_WIDGET(dialog));  
        if (entreprise_form != NULL) {
        gtk_widget_destroy(entreprise_form);
        entreprise_form = NULL;  
        activate_menu(app,NULL);
    }
}

void save_entreprise_website(GtkWidget *button, GtkWidget **entries) {
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
    generate_Entreprise_Website(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7],
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
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entreprise_form),GTK_DIALOG_DESTROY_WITH_PARENT,
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
GtkWidget *create_Entreprise_form(GtkApplication *app) {
    GtkWidget *entreprise_form = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(entreprise_form), "Entreprise_Website");
    gtk_window_set_default_size(GTK_WINDOW(entreprise_form), 1280, 720);
    g_signal_connect(entreprise_form, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(entreprise_form), grid);

    // Ajouter le libellé du titre
    GtkWidget *titleLabel = gtk_label_new("Create your own entreprise website");
    PangoFontDescription *titleFontDesc = pango_font_description_from_string("Sans Bold 18");
    gtk_widget_override_font(titleLabel, titleFontDesc);
    gtk_widget_set_halign(titleLabel, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(grid), titleLabel, 0, 0, 2, 1);
    pango_font_description_free(titleFontDesc);

    const char *parameters[] = {
        "Name", "About Us", "Slogan", "Contact",
        "Service 1 Name", "Service 1 Description",
        "Service 2 Name", "Service 2 Description",
        "Body Color", "Body Font Family",
        "Header BG Color", "Header Text Color",
        "A Text Color", "Footer BG Color",
        "Footer Text Color", "Hero BG Color"
    };

    // Créer un tableau de widgets pour stocker les zones de texte
    GtkWidget **entries = malloc(G_N_ELEMENTS(parameters) * sizeof(GtkWidget *));

    const char *default_texts[] = {
        "Nom de l'Entreprise","Une brève description de l'entreprise et de son histoire", "Un slogan pour l'entreprise","Adresse, numéro de téléphone, formulaire de contact, etc.",
        "Service 1", "Description du service 1",
        "Service 2", "Description du service 2",
        "#000000 ", "Arial, sans-serif", 
        "#333", "#fff", "#fff", "#333", "#fff", "#f4f4f4"
    };

    for (int i = 0; i < G_N_ELEMENTS(parameters); i++) {
        GtkWidget *label = gtk_label_new(parameters[i]);
        GtkWidget *entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(entry), default_texts[i]);

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
    GtkWidget *submit_button = gtk_button_new_with_label("Enregistrer");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(save_entreprise_website), entries);

    // Ajouter de l'espace vertical entre le dernier champ et le bouton
    int vertical_spacing_button = 20;
    gtk_widget_set_margin_bottom(submit_button, vertical_spacing_button);

    // Multiplier par 2 la largeur du bouton
    gtk_widget_set_size_request(submit_button, 2 * gtk_widget_get_allocated_width(submit_button), -1);

    // Ajouter le bouton au GtkGrid
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, G_N_ELEMENTS(parameters) + 1, 2, 1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    return entreprise_form;
}

GtkWidget *create_template_widget(const char *template_name) {
    GtkWidget *template_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *label = gtk_label_new(template_name);
    PangoFontDescription *font_desc = pango_font_description_from_string("Sans 16");
    gtk_widget_override_font(label, font_desc);

    GtkWidget *button = gtk_button_new_with_label("Select");

    //Cliquer sur le bouton ouvre le formulaire de personnalisation du site d'entreprise si on 
    if (strcmp(template_name, "Site d'Entreprise") == 0) 
    g_signal_connect(button, "clicked", G_CALLBACK(activate_Entreprise), NULL);

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

    const char *tab_labels[] = {"Create page from template", "Create page from scratch", "Load page"};

    for (int i = 0; i < G_N_ELEMENTS(tab_labels); i++) {
        GtkWidget *page = gtk_grid_new();
        GtkWidget *label = gtk_label_new(tab_labels[i]);

        PangoFontDescription *tab_font_desc = pango_font_description_from_string("Sans 10");
        gtk_widget_override_font(label, tab_font_desc);

        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, label);

        switch (i) {
            case 1:
                GtkWidget *large_label = gtk_label_new("Create a page from scratch");
                PangoFontDescription *large_font_desc = pango_font_description_from_string("Sans 24");
                gtk_widget_override_font(large_label, large_font_desc);
                gtk_grid_attach(GTK_GRID(page), large_label, 0, 0, 1, 1);

                // Ajouter un bouton "Start"
                GtkWidget *start_button = gtk_button_new_with_label("Start");
                gtk_widget_set_size_request(start_button, 200, 100);
                gtk_grid_attach(GTK_GRID(page), start_button, 0, 1, 1, 1);
                gtk_widget_set_hexpand(start_button, TRUE);
                gtk_widget_set_vexpand(start_button, TRUE);
                gtk_widget_set_halign(start_button, GTK_ALIGN_CENTER);
                gtk_widget_set_valign(start_button, GTK_ALIGN_CENTER);

                // Connecter une fonction de rappel pour le bouton "Start" 
                // g_signal_connect(start_button, "clicked", G_CALLBACK(start_button_clicked), NULL);
                break;

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
                const char *template_names[] = {"Site d'Entreprise", "Blog Personnel ", "Site d'e-commerce", "Site d'Agence de Voyage", "Template de CV en Ligne"};

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
    entreprise_form = create_Entreprise_form(app);

    gtk_widget_show_all(entreprise_form);
    g_signal_connect(entreprise_form, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre du menu
    if (menu_window != NULL) {
        gtk_widget_destroy(menu_window);
        menu_window = NULL;  
    }

    gtk_main();
}

//Procédure se lançant au démarrage de l'application
static void launch(GtkApplication *app, gpointer user_data) {
    login_window = create_login_window(app);

    gtk_widget_show_all(login_window);

    gtk_main();

    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
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

    gtk_main();
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

int main(int argc, char *argv[]) {
    int status;
    char *errMsg = 0;

    // Initialiser GTK
    app = gtk_application_new("projet.c", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_menu), NULL);

    // Ouvrir la base de données (elle sera créée si elle n'existe pas)
    if (sqlite3_open("DataBase.db", &db) == SQLITE_OK) {
        const char *createTableSQL =
            "CREATE TABLE IF NOT EXISTS Entreprise_Website ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT,"
            "about_us TEXT,"
            "slogan TEXT,"
            "contact TEXT,"
            "service1_name,"
            "service1_description," 
            "service2_name,"
            "service2_description," 
            "body_color TEXT,"
            "body_font_family TEXT,"
            "header_bg_color TEXT,"
            "header_text_color TEXT,"
            "a_text_color TEXT,"
            "footer_bg_color TEXT,"
            "footer_text_color TEXT,"
            "hero_bg_color TEXT"
            ");";

        if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
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
                printf("Tuple ajouté avec succès.\n");
            }
        }

        // Fermer la base de données
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
    }

    // Exécuter l'application GTK
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

