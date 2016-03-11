## Application de dessin de triangles

Dans le cadre des tps du cours d'IHM de la L3 Informatique j'ai été amené à réaliser une interface en graphique en utilisant wxWidget. 

## Utilisation

Testé sous l'environnement Ubuntu 15.04.

Compilation : make

Exécution : ./drawtri

Pré-requis :

* g++

* opengl

## Problèmes rencontrés

* Lors de l'agrandissement de la fenêtre le canvas opengl s'adapte mal.

* Lors du dessin d'un triangle puis chargement d'un fichier .tri les triangles suivants seront mal positionnés.

* Dans le menu popup les choix "propriétés triangles" et "suppression triangle" ne fonctionnait pas à l'aide d'EVT_MENU dans la classe OpenGLCanvas. Ces EVT_MENU ont donc été ajouté dans CMainFrame.

## Fonctionnalités supplémentaires

* Nombre de triangle non limité (utilisation de la structure de données vector) 