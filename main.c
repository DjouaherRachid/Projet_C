#include <stdio.h>
#include "sqlite/sqlite3.h"
#include "sqlite/sqlite3.c"

int main() {
    //printf("SQLite version: %s\n", sqlite3_version);
    //return 0;

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

    // Indication of the success of the program
    return 0;
}
