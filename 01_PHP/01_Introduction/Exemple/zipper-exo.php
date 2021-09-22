<?php


function zipper(array $tab1, array $tab2) {
    return (array_combine($tab1, $tab2));
}




var_dump(zipper(tab1 : [1,2,3], tab2: [4,5,6]));