#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
time_t current_time;
struct tm *time_new;
FILE *fptr;
// Function prototypes
void menu();
void afichage();
void supprimer();
void ajouterstatut();
void modifier();
void statistique();
int rechercheid();
void recherchedeadline();
void rechercheidenti();
void ajout();
void recherche_titre();
// struture d'un élément de la liste
typedef struct
{
    int jour;
    int mois;
    int annee;
    int days;
} deadline;
// Structure d'un élément de la liste
typedef struct
{
    int jour;
    int mois;
    int annee;
} date_creation;
// Structure d'un élément de tache
typedef struct
{
    int id;
    char titre[100];
    char description[100];
    deadline dline;
    char statut[100];
    date_creation date_creation;
} taches;

// main function
int main()
{
    // Variables
    taches *tache, t1;
    taches *tache1, tache2;
    int choix, idt = 0, b, taille = 0;
    deadline dline2;
    int ch;
    int day_new;
    time(&current_time);
    time_new = localtime(&current_time);
    day_new = time_new->tm_mday + (time_new->tm_mon + 1) * 30 +
              (time_new->tm_year + 1900) * 365;
    printf("Bienvenue dans votre agenda !\n");
    printf("Choisissez une option :\n");
    //
    do
    {

        menu();
        tache = &t1;
        tache = (taches *)malloc((taille + 1) * sizeof(taches));
        tache1 = &t1;
        printf("Entrez votre choix :");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Ajouter une tache\n");
            tache = &t1 + taille;
            ajout(tache, idt);
            taille++;
            idt++;
            break;
        case 2:
            printf("Entrez le nombre de tache :");
            scanf("%d", &ch);
            for (int i = 0; i < ch; i++)
            {
                tache = &t1 + taille;
                ajout(tache, idt);
                taille++;
                idt++;
            }
            break;

        case 3:
            do
            {
                printf("|=============================================================="
                       "=====|\n");
                printf("|  1-Afficher la liste de toutes les taches                    "
                       "     |\n");
                printf("|  2-Afficher les taches par ordre alphabetique                "
                       "     |\n");
                printf("|  3-Afficher les taches par deadline                          "
                       "     |\n");
                printf("|  4-Afficher les taches dont le deadline est dans 3 jours ou "
                       "moins |\n");
                printf("|  0-Quitter                                                   "
                       "     |\n");
                printf("|=============================================================="
                       "=====|\n");
                printf("Entrez votre choix :");
                scanf("%d", &b);
                switch (b)
                {
                case 1:
                    for (tache = &t1; tache < &t1 + taille; tache++)
                    {
                        afichage(tache);
                    }

                    break;

                case 2:
                    // Afficher la liste de toutes les taches Trier les taches par ordre
                    // alphabetique par titre de tache
                    for (tache = &t1; tache < &t1 + taille; tache++)
                    {
                        for (tache1 = tache + 1; tache1 < &t1 + taille; tache1++)
                        {
                            if (strcmp(tache->titre, tache1->titre) > 0)
                            {
                                tache2 = *tache;
                                *tache = *tache1;
                                *tache1 = tache2;
                            }
                        }
                    }
                    for (tache = &t1; tache < &t1 + taille; tache++)
                    {
                        afichage(tache);
                    }

                    break;
                case 3:
                    // Afficher la liste de toutes les taches Trier les taches par ordre
                    // deadline par jour de tache

                    for (tache = &t1; tache < &t1 + taille; tache++)
                    {
                        for (tache1 = tache + 1; tache1 < &t1 + taille; tache1++)
                        {
                            if (tache->dline.days > tache1->dline.days)
                            {
                                tache2 = *tache;
                                *tache = *tache1;
                                *tache1 = tache2;
                            }
                        }
                    }
                    for (tache = &t1; tache < &t1 + taille; tache++)
                    {
                        afichage(tache);
                    }
                    break;
                case 4:

                    // Afficher les taches dont le deadline est dans 3 jours ou moins
                    for (tache = &t1; tache < &t1 + taille; tache++)
                    {
                        if (tache->dline.days - day_new <= 3 &&
                            tache->dline.days - day_new > 0)
                        {
                            afichage(tache);
                            printf("%d\n", tache->dline.days);
                        }
                    }
                    break;
                case 0:
                    printf("Au revoir !\n");
                    break;

                default:
                    printf("choix incorrect\n");
                    break;
                }
            } while (b != 0);

            break;
        case 4:
            tache = &t1;
            modifier(tache, taille);
            break;
        case 5:
            tache = &t1;
            int b;
            printf("Entrez l'id de la tache a supprimer :");
            scanf("%d", &b);
            if (rechercheid(tache, taille, b) == -1)
            {
                printf("Aucune tache n'a ete trouve.\n");
            }
            else
            {
                supprimer(tache, taille, rechercheid(tache, taille, b));
                taille--;
            }
            break;
        case 6:
            tache = &t1;
            printf("-----------------------------------------------------------------"
                   "\n");
            printf("| [1]Rechercher une tache par son Identifiant                   "
                   "|\n ");
            printf("| [2]Rechercher une tache par son Titre                         "
                   "|\n");
            printf("| [3]Rechercher une tache par son deadline                      "
                   "|\n");
            printf("-----------------------------------------------------------------"
                   "\n");
            printf("Entre votre choix :");
            scanf(" %d", &ch);
            if (ch == 1)
            {
                rechercheidenti(tache, taille);
            }
            else if (ch == 2)
            {
                recherche_titre(tache, taille);
            }
            else if (ch == 3)
            {
                recherchedeadline(tache, taille);
            }
            break;
        case 7:
            tache = &t1;
            statistique(tache, taille, day_new);
            break;
        case 8:
            // Ovrerture du fichier .txt
            fptr = fopen("list_tache.txt", "w");
            // Ecriture des taches dans le fichier .txt
            if (fptr == NULL)
            {
                printf("Erreur d'ouverture du fichier");
            }
            else
            {
                for (tache = &t1; tache < &t1 + taille; tache++)
                {
                    fprintf(
                        fptr,
                        "=========================================================\n");
                    fprintf(fptr, "  id :%d\n", tache->id);
                    fprintf(fptr, "  Titre : %s\n", tache->titre);
                    fprintf(fptr, "  Description: %s\n", tache->description);
                    fprintf(fptr, "  Status   : %s\n", tache->statut);
                    fprintf(fptr, "  Date creation : %d %d %d\n",
                            tache->date_creation.jour, tache->date_creation.mois,
                            tache->date_creation.annee);
                    fprintf(fptr, "  deadline : %d %d %d\n", tache->dline.jour,
                            tache->dline.mois, tache->dline.annee);
                    fprintf(
                        fptr,
                        "=========================================================\n");
                }
                fclose(fptr);
                printf(
                    "Les taches ont ete enregistre dans le fichier list_tache.txt\n");
            }
            break;
        case 0:
            printf("Au revoir !\n");
            break;
        default:
            printf("Erreur \n");
            break;
        }
    } while (choix != 0);
    free(tache);
    return 0;
}
// FancTion Menu
void menu()
{
    printf("---------------Système de Gestion des Taches----------------- \n");
    printf("|   1- Ajouter une nouvelle tache                            | \n");
    printf("|   2- Afficher plusieurs taches                             | \n");
    printf("|   3- Afficher la liste de toutes les taches :              | \n");
    printf("|   4- Modifier une tache:                                   | \n");
    printf("|   5- suprimer une tache par identifiant.                   | \n");
    printf("|   6- Rechercher les Taches :                               | \n");
    printf("|   7- Statistiques :                                        | \n");
    printf("|   8- Exporter les taches dans un fichier .txt              | \n");
    printf("|   0- Quitter                                               | \n");
    printf("-------------------------------------------------------------  \n");
}
// fonction d'afichage
void afichage(taches *tache)
{
    printf("============================================================\n");
    printf("Identifiant :      %d \n", tache->id);
    printf("Titre :            %s \n", tache->titre);
    printf("Description :      %s \n", tache->description);
    printf("Date de creation : %d/%d/%d \n", tache->date_creation.jour,
           tache->date_creation.mois, tache->date_creation.annee);
    printf("Deadline :         %d/%d/%d \n", tache->dline.jour, tache->dline.mois,
           tache->dline.annee);
    printf("Statut :           %s \n", tache->statut);
    printf("============================================================\n");
}

