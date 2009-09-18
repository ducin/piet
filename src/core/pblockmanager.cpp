//// includes

// header file
#include "pblockmanager.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"
#include "pcodepointer.h"

// C++
#include <iostream>

// STL
// none

// Qt
#include <QImage>
#include <QRgb>

/** \file pblockmanager.cpp
 * \brief Plik z kodem źródłowym klasy PBlockManager
 *
 * Plik zawiera kod źródłowy klasy PBlockManager.
 */

/** 
 * Konstruktor menadżera bloków. Pobiera informacje o obrazie z których będzie korzystał za każdym razem gdy wirtualna maszyna będzie chciała wykonać jakąkolwiek instrukcję. Ponadto, alokuje pamięć pod 2-wymiarową tablicę pomocniczą służącą do obliczania ilości kodeli w danym bloku koloru.
 */
PBlockManager::PBlockManager(QImage *given_image, PCodePointer *given_pointer)
{
	debug("CONSTRUCTOR ----- block-manager START\n");
	verbose = false;
	image = given_image;
	pointer = given_pointer;
	height = image->height();
	width = image->width();
	allocateMultiArray();
	debug("CONSTRUCTOR ----- block-manager END\n");
}

/**
 * Destruktor menadżera bloków. Dealokouje pamięć przeznaczoną dla 2-wymiarowej tablicy pomocniczej służącej do obliczania ilości kodeli w danym bloku koloru.
 */
PBlockManager::~PBlockManager()
{
	debug("DESTRUCTOR ----- block-manager START\n");
	deallocateMultiArray();
	debug("DESTRUCTOR ----- block-manager END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void PBlockManager::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

//==================================================================
// zarządzanie pomocniczą 2-wymiarową tablicą

/**
 * Przydziela pamięć pod 2-wymiarową tablicę pomocniczą służącą do obliczenia ilości kodeli w bloku koloru. Metoda wywoływana tylko raz, w konstruktorze. Tablica ta, używana wielokrotnie, jest czyszczona, nie tworzy się jej od nowa przy każdym użyciu.
 */
void PBlockManager::allocateMultiArray()
{
	fields = new int *[height];
	for (int i=0; i<height; i++) {
		fields[i] = new int[width];
	}
}

/**
 * Zwalnia pamięć używaną przez 2-wymiarową tablicę pomocniczą. Metoda wywoływana tylko raz, w destruktorze.
 */
void PBlockManager::deallocateMultiArray()
{
	for (int i=0; i<height; i++) {
		delete fields[i];
	}
	delete [] fields;
}

/**
 * Metoda wstawia zadaną wartość do kodeli w 2-wymiarowej tablicy pomocniczej.
 */
void PBlockManager::fillMultiArray(int value)
{
	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			fields[i][j] = value;
		}
	}
}

// Metoda, używając metody fillMultiArray (wypełniając zerami) czyści 2-wymiarową tablicę pomocniczą. Oznacza to, że każdy z kodeli jest niesprawdzony, a cała tablica gotowa do ponownego użycia.
/**
 * Przydziela pamięć pod 2-wymiarową tablicę pomocniczą służącą do obliczenia ilości kodeli w bloku koloru. Metoda wywoływana tylko raz, w konstruktorze. Tablica ta, używana wielokrotnie, jest czyszczona, nie tworzy się jej od nowa przy każdym użyciu.
 */
void PBlockManager::clearMultiArray()
{
	fillMultiArray(0);
	codel_block_count = 0;
	border_right_codel = 0;
	border_down_codel = 0;
	border_left_codel = 0;
	border_up_codel = 0;
}


//==================================================================
// oznaczanie i obliczanie liczby kodeli w bloku kolorów

