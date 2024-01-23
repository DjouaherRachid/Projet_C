#include <stdio.h>
#include <windows.h>
#include <string.h>
//#include "curlfunc.c"

char currentDirectory[FILENAME_MAX];


//Site vitrine d'entreprise
void generate_Company_Website(const char *name, const char *about, const char *slogan, const char *contact, 
                  const char *service1_name, const char *service1_description,
                  const char *service2_name, const char *service2_description,
                  const char *body_color, const char *body_font_family,
                  const char *header_bg_color, const char *header_text_color,
                  const char *a_text_color, const char *footer_bg_color,
                  const char *footer_text_color, const char *hero_bg_color) {
    char filename[256]; 
    strcpy(filename,"Generated_Websites\\Entreprise_");
    strcat(filename,name);
    strcat(filename,".html");
    
    
    FILE *file = fopen(filename, "w");

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
        printf("Fichier HTML généré avec succès : %s\n", filename);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier HTML de sortie.\n");
    }
    //Ouvrir le fichier html créé
    // Chemin complet du fichier HTML
    char fullPath[FILENAME_MAX];
    strcpy(fullPath,currentDirectory);
    strcat(fullPath,"\\\""); //Ajout de guillemets au cas où il y aurait un espace dans le nom
    strcat(fullPath,filename);
    strcat(fullPath,"\"");
    // Commande pour ouvrir le fichier
    char command[512];
    strcpy(command,"start ");
    strcat(command,fullPath);

    printf("%s",command);
    // Exécuter la commande
    system(command);
}


//Site d'Ecommerce
void generate_ECommerce_Site(const char *site_name, const char *site_description,
                            const char *header_title, const char *header_description,
                            const char *product1_title, const char *product1_description, const char *product1_price,
                            const char *product2_title, const char *product2_description, const char *product2_price,
                            const char *product3_title, const char *product3_description, const char *product3_price,
                            const char *product4_title, const char *product4_description, const char *product4_price,
                            const char *contact_email, const char *footer_text) {

    char filename[256];
    snprintf(filename, sizeof(filename), "Generated_Websites\\ECommerce_%s.html", site_name);

    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        fprintf(file,
                "<!DOCTYPE html>\n"
                "<html lang=\"en\">\n"
                "<head>\n"
                "<meta charset=\"UTF-8\">\n"
                "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                "<style>\n"
                "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; padding: 0; box-sizing: border-box; background-color: #f5f5f5; color: #333; }\n"
                "header { background-color: #4285f4; color: #fff; padding: 20px; text-align: center; }\n"
                "nav ul { list-style: none; margin: 0; padding: 0; }\n"
                "nav li { display: inline; margin-right: 20px; }\n"
                "a { text-decoration: none; color: #4285f4; }\n"
                ".product { background-color: #fff; margin: 20px; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }\n"
                ".product h3 { color: #4285f4; }\n"
                ".product p { color: #666; }\n"
                "section { padding: 40px; }\n"
                "footer { background-color: #333; color: #fff; text-align: center; padding: 10px; }\n"
                "</style>\n"
                "<title>%s</title>\n"
                "</head>\n"
                "<body>\n"
                "<header>\n"
                "    <h1>%s</h1>\n"
                "    <p>%s</p>\n"
                "</header>\n"
                "<nav>\n"
                "    <ul>\n"
                "        <li><a href=\"#accueil\">Accueil</a></li>\n"
                "        <li><a href=\"#produits\">Produits</a></li>\n"
                "        <li><a href=\"#panier\">Panier</a></li>\n"
                "        <li><a href=\"#contact\">Contact</a></li>\n"
                "    </ul>\n"
                "</nav>\n"
                "<section id=\"accueil\">\n"
                "    <div class=\"product\">\n"
                "        <h3>%s</h3>\n"
                "        <p>%s</p>\n"
                "        <p>Prix: %s</p>\n"
                "        <button>Ajouter au panier</button>\n"
                "    </div>\n"
                "    <div class=\"product\">\n"
                "        <h3>%s</h3>\n"
                "        <p>%s</p>\n"
                "        <p>Prix: %s</p>\n"
                "        <button>Ajouter au panier</button>\n"
                "    </div>\n"
                "</section>\n"
                "<section id=\"produits\">\n"
                "    <div class=\"product\">\n"
                "        <h3>%s</h3>\n"
                "        <p>%s</p>\n"
                "        <p>Prix: %s</p>\n"
                "        <button>Ajouter au panier</button>\n"
                "    </div>\n"
                "    <div class=\"product\">\n"
                "        <h3>%s</h3>\n"
                "        <p>%s</p>\n"
                "        <p>Prix: %s</p>\n"
                "        <button>Ajouter au panier</button>\n"
                "    </div>\n"
                "</section>\n"
                "<section id=\"panier\">\n"
                "    <h2>Panier</h2>\n"
                "    <!-- Contenu du panier -->\n"
                "</section>\n"
                "<section id=\"contact\">\n"
                "    <h2>Contactez-nous</h2>\n"
                "    <p>Vous pouvez nous contacter à l'adresse email suivante : <a href=\"mailto:%s\">%s</a></p>\n"
                "</section>\n"
                "<footer>\n"
                "    <p>%s</p>\n"
                "</footer>\n"
                "</body>\n"
                "</html>\n",
                site_name, site_name, site_description,
                product1_title, product1_description, product1_price,
                product2_title, product2_description, product2_price,
                product3_title, product3_description, product3_price,
                product4_title, product4_description, product4_price,
                contact_email, contact_email, footer_text);

        fclose(file);
        printf("Fichier HTML généré avec succès : %s\n", filename);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier HTML de sortie.\n");
    }
     //Ouvrir le fichier html créé
    // Chemin complet du fichier HTML
    char fullPath[FILENAME_MAX];
    strcpy(fullPath,currentDirectory);
    strcat(fullPath,"\\\""); //Ajout de guillemets au cas où il y aurait un espace dans le nom
    strcat(fullPath,filename);
    strcat(fullPath,"\"");
    // Commande pour ouvrir le fichier
    char command[512];
    strcpy(command,"start ");
    strcat(command,fullPath);

    printf("%s",command);
    // Exécuter la commande
    system(command);
}


