#bfevo#
Evolutionarilyy generates brainfuck code that approximates a certain function.
The function bfevo approximates and the test data generator are contained in funct.cpp

###What this actually does:###
This program generates a certain number of brainfuck codes, and then tests them based on how close their output is to that of a given function. The most fit codes, and random mutations of them, are used in subsequent iterations.

###To compile:###
`make`

###To run:###
`./bfevo`

###Arguments:###
```
-i: Number of iterations to run bfevo for (default 1000000)
-t: Number of times to test each code for each iteration (default 1000)
-m: Number of codes to select from each population to use in next population (default 3)
-n: Number of mutations of each starting code to use for each population (default 2)
(Total size of each population is m * (n + 1))
```

##Output:###
Sample output:
```
>,[]-,[,[-,[][]]-]<>>+>+ 120 1000010
>,>,-,[,[-,[][]]-]<<>+>+ 120 1000010
>,[]-,[,[-,[]+,]-]<>>->+ 120 1000010
>,[]-,[,[-,[]-.]-]<>>+>+ 120 1000010
>,,>,-,>,[-,[][]]--<<>+>+ 120 1000010
>,>,-,[,[-,[][>]]-]<<>+<+ 120 1000010
>,[]-,+[,[[-,>]+,]-]<>>->+ 120 1000010
>,[]-,[<,[-,[]<+,]-]<>>->+ 120 1000010
>>,[]-,[,[-.[][]]-]<[],>+>+ 120 1000010
```
First column is bf code.
Second column is total negative fitness (lower is more fit).
Third column is total operations during running.