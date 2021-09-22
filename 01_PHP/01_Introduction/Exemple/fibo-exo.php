<?php

function fibo($nb) {

    static $a = 1;
    
    $a = $a + $nb;
    echo $a;
    //fibo($a);
    
}

$nb = 1;
fibo($nb);