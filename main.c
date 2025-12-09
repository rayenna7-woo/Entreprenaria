#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ============= TACHE 1: STRUCTURES =============
#define MAX_SALLES 10
#define MAX_RESERVATIONS 100

typedef struct {
    int id;
    char nom[50];
    int capacite;
    float tarif_horaire;
    char equipements[100];
} Salle;

typedef struct {
    int id;
    char nom_client[50];
    int salle_id;
    char date[12];
    char heure_debut[6];
    char heure_fin[6];
    int nombre_personnes;
    float tarif;
    char statut[15];
} Reservation;

// Variables globales
Salle salles[MAX_SALLES];
Reservation reservations[MAX_RESERVATIONS];
int nb_salles = 0;
int nb_reservations = 0;

// ============= TACHE 2+3: FONCTIONS RESERVATION =============

int heure_to_minutes(const char *heure) {
    int h, m;
    sscanf(heure, "%d:%d", &h, &m);
    return h * 60 + m;
}

float calculer_duree(const char *debut, const char *fin) {
    return (heure_to_minutes(fin) - heure_to_minutes(debut)) / 60.0;
}

int verifier_disponibilite(int salle_id, const char *date, const char *h_debut, const char *h_fin) {
    int debut = heure_to_minutes(h_debut);
    int fin = heure_to_minutes(h_fin);

    for (int i = 0; i < nb_reservations; i++) {
        if (reservations[i].salle_id == salle_id &&
            strcmp(reservations[i].date, date) == 0 &&
            strcmp(reservations[i].statut, "CONFIRMEE") == 0) {

            int r_debut = heure_to_minutes(reservations[i].heure_debut);
            int r_fin = heure_to_minutes(reservations[i].heure_fin);

            if (debut < r_fin && fin > r_debut) {
                printf("[ERREUR] Creneau occupe!\n");
                return 0;
            }
        }
    }
    return 1;
}

void creer_reservation() {
    if (nb_reservations >= MAX_RESERVATIONS) {
        printf("[ERREUR] Plus de place!\n");
        return;
    }

    Reservation r;
    r.id = nb_reservations + 1;

    printf("\n=== NOUVELLE RESERVATION ===\n");
    printf("Nom client: ");
    scanf("%s", r.nom_client);

    printf("Salle (1-%d): ", nb_salles);
    scanf("%d", &r.salle_id);
    r.salle_id--;

    if (r.salle_id < 0 || r.salle_id >= nb_salles) {
        printf("[ERREUR] Salle invalide!\n");
        return;
    }

    printf("Date (YYYY-MM-DD): ");
    scanf("%s", r.date);

    printf("Heure debut (HH:MM): ");
    scanf("%s", r.heure_debut);

    printf("Heure fin (HH:MM): ");
    scanf("%s", r.heure_fin);

    printf("Nombre de personnes: ");
    scanf("%d", &r.nombre_personnes);

    // Verifier capacite
    if (r.nombre_personnes > salles[r.salle_id].capacite) {
        printf("[ERREUR] Capacite insuffisante! Max: %d\n", salles[r.salle_id].capacite);
        return;
    }

    // Verifier disponibilite
    if (!verifier_disponibilite(r.salle_id, r.date, r.heure_debut, r.heure_fin)) {
        return;
    }

    // TACHE 3: Calcul automatique du tarif
    float duree = calculer_duree(r.heure_debut, r.heure_fin);
    r.tarif = salles[r.salle_id].tarif_horaire * duree;

    strcpy(r.statut, "CONFIRMEE");
    reservations[nb_reservations++] = r;

    printf("[OK] Reservation creee! ID: %d | Tarif: %.2f Dinars\n", r.id, r.tarif);
}

// ============= TACHE 4: FACTURATION =============

