<?php

function xrange(int $start, int $limit, int $step = 1){
    for ($i=$start; $i < $limit; $i+=$step) { 
        yield $i;
    }


}

xrange(1, 20, 2);