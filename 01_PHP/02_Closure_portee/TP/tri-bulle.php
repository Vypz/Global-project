<?php

$tTri =[8,1,0,17,15,2,7,12];


function funcTri($tab) {
    for($a=0; $a < count($tab)-1; $a++) {
        for($b=0; $b < count($tab)-1-$a ; $b++) {
            if ($tab[$b] > $tab[$b+1] ) {
                $c = $tab[$b+1];
                $tab[$b+1] = $tab[$b];
                $tab[$b] = $c;
            }
        }
    }
    return $tab;
}

print_r(funcTri($tTri));