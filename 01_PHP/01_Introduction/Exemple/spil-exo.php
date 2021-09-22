<?php

function split_array(int $pos , array $numbers) {

    $i = 0;
    $len = count($numbers);
    $y = $pos;
    $tmp_array1 = array();
    $tmp_array2 = array();

    if ($pos > $len) {
        return $numbers;
    }

    while ($i != $pos)
    {
        array_push($tmp_array1, array_shift($numbers));
        $i++;
    }
    while ($y < $len) {
        array_push($tmp_array2, array_shift($numbers));
        $y++;
    }
    
    print_r($tmp_array1);
    print_r($tmp_array2);

}

split_array(numbers: [1,2,3,7,8], pos : 3);

/*
<?php
namespace split ;

function split_array(array $numbers, int $pos): array
{
    if ($pos > count($numbers)) return $numbers;

    list($start, $i) = [[], 0];

    while ($i++ <= $pos) 
        $start[] = array_shift($numbers);

    return [$start, $numbers];
}

var_dump(split_array(numbers: [4,6,9, 17], pos: 2  )); */