<?php

// fonction dec
function asc($tab) {

    $permut = true;
    $sizeTab = sizeof($tab);
    $passage = 0;

    while($permut) {
        $permut = false;
        $passage += 1;
        for( $i=0; $i<$sizeTab-$passage ; $i++ ) {
            if( $tab[$i] > $tab[$i + 1]) {
                $permut = true;
                $tmp = $tab[$i + 1] ;
                $tab[$i + 1] = $tab[$i];
                $tab[$i] = $tmp;
            }
        }
    }
    return $tab;
}

// fonction asc
function dec($tab) {

    $permut = true;
    $sizeTab = sizeof($tab);
    $passage = 0;

    while($permut) {
        $permut = false;
        $passage += 1;
        for( $i=0; $i<$sizeTab-$passage ; $i++ ) {
            if( $tab[$i] < $tab[$i + 1]) {
                $permut = true;
                $tmp = $tab[$i + 1] ;
                $tab[$i + 1] = $tab[$i];
                $tab[$i] = $tmp;
            }
        }
    }
    return $tab;
}

// fonction sort
function bubulle_sort ($tab, callable $fn, $init=0) {
    $init = $fn($tab);
    return $init;
}


$tab = [9,4,6,3,7,25,33,1,88,44,64,24];

$resultDec = bubulle_sort($tab, "dec");
print_r($resultDec);
echo PHP_EOL;

echo PHP_EOL;
echo "==================================";
echo PHP_EOL;

$resultAsc = bubulle_sort($tab, "asc");
print_r($resultAsc);
echo PHP_EOL;