<?php

// délégation
function Odd($len) {
    $count = 0;

    while ($count < $len) {
        yield 1;
        $count++;
    }
}
function listI($limit) {
    $i = 0;

    while ($i < $limit) {
        if (($i % 3) == 0) {
            yield from Odd($i);
        }
        else
            yield $i;
        $i++;
    }
}

// instancie le générateur
$gen = listI(10);
foreach($gen as $v) echo $v . PHP_EOL;