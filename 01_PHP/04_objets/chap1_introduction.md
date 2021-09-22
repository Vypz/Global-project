# Objet

L'objet existe depuis la version 3 de PHP, à ce moment on n'a pas vraiment un langage de programmation objet.Ce n'est qu'à partir de la version 5 que PHP introduit les véritables concepts de l'objet.Bien que PHP soit un langage de script on va programmer tout en objet dans la suite de ce cours.

## Introduction à l'objet

### Définitions

- Def Classe 

Une classe est la somme des propriétés et attributs d'un objet. 
C'est une représentation abstraite d'un objet.

- Objet 

Un objet est une instance d'une classe.

- Def Attributs et méthodes d'une classe 

Les attributs d'une classe sont les variables d'une classe et les méthodes sont les fonctions de la classe. Plus généralement on appelle membre d'une classe les attributs ou méthodes d'une classe.
Exemples Ci-dessous une représentation abstraite d'un personnage, la classe "Persona" n'est pas, par définition, concrète. 
La classe représente l'implémentation des attributs (variables de la classe) et méthodes (fonctions de la classe), le code que l'on écrit dans la classe. 

Pour rendre "concrète" son utilisation, on fera une instance de la classe Persona.

```php
class Persona{

    public function __construct(
        private $force, 
        private $secret = "my secret"
    ){}

    public function fight(){
        echo "missile";
    }
}
``` 

Un objet est une instance de classe, c'est une variable dans le script courant.

## Visibilité d'un attribut ou d'une méthode

Si un membre de la classe est privé il est impossible d'y accéder à l'extérieur de la classe, c'est-à-dire à partir de l'objet dans le script courant.

![compilation simple](../images/visibility.png)

### Méta-variable $this

Pour qu'une méthode puisse manipuler une variable de classe à l'intérieur de la classe elle-même, elle utilise la méta-variable :

```php
$this;
```

C'est une référence à une instance unique de la classe dans le script.

### Principe d'encapsulation

Si un attribut ou une méthode est privé il est donc impossible d'y accéder dans le script courant. 

Plus généralement les attributs seront privés et les méthodes publiques.

- Définition 

Les données (attributs) ne peuvent être modifiées dans le script courant directement (ils sont privés), seuls les méthodes qui contrôles les données peuvent le faire. 

Une boîte noire dans un avion par exemple aura un programme possédant des attributs privés et des méthodes publiques; pour modifier les attributs privés, si un événement exceptionnel dans l'avion se produit, seuls les méthodes publiques peuvent le faire.

- Accéder aux attributs: accesseur ou getter

- mutateur ou setter

- accesseur ou getter

## Single Responsability

Lorsqu'on programmera en objet on devra toujours garder à l'esprit le principe suivant: Une classe un rôle, ou attribuer à chaque classe une responsabilité unique définie et bornée. Par exemple la classe Persona, Scene, Role.

Il faudra également respecter le principe suivant, une classe un fichier, c'est comme cela que l'on programme en objet pas autrement.

## Exercice Calculator

Créez une classe Calculator. Cette classe implémentera les spécificités suivantes :

- addition signature : prend deux arguments numériques et retourne un flottant

- multiplication signature : prend deux arguments numériques et retourne un flottant

- division signature : prend deux arguments numériques et retourne un flottant

- somme signature : prend N un entier supérieur à 2 arguments numériques et retourne un flottant

## Exercice Calculator une autre version

Implémentez maintenant une calculatrice qui prend une expression et calcul celle-ci. L'expression ou une opération sera passée sous forme d'un tableau de tableau comme suit :

```php
$calculator = new Calculator;

$operation = [ [11, 2], ["+"] ] ;

$calculator->result($operation);
```


### Principe de l’héritage

Pour faire de l’héritage vous devez appliquer le principe suivant :une classe étendue doit être une sorte de ou est un.

