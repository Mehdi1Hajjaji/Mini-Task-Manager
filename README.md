# Mini Task Manager – Projet étudiant en C

Ce projet a pour objectif de développer un mini gestionnaire de processus en langage C.  
L’application listera les processus actifs du système, affichera leurs informations (PID, nom, état, mémoire utilisée) et permettra d’envoyer des signaux (ex. terminer un processus).  

Le projet est conçu **sans bibliothèque externe au départ** : tout est programmé manuellement pour pratiquer les notions fondamentales vues en cours :

- **Structures (`struct`)** pour modéliser les processus.  
- **Pointeurs** et **allocation dynamique** pour gérer la mémoire.  
- **Fonctions et modularité** pour séparer les responsabilités.  
- **Tableaux dynamiques** et manipulation de chaînes.  
- **Lecture de fichiers système** (`/proc`) pour comprendre le lien avec l’OS.  
- **Signaux UNIX** pour interagir avec les processus.  

Une interface graphique **GTK** et un **Makefile** seront ajoutés à la fin du projet.  
Le code est écrit pas à pas, de manière pédagogique, pour renforcer la compréhension des concepts de **programmation système, architecture et mémoire**.
