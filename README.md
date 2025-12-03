# 🏦 Bank Management System

Voici Mon 3 projet en c++ 
Un système de gestion bancaire en C++ permettant de gérer les clients, leurs comptes et effectuer des transactions.(sans OOP).

## 📋 Fonctionnalités

### Gestion des Clients
- ✅ Ajouter de nouveaux clients
- ✅ Afficher la liste complète des clients
- ✅ Rechercher un client par numéro de compte
- ✅ Modifier les informations d'un client
- ✅ Supprimer un client

### Transactions
- 💰 Dépôt d'argent
- 💸 Retrait d'argent (avec validation du solde)
- 📊 Affichage des soldes totaux

## 🛠️ Prérequis

- Compilateur C++ (g++, Visual Studio, etc.)
- Support C++11 ou supérieur
- Système d'exploitation : Windows, Linux ou macOS

## 📦 Installation

1. Clonez le repository :
```bash
git clone https://github.com/votre-username/bank-management-system.git
cd bank-management-system
```

2. Compilez le programme :
```bash
g++ -o bank_system main.cpp -std=c++11
```

3. Exécutez le programme :
```bash
./bank_system        # Linux/macOS
bank_system.exe      # Windows
```

## 📖 Utilisation

### Menu Principal

Au lancement, vous verrez le menu principal avec les options suivantes :

```
[1] Show Client List       - Afficher tous les clients
[2] Add New Client         - Ajouter un nouveau client
[3] Delete Client          - Supprimer un client
[4] Update Client Data     - Modifier les informations d'un client
[5] Find Client            - Rechercher un client
[6] Transaction            - Menu des transactions
[7] Exit                   - Quitter le programme
```

### Menu Transactions

Le menu transactions propose :

```
[1] Deposit               - Effectuer un dépôt
[2] Withdraw              - Effectuer un retrait
[3] Total Balances        - Voir tous les soldes
[4] Main Menu             - Retour au menu principal
```

## 💾 Stockage des Données

Les données des clients sont stockées dans le fichier `CLIENT.txt` avec le format suivant :

```
AccountNumber#//#PinCode#//#FullName#//#PhoneNumber#//#AccountBalance
```

**Exemple :**
```
A001#//#1234#//#John Doe#//#0123456789#//#5000.50
```

## 📊 Structure des Données

Chaque client contient les informations suivantes :
- **Numéro de compte** : Identifiant unique
- **Code PIN** : Code de sécurité
- **Nom complet** : Nom du client
- **Numéro de téléphone** : Contact
- **Solde du compte** : Montant disponible

## 🔒 Sécurité

- Validation des numéros de compte uniques
- Confirmation avant suppression ou modification
- Vérification du solde avant retrait
- Protection contre les doublons

## 🐛 Corrections Apportées

Version corrigée incluant :
- ✅ Déclaration anticipée des fonctions
- ✅ Correction de la logique du menu transactions
- ✅ Ajout des appels de fonctions manquants
- ✅ Gestion correcte des retours aux menus
- ✅ Correction des valeurs de retour

## 📝 Exemples d'Utilisation

### Ajouter un Client
1. Sélectionnez l'option [2] dans le menu principal
2. Entrez les informations demandées
3. Le client sera ajouté au fichier CLIENT.txt

### Effectuer un Dépôt
1. Sélectionnez [6] Transaction puis [1] Deposit
2. Entrez le numéro de compte
3. Entrez le montant à déposer
4. Confirmez la transaction

### Effectuer un Retrait
1. Sélectionnez [6] Transaction puis [2] Withdraw
2. Entrez le numéro de compte
3. Entrez le montant à retirer (doit être ≤ solde)
4. Confirmez la transaction

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à :
1. Fork le projet
2. Créer une branche pour votre fonctionnalité
3. Commit vos changements
4. Push vers la branche
5. Ouvrir une Pull Request


**Note :** Ce projet est à des fins éducatives. Pour un système bancaire réel, des mesures de sécurité supplémentaires seraient nécessaires.