Ainsi, par exemple si vous avez une classe Book qui est étendue de la classeProduct, vous faites bien de l’héritage, car un livre est un produit ou une sorte de produit.

Si vous n’appliquez pas ce principe vous ne faites pas d’héritage au sens strict du paradigme objet. Voici comment vous devez représenter cette relation en diagramme UML :

![compilation simple](../images/heritage.png)

## traits

C'est une méthode pour réutiliser du code en PHP dans le contexte de l'héritage simple. Une classe peut utiliser plusieurs traits.

Un trait sert à regrouper des fonctionnalités intéressantes, il ne peut pas être instancié. Il s'ajoute à la notion d'héritage qui autorise la composition horizontale des comportements, ou plus exactement l'utilisation de méthodes sans héritage.

```php
trait showHello {
    function hello() { echo "Hello " ; }
}

trait showWorld {
    function world() { echo " World " ; }
}

class View{
    use showHello, showWorld;

    public function exclamation(){
        echo " !";
    }
}

$o = new View();
$o->hello();
$o->word();
$o->exclamation();
// Hello World !
```

### Résolution de conflits

Deux traits identiques dans une même classe lève une erreure fatale. Pour résoudre un conflit entre deux traits il faut utiliser l'opérateur **insteadof**.

```php
trait A {
    public function smallTalk() {
        echo 'a';
    }
    public function bigTalk() {
        echo 'A';
    }
}

trait B {
    public function smallTalk() {
        echo 'b';
    }
    public function bigTalk() {
        echo 'B';
    }
}

class Talker {
    use A, B {
        B::smallTalk insteadof A;
        A::bigTalk insteadof B;
    }
}
``` 

### Changer la visibilité des méthodes 

En utilisant la syntaxe as, vous pouvez aussi ajuster la visibilité de la méthode dans la classe qui l'utilise. Les méthodes privée ne peuvent être modifiées. Une classe peut implémenter plusieurs interfaces.

```php 
trait HelloWorld {
    protected function sayHello() {
        echo 'Hello World!';
    }
}

// Modification de la visibilité de la méthode sayHello protected => public possible
class A {
    use HelloWorld { sayHello as public; }
}

$b = new A;

echo $b->sayHello();

```

## Héritage 

L’héritage permet de factoriser un ensemble de méthodes et d’attributs dans une classe mère que des classes filles peuvent partager.

Les classes filles seront spécialisées par rapport à la classe mère. Par exemple une classe Product mère et une classe Stylo fille, la classe Stylo est dite spécialisée par rapport à la classe Product. La classe Stylo possédera plus de spécificités que la classe Product.

La relation de dépendance entre une classe mère et une classe fille est très forte. On parlera de couplage fort. En effet, pour instancier la classe étendue il faut que la classe mère soit définie dans le script courant.

L’héritage multiple n’existe pas en PHP, vous ne pouvez hériter que d’une seule classe à la fois.


## Interface (rappel)

Les interfaces objet vous permettent de définir des méthodes publiques que vos classes devront implémentées.

```php
interface iTemplate
{
    public function setVariable($name, $var);
    public function getHtml($template);
}
class Template implements iTemplate
{
    private $vars = array();

    public function setVariable($name, $var)
    {
        $this->vars[$name] = $var;
    }

    public function getHtml($template)
    {
        foreach($this->vars as $name => $value) {
            $template = str_replace('{' . $name . '}', $value, $template);
        }

        return $template;
    }
}
```

## TP Yam

Vous allez créer une petite composant qui permet de lancer 5 dés pour jouer au Yam. Il n'y aura qu'un seul joueur dans l'application et nous testerons que le lancer de 5 dés (en même temps). Nous allons faire des statistiques sur les différentes combinaisons du jeu. Vous ne testerez que certaines combinaisons de Yam :

- Brelan : 2 (trois dés identiques)

- Carré : 1 (4 dés indentiques)

- Double paire : 4 (deux dés identiques X 2 les paires sont des dés différents )