// fonction d'ajout de tache

void ajout(taches *tache, int idt)
{
    tache->id = idt;
    printf("Entrer le titre de la tache : ");
    scanf(" %[^\n]s", tache->titre);
    printf("Entrer la description de la tache : ");
    scanf(" %[^\n]s", tache->description);
    printf("Entrer la date de deadline :\n");
    printf("Entrez le jour de la tache : ");
    scanf("%d", &tache->dline.jour);
    printf("Entrez le mois de la tache : ");
    scanf("%d", &tache->dline.mois);
    printf("Entrez l'annee de la tache : ");
    scanf("%d", &tache->dline.annee);
    tache->dline.days =
        tache->dline.jour + tache->dline.mois * 30 + tache->dline.annee * 365;
    printf("Entrez le statut de la tache : ");
    ajouterstatut(tache);
    // Ajout la date de creation
    tache->date_creation.jour = time_new->tm_mday;
    tache->date_creation.mois = time_new->tm_mon + 1;
    tache->date_creation.annee = time_new->tm_year + 1900;
}

// fonction de recherche d'une tache par son titre
void recherche_titre(taches *tache, int taille)
{
    char titre[100];
    taches *tache1;
    tache1 = tache;
    printf("Entrer le titre de la tache : ");
    scanf(" %[^\n]s", titre);
    for (tache = tache1; tache <= tache1 + taille; tache++)
    {
        if (strcmp(tache->titre, titre) == 0)
        {
            afichage(tache);
        }
    }
}

