# 🏢 Système de Gestion de Réservations

Un logiciel complet de gestion de réservations pour salles de réunion avec système de facturation automatique, conçu pour les petites entreprises et espaces de coworking.

## 📋 Description

Ce projet offre une solution complète pour gérer efficacement les réservations de salles de réunion, incluant la vérification automatique des conflits, le calcul des tarifs, la génération de factures et l'analyse statistique de l'utilisation des salles.

## ✨ Fonctionnalités Principales

### 🔍 Système de Réservation Intelligent
- Vérification automatique de la disponibilité des salles
- Validation de la capacité en fonction du nombre de participants
- Détection et prévention des chevauchements de réservations
- Calcul automatique du tarif basé sur la durée et le tarif horaire

### 💰 Gestion Financière
- Système de tarification flexible par salle
- Calcul automatique du coût total des réservations
- Génération de factures professionnelles
- Sauvegarde des configurations tarifaires

### 📊 Statistiques et Analyses
- Suivi du chiffre d'affaires par salle
- Comptage des réservations mensuelles
- Identification des salles les plus populaires
- Tableaux de bord d'utilisation

### 💾 Persistance des Données
- Sauvegarde automatique de toutes les réservations
- Chargement des données au démarrage
- Système de fichiers structuré pour les factures
- Configuration externalisée

## 🚀 Installation

### Prérequis

- **Compilateur GCC** (GNU Compiler Collection)
- **Make** (outil de compilation)
- Système **Linux/Unix** ou **Windows avec MinGW**

### Étapes d'installation

1. **Cloner le dépôt**
```bash
git clone https://github.com/votre-username/gestion-reservations.git
cd gestion-reservations
```

2. **Compiler le projet avec Make**
```bash
make
```

3. **Lancer l'application**
```bash
./gestion_reservations
```

### Compilation manuelle (sans Makefile)

Si vous préférez compiler manuellement :

```bash
gcc -c src/models/*.c src/services/*.c src/utils/*.c
gcc -c src/main.c
gcc -o gestion_reservations *.o
./gestion_reservations
```

## 📖 Utilisation

### Menu Principal

L'application propose un menu interactif avec les options suivantes :

1. ✨ **Créer une nouvelle réservation**
2. 📋 **Afficher toutes les réservations**
3. ✏️ **Modifier une réservation**
4. ❌ **Annuler une réservation**
5. 🧾 **Générer une facture**
6. 📊 **Consulter les statistiques**
7. 🏢 **Gérer les salles**
8. 🚪 **Quitter**

```
### Exemple d'utilisation

=== SYSTÈME DE GESTION DE RÉSERVATIONS ===

1. Nouvelle réservation
2. Afficher les réservations
3. Générer une facture
4. Statistiques
5. Quitter

Votre choix : 1

--- Nouvelle Réservation ---
Nom du client : Jean Dupont
Salle disponible (Salle A, Salle B, Salle C) : Salle A
Date (JJ/MM/AAAA) : 15/01/2024
Heure de début (HH:MM) : 09:00
Heure de fin (HH:MM) : 11:00
Nombre de personnes : 8

✓ Réservation créée avec succès !
  ID : 1001
  Durée : 2 heures
  Tarif : 100.00 TND
  ```

## 📦 Modèles de Données

### Réservation
- `id` : Identifiant unique
- `nom_client` : Nom du client
- `salle` : Nom de la salle réservée
- `date` : Date de la réservation
- `heure_debut` : Heure de début
- `heure_fin` : Heure de fin
- `nombre_personnes` : Nombre de participants
- `tarif` : Coût calculé automatiquement
- `statut` : État de la réservation (confirmée, annulée, etc.)

### Salle
- `nom` : Nom de la salle
- `capacite` : Capacité maximale
- `tarif_horaire` : Tarif par heure
- `equipements` : Liste des équipements disponibles

## 🎯 Fonctionnalités Avancées (Tâche Supplémentaire)

### Système de Notifications par Email
- Envoi automatique de confirmations de réservation
- Rappels 24h avant la réservation
- Notifications d'annulation
- Résumés hebdomadaires pour les administrateurs

### Gestion des Utilisateurs et Permissions
- Système d'authentification
- Rôles (administrateur, gestionnaire, client)
- Historique des réservations par utilisateur
- Profils personnalisés

## 🧪 Tests

Exécuter les tests unitaires :
```bash
python -m pytest tests/
```

Générer un rapport de couverture :
```bash
pytest --cov=src tests/
```


## 🤝 Contribution

Les contributions sont les bienvenues ! Pour contribuer :

1. Forkez le projet
2. Créez une branche pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Committez vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Poussez vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request


## 👥 Auteurs 

- Rayen Nakara
- Moheb Waderni
- Moatez Rouihem

## 📞 Contact

Pour toute question ou suggestion, n'hésitez pas à :
- Ouvrir une issue sur GitHub
- Me contacter par email : rayen.nakara@ensi-uma.com

---

**Note** : Ce projet a été développé dans le cadre d'un projet académique à l'ENSI sur le thème de l'entrepreneuriat.