//Blog
void generate_Personal_Blog(const char *blog_title, const char *blog_description,
                            const char *article1_title, const char *article1_date, const char *article1_content,
                            const char *article2_title, const char *article2_date, const char *article2_content,
                            const char *about_me, const char *contact_email) {

    char filename[256];
    snprintf(filename, sizeof(filename), "Generated_Websites\\Blog_%s.html", blog_title);

    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        fprintf(file,
                "<!DOCTYPE html>\n"
                "<html lang=\"en\">\n"
                "<head>\n"
                "<meta charset=\"UTF-8\">\n"
                "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                "<style>\n"
                "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; padding: 0; box-sizing: border-box; background-color: #f5f5f5; color: #333; }\n"
                "header { background-color: #4285f4; color: #fff; padding: 20px; text-align: center; }\n"
                "nav ul { list-style: none; margin: 0; padding: 0; }\n"
                "nav li { display: inline; margin-right: 20px; }\n"
                "a { text-decoration: none; color: #4285f4; }\n"
                "article { background-color: #fff; margin: 20px; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }\n"
                "article h2 { color: #4285f4; }\n"
                "article p { color: #666; }\n"
                "section { padding: 40px; }\n"
                "footer { background-color: #333; color: #fff; text-align: center; padding: 10px; }\n"
                "</style>\n"
                "<title>%s</title>\n"
                "</head>\n"
                "<body>\n"
                "<header>\n"
                "    <h1>%s</h1>\n"
                "    <p>%s</p>\n"
                "</header>\n"
                "<nav>\n"
                "    <ul>\n"
                "        <li><a href=\"#accueil\">Accueil</a></li>\n"
                "        <li><a href=\"#articles\">Articles</a></li>\n"
                "        <li><a href=\"#a-propos\">À Propos</a></li>\n"
                "        <li><a href=\"#contact\">Contact</a></li>\n"
                "    </ul>\n"
                "</nav>\n"
                "<section id=\"accueil\">\n"
                "    <article>\n"
                "        <h2>%s</h2>\n"
                "        <p>Date de publication: %s</p>\n"
                "        <p>%s</p>\n"
                "    </article>\n"
                "    <article>\n"
                "        <h2>%s</h2>\n"
                "        <p>Date de publication: %s</p>\n"
                "        <p>%s</p>\n"
                "    </article>\n"
                "</section>\n"
                "<section id=\"a-propos\">\n"
                "    <h2>À Propos de Moi</h2>\n"
                "    <p>%s</p>\n"
                "</section>\n"
                "<section id=\"contact\">\n"
                "    <h2>Contact</h2>\n"
                "    <p>Vous pouvez me contacter à l'adresse email suivante : <a href=\"mailto:%s\">%s</a></p>\n"
                "</section>\n"
                "<footer>\n"
                "    <p>&copy; 2024 %s. Tous droits réservés.</p>\n"
                "</footer>\n"
                "</body>\n"
                "</html>\n",
                blog_title, blog_title, blog_description,
                article1_title, article1_date, article1_content,
                article2_title, article2_date, article2_content,
                about_me, contact_email, contact_email, blog_title);

        fclose(file);
        printf("Fichier HTML généré avec succès : %s\n", filename);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier HTML de sortie.\n");
    }
     //Ouvrir le fichier html créé
    // Chemin complet du fichier HTML
    char fullPath[FILENAME_MAX];
    strcpy(fullPath,currentDirectory);
    strcat(fullPath,"\\\""); //Ajout de guillemets au cas où il y aurait un espace dans le nom
    strcat(fullPath,filename);
    strcat(fullPath,"\"");
    // Commande pour ouvrir le fichier
    char command[512];
    strcpy(command,"start ");
    strcat(command,fullPath);

    printf("%s",command);
    // Exécuter la commande
    system(command);   
}

