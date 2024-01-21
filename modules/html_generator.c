#include <stdio.h>
#include "html_generator.h"

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