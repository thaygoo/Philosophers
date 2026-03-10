# Philosophers 🍝🤔

Ce projet est une implémentation classique du problème du **Dîner des Philosophes** (Dining Philosophers problem). L'objectif principal est d'apprendre les bases du **multi-threading** (threads), de la synchronisation de processus et de la gestion de la mémoire partagée à l'aide des **mutexes** en langage C.

## 📝 Description

Des philosophes sont assis autour d'une table ronde, avec un grand bol de spaghettis au centre.
Les philosophes alternent entre trois états : **manger**, **penser** et **dormir**.
- Pour manger, un philosophe a besoin de **deux fourchettes** (celle à sa gauche et celle à sa droite).
- Quand un philosophe a fini de manger, il pose ses fourchettes et commence à dormir.
- Quand il se réveille, il se met à penser en attendant de pouvoir manger à nouveau.
- La simulation s'arrête si un philosophe meurt de faim (c'est-à-dire s'il n'a pas mangé depuis un certain temps).

Le but est de faire survivre les philosophes le plus longtemps possible, sans **data races** et sans **deadlocks**.

## 🚀 Utilisation

### Compilation

Le projet utilise un `Makefile` pour la compilation. Pour compiler l'exécutable `philo`, exécutez simplement :

```bash
make
```

### Exécution

Le programme prend les arguments suivants :

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : Le nombre de philosophes et de fourchettes.
- `time_to_die` (en millisecondes) : Si un philosophe ne commence pas à manger `time_to_die` millisecondes après le début de son dernier repas ou le début de la simulation, il meurt.
- `time_to_eat` (en millisecondes) : Le temps qu'un philosophe prend pour manger. Pendant ce temps, il doit garder ses deux fourchettes.
- `time_to_sleep` (en millisecondes) : Le temps qu'un philosophe passe à dormir.
- `number_of_times_each_philosopher_must_eat` (optionnel) : Si tous les philosophes ont mangé au moins ce nombre de fois, la simulation s'arrête. Si non spécifié, la simulation ne s'arrête qu'à la mort d'un philosophe.

### Exemples

Pour lancer une simulation avec 5 philosophes, un `time_to_die` de 800ms, `time_to_eat` de 200ms et `time_to_sleep` de 200ms :
```bash
./philo 5 800 200 200
```
*(Dans cette configuration, aucun philosophe ne devrait mourir).*

Pour lancer une simulation où un philosophe devrait mourir :
```bash
./philo 4 310 200 100
```

## 🛠️ Architecture du Projet

- `src/main.c` : Point d'entrée, initialisation générale et nettoyage.
- `src/parsing.c` : Gestion et vérification des arguments passés en ligne de commande.
- `src/init.c` : Initialisation des structures de données (philosophes, mutexes, paramètres).
- `src/thread.c` : Création et gestion du cycle de vie des threads.
- `src/philosopher.c` : Routine principale de chaque philosophe (les actions séquentielles).
- `src/actions.c` / `src/eat_utils.c` : Fonctions spécifiques aux actions (prendre les fourchettes, manger, dormir, penser).
- `src/monitor.c` : Thread séparé observant l'état des philosophes pour détecter la mort de l'un d'eux ou la fin des repas.
- `src/utils.c` : Fonctions utilitaires (ft_atoi, gestion du temps, etc.).

## ⚠️ Contraintes du projet

- Écrit entièrement en **C**.
- Norme stricte (Norminette de 42).
- Aucun **Data Race** n'est toléré (vérifiable via `-fsanitize=thread`).
- Utilisation exclusive de `pthread` et des mutex (`pthread_mutex_t`).
- Interdiction d'utiliser des variables globales.
- Un affichage propre et synchronisé de l'état des philosophes.