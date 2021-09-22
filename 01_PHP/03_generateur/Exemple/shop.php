<?php

function genFile($file){

    $f = fopen($file, 'r');

    while($line = fgets($f)) {
        $line = str_replace(["\n", "\r"], ['', ''], $line);
        list($k, $v) = explode('=', $line);

        yield $k => $v;
    } 

    fclose($f);
}

$prices = genFile('./prices.txt');
$users = genFile('./users.txt');




foreach($prices as $line){
    echo $line;
}

echo "TEST" . PHP_EOL;

foreach($users as $line){
    echo $line;
}

