
' Test file for use with test0.b showing that BlitzMax interop works

Import "output.o"
Import "b-lib.o"

SuperStrict

Extern
BFunction bfun1:Int()
BFunction bfun2:Int(a:Int, b:Int, c:Int)
BFunction bfun3:Int(a:Int, b:Int)
BFunction bfun4:Int()
BFunction bfun5:Int(k:Int)
BFunction bfun6:Int(p:Int)
BFunction bfun7:Int(p:Int)
BFunction bfun8:Int(p:Int)
BFunction bfun9:Int(p:Int, a:Int)
BFunction bfun10:Int(f(), g:Int(a:Int, b:Int, c:Int))
BFunction bfun11:Int()
BFunction bfun12:Int()
BFunction bfun13:Int(a:Int, b:Int)
BFunction bfun14:Int(a:Int, b:Int)
End Extern

Print bfun1()
Print bfun2(1, 2, 3)
Print bfun2(0, 2, 3)
Print bfun2(4, 17, 93)
Print bfun2(0, 17, 93)
Print bfun3(4, 5)
Print bfun4()
Print bfun5(10)

Type foo Final
	Field a:Int, b:Int
End Type

Local f:foo = New foo, g:Int = Int(Byte Ptr(f))
bfun6(g)
Print "f.a: " + f.a
Print "f.b: " + f.b

Print ""

Print "0x" + Hex(bfun7(g))
Print "g: " + g + ", bfun8(g): " + bfun8(g)
Print "f.a: " + f.a
Print "f.b: " + f.b

Print bfun10(f1, f2)
bfun11()
bfun12()
Print bfun13(4, 6) + ", " + mfun13(4, 6)
Print bfun14(4, 6) + ", " + mfun14(4, 6)

Print "done."

BFunction f1()
	Print "hello from f!"
End BFunction

BFunction f2:Int(a:Int, b:Int, c:Int)
	Print "in g with " + a + ", " + b + ", " + c
	Return 671
End BFunction

BFunction mfun13:Int(a:Int, b:Int)
	Return ((((a + b) * (a + b)) + ((a + b) * (a + b))) * (a * (a + b * a)))
End BFunction

BFunction mfun14:Int(a:Int, b:Int)
	Return a + (a + (a + (a + (a + (a + (a + (a + b)))))))
End BFunction

