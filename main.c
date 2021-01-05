#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //use terminal codage
#include <math.h> //sqart()
#include <wchar.h> // Header file containing wprintf function
#include <string.h> //use by strcpy()

#define TAILLE_MAX 1000
typedef struct key_value key_value;



struct key_value{
  wchar_t letters[1500];
  int nb_occurance[1500];
};

int check_letter_exist(wchar_t letter_to_check, wchar_t chaine[]){
  int position_in_chaine = 0;

  while (position_in_chaine < 1500) {

    // if find the letter in the char array
    if (letter_to_check == chaine[position_in_chaine]) {
      return position_in_chaine;
      break;
    }

    position_in_chaine ++;
    }
    return -1;

}

void table_occurance(wchar_t chaine[], int longueur, key_value *table_occurance_chaine){

  //key_value table_occurance_chaine;

  int position_in_chaine = 0;
  int array_position = 0;

  while (table_occurance_chaine->letters[array_position] != '\0') {
    array_position++;
  }


  while (chaine[position_in_chaine] != '\0')
  {
    // if not exist
    if (check_letter_exist(chaine[position_in_chaine], table_occurance_chaine->letters) == -1 && chaine[position_in_chaine] != '\n' && chaine[position_in_chaine] != ' ') {
      table_occurance_chaine->letters[array_position] = chaine[position_in_chaine];
      table_occurance_chaine->nb_occurance[array_position] = 1;
      array_position += 1;
    }
    // if exist
    else{
      table_occurance_chaine->nb_occurance[check_letter_exist(chaine[position_in_chaine], table_occurance_chaine->letters)] += 1;
      }

    position_in_chaine ++;

  }

  table_occurance_chaine->letters[array_position] = '\0';
  table_occurance_chaine->nb_occurance[array_position] = '\0';
  }

void *table_frequence(int table_occurance[], double table_frequence[]){
  int total_letters_in_array = 0;
  int i = 0;
  //static double table_frequence[1500] = {0};


  while (table_occurance[i] != '\0') {
    total_letters_in_array += table_occurance[i];
    i++;
  }

  i = 0;
  while (table_occurance[i] != '\0') {
    table_frequence[i] = (double) table_occurance[i] / (double) total_letters_in_array;
    //wprintf(L"%d / %d = %f\n", table_occurance[i], total_letters_in_array, table_frequence[i]);
    i++;
  }

  table_frequence[i] = '\0';

}

void afficher_la_table(key_value *table_occurance, double *table_frequence) {
  int i = 0;
  while (table_occurance->letters[i] != '\0') {
    wprintf(L"%C ---> %d --> %f\n", table_occurance->letters[i], table_occurance->nb_occurance[i], table_frequence[i]);
    i++;
  }
}

void somme_table_frequence(double *table_frequence){
  double somme =0;

  for (int i = 0; table_frequence[i] != '\0'; i++) {
    somme += table_frequence[i];
  }
  wprintf(L"%f\n", somme);

}

double square(double x){
  return x*x;
}

double calcul_distance(wchar_t occurance_langue_inconnue[], wchar_t occurance_langue_connue[],
  double *arrayOfFraquencyInconnue, double *arrayOfFraquencyConnue){
  double resultat = 0;

  for (int i = 0; occurance_langue_inconnue[i] != '\0'; i++) {

    //si la lettre de la langue inconnue existe dans la langue connue
    if (check_letter_exist(occurance_langue_inconnue[i], occurance_langue_connue) >= 0) {
      //wprintf(L"%f - %f\n", arrayOfFraquencyInconnue[i], arrayOfFraquencyConnue[check_letter_exist(occurance_langue_inconnue[i], occurance_langue_connue)]);
      resultat += square(arrayOfFraquencyInconnue[i] - arrayOfFraquencyConnue[check_letter_exist(occurance_langue_inconnue[i], occurance_langue_connue)]);
    }
    else{
      //wprintf(L"%f - 0\n", arrayOfFraquencyInconnue[i]);
      resultat += square(arrayOfFraquencyInconnue[i]);
    }

  }

  return sqrt(resultat);
}


