Za upoznavanje sa strukturom ulaznog formata, djelomi�no �e se razviti kompajler za 
programski jezik B, prethodnika jezika C. Jezik nema tipove. Unutar funkcije,
lokalne varijable se deklari�u klju�nom rje�ju auto, a globalne treba navest uz klju�nu rije�
extrn. Operatori dodjeljivanja su malo druga�iji nego u C, umjesto += koristi se =+ , a
unutar stringova * je escape simbol. Sintaksa uslova, izraza i petlji gotovo je ista kao u C.

Opis jezika u coco/r po�inje listom vrste znakova, nakon �ega slijede definicije tokena u EBNF.
Tokeni mogu da imaju kontekst, simbol koji ako se pojavi iza predstavlja zna�enje
tokena u dva razli�ita slu�aja (vidi u sljede�em primjeru kako se razlikuje identifier i gotolabel).
Nakon tokena defini�e se na�in pisanja komentara u jeziku za koji se pi�e skener i parser, lista
blanko simbola. 


Zatim se defini�u sintaksna pravila jezika u PRODUCTIONS sekciji. U sintaksu se mogu dodati
specijalne olak�ice sintaksne analize:
SYNC predstavlja mjesta gdje se sintaksna analiza nastavlja ako je do�lo do sintaksne gre�ke, radi boljeg
oporavka od gre�aka
WEAK predstavlja simbole koji se �esto gre�kom ispuste, pa se tako olak�ava oporavak od gre�aka.
IF (<funkkcija>=) omogu�ava razrje�avanje dvozna�nosti gramatike.



Sada treba dodati elemente semanti�ke analize. B je jezik vrlo limitirane semantike,
nekoliko o�iglednih pravila su:
- Varijabla u potprogramu mora biti deklarisana prije upotrebe, kao lokalna (auto) ili kao globalna (extrn).
- goto labela ne smije biti dupla i mora postojati
- case vrijednost ne smije biti dupla
- dodijeliti vrijednost se mo�e samo varijabli, pointeru ili elementu niza

Treba�e nekoliko potprograma koji �e biti ugra�eni kao metode klase Parser.cpp.
Metode su IsDeclaredLocal (provjerava da li je varijabla ve� deklarisana na bilo koji na�in u potprogramu), IsAuto (da li je stek tipa),IsDeclaredGlobal (provjerava da li je varijabla ve� deklarisana u glavnom programu), UndecErr (prijavljuje gre�ku nedeklarisanosti), AlreadyError (prijavljuje gre�ku duple deklarisanosti), GetNodeName (vra�a ime �vora u AST, parametar je pozicija u stringu koji ga simulira), ElemPos (vra�a poziciju u stringu koji predstavlja AST za navedeni redni broj elementa �vora)


Napi�ite funkciju bool Assignable(int position) unutar methods.inc koja treba da vrati true ako je rezultat GetNodeName na proslije�enoj poziciji bio L"VAR", L"INDEX" ili L"PTR" i dodajte semanti�ku provjeru 

```
CondExpr          
    [(
    "="                      
    AssignExpr    (. if (!(Assignable(position))) { SemErr(L"Not assignable"); }.)
                                (. ParseList.insert(position,L"(MOV " ); .)
                                (. ParseList.append(L") " );.)
  | "=*"                      
```
Datu liniju za provjeru dodajte iza svih AssignExpr slu�ajeva. Dodajte je i u UnaryExpr i PostfixExpr za operatore inkrementiranja i dekrementiranja.

Napi�ite funkciju koja provjerava da li je goto labela ve� definisana i promijenite pravilo Label da to testira.

Dobijeno apstraktno stablo sintakse sa semanti�kim provjerama, se mo�e dalje iskoristiti za generisanje asemblerskog koda
Po uzoru na ADD, lako realizujte generisanje asemblerskog koda za AND, OR, XOR i MUL. Probajte i SUB (pazite na nekomutativnost)