// Rekursywna metoda oznaczająca wszystkie kodele które są tego samego koloru co zadany parametrem kolor oraz są sąsiadujące z pierwszym, oryginalnym kodelem (co jest właściwie formalną definicją bloku kolorów). Kodel spełniający warunek (ten sam kolor co zadany parametrem kolor) jest zaznaczany jako '1'. Kolor inny - '2', kodel niesprawdzony - pozostaje '0' (ma to miejsce, gdy blok kolorów został "odgrodzony" kodelami innych kolorów - wówczas nie jest zachowany warunek sąsiadowania kodeli).
void PBlockManager::reqCrawlMultiArray(QRgb seedColor, PPoint seedPoint)
{
	PPoint tmpPoint; // zmienne tymczasowe używane do określenia współrzędnych ewentualnych sąsiednich kodeli (sąsiadnich dla zadanego, badanego aktualnie kodela), zostaną użyte jeśli aktualnie badany kodel spełni warunek (ten sam kolor co zadany parametrem).
	if (image->pixel(seedPoint.x, seedPoint.y) == seedColor) { // aktualnie sprawdzany kodel spełnia warunek
		fields[seedPoint.y][seedPoint.x] = 1; // oznacz go '1' (że spełnia warunek)

		// i sprawdź jego wszystkie 4 sąsiednie punkty (pion, poziom, nie skos)
		// podstaw pod robocze zmienne współrzędne hipotetycznego kodela
		// sprawdź czy mieści się w rysunku i czy nie został już oznaczony
		// jeśli powyższe warunki spełnione, wywołaj rekursywnie tą samą metodę dla nowego kodela

		tmpPoint.x = seedPoint.x; tmpPoint.y = seedPoint.y + 1;
		if (!pointer->pointOutsideImage(tmpPoint) && fields[tmpPoint.y][tmpPoint.x] == 0) {
			reqCrawlMultiArray(seedColor, tmpPoint);
		}

		tmpPoint.x = seedPoint.x; tmpPoint.y = seedPoint.y - 1;
		if (!pointer->pointOutsideImage(tmpPoint) && fields[tmpPoint.y][tmpPoint.x] == 0) {
			reqCrawlMultiArray(seedColor, tmpPoint);
		}

		tmpPoint.x = seedPoint.x + 1; tmpPoint.y = seedPoint.y;
		if (!pointer->pointOutsideImage(tmpPoint) && fields[tmpPoint.y][tmpPoint.x] == 0) {
			reqCrawlMultiArray(seedColor, tmpPoint);
		}

		tmpPoint.x = seedPoint.x - 1; tmpPoint.y = seedPoint.y;
		if (!pointer->pointOutsideImage(tmpPoint) && fields[tmpPoint.y][tmpPoint.x] == 0) {
			reqCrawlMultiArray(seedColor, tmpPoint);
		}
	} else {
		fields[seedPoint.y][seedPoint.x] = 2; // oznacz, że kodel ma inny kolor niż zadany parametrem
	}
}

/**
 * Metoda zlicza liczbę kodeli w pomocniczej 2-wymiarowej tabeli (która została właśnie sprawdzona) oznaczonych '1', czyli kodeli spełniających warunek (ten sam kolor co kolor zadany).
 */
void PBlockManager::countCodels()
{
	int count = 0;
	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			if (fields[i][j] == 1) count++;
		}
	}
	codel_block_count = count;
}

/**
 * Metoda zwraca liczbę kodeli w bloku koloru wskazywanym przez zadane parametrami współrzędne. Najbardziej zewnętrzna metoda całego mechanizmu, używa wielu innych metod.
 @return rozmiar bloku koloru
 */
int PBlockManager::getCodelBlockCount()
{
	return codel_block_count; // zwracanie liczby kodeli, przechowywanej w osobnym polu obiektu
}

/**
 * Metoda oznacza odpowiednimi wartościami ('1' lub '2') kodele na pomocniczej 2-wymiarowej tablicy i na koniec zlicza liczbę kodeli.
 */
void PBlockManager::searchAndFillCodels()
{
	clearMultiArray(); // przygotuj tablicę aby można było na niej nanosić oznaczenia (wyzeruj)
	reqCrawlMultiArray(pointer->getPointedPixel(), pointer->getCoordinates()); // rekursywne oznaczanie kodeli
	countCodels();
	findBorderCodels();
}

//==================================================================

int PBlockManager::findRowMostLeftCodel(int row)
{
	int column = 0;
	while ( fields[row][column] != 1 )
		column++;
	return column;
}

int PBlockManager::findRowMostRightCodel(int row)
{
	int column = width - 1;
	while ( fields[row][column] != 1 )
		column--;
	return column;
}

