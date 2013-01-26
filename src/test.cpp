//// includes

// piet core
#include "core/pvirtualmachine.h"
#include "core/penums.h"
#include "debug.h"

// C++
#include <iostream>
#include <fstream>
#include <string>

// STL
// none

// Qt
#include <QString>

/** \file test.cpp
 * \brief Plik z kodem źródłowym aplikacji
 *
 * Plik zawiera kod źródłowy aplikacji testującej interpreter języka Piet. Program przeznaczony do użytku pod konsolą systemu Unix.
 */

/*! \mainpage Dokumentacja kodu projektu Piet
 *
 * <b>Piet</b> to graficzny język programowania autorstwa <b>Davida Morgan-Mar</b>. <b>Interpreter</b> został stworzony przez <b>Tomasza Ducina</b>. Poniższy tekst pochodzi ze wstępu do rozdziału 1, <i>"Język Piet"</i>, pracy magisterskiej Tomasza Ducina pt. <i>"Języki ezoteryczne Piet i Salvador jako uniwersalne maszyny obliczeniowe"</i>.
 *
 * Język zawdzięcza swoją nazwę imieniu malarza, Pieta Mondriana, malarza który zapoczątkował gałąź geometrycznego malarstwa abstrakcyjnego. Z założenia, programy mają przypominać obrazy malarstwa abstrakcyjnego.
 * 
 * Interpreter Pieta wyposażony jest w głowicę, która odczytuje piksle z obrazu, przesuwając się po nim. Dane przetwarzane w trakcie działania programu są umieszczane na stosie.
 *
 * Sposób pisania kodu (a szczególnie algorytmów obliczeniowych) różni się bardzo znacząco od programowania w innych językach nie tylko z powodu iż Piet jest językiem graficznym. Najważniejszymi dwiema cechami egzekucji kodu są: [1] porównywanie sąsiednich kolorów w celu wyboru instrukcji do wykonania (za pomocą głowicy) oraz [2] tzw. bloki kolorów (w których sąsiadujące piksle mają ten sam kolor). Na kod Pieta należy patrzeć „całościowo”, ogarniając kształt całości obrazu, a nie tylko dowolne niewielkie fragmenty. To jest właśnie zasadnicza różnica w sposobie programowania między Pietem i językami imperatywnymi (a również Salvadorem). W uproszczeniu, egzekucja kodu imperatywnego może wyglądać tak: „podstaw wartość pod zmienną, następnie na jej podstawie oblicz kolejne wyrażenie i podstaw pod inną zmienną. Teraz, mając przygotowane wszystkie pomocnicze wartości, sprawdzamy jedną z nich: jeśli sprawdzana wartość jest dodatnia, wykonaj blok instrukcji nr 1, jeśli ujemna, wykonaj blok nr 2, jeśli zero, wyświetl komunikat”. W językach imperatywnych mamy ściśle określoną, liniową kolejność wykonywania instrukcji, łatwo nam ją kontrolować. W Piecie natomiast kierunek w którym przesunie się głowica (czyli kolejność wykonywania instrukcji) zależy od trzech czynników: [1] aktualnego kierunku ruchu głowicy, [2] kolorów po których porusza się głowica i [3] kształtu bloków kolorów. Sprawia to, że programowanie skomplikowanych algorytmów jest stosunkowo trudne.
 *
 */
 
/**
 * Ustawia kolor czcionki konsoli Unix.
 * @param color liczba definiująca kolor czcionki pod konsolą (escape string)
 */
void setConsoleColor(int color)
{
	std::cout << "\033[" << color << "m";
}

/**
 * Wyświetla komunikat błędu na konsolę.
 * @param error tekst komunikatu błędu
 */
void printFormattedError(std::string error)
{
	setConsoleColor(31);
	std::cout << error << std::endl;
	setConsoleColor(0);
}

/**
 * Wyświetla standardowy komunikat na konsolę.
 * @param message tekst standardowego komunikatu
 */
void printFormattedMessage(std::string message)
{
	setConsoleColor(32);
	std::cout << message << std::endl;
	setConsoleColor(0);
}

/**
 * Wirtualna maszyna Pieta - globalna zmienna
 */
PVirtualMachine *m;

/**
 * Wyświetla tekst powitalny programu.
 */
