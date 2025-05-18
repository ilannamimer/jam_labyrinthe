# MAZE RUNNER: SHIFT CONTROL

## Description
MAZE RUNNER: SHIFT CONTROL est un jeu de labyrinthe développé en C++ avec la bibliothèque SFML. 
Le joueur doit naviguer à travers différents labyrinthes en utilisant les touches directionnelles pour atteindre la sortie.
Le jeu propose plusieurs niveaux de difficulté, des paramètres configurables et une bande sonore.

## Prérequis
- Compilateur C++
- SFML 2.5.0 ou supérieur
- Make

## Installation

### Installation des dépendances

#### Sur Debian/Ubuntu
```bash
sudo apt-get update
sudo apt-get install libsfml-dev g++ make
```

#### Sur Fedora
```bash
sudo dnf install SFML-devel gcc-c++ make
```

#### Sur macOS (avec Homebrew)
```bash
brew install sfml
```

### Compilation du jeu
1. Clonez ou téléchargez le dépôt
2. Naviguez vers le répertoire du projet
3. Compilez avec Make:
```bash
make
```

## Exécution du jeu

### Mode standard
```bash
./maze
```

### Mode avec carte personnalisée
```bash
./maze map/map_easy.txt
```

## Commandes du jeu
- **Flèches directionnelles** : Déplacer le personnage (haut, bas, gauche, droite)
- **Échap** : Revenir au menu principal depuis le jeu ou les paramètres
- **Souris** : Navigation dans les menus et ajustement du volume

## Niveaux disponibles
Le jeu propose plusieurs niveaux de difficulté, accessibles via le paramètre de ligne de commande:
- `map_easy.txt` : Niveau facile, idéal pour débuter
- `map_medium.txt` : Niveau intermédiaire
- `map_normal.txt` : Niveau standard
- `map_hard.txt` : Niveau difficile avec un labyrinthe plus complexe
- `map_impossible.txt` : Niveau expert très difficile
- `test1.txt` : Niveau de test

## Structure du projet

### Dossiers principaux

#### `/assets`
Contient toutes les ressources graphiques et audio du jeu:

- **`/assets/font`** : Polices utilisées dans le jeu
  - `arial.ttf` : Police principale

- **`/assets/menu`** : Images pour l'interface utilisateur
  - `menu.png` : Arrière-plan du menu principal
  - `settings.png` : Arrière-plan du menu des paramètres
  - `start.png`, `exit.png`, `setting_button.png` : Boutons du menu
  - `1920x1080button.png`, `950x540button.png` : Boutons de résolution

- **`/assets/player`** : Ressources pour le joueur et les éléments du labyrinthe
  - `player.png` : Sprite du joueur
  - `enter.jpg`, `path.jpg`, `wall.jpg` : Textures du labyrinthe
  - `/perso/` : Animations du personnage dans différentes directions
    - `perso_avant1.png`, `perso_avant2.png` : Animation vers l'avant
    - `perso_droite1.png`, `perso_droite2.png`, `perso_droite3.png` : Animation vers la droite
    - `perso_gauche1.png`, `perso_gauche2.png`, `perso_gauche3.png` : Animation vers la gauche

- **`/assets/song`** : Fichiers audio
  - `menu_song.ogg` : Musique du menu
  - `game_song.ogg` : Musique du jeu

#### `/map`
Contient les fichiers de définition des labyrinthes:
- Le format utilise les caractères suivants:
  - `#` : Mur
  - `E` : Entrée (position de départ)
  - `S` : Sortie
  - Espace : Chemin vide

#### `/src`
Contient tous les fichiers source du jeu:

- **Structure principale**:
  - `main.cpp` : Point d'entrée du programme
  - `game_context.hpp/cpp` : Gestion du contexte global du jeu
  - `game_state.hpp` : Définition des états du jeu (MENU, GAME, SETTINGS, QUIT_GAME)

- **Modules du jeu**:
  - `maze.hpp/cpp` : Logique du labyrinthe et du personnage
  - `menu.hpp/cpp` : Interface du menu principal
  - `settings.hpp/cpp` : Paramètres du jeu (résolution, volume)
  - `resolution.hpp/cpp` : Gestion des résolutions d'écran

### Makefile
Le projet utilise un Makefile avec plusieurs commandes utiles:
- `make` : Compile le jeu
- `make run` : Exécute le jeu
- `make run_test` : Exécute le jeu avec la carte de test
- `make debug` : Compile avec les symboles de débogage
- `make clean` : Supprime les fichiers objets
- `make fclean` : Effectue un nettoyage complet
- `make re` : Recompile entièrement le projet
- `make valgrind` : Lance le jeu avec Valgrind pour vérifier les fuites mémoire
- `make help` : Affiche l'aide du Makefile

## Fonctionnalités
- Menu principal interactif
- Système de paramètres (résolution, volume)
- Plusieurs niveaux de difficulté
- Chargement de cartes personnalisées
- Musique d'ambiance
- Adaptation automatique à différentes résolutions d'écran

## Crédits
Développé par Deniz Demir et Ilann Amimer dans le cadre d'une GameJAM organisée par Epitech.
Le défi consistait à créer un jeu en seulement 2 jours sur le thème "Hors de Contrôle".

## Licence
Ce jeu est distribué sous licence libre.