int PBlockManager::findColumnTopCodel(int column)
{
	int row = 0;
	while ( fields[row][column] != 1 )
		row++;
	return row;
}

int PBlockManager::findColumnBottomCodel(int column)
{
	int row = height - 1;
	while ( fields[row][column] != 1 )
		row--;
	return row;
}

//
void PBlockManager::findBorderCodels()
{
	bool found = false;
	int h;
	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			if (fields[i][j] == 1) {
				h = i;
				if ( !found) {
					found = true;
					border_up_codel = i;
					border_right_codel = j;
					border_left_codel = j;
				}
				if ( j < border_left_codel) {
					border_left_codel = j;
				}
				if ( j > border_right_codel) {
					border_right_codel = j;
				}
			}
		}
	}
	border_down_codel = h;
}

/**
 * Wyznacza współrzędne punktu sąsiadującego bloku kolorów, od którego przesunie się głowica przy aktualnych wartościach DP i CC.
 * @return współrzedne punktu
 */
PPoint PBlockManager::getNextPossibleCodel()
{
	PPoint new_point;
	PPoint actual_point = pointer->getCoordinates();
	// w zależności od wartości DIRECTION POINTER
	switch( pointer->getDirectionPointerValue() ) {
	// dla każdego z 4 kierunków sprawdź wartość CODEL CHOOSER
	// i na tej podstawie jednoznacznie określ nowego kodela (z następnego bloku)
		case dp_right:
			switch ( pointer->getCodelChooserValue() ) {
				case cc_left:
					// dp = prawo, cc = lewo, kierunek = skrajny górny
					new_point.y = findColumnTopCodel(border_right_codel);
					break;
				case cc_right:
					// dp = prawo, cc = prawo, kierunek = skrajny dolny
					new_point.y = findColumnBottomCodel(border_right_codel);
					break;
			}
			new_point.x = border_right_codel + 1;
			break;
		case dp_down:
			switch ( pointer->getCodelChooserValue() ) {
				case cc_left:
					// dp = dół, cc = lewo, kierunek = skrajny prawy
					new_point.x = findRowMostRightCodel(border_down_codel);
					break;
				case cc_right:
					// dp = dół, cc = prawo, kierunek = skrajny lewy
					new_point.x = findRowMostLeftCodel(border_down_codel);
					break;
			}
			new_point.y = border_down_codel + 1;
			break;
		case dp_left:
			switch ( pointer->getCodelChooserValue() ) {
				case cc_left:
					// dp = lewo, cc = lewo, kierunek = skrajny dolny
					new_point.y = findColumnBottomCodel(border_left_codel);
					break;
				case cc_right:
					// dp = lewo, cc = prawo, kierunek = skrajny górny
					new_point.y = findColumnTopCodel(border_left_codel);
					break;
			}
			new_point.x = border_left_codel - 1;
			break;
		case dp_up:
			switch ( pointer->getCodelChooserValue() ) {
				case cc_left:
					// dp = góra, cc = lewo, kierunek = skrajny lewy
					new_point.x = findRowMostLeftCodel(border_up_codel);
					break;
				case cc_right:
					// dp = góra, cc = prawo, kierunek = skrajny prawy
					new_point.x = findRowMostRightCodel(border_up_codel);
					break;
			}
			new_point.y = border_up_codel - 1;
			break;
		default:
			std::cout << "ERROR: PPoint PBlockManager::getNextPossibleCodel()" << std::endl;
			exit(1);
	}
	return new_point;
}

//==================================================================

/**
 * METODA TESTOWA. Metoda wyświetla na stdout 2-wymiarową tablicę pomocniczą.
 */
void PBlockManager::__dev__showMultiArray()
{
	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			std::cout << "[" << fields[i][j] << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/**
 * METODA TESTOWA. Metoda wyświetla liczbę kodeli w aktualym bloku kolorów oraz skrajne kodele.
 */
void PBlockManager::__dev__showCountAndBorderCodels()
{
	std::cout << "kodele:" << codel_block_count;
	std::cout << ",graniczne: right=" << border_right_codel << " down=" << border_down_codel << " left=" << border_left_codel << " up=" << border_up_codel << std::endl;
}