- Yam : 2 (5 dés identiques)

Créez autant de classe que nécessaire pour implémenter ce composant.

## TP Panier 

En partant du code ci-dessous construisez un système de commande de produits à l'aide d'un panier.

```php  
<?php

require_once __DIR__ . '/vendor/autoload.php';

// importer les namespaces 
use Fruit\{Product, Cart, StorageArray};

// Hydratation de quelques produits qui viennent de la base de données
$dbProducts = [
    'apple'      => 10.5,
    'raspberry'  => 13,
    'strawberry' => 7.8,
];

// Hydratation des produits à partir des produits de la base de données
$products = []; // Objets de type Product

foreach($dbProducts as $name => $price){
    $products[$name] = new Product($name, $price);
}

extract($products); // variable clé avec valeur du tableau associatif

// echo '<pre>';
// print_r($apple);
// echo '</pre>';

$cart = new Cart( new StorageSession );

$cart->buy($apple, 1);
$cart->buy($apple, 1);
$cart->buy($apple, 1);
// $cart->reset();
$cart->buy($strawberry, 10);

echo '<pre>';
print_r($cart->total());
echo '</pre>';

$cart->restore($strawberry);

echo '<pre>';
print_r($cart->total());
echo '</pre>';
```

Créez autant de classe que nécessaire pour implémenter ce composant.

## TP Queue

Implémentez une Queue en définissant une classe. Voici comment dans le script courant vous devez appeler votre code pour ajouter un élément dans la queue et récupérer le premier élément de la queue.

```php
$queue = new Queue();
$queue->push(1);
$queue->push(2);
$queue->push(3);
$queue->pop(); // affiche 1
$queue->clear(); // retire tous les éléments de la queue
```

Votre Queue peut implémenter l'interface ArrayAccess.

```php
class Obj implements ArrayAccess {

    public function __construct(
        private array $container = [
             "un"    => 1,
            "deux"  => 2,
            "trois" => 3,
        ]
    ) {}

    public function offsetSet($offset, $value) {
        if (is_null($offset)) {
            $this->container[] = $value;
        } else {
            $this->container[$offset] = $value;
        }
    }

    public function offsetExists($offset) {
        return isset($this->container[$offset]);
    }

    public function offsetUnset($offset) {
        unset($this->container[$offset]);
    }

    public function offsetGet($offset) {
        return isset($this->container[$offset]) ? $this->container[$offset] : null;
    }
}

$obj = new Obj;

var_dump($obj["deux"] ?? 'no exist');
unset($obj["deux"]); // supprime l'élément
var_dump(?? $obj["deux"] 'no exist');
$obj["deux"] = "Une valeur";
var_dump($obj["deux"]);
$obj[] = 'Ajout 1';
$obj[] = 'Ajout 2';
$obj[] = 'Ajout 3';
print_r($obj);
```


## TP Exercice Button & Lamp

Imaginez une lampe dans votre salon. Décomposez celle-ci en deux entités : un Button et une Lamp. Vous ferez également un schéma sur papier pour vous représenter les relations entre ces deux entités.

```php
$lamp= new Button(new Lamp);
```

Puis implémentez le déclenchement lumière alumé/éteint.

```php
echo $lamp->switchDevice(); // turn on
echo $lamp->switchDevice(); // turn off
echo $lamp->switchDevice(); // turn on
echo $lamp->switchDevice(); // turn off
```

## TP exercices Letter & Console

Créez deux classes Letter et Console. La première classe génère les lettres de l'alphabet et la deuxième affiche le contenu d'un tableau de dimension 1 dans le terminal.

La méthode generate de la classe Letter génère 10 lettres aléatoirement de l'alphabet et retourne ces lettres dans un tableau. La show affiche en console le résultat.

```php
$letter = new Letter();
$console = new Console();

$alphabet = $letter->generate(10);

$console->show($alphabet);
```