// fonction recherche d'une tache par son deadline
void recherchedeadline(taches *tache, int taille)
{
    deadline dline2;
    taches *tache1;
    tache1 = tache;
    printf("Entrer le jour de la tache : ");
    scanf("%d", &dline2.jour);
    printf("Entrer le mois de la tache : ");
    scanf("%d", &dline2.mois);
    printf("Entrer l'annee de la tache : ");
    scanf("%d", &dline2.annee);
    for (tache = tache1; tache <= tache1 + taille; tache++)
    {
        if (tache->dline.annee == dline2.annee &&
            tache->dline.jour == dline2.jour && tache->dline.mois == dline2.mois)
        {
            printf("Tache trouve : \n");
            afichage(tache);
        }
    }
}
// fonction de recherche d'une tache par son id
int rechercheid(taches *tache, int taille, int id)
{
    int i = 0;
    taches *tache1;
    tache1 = tache;
    for (tache = tache1; tache <= tache1 + taille; tache++)
    {
        if (tache->id == id)
        {
            return i;
        }
        i++;
    }
    return -1;
}
// recherche tache par identifiant
void rechercheidenti(taches *tache, int taille)
{
    int ID;
    printf("Entrer l'identifiant de la tache : ");
    scanf("%d", &ID);
    for (tache = tache; tache <= tache + taille; tache++)
    {
        if (tache->id == ID)
        {
            printf("Tache trouve : \n");
            afichage(tache);
            break;
        }
    }
}
// fonction de suppression d'une tache
void supprimer(taches *tache, int taille, int b)
{
    taches *tache1;
    tache1 = tache;
    for (tache = tache1 + b; tache <= tache1 + taille; tache++)
    {
        *tache = *(tache + 1);
    }
}
// fonction modifier d'une tache
void modifier(taches *tache, int taille)
{
    char description[100];
    int choix, b, ID;
    printf("Entrer l'identifiant de la tache : ");
    scanf("%d", &ID);
    b = rechercheid(tache, taille, ID);
    if (b == -1)
    {
        printf("Aucune tache n'a ete trouve.\n");
    }
    else
    {
        // choix de la tache a modifier
        printf("=========Que voulez vous modifier ?=========\n");
        printf("--------------------------------------------\n");
        printf("| 1- Modifie le descripion de la tache      |\n");
        printf("| 2- Modifie la statut de la tache          |\n");
        printf("| 3- Modifie la deadline de la tache        |\n");
        printf("|-------------------------------------------|\n");
        tache = tache + b;
        printf("Entrer votre choix : \n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            // Modifie la description de la tache

            printf("Entrer nouveau description : \n");
            scanf(" %[^\n]s", description);
            strcpy(tache->description, description);
            break;
        case 2:
            // Modifie la statut de la tache
            printf("Entrer nouveau statut : \n");
            ajouterstatut(tache);
            break;
        case 3:
            // Modifie la deadline de la tache
            printf("===========Entrer nouvelle deadline ================ \n");
            printf("     Entrez le jour de la tache : ");
            scanf("%d", &tache->dline.jour);
            printf("     Entrez le mois de la tache : ");
            scanf("%d", &tache->dline.mois);
            printf("     Entrez l'annee de la tache : ");
            scanf("%d", &tache->dline.annee);
            tache->dline.days =
                tache->dline.jour + tache->dline.mois * 30 + tache->dline.annee * 365;
            break;
        }
    }
}