void runWelcome()
{
	setConsoleColor(33);
	std::cout << std::endl;
	std::cout << "Interpreter języka Piet" << std::endl;
	std::cout << "Załącznik do pracy magisterskiej:" << std::endl;
	std::cout << "\"Graficzne języki programowania na przykładzie języków Piet i Salvador\"" << std::endl;
	std::cout << "Tomasz Ducin, 2009" << std::endl;
	setConsoleColor(0);
	std::cout << std::endl;
}

/**
 * Wyświetla menu programu, prosi użytkownika o wybór zadania i zwraca ów wybór.
 * @return numer zadania wybrany przez użytkownika
 */
int runMenu()
{
	std::cout << "wybierz opcję:" << std::endl;
	std::cout << "1. uruchom maszynę i wykonuj instrukcje krok po kroku" << std::endl;
	std::cout << "2. uruchom maszynę i wykonaj wszystkie instrukcje" << std::endl;
	std::cout << "3. włącz/wyłącz tryb gadatliwy (" << (m->isVerbose() ? "włączony" : "wyłączony" ) << ")" << std::endl;
	std::cout << "4. koniec" << std::endl;

	std::string answer;
	std::cout << std::endl << "> "; getline(std::cin, answer); std::cout << std::endl;
	while (!atoi(answer.c_str()))
	{
		std::cout << "> "; getline(std::cin, answer); std::cout << std::endl;
	}
	return atoi(answer.c_str());
}

/**
 * Główna procedura całej aplikacji. Wyświetla przywitanie, potem w pętli pobiera od użytkownika numer zadania i wykonuje je. Działanie programu zależy od decyzji użytkownika.
 */
void runProgram()
{
	// wyświetlanie informacji o programie
	runWelcome();
	// zmienne robocze sterujące pracą programu
	int continued = 1, choice;
	int final_choice = 4;
	// główna pętla programu
	while (continued)
	{
		// wyświetlanie menu programu i pobranie odpowiedzi od użytkownika
		choice = runMenu();
		// wykonanie danego zadania w zależności od odpowiedzi użytkownika
		switch (choice)
		{
			case 1: // uruchom maszynę i wykonuj instrukcje krok po kroku
				if ( m->startMachine() ) {
					printFormattedMessage("maszyna uruchomiona");
					std::string confirm_str;
					while (m->isRunning())
					{
						if ( m->executeSingleInstr() ) {
							printFormattedMessage("\r\ninstrukcja wykonana");
						} else {
							printFormattedError("błąd wykonywania instrukcji");
						}
						std::cout << "naciśnij enter"; getline(std::cin, confirm_str);
					}
				} else {
					printFormattedError("maszyna nie jest gotowa");
				}
				break;
			case 2: // uruchom maszynę i wykonaj wszystkie instrukcje
				if ( m->startMachine() ) {
					printFormattedMessage("maszyna uruchomiona");
					m->executeAllInstr();
				} else {
					printFormattedError("maszyna nie jest gotowa");
				}
				break;
			case 3: // włącz/wyłącz tryb gadatliwy
				m->toggleVerbosity();
				break;
			case 4: // koniec
				m->stopMachine();
				break;
		}
		continued = (choice != final_choice) && (m->isRunning() || m->isReady());
	}
	if (choice != final_choice)
		printFormattedMessage("\r\nPraca programu zakończona");
	else
		printFormattedError("Praca programu przerwana");
}

/**
 * Procedura wejściowa aplikacji, pośrednicząca z linią poleceń (wczytuje nazwę programu z tablicy parametrów). Tworzy wszystkie potrzebne zmienne i wywołuje runProgram().
 * @param argc liczba parametrów pobranych z komendy uruchamiającej program
 * @param argv tablica z wartościami parametrów pobranych z komendy uruchamiającej program
 */
int main(int argc, char **argv)
{
	if ( argc != 2 ) // źle wywołany program
	{
		printFormattedMessage("Podaj nazwę programu przez argument");
		return 1;
	}
	std::string STD_STR_code_path = "data/" + std::string(argv[1]);
	std::ifstream fin(STD_STR_code_path.c_str());
	if ( !fin )
	{
		printFormattedMessage("Plik nie istnieje, sprawdź przyczynę błędu i spróbuj ponownie");
		return 2;
	}
	// zmienna robocza przechowująca ścieżkę do pliku z kodem Pieta
	QString QSTR_code_path(STD_STR_code_path.c_str());
	// tworzenie wirtualnej maszyny Pieta, odpalenie aplikacji, zniszczenie maszyny
	m = new PVirtualMachine(QSTR_code_path);
	runProgram();
	m->~PVirtualMachine();
}
