#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

////////////////////////////////////////////////////////////////
//              noch zu erledigenden Aufgaben                 //
////////////////////////////////////////////////////////////////
/*
		Alles was Vorgenommen Wurde ist erledigt
*/

//Prototyping
//minimax-algorhytmus methoden
bool minimax_ZuegeNochMoeglich(char[9]);
int minimax_ZugWertung(char[9]);
int minimax_Rekursion(char[9], int, bool);
int minimax_findeBestenZug(char[9]);
//Spiel methoden
void feldZeichnen(char[9]);
void ladebalken();
int zug(char[9], int, int);
int gameover_bedingung(char[9], int);
int menu();
int mode();
void spiel(int, int, bool, char[9], int, int);

////////////////////////////////////////////////////////////////
//                       Main                                 //
////////////////////////////////////////////////////////////////

int main()
{
	char spielFeldArray[9];						//inhalt der Spielfelder
	bool gameover = false, beendet = false;		//Variablen zur beendung der Spielschleife und der Programmschleife
	int anzahlZuege = 0;						//momentaner zug
	int anfangs_spieler, spieler = 0;			//SpielerVariablen
	int modus = 1;								//Standardmaeßig spielmodus ist gegen bot (1) sonst localer multiplayer gegen einen anderen spieler.

	//zufallsgeneration des anfangsspielers
	srand(time(NULL));
	anfangs_spieler = rand() % (2);

	//felder vorläufig mit leerstelle befüllen
	for (int i = 0; i < 9; i++)
	{
		spielFeldArray[i] = ' ';
	}
	
	//spaßeshalber ein Ladebalken, des geschmacks wegen
	ladebalken();

	//menüaufruf und schlaufe bis das programm manuell beendet wird
	while (beendet == false)
	{
		//menu aufruf mit eingabeaufforderung
		int eingabe = menu();
		//Spielstart
		if (eingabe == 1)
		{
			//Spiel wird ausgefuehrt mit eingestellten modus
			spiel(spieler, anfangs_spieler, gameover, spielFeldArray, anzahlZuege, modus);
			//nach der beendung des spiels wird das spielfeld zurückgesetzt.
			for (int i = 0; i < 9; i++)
			{
				spielFeldArray[i] = ' ';
			}
		}
		//Modusauswahl
		else if (eingabe == 2)
		{
			modus = mode();
		}
		//Programm wird beendet
		else if (eingabe == 3)
		{
			beendet = true;
		}
	}
}

////////////////////////////////////////////////////////////////
//                   Minimax Anteile                          //
////////////////////////////////////////////////////////////////

bool minimax_ZuegeNochMoeglich(char feldarray[9])
{
	//Gibt true zurück falls es noch offene spielfeldstellen gibt
	for (int i = 0; i < 9; i++)
	{
		if (feldarray[i] == ' ')return true;
	}
	return false;
}

int minimax_ZugWertung(char feldarray[9])
{
	//Prüft ob einer der spieler gewonnen hat oder nicht und gibt auf grund dessen einen wert zurück
	//werte: -10 für spieler, 10 für bot, 0 für unentschieden
	
	//Horizontal victory check
	for (int i = 0; i < 9; i = i + 3)
	{
		if (feldarray[i] == feldarray[i + 1] && feldarray[i + 1] == feldarray[i + 2] && feldarray[i] == 'X')
		{
			if (feldarray[i] == 'X')return 10;
		}
	}

	//Vertikal victory check
	for (int i = 0; i < 9; i++)
	{
		if (feldarray[i] == feldarray[i + 3] && feldarray[i + 3] == feldarray[i + 6] && feldarray[i] == 'X')
		{
			if (feldarray[i] == 'X')return 10;
		}
	}

	//Diagonal victory check
	if (feldarray[0] == feldarray[4] && feldarray[4] == feldarray[8] && feldarray[0] == 'X')
	{
		if (feldarray[0] == 'X')return 10;
	}
	if (feldarray[2] == feldarray[4] && feldarray[4] == feldarray[6] && feldarray[2] == 'X')
	{
		if (feldarray[2] == 'X')return 10;
	}

	//Horizontal victory check
	for (int i = 0; i < 9; i = i + 3)
	{
		if (feldarray[i] == feldarray[i + 1] && feldarray[i + 1] == feldarray[i + 2] && feldarray[i] == 'O')
		{
			if (feldarray[i] == 'O')return -10;
		}
	}

	//Vertikal victory check
	for (int i = 0; i < 9; i++)
	{
		if (feldarray[i] == feldarray[i + 3] && feldarray[i + 3] == feldarray[i + 6] && feldarray[i] == 'O')
		{
			if (feldarray[i] == 'O')return -10;
		}
	}

	//Diagonal victory check
	if (feldarray[0] == feldarray[4] && feldarray[4] == feldarray[8] && feldarray[0] == 'O')
	{
		if (feldarray[0] == 'O')return -10;
	}
	if (feldarray[2] == feldarray[4] && feldarray[4] == feldarray[6] && feldarray[2] == 'O')
	{
		if (feldarray[2] == 'O')return -10;
	}

	return 0;
}

