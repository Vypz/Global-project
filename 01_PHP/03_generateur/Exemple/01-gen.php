<?php

function genOdd(){
    for ($i = 2; $i <= 10; $i = $i + 2) {
        yield $i;
    }
}

$gen = genOdd();

foreach($gen as $v) echo $v . PHP_EOL;


function genOddN(int $n){
    for ($i = 2; $i <= $n; $i = $i + 2) {
        yield $i;
    }
}

$gen = genOddN(50);
foreach($gen as $v) echo $v . PHP_EOL;