void generate_Travel_Website(const char *name, const char *slogan, const char *about_us,
                             const char *header_title, const char *header_description,
                             const char *destination_title, const char *destination_image, const char *destination_description,
                             const char *special_offer_title, const char *special_offer_image, const char *special_offer_description,
                             const char *contact_email, const char *footer_text) {

    printf("Début de la génération du site Web de voyage...\n");

    char filename[256];
    snprintf(filename, sizeof(filename), "Generated_Websites\\Travel_%s.html", name);

    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        int result;

        // Partie 1: Doctype et balise html
        printf("Partie 1: Doctype et balise html\n");
        result = fprintf(file, "<!DOCTYPE html>\n"
                               "<html lang=\"en\">\n");

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 1 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 2: Balise head
        printf("Partie 2: Balise head\n");
        result = fprintf(file, "<head>\n"
                               "    <meta charset=\"UTF-8\">\n"
                               "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                               "    <title>%s</title>\n"
                               "    <style>\n"
                               "        body {\n"
                               "            font-family: 'Arial', sans-serif;\n"
                               "            margin: 0;\n"
                               "            padding: 0;\n"
                               "            box-sizing: border-box;\n"
                               "            background-color: #f9f9f9;\n"
                               "            color: #333;\n"
                               "        }\n"
                               "        header {\n"
                               "            background-color: #003366;\n"
                               "            color: #fff;\n"
                               "            padding: 20px;\n"
                               "            text-align: center;\n"
                               "        }\n"
                               "        nav ul {\n"
                               "            list-style: none;\n"
                               "            margin: 0;\n"
                               "            padding: 0;\n"
                               "            text-align: center;\n"
                               "        }\n"
                               "        nav li {\n"
                               "            display: inline;\n"
                               "            margin-right: 20px;\n"
                               "        }\n"
                               "        a {\n"
                               "            text-decoration: none;\n"
                               "            color: #333;\n"
                               "        }\n"
                               "        section {\n"
                               "            padding: 20px;\n"
                               "        }\n"
                               "        .destination {\n"
                               "            background-color: #fff;\n"
                               "            margin: 10px;\n"
                               "            padding: 20px;\n"
                               "            border-radius: 8px;\n"
                               "            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\n"
                               "        }\n"
                               "        footer {\n"
                               "            background-color: #003366;\n"
                               "            color: #fff;\n"
                               "            text-align: center;\n"
                               "            padding: 10px;\n"
                               "        }\n"
                               "    </style>\n"
                               "</head>\n", header_title);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 2 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 3: Balise body et div.container
        printf("Partie 3: Balise body et div.container\n");
        result = fprintf(file, "<body>\n"
                               "    <div class=\"container\">\n");

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 3 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 4: Header
        printf("Partie 4: Header\n");
        result = fprintf(file, "        <header>\n"
                               "            <h1>%s</h1>\n"
                               "            <p>%s</p>\n"
                               "        </header>\n",
                               name, slogan);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 4 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 5: Section A propos de nous
        printf("Partie 5: Section A propos de nous\n");
        result = fprintf(file, "        <section id=\"aboutUs\" class=\"section\">\n"
                               "            <h2>A propos de nous</h2>\n"
                               "            <p>%s</p>\n"
                               "        </section>\n",
                               about_us);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 5 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 6: Section Destinations
        printf("Partie 6: Section Destinations\n");
        printf("Destination Title: %s\n", destination_title);
        printf("Destination Image: %s\n", destination_image);
        printf("Destination Description: %s\n", destination_description);


        /* char filename1[FILENAME_MAX];
        snprintf(filename1, sizeof(filename1), "Generated_Websites\\Travel_%s1.png", name);
        download_image(destination_image,filename1); */
        
        

        result = fprintf(file, "        <section id=\"destinations\" class=\"section\">\n"
                               "            <h2>Destinations Populaires</h2>\n"
                               "            <div class=\"destination\">\n"
                               "                <h3>%s</h3>\n"
                               "                <img src=\"Travel_%s1.png\" alt=\"image1\">\n"
                               "                <p>%s</p>\n"
                               "                <button>En savoir plus</button>\n"
                               "            </div>\n"
                               "        </section>\n",
                               destination_title, name, destination_image, destination_description);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 6 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 7: Section Offres Spéciales

          /* char filename2[FILENAME_MAX];
        snprintf(filename2, sizeof(filename2), "Generated_Websites\\Travel_%s2.png", name);
        download_image(destination_image,filename2); */
        
        printf("Partie 7: Section Offres Spéciales\n");
        result = fprintf(file, "        <section id=\"specialOffers\" class=\"section\">\n"
                               "            <h2>Offres Spéciales</h2>\n"
                               "            <div class=\"destination\">\n"
                               "                <h3>%s</h3>\n"
                               "                <img src=\"Travel_%s2.png\" alt=\"%s\">\n"
                               "                <p>%s</p>\n"
                               "                <button>Réservez maintenant</button>\n"
                               "            </div>\n"
                               "        </section>\n",
                               special_offer_title, name, special_offer_image, special_offer_description);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 7 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 8: Section Contact
        printf("Partie 8: Section Contact\n");
        result = fprintf(file, "        <section id=\"contact\" class=\"section\">\n"
                               "            <h2>Contactez-nous</h2>\n"
                               "            <p>%s</p>\n"
                               "            <p>Email: <a href=\"mailto:%s\">%s</a></p>\n"
                               "        </section>\n",
                               contact_email, contact_email, contact_email);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 8 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 9: Footer
        printf("Partie 9: Footer\n");
        result = fprintf(file, "        <footer>\n"
                               "            <p>%s</p>\n"
                               "        </footer>\n"
                               "    </div>\n"
                               "</body>\n"
                               "</html>\n",
                               footer_text);

        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 9 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Fermer le fichier
        fclose(file);
        printf("Fichier HTML généré avec succès : %s\n", filename);
    } else {
        // L'ouverture du fichier a échoué
        fprintf(stderr, "Erreur lors de l'ouverture du fichier HTML de sortie.\n");
    }
    printf("Fin de la génération du site Web de voyage.\n");
    //Ouvrir le fichier html créé
    // Chemin complet du fichier HTML
    char fullPath[FILENAME_MAX];
    strcpy(fullPath,currentDirectory);
    strcat(fullPath,"\\\""); //Ajout de guillemets au cas où il y aurait un espace dans le nom
    strcat(fullPath,filename);
    strcat(fullPath,"\"");
    // Commande pour ouvrir le fichier
    char command[512];
    strcpy(command,"start ");
    strcat(command,fullPath);

    printf("%s",command);
    // Exécuter la commande
    system(command);
}

