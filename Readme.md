# Voyageur de commerce
Ce programme est un solveur du probleme du voyageur de commerce
## utilisation:
### configuration
le programme prends en arguments un fichier constitué des coordonnées des différents points de passage, chaques lignes représente un point et est constituée des différents composant du point separés d'un espace. La dimension dans laquelle seront effectués les calculs est la dimension du point avec la plus grande dimension, si certains points ont une dimension supérieure à d'autres alors la plus grande dimension sera conservé et les points avec les plus petites dimensions verront leurs coordonnées completées par des 0 pour les dimensions manquantes.
### compilation
pour compiler le programme, il suffit d'executer la commande make dans le dossier du projet.
### execution
le programme prends en argument le chemin vers le fichier de configuration, l'option "-d" peut etre indiquée pour deboguer 

## a faire:
* regler le bug qui provoque une difference entre la longueur du chemin calculé et la valeur de retour de l algorithme
* utiliser getopt pour gerer les options et pouvoir manipuler plus simplement le programme

* ajouter plus d algorithmes...
