# UTComputer
Scientific calculator

__TODO :__

  1. A partir du TD sur la calculette, implémenter l'opérateur NEG
  
  2. A partir du TD sur Qt:
  
      2.1.Dans sa vue principale:  
          &nbsp;&nbsp;&nbsp;&nbsp;* Affichage de l’état du calculateur (état de la pile(!), message pour l’utilisateur)  
          &nbsp;&nbsp;&nbsp;&nbsp;* Barre de commande affichant la suite d’opérandes en train d’être saisie   
          &nbsp;&nbsp;&nbsp;&nbsp;* Clavier cliquable à la souris comprenant un pavé numérique et les opérateurs les plus utilisés  
          &nbsp;&nbsp;&nbsp;&nbsp;* Les X derniers éléments de la pile sont affichés (où X est paramétrable dans l’application).  
          &nbsp;&nbsp;&nbsp;&nbsp;* Le calculateur peut être utilisé à la souris ou directement en utilisant le clavier.  
          &nbsp;&nbsp;&nbsp;&nbsp;* L’affichage ou non du clavier cliquable est une option paramétrable par l’utilisateur.  
          &nbsp;&nbsp;&nbsp;&nbsp;* L’affichage d’un nouveau message destiné à l’utilisateur peut s’accompagner d’un bip sonore qui peut être     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;désactivé par l’utilisateur.  

      2.2. Une vue secondaire de l’application sera dédiée à la gestion et l’édition des variables stockées dans l’application. 
      
      2.3. Une vue secondaire de l’application sera dédiée à la gestion et l’édition des (mini-)programmes utilisateurs  
            stockés dans l’application.  
          
      2.4. Une vue secondaire de l’application sera dédiée à l’édition des paramètres du calculateur.
      
  3. Différents types de littérales
  
    3.1. Littérale entière.

    3.2. Littérale rationnelle (automatiquement simplifiée, peut s’obtenir en faisant une division entre deux littérales entières).
    
    3.3. Littérale réelle. 
    
    3.4. Littérale complexe (peut s’obtenir en appliquant l’opérateur binaire $ sur deux littérales)
    
    3.5. Littérale atome. Suite de caractères, identificateur d’une variable, d’un programme ou au nom d’un opérateur.
    
    3.6. Littérale expression. Suite de caractères entre guillemets, composée de littérales séparées par
        des opérateurs numériques.    
    3.7. Littérale programme. Suite d’opérandes entourés de [].
    
  4. Évaluation d’une ligne d’opérandes
    4.1. L’utilisateur entre une suite d’opérandes séparés par des espaces.

    4.2 Tant qu’elle n’est pas évaluée, cette suite peut être rectifiée avec la touche BACKSPACE
    
    4.3. Quand une ligne d’opérandes est évaluée directement, pas nécessaire d'utiliser l'espace anvant.
    
    4.4. Les opérandes sont traitées une par une, de la gauche vers la droite.
    
    4.5. Le traitement d’une littérale "normale" provoque l’empilement.
    4.6. Le traitement d’une littérale atome dépend des cas :
        – si elle correspond à une variable, empilement de la littérale associée cette variable;
        – si elle correspond à un programme, évaluation du programme associé (exécution du programme);
        – sinon, provoque la création d’une nouvelle littérale expression avec la valeur de l’atome entre guillemets.
    4.7. Le traitement d’un opérateur n-aire provoque le dépilement des n dernières littérales de la pile avec lesquelles
sera effectuée l’opération. L’opération est effectué sur ces littérales. Le résultat de l’opération (s’il y en a un)
est empilé. Si la pile ne contient pas assez de littérales pour exécuter un opérateur, la pile est laissée intacte
et un message prévient de la non-validité de l’opération.
Si, lors de son traitement, une opérande n’est pas correcte syntaxiquement, elle est laissée sur la ligne de commande
en attente d’une correction de l’utilisateur et un message d’erreur adéquat prévient l’utilisateur. On remarque
qu’une littérale expression ou une littérale programme n’est pas évaluée automatiquement; elle est simplement
empilée sur la pile.

