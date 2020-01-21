#!/bin/bash
FILE=PNG32:goban.png
convert -size 570x570 -alpha transparent xc:white $FILE
let i=13
while [[ $i -le 570 ]]; do
    let j=$i
    let max=$i+4
    while [[ $j -lt $max ]]; do
	convert $FILE -fill "#000000CC" -draw "line $j,0 $j,570" $FILE
	convert $FILE -fill "#000000CC" -draw "line 0,$j 570,$j" $FILE
	let j=$j+1
    done
    let i=$i+30
done
