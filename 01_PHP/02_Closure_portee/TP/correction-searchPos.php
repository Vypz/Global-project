<?php

function search_pos_seq(array $content, array $seq): int | null
{

    $j = 0; // avancé sur la séquence
    $len = count($content);
    $lenSeq = count($seq);
    for ($i = 0; $i < $len; $i++) {

        if ( $content[$i] === $seq[$j])
            $j += 1;
        else
            $j = 0;

        if ($j === $lenSeq)
            return $i - ($j - 1);
    }

    return null;
}

$content = [2, 1, 4, 2, 6, 1, 2, 3, 7];
$seq = [1, 2, 3];

echo search_pos_seq(content: $content, seq: $seq);