//Celui là est divisé en plusieurs sections 
void generate_CV(const char *name, const char *email, const char *phone, const char *linkedin, const char *job_title,
                 const char *company, const char *job_date, const char *job_description,
                 const char *education, const char *education_date,
                 const char *skills, const char *download_link) {

    char filename[256];
    snprintf(filename, sizeof(filename), "Generated_Websites\\CV_%s.html", name);

    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        int result;

        // Partie 1: Doctype et balise html
        result = fprintf(file, "<!DOCTYPE html>\n"
                               "<html lang=\"en\">\n");

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 1 dans le fichier HTML.\n");
            fclose(file);
            return;
        }else{printf("partie 1 terminée");}

        // Partie 2: Balise head
        result = fprintf(file, "<head>\n"
                               "    <meta charset=\"UTF-8\">\n"
                               "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
                               "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                               "    <title>%s - CV</title>\n"
                               "    <style>\n"
                               "        body {\n"
                               "            font-family: Arial, sans-serif;\n"
                               "            margin: 0;\n"
                               "            padding: 0;\n"
                               "            box-sizing: border-box;\n"
                               "            background-color: #f4f4f4;\n"
                               "        }\n"
                               "        .container {\n"
                               "            max-width: 800px;\n"
                               "            margin: 50px auto;\n"
                               "            background-color: #fff;\n"
                               "            padding: 20px;\n"
                               "            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\n"
                               "        }\n"
                               "        h1, h2, h3 {\n"
                               "            color: #333;\n"
                               "        }\n"
                               "        p {\n"
                               "            color: #666;\n"
                               "        }\n"
                               "        .section {\n"
                               "            margin-bottom: 20px;\n"
                               "        }\n"
                               "        #downloadButton {\n"
                               "            display: block;\n"
                               "            width: 100%;\n"
                               "            padding: 10px;\n"
                               "            background-color: #007bff;\n"
                               "            color: #fff;\n"
                               "            text-align: center;\n"
                               "            text-decoration: none;\n"
                               "            border: none;\n"
                               "            border-radius: 5px;\n"
                               "            cursor: pointer;\n"
                               "            font-size: 16px;\n"
                               "        }\n"
                               "    </style>\n"
                               "</head>\n");

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 2 dans le fichier HTML.\n");
            fclose(file);
            return;
        }else{printf("partie 2");}

        // Partie 3: Balise body et div.container
        result = fprintf(file, "<body>\n"
                               "    <div class=\"container\">\n");

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 3 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 4: Header
        result = fprintf(file, "        <header>\n"
                               "            <h1>%s</h1>\n"
                               "            <p>%s</p>\n"
                               "        </header>\n",
                               name, job_title);

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 4 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 5: Section Coordonnées
        result = fprintf(file, "        <section class=\"section\">\n"
                               "            <h2>Coordonnées</h2>\n"
                               "            <p>Email: %s</p>\n"
                               "            <p>Téléphone: %s</p>\n"
                               "            <p>LinkedIn: %s</p>\n"
                               "        </section>\n",
                               email, phone, linkedin);

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 5 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 6: Section Expérience Professionnelle
        result = fprintf(file, "        <section class=\"section\">\n"
                               "            <h2>Expérience Professionnelle</h2>\n"
                               "            <h3>%s - %s</h3>\n"
                               "            <p>Date: %s</p>\n"
                               "            <p>%s</p>\n"
                               "        </section>\n",
                               company, job_title, job_date, job_description);

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 6 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 7: Section Formation
        result = fprintf(file, "        <section class=\"section\">\n"
                               "            <h2>Formation</h2>\n"
                               "            <h3>%s</h3>\n"
                               "            <p>Date d'obtention: %s</p>\n"
                               "        </section>\n",
                               education, education_date);

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 7 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 8: Section Compétences
        result = fprintf(file, "        <section class=\"section\">\n"
                               "            <h2>Compétences</h2>\n"
                               "            <p>%s</p>\n"
                               "        </section>\n",
                               skills);

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 8 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Partie 9: Bouton Télécharger
        result = fprintf(file, "        <a id=\"downloadButton\" href=\"%s\" download=\"%s\">Télécharger le CV</a>\n"
                               "    </div>\n"
                               "</body>\n"
                               "</html>\n",
                               download_link, name);

        // Vérifier le résultat de l'écriture
        if (result < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de la partie 9 dans le fichier HTML.\n");
            fclose(file);
            return;
        }

        // Fermer le fichier
        fclose(file);
        printf("Fichier HTML généré avec succès : %s\n", filename);
    } else {
        // L'ouverture du fichier a échoué
        fprintf(stderr, "Erreur lors de l'ouverture du fichier HTML de sortie.\n");
    }
    //Ouvrir le fichier html créé
    // Chemin complet du fichier HTML
    char fullPath[FILENAME_MAX];
    strcpy(fullPath,currentDirectory);
    strcat(fullPath,"\\\""); //Ajout de guillemets au cas où il y aurait un espace dans le nom
    strcat(fullPath,filename);
    strcat(fullPath,"\"");
    // Commande pour ouvrir le fichier
    char command[512];
    strcpy(command,"start ");
    strcat(command,fullPath);

    printf("%s",command);
    // Exécuter la commande
    system(command);
}