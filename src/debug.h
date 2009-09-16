#ifndef P_DEBUG
#define P_DEBUG

/** \file debug.h
 * \brief Plik nagłówkowy debuggera
 *
 * Plik zawiera makro definiujące operacje debuggera.
 */

	#ifdef DEBUG
		#define debug(...) do { \
		fprintf(stderr, __VA_ARGS__); \
		} while(false)
	#else
		#define debug(...) 
	#endif

#endif
