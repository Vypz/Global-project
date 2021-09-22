<?php

class Calculator
{
    public function __construct(private $precision = 2)
    {}

    public function result($tab) {
        $v1 = $tab[0][0];
        $v2 = $tab[0][1];

        switch ($tab) {
            case $tab[1][0] == "+":
                {
                    echo 'Adition' . PHP_EOL;
                    echo $this->add($v1, $v2) . PHP_EOL;
                    break;
                }

            
            // default:
            //     # code...
            //     break;
        }
    }

    public function add(float $a, float $b): float
    {
        return round($a + $b, $this->precision);
    }

    public function multiply(float $a, float $b): float
    {
        return round($a * $b, $this->precision);
    }

    public function division(float $a, float $b): float
    {
        // arrête le script avec une fatale erreure throw lance une exception 
        if ($b === 0.0) throw new DivisionByZeroError("Impossible de diviser par zéro");

        return round($a / $b, $this->precision);
    }
}


$calculator = new Calculator;

$operation = [ [11, 2], ["+"] ] ;

$calculator->result($operation);