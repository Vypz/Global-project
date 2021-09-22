<?php

function transformNumbers($numbers) {
    $tab = array();
    foreach ($numbers as $value) {
        $tab[] = $value * 2;
    }
    return $tab;
}

function transformStrings($chaines) {
    $tab = array();
    foreach ($chaines as $word) {
        $tab[] = strtoupper($word);
    }
    return $tab;
}

function transform(array $tab, callable $fn): array {
    $transformation = [];

    foreach ($tab as $index => $value) {
        $transformation[] = $fn($value, $index);
    }
    return $transformation;
}

$tab = [1, 2, 3, 4];

$resultat = transform($tab, function (int $n) {
    return $n * 2;
});

