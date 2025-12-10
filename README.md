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

### Étapes d'installation

1. Cloner le dépôt :
```bash
git clone https://github.com/votre-username/gestion-reservations.git
cd gestion-reservations
```

2. Créer un environnement virtuel (recommandé) :
```bash
python -m venv venv
source venv/bin/activate  # Sur Windows: venv\Scripts\activate
```

3. Installer les dépendances :
```bash
pip install -r requirements.txt
```

4. Lancer l'application :
```bash
python src/main.py
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
