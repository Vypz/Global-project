<?php

/**
 * Finir la journée en beauté : notre propre framework de tests !
 * 
 * 1) Renommez vos fonctions de test en séparant les mots par des _
 * 
 * Exemple : testItCanFilter devient test_it_can_filter
 * 
 * NOTE : Conservez tout de même le mot "test" en premier !
 * 
 * 2) Trouvez un moyen de récupérer toutes les fonctions qui sont définies dans ce fichier
 * 
 * 3) Trouvez un moyen de ne conserver que les fonctions qui commencent par le mot "test"
 * 
 * 4) Exécutez chaque fonction et trouvez le moyen de savoir si elle marche ou pas tout en affichant dans le terminal le résultat (Ca marche ou pas)
 * 
 * 5) Si ça ne marche pas, essayez d'informer le développeur de pourquoi ça marche pas !
 */
 

function filter(array $numbers, callable $fn): array {
    $tab = array();

    foreach($numbers as $value) {
        if ($fn($value)) {
            array_push($tab, $value);
        }
    }

    return $tab;
}

function test_we_can_filter() {
    $nbs = [2, 20, 1, 15, 11];

    $results = filter($nbs, function($numbers) {
        return $numbers > 10;
    });

    assert(is_array($results));
    assert(count($results) === 3);
    assert($results[0] === 20);
    assert($results[1] === 15);
    assert($results[2] === 11);
}

function test_we_can_filter_other() {
    $numbers = [2, 20, 1, 15, 11];

    $results = filter($numbers, function($numbers) {
        return $numbers < 10;
    });

    assert(is_array($numbers));
    assert(count($results) === 2);
    assert($results[0] === 2);
    assert($results[1] === 1);
}



function getFunctionTab() {

    $arr = get_defined_functions()['user'];
    $tab_func = array();

    foreach($arr as $value) {
        if (str_starts_with($value, 'test')) {
            $tab_func[] = $value;
        }
    }

    foreach ($tab_func as $value) {
        try {
            $value();
            echo "J'ai validé $value" . PHP_EOL;
        }
        catch (AssertionError $e) {
            echo "J'ai une erreur sur $value" . PHP_EOL;
        }
    }
}

getFunctionTab();