void generer_facture() {
    int id;
    printf("ID reservation: ");
    scanf("%d", &id);

    Reservation *r = NULL;
    for (int i = 0; i < nb_reservations; i++) {
        if (reservations[i].id == id) {
            r = &reservations[i];
            break;
        }
    }

    if (!r || strcmp(r->statut, "ANNULEE") == 0) {
        printf("[ERREUR] Reservation introuvable ou annulee!\n");
        return;
    }

    printf("\n========================================\n");
    printf("           FACTURE #%d\n", r->id);
    printf("========================================\n");
    printf("Client: %s\n", r->nom_client);
    printf("Salle: %s\n", salles[r->salle_id].nom);
    printf("Date: %s\n", r->date);
    printf("Horaire: %s - %s\n", r->heure_debut, r->heure_fin);
    printf("Duree: %.1f heures\n", calculer_duree(r->heure_debut, r->heure_fin));
    printf("Tarif horaire: %.2f Dinars/h\n", salles[r->salle_id].tarif_horaire);
    printf("----------------------------------------\n");
    printf("TOTAL: %.2f Dinars\n", r->tarif);
    printf("========================================\n\n");

    // Sauvegarder dans fichier
    char filename[50];
    sprintf(filename, "facture_%d.txt", r->id);
    FILE *f = fopen(filename, "w");
    if (f) {
        fprintf(f, "FACTURE #%d\n", r->id);
        fprintf(f, "Client: %s\n", r->nom_client);
        fprintf(f, "Salle: %s\n", salles[r->salle_id].nom);
        fprintf(f, "TOTAL: %.2f Dinars\n", r->tarif);
        fclose(f);
        printf("[OK] Facture sauvegardee: %s\n", filename);
    }
}

// ============= TACHE 5: STATISTIQUES =============

void afficher_stats() {
    printf("\n========================================\n");
    printf("            STATISTIQUES\n");
    printf("========================================\n\n");

    // CA par salle
    printf("CHIFFRE D'AFFAIRES PAR SALLE:\n");
    float total_ca = 0;
    for (int i = 0; i < nb_salles; i++) {
        float ca = 0;
        int count = 0;
        for (int j = 0; j < nb_reservations; j++) {
            if (reservations[j].salle_id == i && strcmp(reservations[j].statut, "CONFIRMEE") == 0) {
                ca += reservations[j].tarif;
                count++;
            }
        }
        printf("  %s: %.2f Dinars (%d reservations)\n", salles[i].nom, ca, count);
        total_ca += ca;
    }
    printf("  TOTAL: %.2f Dinars\n\n", total_ca);

    // Reservations par mois
    printf("RESERVATIONS PAR MOIS:\n");
    int mois_count[12] = {0};
    for (int i = 0; i < nb_reservations; i++) {
        if (strcmp(reservations[i].statut, "CONFIRMEE") == 0) {
            int mois = (reservations[i].date[5] - '0') * 10 + (reservations[i].date[6] - '0');
            if (mois >= 1 && mois <= 12) mois_count[mois - 1]++;
        }
    }
    char *mois[] = {"Jan", "Fev", "Mar", "Avr", "Mai", "Jun", "Jul", "Aou", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++) {
        if (mois_count[i] > 0) printf("  %s: %d\n", mois[i], mois_count[i]);
    }

    // Salles populaires
    printf("\nTOP SALLES:\n");
    int usage[MAX_SALLES] = {0};
    for (int i = 0; i < nb_reservations; i++) {
        if (strcmp(reservations[i].statut, "CONFIRMEE") == 0) {
            usage[reservations[i].salle_id]++;
        }
    }
    for (int rank = 1; rank <= 3; rank++) {
        int max_idx = 0, max_val = 0;
        for (int j = 0; j < nb_salles; j++) {
            if (usage[j] > max_val) {
                max_val = usage[j];
                max_idx = j;
            }
        }
        if (max_val > 0) {
            printf("  %d. %s (%d reservations)\n", rank, salles[max_idx].nom, max_val);
            usage[max_idx] = -1;
        }
    }
    printf("\n");
}

// ============= TACHE 6: PERSISTANCE =============

void sauvegarder() {
    FILE *f = fopen("salles.txt", "w");
    if (f) {
        for (int i = 0; i < nb_salles; i++) {
            fprintf(f, "%d;%s;%d;%.2f;%s\n", salles[i].id, salles[i].nom,
                    salles[i].capacite, salles[i].tarif_horaire, salles[i].equipements);
        }
        fclose(f);
    }

    f = fopen("reservations.txt", "w");
    if (f) {
        for (int i = 0; i < nb_reservations; i++) {
            fprintf(f, "%d;%s;%d;%s;%s;%s;%d;%.2f;%s\n",
                    reservations[i].id, reservations[i].nom_client, reservations[i].salle_id,
                    reservations[i].date, reservations[i].heure_debut, reservations[i].heure_fin,
                    reservations[i].nombre_personnes, reservations[i].tarif, reservations[i].statut);
        }
        fclose(f);
    }
    printf("[OK] Donnees sauvegardees!\n");
}

