# Jump if Lesser

## Operands

### arg1 
* Register
* Immediate

### arg2 
* AL/AX/EAX (only if arg1 is immediate)
* Register
* Memory

Performs a bit-wise logical AND on arg1 and arg2 the result of which we will refer to as Temp and sets the ZF(zero), SF(sign) and PF(parity) flags based on Temp. Temp is then discarded.

## Modified flags 
* SF = MostSignificantBit(Temp)
* If (Temp == 0) ZF = 1 else ZF = 0
* PF = BitWiseXorNor(Temp[Max-1:0]), so PF is set if and only if Temp[Max-1:0] has an even number of 1 bits
* CF = 0
* OF = 0
* AF is undefined



```
cmp arg2, arg1
```

```
jl loc
```


