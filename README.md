MiniMax Algorhytmus anhand TicTacToe Spiel In C++
=================
Projekt Arbeit aus dem Ersten Jahr meiner Ausbildung.  
Tic Tac Toe Consolen App mit Spielmodusauswahl und MiniMax Algorhytmus für den Bot.  

## Infos
Bis auf den Code in eine IDE zu kopieren und auszuführen, gibt es momentan keine möglichkeit das Spiel zu testen.  
Das Ziel des Projekts war sich mit dem MiniMax Algorhytmus auseinanderzusetzen, somit blieb sonstiges relativ rudimentär, wie beispielweise die Darstellung.  
Das Projekt ist im zeitrahmen einer woche entstanden.

## Spielanleitung

* Im menü besteht die auswahl Neues Spiel, Modus, Programm beenden.
* Spielmodi die zur verfügung stehen sind Einzelspieler-Modus und Mehrspieler-modus.
* Nach einem Spiel kehrt das programm automatisch wieder zurück zum hauptmenü.

## Animierte veranschaulichung des Minimax algorhytmus
![minimax animated](https://user-images.githubusercontent.com/105810795/191184028-6cf81603-61af-4a84-bfd7-f9d000e37150.gif)

### Genauere Beschreibung des MiniMax Algorhytmus
Bei dem Minimax Algorhytmus handelt es sich um eine rekursive funktion, also eine Funktion die sich selbst aufruft bis eine bestimmte bedingung erfüllt ist.  
Zweck dahinter ist es ein spiel zu simulieren und eine Wertung aller möglichen spielzüge zu erstellen und den besten Zug auszuwählen.
* Bedingung zur Beendung des rekursiven aufrufs => Spiel ist beendet (keine spielzüge mehr möglich oder jemand hat gewonnen)
* Innerhalb des rekursiven aufrufs wird dann eine wertung möglicher spielzüge erstellt anhand eines komplett simulierten spiels.
  * Dafür gibt es einen Maximizer der den Bot repräsentiert und dessen aufgabe es ist den zug zu wählen der die höchste wertung erreicht.
  * abwechseln tut sich das mit dem Minimizer der den gegner repräsentieren soll und dessen aufgabe es ist immer den Zug zu wählen der die Niedrigste wertung erreicht.
* Wie In der [animation](#animierte-veranschaulichung-des-minimax-algorhytmus) bereits gezeigt arbeitet sich die funktion wie eine verzweigung nach und nach ab bis eine Endbedingung erreicht wird und arbeitet sich die verzweigung dann wieder hoch mit weitergabe der wertung des zuges.

## Zur projekterstellung genutze software und resourcen

* Visual Studio community edition 2020.
* Zur recherche von Minimax wurden diverse online resourcen verwendet.
* Powerpoint zur erstellung der Animation.