int minimax_Rekursion(char feldarray[9], int depth, bool isMax)
{
	//ruft recursiv die minimax_Recursion's methode auf solange bis die Endbedingungen erreicht sind
	
	//Wert nach dem die züge gemessen werden
	int score = minimax_ZugWertung(feldarray);

	//Werte werden zurückgegeben wenn alle züge ausgeschöpft wurden
	if (score == 10)return score;
	if (score == -10)return score;
	if (minimax_ZuegeNochMoeglich(feldarray) == false)return 0;

	if (isMax)
	{
		int best = -1000;

		for (int i = 0; i < 9; i++)
		{
			if (feldarray[i] == ' ')
			{
				feldarray[i] = 'X';
				best = max(best, minimax_Rekursion(feldarray, depth + 1, !isMax));
				feldarray[i] = ' ';
			}
		}
		return best;
	}
	else
	{
		int best = 1000;

		for (int i = 0; i < 9; i++)
		{
			if (feldarray[i] == ' ')
			{
				feldarray[i] = 'O';
				best = min(best, minimax_Rekursion(feldarray, depth + 1, !isMax));
				feldarray[i] = ' ';
			}
		}
		return best;
	}
}

int minimax_findeBestenZug(char feldarray[9])
{
	int bestVal = -1000;
	int bestMove = -1;

	for (int i = 0; i < 9; i++)
	{
		if (feldarray[i] == ' ')
		{
			feldarray[i] = 'X';
			int moveVal = minimax_Rekursion(feldarray, 0, false);
			feldarray[i] = ' ';

			if (moveVal > bestVal)
			{
				bestMove = i;
				bestVal = moveVal;
			}
		}
	}
	return bestMove;
}

////////////////////////////////////////////////////////////////
//                   SpielMethoden                            //
////////////////////////////////////////////////////////////////

void feldZeichnen(char feldarray[9])
{
	//Spielfelderstellung mit arrayvariablen
	cout << "\n\n"
		<< "\t" << "-------------" << endl
		<< "\t" << "| " << feldarray[0] << " | " << feldarray[1] << " | " << feldarray[2] << " |" << endl
		<< "\t" << "|---|---|---|" << endl
		<< "\t" << "| " << feldarray[3] << " | " << feldarray[4] << " | " << feldarray[5] << " |" << endl
		<< "\t" << "|---|---|---|" << endl
		<< "\t" << "| " << feldarray[6] << " | " << feldarray[7] << " | " << feldarray[8] << " |" << endl
		<< "\t" << "-------------" << endl
		<< "\n\n";
}

void ladebalken()
{
	//Erstellt einen ladebalken aus style gründen
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		//Pause von sekunden (1000 = 1 sekunde)
		Sleep(100);
	}
	system("cls");
}

int zug(char feldarray[9], int spieler, int modus)
{
	//EingabeAuforderung an Spieler

	int eingabe = -1;

	if (spieler == 1)	//spieler eins mit O Zeichen
	{
		while (eingabe < 1 || eingabe > 9 || feldarray[eingabe - 1] != ' ')
		{
			cout << "Geben sie das feld was sie beschreiben wollen an (1-9): "; cin >> eingabe; cout << endl;
			if (eingabe < 1 || eingabe > 9) cout << "Eingabe muss von 1 bis 9 sein." << endl;
			if (feldarray[eingabe - 1] != ' ') cout << "Feld ist bereits befuellt." << endl;
		}
		feldarray[eingabe - 1] = 'O';
	}
	else if (spieler == -1)	//spieler 2
	{
		if (modus == 1)feldarray[minimax_findeBestenZug(feldarray)] = 'X';	//falls es sich um ein spielmodus mit bot handelt
		else
		{	//sonst Spieler 2 Mit X Zeichen
			while (eingabe < 1 || eingabe > 9 || feldarray[eingabe - 1] != ' ')
			{
				cout << "Geben sie das feld was sie beschreiben wollen an (1-9): "; cin >> eingabe; cout << endl;
				if (eingabe < 1 || eingabe > 9) cout << "Eingabe muss von 1 bis 9 sein." << endl;
				if (feldarray[eingabe - 1] != ' ') cout << "Feld ist bereits befuellt." << endl;
			}
			feldarray[eingabe - 1] = 'X';
		}
	}
	else cout << "Es ist ein Fehler bei der Spieler zugwahl aufgetreten." << endl;
	system("CLS");
	feldZeichnen(feldarray);

	spieler = spieler * (-1);	//nach spielzug wird aktiver spieler ausgewechselt
	return spieler;
}