void charger() {
    FILE *f = fopen("salles.txt", "r");
    if (f) {
        while (fscanf(f, "%d;%49[^;];%d;%f;%99[^\n]\n", &salles[nb_salles].id, salles[nb_salles].nom,
                      &salles[nb_salles].capacite, &salles[nb_salles].tarif_horaire,
                      salles[nb_salles].equipements) == 5) {
            nb_salles++;
        }
        fclose(f);
    }

    f = fopen("reservations.txt", "r");
    if (f) {
        while (fscanf(f, "%d;%49[^;];%d;%11[^;];%5[^;];%5[^;];%d;%f;%14[^\n]\n",
                      &reservations[nb_reservations].id, reservations[nb_reservations].nom_client,
                      &reservations[nb_reservations].salle_id, reservations[nb_reservations].date,
                      reservations[nb_reservations].heure_debut, reservations[nb_reservations].heure_fin,
                      &reservations[nb_reservations].nombre_personnes,
                      &reservations[nb_reservations].tarif, reservations[nb_reservations].statut) == 9) {
            nb_reservations++;
        }
        fclose(f);
    }
}

// ============= TACHE 7 BONUS: ANNULATION =============

void annuler_reservation() {
    int id;
    printf("ID a annuler: ");
    scanf("%d", &id);

    for (int i = 0; i < nb_reservations; i++) {
        if (reservations[i].id == id) {
            strcpy(reservations[i].statut, "ANNULEE");
            printf("[OK] Reservation %d annulee!\n", id);
            return;
        }
    }
    printf("[ERREUR] Reservation introuvable!\n");
}

// ============= AUTRES FONCTIONS =============

void afficher_salles() {
    printf("\nSALLES DISPONIBLES:\n");
    for (int i = 0; i < nb_salles; i++) {
        printf("  %d. %s - Capacite: %d - Tarif: %.2f Dinars/h - %s\n",
               i + 1, salles[i].nom, salles[i].capacite,
               salles[i].tarif_horaire, salles[i].equipements);
    }
    printf("\n");
}

void afficher_reservations() {
    printf("\nRESERVATIONS:\n");
    for (int i = 0; i < nb_reservations; i++) {
        printf("  ID:%d | %s | %s | %s-%s | %s | %.2f Dinars | %s\n",
               reservations[i].id, reservations[i].nom_client,
               salles[reservations[i].salle_id].nom, reservations[i].heure_debut,
               reservations[i].heure_fin, reservations[i].date,
               reservations[i].tarif, reservations[i].statut);
    }
    printf("\n");
}

void init_default() {
    strcpy(salles[0].nom, "Salle A");
    salles[0].id = 1; salles[0].capacite = 10;
    salles[0].tarif_horaire = 25.0;
    strcpy(salles[0].equipements, "TV, Projecteur");

    strcpy(salles[1].nom, "Salle B");
    salles[1].id = 2; salles[1].capacite = 20;
    salles[1].tarif_horaire = 35.0;
    strcpy(salles[1].equipements, "TV, Videoconf");

    strcpy(salles[2].nom, "Salle C");
    salles[2].id = 3; salles[2].capacite = 8;
    salles[2].tarif_horaire = 15.0;
    strcpy(salles[2].equipements, "Tableau");

    nb_salles = 3;
}

// ============= MAIN =============

int main() {
    printf("========================================\n");
    printf("  SYSTEME DE RESERVATIONS DE SALLES\n");
    printf("========================================\n\n");

    charger();
    if (nb_salles == 0) {
        init_default();
        printf("[OK] 3 salles creees par defaut\n\n");
    }

    int choix;
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Voir salles\n");
        printf("2. Creer reservation\n");
        printf("3. Voir reservations\n");
        printf("4. Generer facture\n");
        printf("5. Statistiques\n");
        printf("6. Annuler reservation\n");
        printf("0. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: afficher_salles(); break;
            case 2: creer_reservation(); break;
            case 3: afficher_reservations(); break;
            case 4: generer_facture(); break;
            case 5: afficher_stats(); break;
            case 6: annuler_reservation(); break;
            case 0:
                sauvegarder();
                printf("Au revoir!\n");
                return 0;
            default: printf("[ERREUR] Choix invalide!\n");

        }
    }

    return 0;
}