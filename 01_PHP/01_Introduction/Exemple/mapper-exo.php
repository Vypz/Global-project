<?php

function mapped(array $numbers, $glue, $symbol) {
    
    $text = "";
    foreach ($numbers as $key => $value) {
        $text .= $key . " " . $symbol . " " . $value . $glue;
    }
    
    echo $text;
}


mapped(numbers: ['x' => 1,'y' => 2,'z' => 3,'t' => 7], glue : ', ', symbol : "=");