#include <stdio.h>
#include "sqlite/sqlite3.h"
#include "sqlite/sqlite3.c"
#include <gtk/gtk.h>


static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Hello");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_window_set_child (GTK_WINDOW (window), button);

  gtk_window_present (GTK_WINDOW (window));
}


int main(int    argc,
      char **argv) {
    // Declaration of a SQLite database pointer
    sqlite3 *db;
    // Pointer to store SQLite error messages
    char *err_msg = 0;

    // Attempt to open the "Website_Project.db" database
    int rc = sqlite3_open("Website_Project.db", &db);

    // Check if the database opening was successful
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Unable to open the database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // SQL query to create the "User" table if it doesn't exist
    char *sql = "CREATE TABLE IF NOT EXISTS User (\n"
                "                                         id INTEGER PRIMARY KEY,\n"
                "                                         username TEXT NOT NULL,\n"
                "                                         password TEXT NOT NULL\n"
                ");";

    // Execute the SQL query
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    // Check if the execution of the SQL query was successful
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", err_msg);

        // Free the memory allocated for the error message
        sqlite3_free(err_msg);

        // Close the database
        sqlite3_close(db);

        return rc;
    }

    // Close the database after a successful operation
    sqlite3_close(db);

      GtkApplication *app;
     int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

  return status;
    
    // Indication of the success of the program
    return 0;
}
