<?php

$content = [2, 1, 4, 2, 6, 0, 1, 2, 3, 7];    // Liste donnée
$seq = [1,2,3];                         // mot recherche ( ici faut trouver 1,2,3 a la suite)



function search_pos_word($content, $seq) {
    $return_pos = 0;
    $y = 0;

    for($i = 0; $i < count($content); $i++) {
       if ($content[$i] == $seq[$y]) {
            // Façon flexible par rapport a la taille de $seq


            // Façon en dur 
            if ($content[$i+1] == $seq[$y+1] && $content[$i+2] == $seq[$y+2]) {
                $return_pos = $i;
           }


       }
    }
    echo "result = $return_pos" . PHP_EOL;
}


search_pos_word($content, $seq);