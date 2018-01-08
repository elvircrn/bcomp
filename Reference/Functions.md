# Functions

## The stack frame
The stack frame, also known as activation record is the collection of all data on the stack associated with one subprogram call.

The stack frame generally includes the following components:

* The return address
* Argument variables passed on the stack
* Local variables (in HLLs)
* Saved copies of any registers modified by the subprogram that need to be restored (e.g. $s0 - $s8 in MAL).


## Function entry sequence

Standard function entry sequence for many compilers

```
push ebp
mov ebp, esp
sub esp, X 
```

### Local variables

```
a = 10;
b = 5;
c = 2;
```

```
mov [ebp -  4], 10  ; location of variable a
mov [ebp -  8], 5   ; location of b
mov [ebp - 12], 2   ; location of c
```

### Function parameters

The following code produces

```
void MyFunction2(int x, int y, int z)
{
  ...
}
```

```
_MyFunction2:
  push ebp 
  mov ebp, esp
  sub esp, 0     ; no local variables, most compilers will omit this line
```

  
