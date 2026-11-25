# cpp07 — guide de correction

Ce guide suit les trois exercices et le code de ce dossier. Le module introduit les templates : une fonction ou une classe peut ainsi travailler avec différents types, et le compilateur crée la version adaptée au type utilisé.

## ex00 — `swap`, `min`, `max`

Les trois fonctions du header `whatever.hpp` sont des templates.

- `swap(T&, T&)` reçoit deux références modifiables. Une variable temporaire conserve la première valeur pendant l’échange.
- `min(const T&, const T&)` renvoie une référence constante vers la plus petite valeur.
- `max(const T&, const T&)` renvoie une référence constante vers la plus grande valeur.

Si les valeurs sont égales, `min` et `max` renvoient le **deuxième argument** : leur condition est fausse, donc elles retournent `second`. Les types utilisés doivent fournir les comparaisons nécessaires; les entiers et `std::string` conviennent.

Dans `main.cpp`, `::swap`, `::min` et `::max` désignent les fonctions déclarées dans l’espace de noms global.

### Questions possibles

**Pourquoi `min` et `max` renvoient-elles une référence constante ?**  
Elles renvoient l’un des objets reçus : la référence évite une copie et `const` empêche de modifier la valeur par ce résultat.

**Pourquoi le template est-il défini dans le header ?**  
Le compilateur doit voir sa définition au moment où il instancie la fonction pour un type donné.

**Que faut-il pour utiliser ces fonctions avec un type personnalisé ?**  
Le type doit permettre les opérations utilisées : affectation pour `swap`, comparaison `<` pour `min` et `>` pour `max`.

## ex01 — `iter`

`iter` reçoit un pointeur vers un tableau, sa longueur et une fonction. Elle appelle cette fonction sur chaque élément, des indices `0` à `length - 1`. Un pointeur nul entraîne un retour immédiat.

Le deuxième paramètre template, `Function`, laisse le compilateur déduire le type du callback. Dans `main.cpp`, `addOne(int&)` modifie les entiers; `printValue(const T&)` les lit sans les modifier. Un tableau de chaînes constantes montre aussi le cas où les éléments ne sont pas modifiables.

La définition se trouve dans `iter.hpp`, car le code du template doit être visible lors de son instanciation.

### Questions possibles

**Pourquoi le callback reçoit-il parfois une référence mutable et parfois une référence constante ?**  
Cela dépend du callback transmis. `iter` lui passe directement `array[i]`; le type du paramètre de la fonction détermine si l’élément peut être modifié.

**Combien de fois le callback est-il appelé ?**  
Une fois par élément, donc `length` fois si le tableau n’est pas nul.

**Pourquoi `length` est-il `const` ?**  
La longueur sert à borner la boucle et la fonction n’a aucune raison de la modifier.

## ex02 — `Array<T>`

`Array<T>` contient un pointeur `_data` vers un tableau dynamique et un entier `_size`.

### Construction et destruction

- Le constructeur par défaut crée un tableau vide.
- Le constructeur avec une taille alloue `new T[n]()`; les parenthèses initialisent les éléments par défaut.
- Le destructeur utilise `delete[]`, qui correspond à l’allocation faite avec `new[]`.

### Copie profonde

Le constructeur de copie alloue un nouveau tableau puis copie chaque élément. L’opérateur d’affectation fait aussi une nouvelle allocation avant de remplacer l’ancien contenu. La copie et l’original possèdent donc des données séparées.

L’opérateur d’affectation vérifie l’auto-affectation. S’il y a une exception pendant la copie des éléments dans le nouveau tableau, le bloc `catch` libère ce tableau temporaire puis relance l’exception. L’ancien contenu de l’objet destination reste disponible.

### Accès aux éléments

Les deux versions de `operator[]` vérifient que `index < _size`. Si l’index est trop grand, elles lancent `std::out_of_range`.

- La version non constante renvoie `T&`, donc l’élément peut être modifié.
- La version constante renvoie `const T&`, donc l’élément peut être lu mais pas modifié.
- `size() const` renvoie la taille sans changer l’objet.

### Questions possibles

**Pourquoi ne pas copier seulement `_data` dans le constructeur de copie ?**  
Cela ferait pointer les deux objets vers la même allocation. Une modification affecterait les deux objets et leurs destructeurs tenteraient de libérer la même mémoire. La copie profonde donne une allocation indépendante à chacun.

**Pourquoi `new T[n]()` avec les parenthèses ?**  
Cela initialise les éléments. Pour `Array<int>`, chaque élément commence à zéro.

**Pourquoi `delete[]` plutôt que `delete` ?**  
`_data` vient de `new[]`; il faut utiliser la forme tableau de la libération.

**Pourquoi vérifier `index >= _size` ?**  
Les indices valides sont de `0` à `_size - 1`. L’index égal à la taille est déjà hors limites.

**Pourquoi l’affectation alloue-t-elle avant de supprimer l’ancien tableau ?**  
Si l’allocation ou la copie échoue, les anciennes données sont encore intactes. Cela évite de perdre le contenu destination trop tôt.

## Présentation courte

> « `cpp07` porte sur les templates. `ex00` généralise trois fonctions à différents types. `ex01` applique un callback à chaque élément d’un tableau et permet aussi bien la lecture que la modification. `ex02` est une classe tableau générique : elle alloue avec `new[]`, vérifie les indices et implémente la copie profonde pour que deux tableaux copiés restent indépendants. »

## Entraînement avant la correction

Essaie de répondre sans regarder le README, puis retrouve le code qui justifie ta réponse :

1. Pourquoi les templates sont-ils définis dans des headers ?
2. Quel argument `min` renvoie-t-elle si les deux valeurs sont égales ?
3. Comment `iter` reçoit-elle une fonction qui modifie les éléments ?
4. Quelle différence entre les deux versions de `operator[]` ?
5. Comment la copie profonde évite-t-elle le partage de mémoire ?
6. Que se passe-t-il si on accède à `array[array.size()]` ?
7. Pourquoi l’affectation vérifie-t-elle `this != &other` ?

## Compiler et lancer

Depuis le dossier de chaque exercice :

```sh
make re
./ex00
```

Remplace `ex00` par `ex01` ou `ex02` dans le bon dossier. Les Makefiles utilisent `-Wall -Wextra -Werror -std=c++98`.
