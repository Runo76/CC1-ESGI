Ce projet implémente un système de gestion des étudiants avec des requêtes SQL de base, utilisant C pour manipuler les données des étudiants stockées dans un fichier TXT.

Fonctionnalités
Ajout d'un étudiant (via INSERT)
Consultation de tous les étudiants (via SELECT)
Suppression d'un étudiant (via DELETE)
Installation
Clonez ce dépôt GitHub sur votre machine locale :

git clone git@github.com:runo76/cc1-ESGI.git
Lancement
mingw32-make clean
mingw32-make
./database

Exemple de requête sql
INSERT INTO students (id, name, grade) VALUES (2, 'Kiko', 10);
SELECT * FROM students;
SELECT FROM students WHERE id = l'id de l'utilisateur;
DELETE FROM students WHERE id = l'id de l'utilisateur;

Quitter le programme :
CTRL + C
