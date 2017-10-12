# CHDL -- Implement Nand2tetris HDL in C

A framework to simulate HDL (Hardware Description Language) in C

## Compile

```
$ gcc test.c -o test -std=c99
```

## Run

```
$ test
```

## Output

```
D:\Dropbox\project\chdl>test
=========== test1Gate() =============
in=0
in=1
=========== testGate2() =============
a=0 b=0
a=0 b=1
a=1 b=0
a=1 b=1
=========== testGate3() =============
a=0 b=0 c=0 sum=0 carry=0
a=0 b=0 c=1 sum=1 carry=0
a=0 b=1 c=0 sum=1 carry=0
a=0 b=1 c=1 sum=0 carry=1
a=1 b=0 c=0 sum=1 carry=0
a=1 b=0 c=1 sum=0 carry=1
a=1 b=1 c=0 sum=0 carry=1
a=1 b=1 c=1 sum=1 carry=1
=========== testAlu() =============
a+b = 14
a+b = 5000
```

## Reference 

* http://nand2tetris.org/