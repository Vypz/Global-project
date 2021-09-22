<?php

// Créer une fonction transform à laquelle vous pourrez passer une fonction de transformation
// Elle devrait pouvoir travailler autant sur un tableau de strings que sur un tableau de nombres
// Et elle devrait appliquer la transformation voulue

function transform(array $arr, callable $fn): array
{
    $transformation = [];

    foreach ($arr as $index => $value) {
        $transformation[] = $fn($value, $index);
    }

    return $transformation;
}

$numbers = [1, 2, 3, 4];

$resultat = array_map(function (int $n) {
    return $n * 2;
}, $numbers);

assert(is_array($resultat));
assert($resultat[0] === 2);
assert($resultat[1] === 4);
assert($resultat[2] === 6);
assert($resultat[3] === 8);

$strings = ['Lior', 'Magali', 'Elise'];

$resultat = transform($strings, function (string $str) {
    return strtoupper($str);
});
assert($resultat[0] === 'LIOR');
assert($resultat[1] === 'MAGALI');
assert($resultat[2] === 'ELISE');