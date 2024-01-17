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



//Animation lorsque l'utilisateur change d'onglet dans le menu
static void on_tab_selected(GtkNotebook *notebook, GtkWidget *page, guint page_num, gpointer user_data) {
    gtk_stack_set_visible_child_name(GTK_STACK(user_data), gtk_notebook_get_tab_label_text(notebook, page));
}

//Menu principal
GtkWidget *create_menu_window(GtkApplication *app) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu principal");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    GtkWidget *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_LEFT);
    g_signal_connect(notebook, "switch-page", G_CALLBACK(on_tab_selected), stack);

    const char *tab_labels[] = {"Onglet 1", "Onglet 2", "Onglet 3"};

    for (int i = 0; i < G_N_ELEMENTS(tab_labels); i++) {
        GtkWidget *page = gtk_label_new(g_strdup_printf("Contenu de l'onglet %d", i + 1));
        GtkWidget *label = gtk_label_new(tab_labels[i]);
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, label);
    }

    GtkWidget *boxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(boxLeft), notebook, TRUE, TRUE, 0);

    GtkWidget *label1 = gtk_label_new("Contenu de l'onglet 1");
    GtkWidget *label2 = gtk_label_new("Contenu de l'onglet 2");
    GtkWidget *label3 = gtk_label_new("Contenu de l'onglet 3");

    gtk_stack_add_named(GTK_STACK(stack), label1, "Onglet 1");
    gtk_stack_add_named(GTK_STACK(stack), label2, "Onglet 2");
    gtk_stack_add_named(GTK_STACK(stack), label3, "Onglet 3");

    gtk_container_add(GTK_CONTAINER(box), boxLeft);
    gtk_container_add(GTK_CONTAINER(box), stack);

    return window;
}

//Fenêtre de connexion
GtkWidget *create_login_window(GtkApplication *app) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Interface de Connexion");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), login_window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *username_label = gtk_label_new("Username:");
    GtkWidget *username_entry = gtk_entry_new();

    GtkWidget *password_label = gtk_label_new("Password:");
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    GtkWidget *connect_button = gtk_button_new_with_label("Connexion");
    g_signal_connect(connect_button, "clicked", G_CALLBACK(activate_menu), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), username_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), username_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), connect_button, FALSE, FALSE, 0);

    return window;
}

//Procédure se lançant au démarrage de l'application
static void launch(GtkApplication *app, gpointer user_data) {
    login_window = create_login_window(app);

    gtk_widget_show_all(login_window);

    gtk_main();
}

//Procédure censée se lancer lorsque l'utilisateur appuie sur connexion et ouvrant le menu
static void activate_menu(GtkApplication *app, gpointer user_data) {
    GtkWidget *menu_window = create_menu_window(app);

    gtk_widget_show_all(menu_window);

    // Fermer la fenêtre de connexion
    if (login_window != NULL) {
        gtk_widget_destroy(login_window);
        login_window = NULL;  
    }

    gtk_main();
}

int main(int argc, char *argv[]) {
    int status;
    GtkApplication *app = gtk_application_new("projet.c", G_APPLICATION_DEFAULT_FLAGS);
    // Créer la fenêtre de connexion en appelant la fonction
    g_signal_connect (app, "activate", G_CALLBACK (launch), NULL);

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
