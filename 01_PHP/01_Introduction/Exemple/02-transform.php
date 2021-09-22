<?php

function transform($numbers) {
    $tab = array();
    foreach ($numbers as $value) {
        $tab[] = $value * 2;
    }
    return $tab;
}
$nombres = [1, 2, 3, 4];
$transformation = transform($nombres);
//print_r($transformation);


function transformStrings($chaines) {
    $tab = array();
    foreach ($chaines as $word) {
        $tab[] = strtoupper($word);
    }
    return $tab;
}


function testThatTransformStringWorks() {
    $chaines = ['Lior', 'Magali', 'Elise'];

    $transformation = transformStrings($chaines);

    print_r($transformation);
}


testThatTransformStringWorks();