int gameover_bedingung(char feldarray[9], int playerturn)
{
	int gameover = 2;
	playerturn = playerturn * (-1);
	char spieler;

	//nach welchem spieler geprüft wird.
	if (playerturn == 1)spieler = 'O';
	else if (playerturn == -1)spieler = 'X';
	else cout << "Es ist ein fehler bei der gameover_bedingung spielerentscheidung passiert." << endl;

	if (gameover == 2)
	{
		for (int i = 0; i <= 2; i++)
		{
			//Vertikaler check
			if (feldarray[i] == spieler && feldarray[i + 3] == spieler && feldarray[i + 6] == spieler)
			{
				if (spieler == 'O')gameover = 1;
				else gameover = -1;
				break;
			}
		}
	}
	if (gameover == 2)
	{
		for (int i = 0; i < 7; i = i + 3)
		{
			//Horizontaler check
			if (feldarray[i] == spieler && feldarray[i + 1] == spieler && feldarray[i + 2] == spieler)
			{
				if (spieler == 'O')gameover = 1;
				else gameover = -1;
				break;
			}
		}
	}
	if (gameover == 2)
	{
		//diagonaler check
		if (feldarray[0] == spieler && feldarray[4] == spieler && feldarray[8] == spieler)
		{
			if (spieler == 'O')gameover = 1;
			else gameover = -1;
		}
		if (feldarray[2] == spieler && feldarray[4] == spieler && feldarray[6] == spieler)
		{
			if (spieler == 'O')gameover = 1;
			else gameover = -1;
		}
	}
	if (gameover == 2)
	{
		//unentschieden
		//Checkt ob alle felder befüllt worden und es keinen gewinner gibt
		for (int i = 0; i < 9; i++)
		{
			if (feldarray[i] == ' ')
			{
				gameover = 2;
				break;
			}
			else
			{
				gameover = 0;
			}
		}
	}

	return gameover;
}

int menu()
{
	int eingabe;
	cout << "(1) Neues Spiel" << endl
		<< "(2) Modus" << endl
		<< "(3) Spiel beenden" << endl
		<< "Eingabe: ";
	cin >> eingabe;
	system("cls");

	return eingabe;
}

int mode()
{
	int eingabe;
	cout << "(1) Singleplayer" << endl
		<< "(2) Multiplayer" << endl
		<< "Eingabe: ";
	cin >> eingabe;
	system("cls");
	if (eingabe == 1)cout << "Singleplayer modus ausgewaehlt." << endl;
	if (eingabe == 2)cout << "Multiplayer modus ausgewaehlt." << endl;
	system("pause");
	system("cls");

	return eingabe;
}

void spiel(int spieler, int anfangs_spieler, bool gameover, char feldarray[9], int turn, int modus)
{
	if (anfangs_spieler == 0)
	{
		if (modus == 1)
		{
			cout << "Sie fangen an." << endl;
			spieler = 1;
		}
		else
		{
			cout << "Spieler 1 faengt an." << endl;
			spieler = 1;
		}
	}
	if (anfangs_spieler == 1)
	{
		if (modus == 1)
		{
			cout << "Pc faengt an." << endl;
			spieler = -1;
		}
		else
		{
			cout << "Spieler 2 faengt an." << endl;
			spieler = -1;
		}
	}
	system("pause");
	system("CLS");

	cout << "" << endl;
	//Aufruf der Felderstellung
	while (gameover == false) //solange das spiel nicht beendet ist
	{
		feldZeichnen(feldarray);
		spieler = zug(feldarray, spieler, modus);
		if (gameover_bedingung(feldarray, spieler) != 2)gameover = true;
		turn = turn + 1;
		if (gameover == true)
		{
			cout << "Game Over" << endl;
			if (gameover_bedingung(feldarray, spieler) == 1)
			{
				if (modus == 1)cout << "Sie haben gewonnen." << endl;
				else cout << "Spieler 1 hat gewonnen." << endl;
			}
			else if (gameover_bedingung(feldarray, spieler) == -1)
			{
				if (modus == 1)cout << "Bot hat gewonnen." << endl;
				else cout << "Spieler 2 hat gewonnen." << endl;
			}
			else if (gameover_bedingung(feldarray, spieler) == 0)
			{
				cout << "Unentschieden." << endl;
			}
			system("pause");
			break;
		}
		Sleep(100);

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });	//console wird nur überschrieben nicht gelöscht

		//system("pause");
	}
}

