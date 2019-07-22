-- DESCRIPTION --

Ce petit fichier texte présente comment utiliser les informations obtenues
avec Lizard et avec le calcul du temps CPU pour faire du feedback textuel (pour
l'étudiant) et par tag custom (pour les tuteurs). L'exercice pilote est 
"Palindrome", vous pouvez vous y référer pour voir comment cela est fait en
pratique.

-- HOWTO : LIZARD --

Lizard est un outil qui analyse pour nous le nombre de lignes que contient un code
ainsi que sa complexité cyclomatique (censée représenter la complexité du code,
autrement dit la difficulté pour une personne tierce de comprendre le code en
question). 

Ces deux informations sont maintenant disponibles pour chaque tâche
et pour chaque question de chacune de ces tâches dans les tags customs associés 
(visibles lorsqu'on télécharge une soumission dans "submission.test" au champ
"custome"). Ces tags sont dénommés ainsi : cc_q1 et nlines_q1 pour la première
question, cc_q2 et nlines_q2 pour la seconde, etc. Attention cependant que si une
des questions n'est pas de type "multiline code", les numéros peuvent être décalés.
Par exemple si la première question n'est pas un code alors cc_q1 référera à la q2.
Cela sera amélioré plus tard.

En plus de ces tags customs, il est possible de donner un feedback textuel à
l'étudiant (car celui-ci n'a pas accès aux tags customs). Pour cela, il faut créer
un fichier avec le nom "lizard.txt" au même emplacement que là où se trouve le
fichier "run". Ce fichier contient un entier par ligne et deux entiers par
question (donc deux lignes s'il n'y a qu'une question). La première ligne est
le threshold pour la complexité cyclomatique de la question 1 et la deuxième pour
le nombre de lignes de cette même question. S'il y a une deuxième question (ou
plus), il faut alors toujours respecter cet ordre (et commencer par la question 1
puis la question 2, etc.). Ce threshold sert à vérifier que le code de l'étudiant
ne les dépasse pas. Si c'est le cas, un feedback est fourni en disant que le code
de l'étudiant est trop compliqué ou trop long et en lui indiquant les valeurs
calculées sur la solution présente dans "student/solutions/student_sol_code.c".
Il est à noter que ce feedback arrive que la question soit réussie ou ratée et
que ces deux "tests" n'ont aucun impact sur la réussite de la question.

-- HOWTO : CPU --

Pour le temps CPU, on ne le calcule que dans les questions où cela est nécessaire.
A l'écriture de ce tutoriel, le seul exercice où cela est fait est la tâche pilote
"Palindrome". Pour cette mesure, il existe également un tag custom et un feedback
textuel.

Pour les utiliser, il faut créer un test spécial dans "tests.c" qui va calculer le
temps CPU pris par la fonction de l'étudiant et ensuite celui pris par la fonction
solution (disponible dans "student/solutions/student_code_sol.c"). Ce test doit
bien sûr être effectué sur une donnée de grande taille pour le rendre
pertinent. Il est indépendant entre chaque question et donc peut se faire que sur
une partie des questions d'une tâche. Pour exemple, dans "Palindrome", le test 
s'appelle test_CPU() et vaut pour 1/10 des points de la tâche (n'hésitez pas à 
aller regarder comment cela est fait avant de le faire pour votre tâche).

Ce test spécial va alors faire deux choses avec les temps calculés. D'abord il va
écrire dans un fichier "cpu.txt" dans le répertoire courant le temps pris par la
fonction de l'étudiant (ATTENTION : pour ce faire il est impératif d'utiliser
fprintf, puisque cela sera analysé par le code python du run qui ne peut lire que
des strings, et de créer le fichier à l'ouverture, c'est-à-dire utiliser le mode 
"w+" pour la fonction fopen). S'il y a plusieurs questions qui doivent être 
analysées, il faut écrire un flottant par ligne dans l'ordre des questions.
Ensuite, le test vérifie que le temps pris par la fonction de l'étudiant n'est pas
supérieure à une certaine valeur (dans "Palindrome" nous avons mis 
"studtime > 2*soltime"). Si c'est le cas, le test est raté et un feedback textuel 
est fait à l'étudiant en lui indiquant le temps pris par chacune des deux 
fonctions (celle de l'étudiant et celle de la solution).

Le fichier créé quant à lui est utilisé dans le fichier "run" pour créer les tags
customs en rapport avec le CPU. Pour ce faire, il regarde si le fichier existe et
si oui, il lit ligne par ligne le(s) flottant(s) présent(s) dans le fichier et
output les tags de nom cpu_q1, cpu_q2, etc. Attention cependant que le chiffre est
en rapport avec la première question analysée et pas avec la première question de
la tâche ! Si par exemple vous analysez seulement la question 2 d'une tâche,
le tag en rapport avec ce test sera cpu_q1 car c'est la première question que vous
analysez (une amélioration est possible et sera sûrement faite plus tard en
remplaçant le fichier texte par un fichier JSON ou YAML ou XML qui permettra
d'établir des paires question/temps CPU plus facilement).
