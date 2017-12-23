Za upoznavanje sa strukturom ulaznog formata, djelomièno æe se razviti kompajler za 
programski jezik B, prethodnika jezika C. Jezik nema tipove. Unutar funkcije,
lokalne varijable se deklarišu kljuènom rjeèju auto, a globalne treba navest uz kljuènu rijeè
extrn. Operatori dodjeljivanja su malo drugaèiji nego u C, umjesto += koristi se =+ , a
unutar stringova * je escape simbol. Sintaksa uslova, izraza i petlji gotovo je ista kao u C.

Opis jezika u coco/r poèinje listom vrste znakova, nakon èega slijede definicije tokena u EBNF.
Tokeni mogu da imaju kontekst, simbol koji ako se pojavi iza predstavlja znaèenje
tokena u dva razlièita sluèaja (vidi u sljedeæem primjeru kako se razlikuje identifier i gotolabel).
Nakon tokena definiše se naèin pisanja komentara u jeziku za koji se piše skener i parser, lista
blanko simbola. 


Zatim se definišu sintaksna pravila jezika u PRODUCTIONS sekciji. U sintaksu se mogu dodati
specijalne olakšice sintaksne analize:
SYNC predstavlja mjesta gdje se sintaksna analiza nastavlja ako je došlo do sintaksne greške, radi boljeg
oporavka od grešaka
WEAK predstavlja simbole koji se èesto greškom ispuste, pa se tako olakšava oporavak od grešaka.
IF (<funkkcija>=) omoguæava razrješavanje dvoznaènosti gramatike.



Sada treba dodati elemente semantièke analize. B je jezik vrlo limitirane semantike,
nekoliko oèiglednih pravila su:
- Varijabla u potprogramu mora biti deklarisana prije upotrebe, kao lokalna (auto) ili kao globalna (extrn).
- goto labela ne smije biti dupla i mora postojati
- case vrijednost ne smije biti dupla
- dodijeliti vrijednost se može samo varijabli, pointeru ili elementu niza

Trebaæe nekoliko potprograma koji æe biti ugraðeni kao metode klase Parser.cpp.
Metode su IsDeclaredLocal (provjerava da li je varijabla veæ deklarisana na bilo koji naèin u potprogramu), IsAuto (da li je stek tipa),IsDeclaredGlobal (provjerava da li je varijabla veæ deklarisana u glavnom programu), UndecErr (prijavljuje grešku nedeklarisanosti), AlreadyError (prijavljuje grešku duple deklarisanosti), GetNodeName (vraæa ime èvora u AST, parametar je pozicija u stringu koji ga simulira), ElemPos (vraæa poziciju u stringu koji predstavlja AST za navedeni redni broj elementa èvora)


Napišite funkciju bool Assignable(int position) unutar methods.inc koja treba da vrati true ako je rezultat GetNodeName na proslijeðenoj poziciji bio L"VAR", L"INDEX" ili L"PTR" i dodajte semantièku provjeru 

```
CondExpr          
    [(
    "="                      
    AssignExpr    (. if (!(Assignable(position))) { SemErr(L"Not assignable"); }.)
                                (. ParseList.insert(position,L"(MOV " ); .)
                                (. ParseList.append(L") " );.)
  | "=*"                      
```
Dobijeno apstraktno stablo sintakse sa semantièkim provjerama, se može dalje iskoristiti za generisanje asemblerskog koda
Po uzoru na ADD, lako realizujte generisanje asemblerskog koda za AND, OR, XOR i MUL. Probajte i SUB (pazite na nekomutativnost)



