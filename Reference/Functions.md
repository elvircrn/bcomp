# Functions

## The stack frame
The stack frame, also known as activation record is the collection of all data on the stack associated with one subprogram call.

The stack frame generally includes the following components:

* The return address
* BArgument variables passed on the stack
* Local variables (in HLLs)
* Saved copies of any registers modified by the subprogram that need to be restored (e.g. $s0 - $s8 in MAL).


## Caller Rules

After the subroutine returns (immediately following the call instruction), the caller can expect to find the return value of the subroutine in the register EAX. To restore the machine state, the caller should:
* Remove the parameters from stack. This restores the stack to its state before the call was performed.
* Restore the contents of caller-saved registers (EAX, ECX, EDX) by popping them off of the stack. The caller can assume that no other registers were modified by the subroutine.

```
push (ebx)    /* Push last parameter first */
push $216      /* Push the second parameter */
push eax      /* Push first parameter last */

call myFunc    /* Call the function (assume C naming) */

add $12, esp
```

Note that after the call returns, the caller cleans up the stack using the add instruction. We have 12 bytes (3 parameters * 4 bytes each) on the stack, and the stack grows down. Thus, to get rid of the parameters, we can simply add 12 to the stack pointer.

## Callee Rules
Standard function entry sequence for many compilers

```
push ebp
mov ebp, esp
sub esp, X 
```

## Caller Rules

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

### BFunction parameters

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

  
