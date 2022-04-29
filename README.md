# Atari Tempest

Implémentation du jeu Atari Tempest en C++ moderne avec la SDL2 comme libraire graphique.
Cette version n'est disponible que sur Linux.


## Compilation du projet

La compilation du projet se fait grâce à CMake. Afin de faciliter l'étape de compilation, un Makefile est fourni à la racine du projet.

- Pour compiler le jeu:
```
$ make
```
Ou manuellement:
```
$ mkdir build
$ cd build
$ cmake ..
$ make -j 8
$ cp tempest ..
```

## Lancement du jeu

Avant de lancer le jeu, il faut s'assurer que le dossier `data/` est présent au même niveau que le binaire et contient bien tous les fichiers nécessaires au lancement du jeu. C'est-à-dire les informations des niveaux, `level_data.txt`, et des couleurs utilisées, `color_data.txt`. 

Si la condition ci-dessus est respectée, alors il suffit de lancer le jeu depuis la ligne de commande. 
```
$ ./tempest
```
## Commandes

Pour naviguer dans la sélection de niveau, il suffit d'utiliser les flèches directionnelles du clavier afin d'accéder aux 80 niveaux disponibles.

Les touches ainsi que leurs actions spécifiques à chaque scène sont précisés dans ceux-ci.

En appuyant sur la touche `q`, il est possible de quitter complètement le jeu, depuis **n'importe quelle scène**. 

Un menu de debug est disponible, afin de présenter diverses informations au joueur. Pour y accéder il suffit d'appuyer sur la touche `d` depuis n'importe quelle scène.

## Auteurs
- Massimo Venuti
- Tarek Kunze