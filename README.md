Class AapjeOmino:
1.	Het BORD is gepresenteerd door
-	pair<int,int> bord[MaxDimensie][MaxDimensie];” -  steennummer en een rotatie
-	Hoogte >=1, Breedte <=10
-	Kolommen en rijen worden genummerd vanaf 0. 
2.	Het SPEL is gepresenteerd door
-	Het aantal stenen (nrStenen)
-	Wie is er aan de beur (aanBeurt)
-	Hoe veel stenen krijgen spelers aan het beging (NODIG?)

3.	Elke SPELER is gerepresenteerd door
-	Een vector met aantal stenen daarin (bector Speler1 <Steen>;)
-	Hoe veel stenen? The size of the vector
4.	POT is gerepresenteerd door
-	Stack van steden (stack pot <Steen>)

Class STEEN:
1.	4 getallen (N,O,Z,W)
2.	steennummer (NODIG?)


Class ZET:
1.	Nummer van de steen – i
2.	Rotatie van de steen – r: 
-	0 – geen rotatie
-	1 – 90 graden
-	2 – 180 graden
-	3 – 270 graden
3.	Rij, Kolom – vakje op het bord

AAN HET BEGIN: 
-	Elke speller krijgt hetzelfde aantal stenen. 
-	Stenen hebben een vaste volgorde.
-	Steen 0 op het bord (ZONDER ROTATIE), STEEN 1 – FEMKE, STEEN 2 – LIEKE, dan alweer Femke en dan Lieke etc. 
-	De rest gaat naar de pot 








Week 1: 02-03-2021 - 09-03-2021
TO DO:
1.	Finish all class descriptions 
2.	Functions:
-	LeesIn
-	Eindstand
-	Drukaf
-	HaalSteenUitPot
-	WisselSpeler
