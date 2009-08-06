//// includes

// header file
#include "pblockmanager.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pcodepointer.h"

// C++
#include <iostream>

// STL
// none

// Qt
#include <QImage>
#include <QRgb>

/** \brief konstruktor klasy PBlockManager
 *
 * xyz...
 */
PBlockManager::PBlockManager(QImage *given_image, PCodePointer *given_pointer)
{
	debug("CONSTRUCTOR ----- block-manager START\n");
	image = given_image;
	pointer = given_pointer;
	height = image->height();
	width = image->width();
	allocateMultiArray();
	debug("CONSTRUCTOR ----- block-manager END\n");
}

/** \brief destruktor
 *
 * abc...
 */
PBlockManager::~PBlockManager()
{
	debug("DESTRUCTOR ----- block-manager START\n");
	deallocateMultiArray();
	debug("DESTRUCTOR ----- block-manager END\n");
}

//==================================================================
// zarządzanie pomocniczą 2-wymiarową tablicą

// przydziela pamięć pod 2-wymiarową tablicę pomocniczą służącą do obliczenia ilości kodeli w bloku koloru. Metoda wywoływana tylko raz, w konstruktorze. Tablica ta, używana wielokrotnie, jest czyszczona, nie tworzy się jej od nowa przy każdym użyciu.
void PBlockManager::allocateMultiArray()
{
	fields = new int *[height];
	for (int i=0; i<height; i++) {
		fields[i] = new int[width];
	}
}

// zwalnia pamięć używaną przez 2-wymiarową tablicę pomocniczą. Metoda wywoływana tylko raz, w destruktorze.
void PBlockManager::deallocateMultiArray()
{
	for (int i=0; i<height; i++) {
		delete fields[i];
	}
	delete [] fields;
}

// Metoda wstawia zadaną wartość do kodeli w 2-wymiarowej tablicy pomocniczej.
void PBlockManager::fillMultiArray(int value)
{
	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			fields[i][j] = value;
		}
	}
}

// Metoda, używając metody fillMultiArray (wypełniając zerami) czyści 2-wymiarową tablicę pomocniczą. Oznacza to, że każdy z kodeli jest niesprawdzony, a cała tablica gotowa do ponownego użycia.
void PBlockManager::clearMultiArray()
{
	fillMultiArray(0);
}


//==================================================================
// oznaczanie i obliczanie liczby kodeli w bloku kolorów

// Metoda determinuje, czy punkt o zadanych współrzędnych mieści się w obrazie kodu.
bool PBlockManager::pixelInsideImage(int x, int y)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

// Rekursywna metoda oznaczająca wszystkie kodele które są tego samego koloru co zadany parametrem kolor oraz są sąsiadujące z pierwszym, oryginalnym kodelem (co jest właściwie formalną definicją bloku kolorów). Kodel spełniający warunek (ten sam kolor co zadany parametrem kolor) jest zaznaczany jako '1'. Kolor inny - '2', kodel niesprawdzony - pozostaje '0' (ma to miejsce, gdy blok kolorów został "odgrodzony" kodelami innych kolorów - wówczas nie jest zachowany warunek sąsiadowania kodeli).
void PBlockManager::reqCrawlMultiArray(QRgb color, int x, int y)
{
	int tmpX, tmpY; // zmienne tymczasowe używane do określenia współrzędnych ewentualnych sąsiednich kodeli (sąsiadnich dla zadanego, badanego aktualnie kodela), zostaną użyte jeśli aktualnie badany kodel spełni warunek (ten sam kolor co zadany parametrem).
	if (image->pixel(x, y) == color) { // aktualnie sprawdzany kodel spełnia warunek
		fields[y][x] = 1; // oznacz go '1' (że spełnia warunek)

		// i sprawdź jego wszystkie 4 sąsiednie punkty (pion, poziom, nie skos)
		// podstaw pod robocze zmienne współrzędne hipotetycznego kodela
		// sprawdź czy mieści się w rysunku i czy nie został już oznaczony
		// jeśli powyższe warunki spełnione, wywołaj rekursywnie tą samą metodę dla nowego kodela

		tmpX = x; tmpY = y+1;
		if (pixelInsideImage(tmpX, tmpY) && fields[tmpY][tmpX] == 0) {
			reqCrawlMultiArray(color, tmpX, tmpY);
		}

		tmpX = x; tmpY = y-1;
		if (pixelInsideImage(tmpX, tmpY) && fields[tmpY][tmpX] == 0) {
			reqCrawlMultiArray(color, tmpX, tmpY);
		}

		tmpX = x+1; tmpY = y;
		if (pixelInsideImage(tmpX, tmpY) && fields[tmpY][tmpX] == 0) {
			reqCrawlMultiArray(color, tmpX, tmpY);
		}

		tmpX = x-1; tmpY = y;
		if (pixelInsideImage(tmpX, tmpY) && fields[tmpY][tmpX] == 0) {
			reqCrawlMultiArray(color, tmpX, tmpY);
		}
	} else {
		fields[y][x] = 2; // oznacz, że kodel ma inny kolor niż zadany parametrem
	}
}

// Metoda zlicza liczbę kodeli w pomocniczej 2-wymiarowej tabeli (która została właśnie sprawdzona) oznaczonych '1', czyli kodeli spełniających warunek (ten sam kolor co kolor zadany).
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

// Metoda zwraca liczbę kodeli w bloku koloru wskazywanym przez zadane parametrami współrzędne.
// Najbardziej zewnętrzna metoda całego mechanizmu, używa wielu innych metod.
int PBlockManager::getCodelBlockCount()
{
	return codel_block_count; // zwracanie liczby kodeli, przechowywanej w osobnym polu obiektu
}

// Metoda oznacza odpowiednimi wartościami ('1' lub '2') kodele na pomocniczej 2-wymiarowej tablicy i na koniec zlicza liczbę kodeli.
void PBlockManager::searchAndFillCodels()
{
	clearMultiArray(); // przygotuj tablicę aby można było na niej nanosić oznaczenia (wyzeruj)
	reqCrawlMultiArray(image->pixel(pointer->getCoordX(), pointer->getCoordY()), pointer->getCoordX(), pointer->getCoordY()); // rekursywne oznaczanie kodeli
	countCodels();
}

//==================================================================

// Metoda testowa.
// Metoda wyświetla na stdout 2-wymiarową tablicę pomocniczą.
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
