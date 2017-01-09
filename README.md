# Etudiants

- Alexandre BECART
- Aymeric DUCROQUETZ

# LightingControlSystem

Le projet permet de contrôler, de manière précise, la lumière d'une pièce.

Le système de contrôle de la lumière permet de :
- contrôler l'allumage de la lumière
- contrôler et afficher la luminosité de la pièce
- contrôler la couleur de la lumière

Le système propose également 2 interfaces :
- le site Web
- le bouton sur le tableau de bord

## Installation

### Manuelle

Pour installer le projet :

1. Télécharger la chaine de compilation **GNU ARM Embedded Toolchain** à l'adresse suivante : [https://launchpad.net/gcc-arm-embedded/](https://launchpad.net/gcc-arm-embedded/)
2. Placer la chaine de compilation à un endroit désiré et ajouter dans votre fichier `.bashrc`  : `export GNU_ARM_TOOLCHAIN=LOCATION` avec `LOCATION` = l'adresse absolue de votre dossier contenant la chaine de compilation.
3. Ensuite, toujours dans le fichier `.bashrc`, ajouter : `export PATH=$PATH:$GNU_ARM_TOOLCHAIN/gcc-arm-none-eabi-*/bin`. **Attention** : Vous devez préciser la version de la chaine de compilation `gcc-arm-none-eabi-*`.
4. Télécharger et configurer le projet Smews à l'adresse suivante : [https://github.com/2xs/smews](https://github.com/2xs/smews)

### Automatique

Un script d'installation `install.sh` est également à votre disposition. Celui-ci télécharge la chaine de compilation, la librairie RFLPC et Smews.

Par défaut, avec le script, la chaine de compilation se trouve dans le dossier `~/cross-compiler`.

1. Lancer le script `install.sh` à la racine du projet.

```shell
$ ./install.sh
```

### Compilation

Pour compiler le projet et transférer le programme sur la MBED :

```shell
$ make program
```

### Branchement

1. Connecter la MBED sur la MBED SHIELD.
2. Connecter la BASE SHIELD sur la MBED SHIELD.
3. Connecter les composants ci-dessous sur la BASE SHIELD.

|      Composant     | Port |
|:------------------:|:----:|
|         LED        |  D2  |
|       4DIGIT       |  D3  |
|       Bouton       |  D6  |
| Capteur de lumière |  A0  |