key_value table_occurance_langue_connue(char file_name[]) {
  key_value occurance_langue_connue;

  //initialiser tous les case de la table "occurance_langue_connue" a zero
  for (size_t i = 0; i < 1500; i++) {
    occurance_langue_connue.letters[i] = 0;
    occurance_langue_connue.nb_occurance[i] = 0;
  }

  char *locale = setlocale(LC_ALL, "");

  FILE *fp = fopen(file_name,"r");
  wchar_t chaine[TAILLE_MAX] = L"";

  // exit if could not open file
  if (fp == NULL){
    exit(1);
  }

  while (fgetws(chaine, TAILLE_MAX, fp) != NULL) {
    table_occurance(chaine, 50, &occurance_langue_connue);
    }

  fclose(fp);

  return occurance_langue_connue;
}

wchar_t *chaine_from_file(char path[]) {
  static wchar_t text_from_file[100000] = {0};

  char *locale = setlocale(LC_ALL, "");

  FILE *fp = fopen(path,"r");
  wchar_t chaine[TAILLE_MAX] = L"";

  // exit if could not open file
  if (fp == NULL){
    exit(1);
  }

  while (fgetws(chaine, TAILLE_MAX, fp) != NULL) {
    wcscat(text_from_file, chaine);
    }

  fclose(fp);

  return text_from_file;
}




int main(){

  //get unknown language from user
  wprintf(L"Enter your text : ");
  wchar_t user_text[10000] = L"";
  fgetws (user_text , 10000 , stdin);

  //chemin des fichiers de la langue
  char directory_name[32][30] = {
      "langues/ancient_greek",
      "langues/arabic",
      "langues/bulgarian",
      "langues/catalan",
      "langues/chinese",
      "langues/czech",
      "langues/danish",
      "langues/dutch",
      "langues/english",
      "langues/esperanto",
      "langues/farsi",
      "langues/finnish",
      "langues/french",
      "langues/german",
      "langues/hebrew",
      "langues/hungarian",
      "langues/icelandic",
      "langues/italian",
      "langues/japanese",
      "langues/korean",
      "langues/latin",
      "langues/modern_greek",
      "langues/norwegian",
      "langues/polish",
      "langues/portuguese",
      "langues/russian",
      "langues/spanish",
      "langues/swedish",
      "langues/tagalog",
      "langues/turkish",
      "langues/urdu",
      "\0"
  };


  key_value occurance_langue_inconnue;

  //initialiser tous les case de la table d'occurance de la langue inconnue a zero
  for (size_t i = 0; i < 1500; i++) {
    occurance_langue_inconnue.letters[i] = 0;
    occurance_langue_inconnue.nb_occurance[i] = 0;
  }

  //table d'occurance et frequence de la langue inconnue
  table_occurance(user_text, 50, &occurance_langue_inconnue);
  double arrayOfFraquencyInconnue[1500] = {0} ;
  table_frequence(occurance_langue_inconnue.nb_occurance, arrayOfFraquencyInconnue);


  double petit_distance = 10000;
  char nom_de_petit_distance[30] = {0};

  //calculer la table de frequence des langues
  for (int i = 0; i < 31; i++) {
    key_value occurance_langue_connue;
    double arrayOfFraquencyConnue[1500];

    //initialiser la table d'occurance cree precedement
    for (size_t i = 0; i < 1500; i++) {
      occurance_langue_connue.letters[i] = 0;
      occurance_langue_connue.nb_occurance[i] = 0;
      arrayOfFraquencyConnue[i] = 0;
    }

    occurance_langue_connue = table_occurance_langue_connue(directory_name[i]);
    table_frequence(occurance_langue_connue.nb_occurance, arrayOfFraquencyConnue);


    double distance = calcul_distance(occurance_langue_inconnue.letters,
      occurance_langue_connue.letters, arrayOfFraquencyInconnue, arrayOfFraquencyConnue);

    if (distance < petit_distance) {
      petit_distance = distance;
      strcpy(nom_de_petit_distance, directory_name[i]);
    }

  }

  //show the result in terminal
  wprintf(L"%s\n", nom_de_petit_distance);

  return EXIT_SUCCESS;



}
