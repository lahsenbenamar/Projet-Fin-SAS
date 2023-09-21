#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
time_t current_time;
struct tm *time_new;
FILE *fptr;
void menu();
void afichage();
void supprimer();
void ajouterstatut();
void modifier();
void statistique();
int recherchedline();
int rechercheid();
void recherchedeadline();
void rechercheidenti();
void ajout();
void recherche();
typedef struct {
  int jour;
  int mois;
  int annee;
  int days;
} deadline;
typedef struct {
  int jour;
  int mois;
  int annee;
} date_creation;
typedef struct {
  int id;
  char titre[100];
  char description[100];
  deadline dline;
  char statut[100];
  date_creation date_creation;
} taches;
int main() {
  taches *tache, t1;
  taches *tache1, tache2;

  int n, idt = 0, b, t = 0;
  deadline dline2;
  int ch;
  int day_new;

  time(&current_time);
  time_new = localtime(&current_time);
  day_new = time_new->tm_mday + (time_new->tm_mon + 1) * 30 +
            (time_new->tm_year + 1900) * 365;
  printf("Bienvenue dans votre agenda !\n");
  printf("Choisissez une option :\n");
  do {

    menu();
    tache = &t1;
    tache = (taches *)malloc((t + 1) * sizeof(taches));
    tache1 = &t1;
    printf("Entrez votre choix :");
    scanf("%d", &n);
    switch (n) {
    case 1:

      printf("entrez le nombre de tache :");
      scanf("%d", &ch);
      for (int i = 0; i < ch; i++) {
        tache = &t1 + t;
        ajout(tache, idt);
        t++;
        idt++;
      }
      break;

    case 2:
      do {
        printf("|=============================================================="
               "=====|\n");
        printf("|  1-Afficher la liste de toutes les tâches                    "
               "     |\n");
        printf("|  2-Afficher les tâches par ordre alphabétique                "
               "     |\n");
        printf("|  3-Afficher les tâches par deadline                          "
               "     |\n");
        printf("|  4-Afficher les tâches dont le deadline est dans 3 jours ou "
               "moins |\n");
        printf("|  0-Quitter                                                   "
               "     |\n");
        printf("|=============================================================="
               "=====|\n");
        printf("Entrez votre choix :");
        scanf("%d", &b);
        switch (b) {
        case 1:
          for (tache = &t1; tache < &t1 + t; tache++) {
            afichage(tache);
          }

          break;

        case 2:
          // Afficher la liste de toutes les tâches Trier les tâches par ordre
          // alphabétique par titre de tâche
          for (tache = &t1; tache < &t1 + t; tache++) {
            for (tache1 = tache + 1; tache1 < &t1 + t; tache1++) {
              if (strcmp(tache->titre, tache1->titre) > 0) {
                tache2 = *tache;
                *tache = *tache1;
                *tache1 = tache2;
              }
            }
          }
          for (tache = &t1; tache < &t1 + t; tache++) {
            afichage(tache);
          }

          break;
        case 3:
          // Afficher la liste de toutes les tâches Trier les tâches par ordre
          // deadline par jour de tâche

          for (tache = &t1; tache < &t1 + t; tache++) {
            for (tache1 = tache + 1; tache1 < &t1 + t; tache1++) {
              if (tache->dline.days > tache1->dline.days) {
                tache2 = *tache;
                *tache = *tache1;
                *tache1 = tache2;
              }
            }
          }
          for (tache = &t1; tache < &t1 + t; tache++) {
            afichage(tache);
          }
          break;
        case 4:

          // Afficher les tâches dont le deadline est dans 3 jours ou moins
          for (tache = &t1; tache < &t1 + t; tache++) {
            if (tache->dline.days - day_new <= 3 &&
                tache->dline.days - day_new >= 0) {
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
    case 3:
      tache = &t1;
      modifier(tache, t);
      break;
    case 4:
      tache = &t1;
      int b;
      printf("Entrez l'id de la tache a supprimer :");
      scanf("%d", &b);
      if (rechercheid(tache, t, b) == -1) {
        printf("Aucune tâche n'a été trouvé.\n");

      } else {
        supprimer(tache, t, rechercheid(tache, t, b));
        t--;
      }
      break;
    case 5:
      printf(
          "[1]Rechercher une tâche par son Identifiant \n [2]Rechercher une "
          "tâche par son Titre\n [3]Rechercher une tâche par son deadline \n");
      printf("Entre votre choix :");
      scanf(" %d", &ch);
      if (ch == 1) {
        tache = &t1;
        rechercheidenti(tache, t);
      } else if (ch == 2) {
        tache = &t1;
        recherche(tache, t);
      } else if (ch == 3) {
        tache = &t1;
        recherchedeadline(tache, t);
      }
      break;
    case 6:
      statistique(tache, t, day_new);
      break;
    case 7:
      fptr = fopen("filename.txt", "w");

      for (tache = &t1; tache < &t1 + t; tache++) {
        fprintf(fptr, "id :%d\n", tache->id);
        fprintf(fptr, "Titre : %s\n", tache->titre);
        fprintf(fptr, "Description: %s\n", tache->description);
        fprintf(fptr, "Status   : %s\n", tache->statut);
        fprintf(fptr, "Date creation : %d %d %d\n", tache->date_creation.jour,
                tache->date_creation.mois, tache->date_creation.annee);
        fprintf(fptr, "deadline : %d %d %d\n", tache->dline.jour,
                tache->dline.mois, tache->dline.annee);
      }
      fclose(fptr);
      break;

    case 0:
      printf("Au revoir !\n");
      break;
    default:
      printf("Erreur \n");
      break;
    }
  } while (n != 0);
  return 0;
}
void menu() {
  printf("---------------Système de Gestion des Tâches----------------- \n");
  printf("|   1- Ajouter une nouvelle tâche                            | \n");
  printf("|   2- Afficher la liste de toutes les tâches :              | \n");
  printf("|   6- Modifier une tâche:                                   | \n");
  printf("|   7- suprimer une tâche par identifiant.                   | \n");
  printf("|   8- Rechercher les Tâches :                               | \n");
  printf("|   9- Statistiques :                                        | \n");
  printf("|   10- Quitter                                              | \n");
  printf("-------------------------------------------------------------  \n");
}
// fonction d'afichage
void afichage(taches *tache) {
  printf("============================================================\n");
  printf("Identifiant :   %d \n", tache->id);
  printf("Titre :         %s \n", tache->titre);
  printf("Description :   %s \n", tache->description);
  printf("Deadline :      %d/%d/%d \n", tache->dline.jour, tache->dline.mois,
         tache->dline.annee);
  printf("Statut :        %s \n", tache->statut);
  printf("============================================================\n");
}

// fonction d'ajout de tâche

void ajout(taches *tache, int idt) {
  tache->id = idt;
  printf("Entrer le titre de la tache : ");
  scanf(" %[^\n]s", tache->titre);
  printf("Entrer la description de la tache : ");
  scanf(" %[^\n]s", tache->description);
  printf("Entrer la date de deadline : ");
  printf("Entrez le jour de la tâche : ");
  scanf("%d", &tache->dline.jour);
  printf("Entrez le mois de la tâche : ");
  scanf("%d", &tache->dline.mois);
  printf("Entrez l'année de la tâche : ");
  scanf("%d", &tache->dline.annee);
  tache->dline.days =
      tache->dline.jour + tache->dline.mois * 30 + tache->dline.annee * 365;
  printf("Entrez le statut de la tâche : ");
  int b;
  printf("1-à réaliser\n 2-en cours de réalisation\n3-finalisée\n");
  scanf("%d", &b);
  switch (b) {
  case 1:
    strcpy(tache->statut, "realiser");
    break;
  case 2:
    strcpy(tache->statut, "en cours de réalisation");
    break;
  case 3:
    strcpy(tache->statut, "finalisée");
    break;
  }
}

// fonction de recherche d'une tâche par son titre
void recherche(taches *tache, int t) {
  char titre[100];
  taches *tache1;
  tache1 = tache;
  printf("Entrer le titre de la tache : ");
  scanf(" %[^\n]s", titre);
  for (tache = tache1; tache <= tache1 + t; tache++) {
    if (strcmp(tache->titre, titre) == 0) {
      afichage(tache);
    }
  }
}

// fonction recherche d'une tâche par son deadline
int recherchedline(taches *tache, int t, deadline dline2) {
  int i = 0;
  taches *tache1;
  tache1 = tache;
  for (tache = tache1; tache <= tache1 + t; tache++) {
    if (tache->dline.annee == dline2.annee &&
        tache->dline.jour == dline2.jour && tache->dline.mois == dline2.mois) {
      return i;
    }
    i++;
  }
  return -1;
}

void recherchedeadline(taches *tache, int t) {
  deadline dline2;
  taches *tache1;
  tache1 = tache;
  printf("Entrer le jour de la tâche : ");
  scanf("%d", &dline2.jour);
  printf("Entrer le mois de la tâche : ");
  scanf("%d", &dline2.mois);
  printf("Entrer l'année de la tâche : ");
  scanf("%d", &dline2.annee);
  for (tache = tache1; tache <= tache1 + t; tache++) {
    if (tache->dline.annee == dline2.annee &&
        tache->dline.jour == dline2.jour && tache->dline.mois == dline2.mois) {
      printf("Tâche trouvé : \n");
      afichage(tache);
    }
  }
}
// fonction de recherche d'une tâche par son id
int rechercheid(taches *tache, int t, int id) {
  int i = 0;
  taches *tache1;
  tache1 = tache;
  for (tache = tache1; tache <= tache1 + t; tache++) {
    if (tache->id == id) {
      return i;
    }
    i++;
  }
  return -1;
}

// fonction de suppression d'une tâche
void supprimer(taches *tache, int t, int b) {
  taches *tache1;
  tache1 = tache;
  for (tache = tache1 + b; tache <= tache1 + t; tache++) {
    *tache = *(tache + 1);
  }
}
// fonction modifier d'une tâche
void modifier(taches *tache, int t) {
  deadline dline2;
  taches tache1;
  int a, b, c;
  printf("Entrer l'identifiant de la tache : ");
  scanf("%d", &c);
  b = rechercheid(tache, t, c);
  if (b < 0 || b > t) {
    printf("Aucune tâche n'a été trouvé.\n");

  } else {
    printf("1- Modifié le descripion de la tache\n");
    printf("2- Modifié la statut de la tache\n");
    printf("3- Modifié la deadline de la tache\n");
    tache = tache + b;
    printf("Entrer votre choix : \n");
    scanf("%d", &a);
    switch (a) {
    case 1:
      printf("Entrer nouveau description : \n");
      scanf(" %[^\n]s", tache1.description);
      strcpy(tache->description, tache1.description);
      break;
    case 2:
      printf("Entrer nouvelle status : \n");
      ajouterstatut(tache);
      break;
    case 3:
      printf("Entrer nouvelle deadline : \n");
      printf("Entrez le jour de la tâche : ");
      scanf("%d", &tache->dline.jour);
      printf("Entrez le mois de la tâche : ");
      scanf("%d", &tache->dline.mois);
      printf("Entrez l'année de la tâche : ");
      scanf("%d", &tache->dline.annee);
      tache->dline.days =
          tache->dline.jour + tache->dline.mois * 30 + tache->dline.annee * 365;
      break;
    }
  }
}

// fonction d'ajout d'une statut
void ajouterstatut(taches *tache) {
  int b;
  printf("1-à réaliser\n2-en cours de réalisation\n3-finalisée\n");
  scanf("%d", &b);
  switch (b) {
  case 1:
    strcpy(tache->statut, "realiser");
    break;
  case 2:
    strcpy(tache->statut, "en cours de réalisation");
    break;
  case 3:
    strcpy(tache->statut, "finalisée");
    break;
  }
}
// recherche tâche par identifiant
void rechercheidenti(taches *tache, int t) {
  int b;
  printf("Entrer l'identifiant de la tâche : ");
  scanf("%d", &b);
  for (tache = tache; tache <= tache + t; tache++) {
    if (tache->id == b) {
      printf("Tâche trouvé : \n");
      afichage(tache);
      break;
    }
  }
}
// Fonction d'affichage d'une statistiques
void statistique(taches *tache, int t, int day_new) {
  int b, c = 0, d = 0, a;
  taches *tache1;
  tache1 = tache;

  printf("1-Afficher le nombre total des tâches.\n2-Afficher le nombre de "
         "tâches complètes et incomplètes.\n3-Afficher le nombre de jours "
         "restants jusqu'au délai de chaque tâche.\n");
  printf("Entrer votre choix : ");
  scanf("%d", &b);
  switch (b) {
  case 1:
    printf("Le nombre total des tâches est : %d\n", t);
    break;
  case 2:
    for (tache = tache1; tache < tache1 + t; tache++) {
      if (strcmp(tache->statut, "finalisée") == 0) {
        c++;
      } else {
        d++;
      }
    }
    printf("Le nombre de tâches complètes est : %d\n", c);
    printf("Le nombre de tâches incomplètes est : %d\n", d);
    break;
  case 3:

    printf(
        "Le nombre de jours restants jusqu'au délai de chaque tâche est : \n");
    for (tache = tache1; tache < tache1 + t; tache++) {
      printf("Tâche : %d\n", tache->id);
      a = tache->dline.days - day_new;
      if (a < 0) {
        printf("Le délai a expiré il y a %d jours\n", a);
      } else if (a == 0) {
        printf("Le délai est terminé\n");
      } else {
        printf("Le délai reste %d jours\n", a);
      }
      printf("---------------------------------------------------\n");
    }
    break;
  }
}
