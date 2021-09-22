<?php

$a = 1; /* portée globale */

// portée spécifique
function foo()
{ 
    $a = "test";
    echo $a; /* portée locale */
}

foo();