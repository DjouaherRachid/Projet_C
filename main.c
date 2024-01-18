#include <stdio.h>
#include "sqlite/sqlite3.h"
#include "sqlite/sqlite3.c"
#include <gtk/gtk.h>

static void launch(GtkApplication *app, gpointer user_data);
static void activate_menu(GtkApplication *app, gpointer user_data);
static void on_tab_selected(GtkNotebook *notebook, GtkWidget *page, guint page_num, gpointer user_data);
GtkWidget *create_menu_window(GtkApplication *app);
GtkWidget *create_login_window(GtkApplication *app);
GtkWidget *login_window = NULL;


//Menu principal
GtkWidget *create_menu_window(GtkApplication *app) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu principal");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_LEFT);

    const char *tab_labels[] = {"Create page from scratch", "Create page from template", "Load page"};

    for (int i = 0; i < G_N_ELEMENTS(tab_labels); i++) {
        GtkWidget *page = gtk_grid_new();
        GtkWidget *label = gtk_label_new(tab_labels[i]);

        PangoFontDescription *tab_font_desc = pango_font_description_from_string("Sans 10");
        gtk_widget_override_font(label, tab_font_desc);

        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, label);

        // "Create page from scratch"
        switch (i)
        {
        case 0:
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

        case 1:
            // Label "Create a page from template" centré
            GtkWidget *template_label = gtk_label_new("Create a page from template");
            PangoFontDescription *template_font_desc = pango_font_description_from_string("Sans 24");
            gtk_widget_override_font(template_label, template_font_desc);
            gtk_grid_attach(GTK_GRID(page), template_label, 0, 0, 1, 1);
            gtk_widget_set_halign(template_label, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(template_label, GTK_ALIGN_CENTER);

        break;
        
        default:
            break;
        }
    }

    GtkWidget *boxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(boxLeft), notebook, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(box), boxLeft);

    // Afficher la fenêtre principale
    gtk_widget_show_all(window);

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


//Procédure se lançant au démarrage de l'application
static void launch(GtkApplication *app, gpointer user_data) {
    login_window = create_menu_window(app);

    gtk_widget_show_all(login_window);

    gtk_main();

     g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

//Procédure censée se lancer lorsque l'utilisateur appuie sur connexion et ouvrant le menu
static void activate_menu(GtkApplication *app, gpointer user_data) {
    GtkWidget *menu_window = create_menu_window(app);

    gtk_widget_show_all(menu_window);
    g_signal_connect(menu_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fermer la fenêtre de connexion
    if (login_window != NULL) {
        gtk_widget_destroy(login_window);
        login_window = NULL;  
    }

    gtk_main();
     g_signal_connect(menu_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

int main(int argc, char *argv[]) {
    int status;
    GtkApplication *app = gtk_application_new("projet.c", G_APPLICATION_DEFAULT_FLAGS);
    // Créer la fenêtre de connexion en appelant la fonction
    g_signal_connect (app, "activate", G_CALLBACK (launch), NULL);
    g_signal_connect(app, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
