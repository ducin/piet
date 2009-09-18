#ifndef P_STRUCTS
#define P_STRUCTS

/** \file pstructs.h
 * \brief Plik nagłówkowy z definicjami rekordów
 *
 * Plik nagłówkowy zawiera wszystkie definicje rekordów które są wykorzystywane w projekcie.
 */

/**
 * Struktura reprezentująca punkt (a w zasadzie tylko jego współrzędne) na pewnym obrazie.
 */
typedef struct struct_point {
	/** Odcięta (współrzędna) punktu. */ int x;
	/** Rzędna (współrzędna) punktu. */ int y;
} PPoint;

#endif
