<?php 


function lancer(int $nb_lancer) : array {
    $tab_lance = array();
    $i = 0;

    while ($i < $nb_lancer) {
        for ($j=0; $j < 5 ; $j++) { 
            $tab_lance[$i][$j] = rand(1, 6);
        }
        $i++;
    }

    return $tab_lance;
}


function yam(array $lancer) {
    $tab = array_count_values($lancer);
    print_r($tab);

    foreach($tab as $key => $value) {
        //echo "KEY = $key / Value = $value" . PHP_EOL;
        if ($value == 3) {
            echo "BRELAN sur le $key" . PHP_EOL;
        }
        if ($value == 4) {
            echo "CARRE sur le $key" . PHP_EOL;
        }
        if ($value == 5) {
            echo "YAM sur le $key" . PHP_EOL;
        }


    }

}

$total_lancer = (lancer(2));
//print_r($lancer);

foreach ($total_lancer as $lancer) {
    //print_r($lancer) . PHP_EOL;
    yam($lancer);
    
}
