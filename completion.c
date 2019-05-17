#include "cimp.h"

int nb_completions;
char **completions;

/* fonction qui engendre les completions possibles :
   a  chaque num >= 0 correspond une completion;
   la fin de la liste des completions est donnee par NULL
   
   ici on compla¨te si c'est un prefixe de "toto" ou de "turlututu",
   sinon c'est la completion par defaut */
char *command_generator (const char *com, int num){
  /* a  l'entree de cette fonction : com est le debut deja  ecrit de la commande,
     on est en train de chercher la completion numero num */
  static int indice, len;
  char *completion;

  /* si c'est la premia¨re completion qu'on cherche, on dit qu'on va chercher a  partir
     de la premiere case du tableau completion et on garde en memoire la longueur
     du texte tape */
  if (num == 0){
    indice = 0;
    len = strlen(com);
  }

  /* on renvoie une completion de prefixe le debut de la commande ecrite */
  while (indice < nb_completions)
    {
      completion = completions[indice++];

      if (strncmp (completion, com, len) == 0)
  return strdup(completion);
    }
  
  /* est renvoye quand num est > au numero de la dernia¨re completion
     automatique */
  return NULL;
}

/* com : tout ce que l'utilisateur a deja  ecrit sur la ligne de commande
   start, end : les indices de debut et de fin du mot sur lequel TAB a ete lance */
char ** fileman_completion (const char *com, int start, int end){
  char **matches;

  matches = (char **)NULL; /* assure la completion par defaut */

  /* si c'est le premier mot de la ligne de commande, on l'analyse;
     sinon on utilise l'analyse par defaut */
  if (start == 0)
    matches = rl_completion_matches (com, command_generator);

  return (matches);
}


//ajout dans la fonction de base de l'initialisation du tableau de completion
int initialize_readline(char **env1){
  rl_readline_name = "cimp";
  
  /* explicite la completion souhaitee */
  rl_attempted_completion_function = fileman_completion;
  return 0;
}