<?php

function filter(array $numbers): array {
    $tab = array();

    foreach($numbers as $value) {
        if ($value > 10) {
            $tab[] = $value;
        }
    }

    return $tab;
}

function testWeCanFilter() {
    $numbers = [2, 20, 1, 15, 11];

    $results = filter($numbers);

    assert(is_array($numbers));
    assert(count($results) === 3);
    assert($results[0] === 20);
    assert($results[1] === 15);
    assert($results[2] === 11);
}

function filter2(array $numbers): array {
    $tab = array();

    foreach($numbers as $value) {
        if ($value < 10) {
            $tab[] = $value;
        }
    }

    return $tab;
}

function testWeCanFilterOther() {
    $numbers = [2, 20, 1, 15, 11];

    $results = filter2($numbers);

    assert(is_array($numbers));
    assert(count($results) === 2);
    assert($results[0] === 2);
    assert($results[1] === 1);
}

testWeCanFilter();
testWeCanFilterOther();