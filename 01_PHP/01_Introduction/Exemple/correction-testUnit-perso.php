<?php

/**
 * PARTIE QUI GERE LA LIGNE DE COMMANDE ET LES ARGUMENTS
 * -----------------------------------------------------
 */

// 1. Le nom du fichier où se trouvent les tests devrait être dans l'argument 1 de $argv
if (!isset($argv[1])) {
    exit("⚠️ Vous n'avez pas précisé le fichier de test !" . PHP_EOL);
}

$fileName = $argv[1];

// 2. Le fichier doit exister :
if (!file_exists($fileName)) {
    exit("⚠️ Le fichier \"$fileName\" n'existe pas !" . PHP_EOL);
}

// 3. Importons le fichier pour pouvoir connaître ses fonctions
require($fileName);

/**
 * EXECUTION DE LA SUITE DE TESTS :
 * --------------------------------
 */

// 1. Récupérer toutes les fonctions du fichier :
$userFunctions = get_defined_functions()['user'];

// 2. Ne garder que les fonctions qui commencent par 'test'
$testFunctions = array_filter($userFunctions, fn ($name) => str_starts_with($name, 'test'));

// 3. Conserver le moment où les tests commencent
$time = microtime(true);

echo "\n🛠️ Début des tests unitaires :\n\n";

// Pour chaque fonction de test trouvée :
foreach ($testFunctions as $fn) {
    // On fait un joli titre en supprimant le mot test
    $fnTitle = substr($fn, 4);
    // Et en remplaçant ces underscores très moches par un espace
    $fnTitle = str_replace('_', ' ', $fnTitle);

    // On essaye de lancer la fonction : si ça passe, ça marche, si on catch c'est qu'il y a eu un soucis !
    try {
        $fn();
        echo "  ✅ $fnTitle\n";
    } catch (AssertionError $e) {
        echo "  ❌ $fnTitle : {$e->getMessage()} à la ligne {$e->getFile()}:{$e->getLine()}\n";
    }
}

// On calcule le temps que ça a pris :
$ms = (microtime(true) - $time) * 1000;

echo "\n⏳ Exécutés en $ms ms\n";
