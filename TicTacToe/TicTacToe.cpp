// TicTacToe


// !!! noch zu erledigenden Aufgaben !!!
// Keine, alles erledigt was ich mir vorgenommen hatte

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

//Prototyping
bool minimax_isMovesLeft(char[9]);			//minimax-algorhytmus methoden
int minimax_evaluate(char[9]);
int minimax_minimax(char[9], int, bool);
int minimax_findBestMove(char[9]);
void feldZeichnen(char[9]);					//Spiel methoden
void ladebalken();
int zug(char[9], int, int);
int gameover_bedingung(char[9], int);
int menu();
int mode();
void spiel(int, int, bool, char[9], int, int);
bool zugErmittlung(char, char[9], bool);	//bot methoden
void bot(char[9], int);

int main()
{
	char feldarray[9];
	bool gameover = false, beendet = false;
	int turn = 0;
	int anfangs_spieler, spieler = 0;
	int modus = 1;

	//zufallsgeneration des anfangsspielers
	srand(time(NULL));
	anfangs_spieler = rand() % (2);

	//felder vorläufig mit leerstelle befüllen
	for (int i = 0; i < 9; i++)
	{
		feldarray[i] = ' ';
	}
	
	//spaßeshalber
	ladebalken();

	//menüaufruf und schlaufe bis das programm manuell beendet wird
	while (beendet == false)
	{
		int eingabe = menu();
		//Spielstart
		if (eingabe == 1)
		{
			spiel(spieler, anfangs_spieler, gameover, feldarray, turn, modus);
			for (int i = 0; i < 9; i++)
			{
				feldarray[i] = ' ';
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

bool minimax_isMovesLeft(char feldarray[9])
{
	//Gibt true zurück falls es noch offene stellen gibt
	for (int i = 0; i < 9; i++)
	{
		if (feldarray[i] == ' ')return true;
	}
	return false;
}

int minimax_evaluate(char feldarray[9])
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

int minimax_minimax(char feldarray[9], int depth, bool isMax)
{
	//Wert nach dem die züge gemessen werden
	int score = minimax_evaluate(feldarray);

	//Werte werden zurückgegeben wenn alle züge ausgeschöpft wurden
	if (score == 10)return score;
	if (score == -10)return score;
	if (minimax_isMovesLeft(feldarray) == false)return 0;

	if (isMax)
	{
		int best = -1000;

		for (int i = 0; i < 9; i++)
		{
			if (feldarray[i] == ' ')
			{
				feldarray[i] = 'X';
				best = max(best, minimax_minimax(feldarray, depth + 1, !isMax));
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
				best = min(best, minimax_minimax(feldarray, depth + 1, !isMax));
				feldarray[i] = ' ';
			}
		}
		return best;
	}
}

int minimax_findBestMove(char feldarray[9])
{
	int bestVal = -1000;
	int bestMove = -1;

	for (int i = 0; i < 9; i++)
	{
		if (feldarray[i] == ' ')
		{
			feldarray[i] = 'X';
			int moveVal = minimax_minimax(feldarray, 0, false);
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

void feldZeichnen(char feldarray[9])
{
	//Felderstellung mit arrayvariablen
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
	for (int i = 0; i < 10; i++)
	{
		cout << ".";
		//Pause von sekunden (1000 = 1 sekunde)
		Sleep(100);
	}
	system("cls");
}

bool zugErmittlung(char symbol, char feldarray[9], bool zugermittelt)
{
	//horizontal
	if (zugermittelt == false)
	{
		for (int i = 0; i < 9; i = i + 3)
		{
			if (feldarray[i] == symbol && feldarray[i + 1] == symbol && feldarray[i + 2] == ' ')
			{
				feldarray[i + 2] = 'X';
				zugermittelt = true;
				break;
			}
			if (feldarray[i + 1] == symbol && feldarray[i + 2] == symbol && feldarray[i] == ' ')
			{
				feldarray[i] = 'X';
				zugermittelt = true;
				break;
			}
			if (feldarray[i] == symbol && feldarray[i + 2] == symbol && feldarray[i + 1] == ' ')
			{
				feldarray[i + 1] = 'X';
				zugermittelt = true;
				break;
			}
		}
	}
	//vertikal
	if (zugermittelt == false)
	{
		for (int i = 0; i < 9; i++)
		{
			if (feldarray[i] == symbol && feldarray[i + 3] == symbol && feldarray[i + 6] == ' ')
			{
				feldarray[i + 6] = 'X';
				zugermittelt = true;
				break;
			}
			if (feldarray[i + 3] == symbol && feldarray[i + 6] == symbol && feldarray[i] == ' ')
			{
				feldarray[i] = 'X';
				zugermittelt = true;
				break;
			}
			if (feldarray[i] == symbol && feldarray[i + 6] == symbol && feldarray[i + 3] == ' ')
			{
				feldarray[i + 3] = 'X';
				zugermittelt = true;
				break;
			}
		}
	}
	//diagonal
	if (zugermittelt == false)
	{
		if (feldarray[0] == symbol && feldarray[4] == symbol && feldarray[8] == ' ')
		{
			feldarray[8] = 'X';
			zugermittelt = true;
		}
		else if (feldarray[0] == symbol && feldarray[8] == symbol && feldarray[4] == ' ')
		{
			feldarray[4] = 'X';
			zugermittelt = true;
		}
		else if (feldarray[4] == symbol && feldarray[8] == symbol && feldarray[0] == ' ')
		{
			feldarray[0] = 'X';
			zugermittelt = true;
		}
		else if (feldarray[2] == symbol && feldarray[4] == symbol && feldarray[6] == ' ')
		{
			feldarray[6] = 'X';
			zugermittelt = true;
		}
		else if (feldarray[4] == symbol && feldarray[6] == symbol && feldarray[2] == ' ')
		{
			feldarray[2] = 'X';
			zugermittelt = true;
		}
		else if (feldarray[2] == symbol && feldarray[6] == symbol && feldarray[4] == ' ')
		{
			feldarray[8] = 'X';
			zugermittelt = true;
		}
	}
	return zugermittelt;
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

	feldarray[minimax_findBestMove(feldarray)] = 'X';
}

int zug(char feldarray[9], int spieler, int modus)
{
	int eingabe = -1;

	if (spieler == 1)
	{
		while (eingabe < 1 || eingabe > 9 || feldarray[eingabe - 1] != ' ')
		{
			cout << "Geben sie das feld was sie beschreiben wollen an (1-9): "; cin >> eingabe; cout << endl;
			if (eingabe < 1 || eingabe > 9) cout << "Eingabe muss von 1 bis 9 sein." << endl;
			if (feldarray[eingabe - 1] != ' ') cout << "Feld ist bereits befuellt." << endl;
		}
		feldarray[eingabe - 1] = 'O';
	}
	else if (spieler == -1)
	{
		if (modus == 1)bot(feldarray, spieler);
		else
		{
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

	spieler = spieler * (-1);
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