// fonction d'ajout d'une statut
void ajouterstatut(taches *tache)
{
    int choix;
    printf("\n1-à realiser\n2-en cours de realisation\n3-finalisee\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        strcpy(tache->statut, "realiser");
        break;
    case 2:
        strcpy(tache->statut, "en cours de realisation");
        break;
    case 3:
        strcpy(tache->statut, "finalisee");
        break;
    }
}

// Fonction d'affichage d'une statistiques
void statistique(taches *tache, int taille, int day_new)
{
    int b, c = 0, d = 0, a;
    taches *tache1;
    tache1 = tache;
    do
    {
        printf("==================================================================="
               "=======\n");
        printf("| 1-Afficher le nombre total des taches.                           "
               "      |\n");
        printf("| 2-Afficher le nombre de taches complètes et incomplètes.         "
               "      |\n");
        printf("| 3-Afficher le nombre de jours restants jusqu'au delai de chaque "
               "tache. |\n");
        printf("| 0-Retour au menu principal.                                      "
               "      |\n");
        printf("==================================================================="
               "=======\n");
        printf("Entrer votre choix : ");
        scanf("%d", &b);
        switch (b)
        {
        case 1:
            // affichage du nombre total des taches
            printf("Le nombre total des taches est : %d\n", taille);
            break;
        case 2:
            // recherche a le nombre de taches complètes et incomplètes
            for (tache = tache1; tache < tache1 + taille; tache++)
            {
                if (strcmp(tache->statut, "finalisee") == 0)
                {
                    c++;
                }
                else
                {
                    d++;
                }
            }
            printf("Le nombre de taches complètes est : %d\n", c);
            printf("Le nombre de taches incomplètes est : %d\n", d);
            break;
        case 3:
            // affichage du nombre de jours restants jusqu'au delai de chaque tache
            for (tache = tache1; tache < tache1 + taille; tache++)
            {
                printf("Tache id : %d\n", tache->id);
                a = tache->dline.days - day_new;
                if (a < 0)
                {
                    printf("Le delai a expire il y a %d jours\n", a * (-1));
                }
                else if (a == 0)
                {
                    printf("Le delai est termine\n");
                }
                else
                {
                    printf("Le delai reste %d jours\n", a);
                }
                printf("---------------------------------------------------\n");
            }
            break;
        }
    } while (b != 0);
}