////////////////////////////////////////////////////////////////
//                Manuelle BotMethoden                        //
////////////////////////////////////////////////////////////////
//
//		zugErmittlung wird momentan nicht genutzt
//		bot beinhaltet vorige version von einem bot und ruft moment nur die Minimaxx methode auf.

bool zugErmittlung(char symbol, char feldarray[9], bool zugermittelt)
{
//	//horizontal
//	if (zugermittelt == false)
//	{
//		for (int i = 0; i < 9; i = i + 3)
//		{
//			if (feldarray[i] == symbol && feldarray[i + 1] == symbol && feldarray[i + 2] == ' ')
//			{
//				feldarray[i + 2] = 'X';
//				zugermittelt = true;
//				break;
//			}
//			if (feldarray[i + 1] == symbol && feldarray[i + 2] == symbol && feldarray[i] == ' ')
//			{
//				feldarray[i] = 'X';
//				zugermittelt = true;
//				break;
//			}
//			if (feldarray[i] == symbol && feldarray[i + 2] == symbol && feldarray[i + 1] == ' ')
//			{
//				feldarray[i + 1] = 'X';
//				zugermittelt = true;
//				break;
//			}
//		}
//	}
//	//vertikal
//	if (zugermittelt == false)
//	{
//		for (int i = 0; i < 9; i++)
//		{
//			if (feldarray[i] == symbol && feldarray[i + 3] == symbol && feldarray[i + 6] == ' ')
//			{
//				feldarray[i + 6] = 'X';
//				zugermittelt = true;
//				break;
//			}
//			if (feldarray[i + 3] == symbol && feldarray[i + 6] == symbol && feldarray[i] == ' ')
//			{
//				feldarray[i] = 'X';
//				zugermittelt = true;
//				break;
//			}
//			if (feldarray[i] == symbol && feldarray[i + 6] == symbol && feldarray[i + 3] == ' ')
//			{
//				feldarray[i + 3] = 'X';
//				zugermittelt = true;
//				break;
//			}
//		}
//	}
//	//diagonal
//	if (zugermittelt == false)
//	{
//		if (feldarray[0] == symbol && feldarray[4] == symbol && feldarray[8] == ' ')
//		{
//			feldarray[8] = 'X';
//			zugermittelt = true;
//		}
//		else if (feldarray[0] == symbol && feldarray[8] == symbol && feldarray[4] == ' ')
//		{
//			feldarray[4] = 'X';
//			zugermittelt = true;
//		}
//		else if (feldarray[4] == symbol && feldarray[8] == symbol && feldarray[0] == ' ')
//		{
//			feldarray[0] = 'X';
//			zugermittelt = true;
//		}
//		else if (feldarray[2] == symbol && feldarray[4] == symbol && feldarray[6] == ' ')
//		{
//			feldarray[6] = 'X';
//			zugermittelt = true;
//		}
//		else if (feldarray[4] == symbol && feldarray[6] == symbol && feldarray[2] == ' ')
//		{
//			feldarray[2] = 'X';
//			zugermittelt = true;
//		}
//		else if (feldarray[2] == symbol && feldarray[6] == symbol && feldarray[4] == ' ')
//		{
//			feldarray[8] = 'X';
//			zugermittelt = true;
//		}
//	}
//	return zugermittelt;
}

void bot(char feldarray[9], int spieler)
{
	//bool ersterZug = false;
	//bool zugermittelt = false;
	//int zug = -1;

	////ersterZug
	//for (int i = 0; i < 9; i++)
	//{
	//	if (feldarray[i] != ' ')
	//	{
	//		ersterZug = false;
	//		break;
	//	}
	//	else ersterZug = true;
	//}
	//if (ersterZug == true)
	//{
	//	feldarray[4] = 'X';
	//	zugermittelt = true;
	//}
	//if (zugermittelt == false)
	//{	//gewinnzug spielen
	//	zugermittelt = zugErmittlung('X', feldarray, zugermittelt);
	//}
	//if (zugermittelt == false)
	//{
	//	//Verliererzug verhindern
	//	zugermittelt = zugErmittlung('O', feldarray, zugermittelt);
	//}
	//if (zugermittelt == false)
	//{
	//	while (feldarray[zug] != ' ')
	//	{
	//		zug = rand() % (9) + 1;
	//	}
	//	feldarray[zug] = 'X';
	//}

	//Aufruf der Minimx methode zur Ermittlung des besten zuges.
	feldarray[minimax_findeBestenZug(feldarray)] = 'X';
}
