/* 
 * File:   tempo.h
 * Author: Eliane Karasawa
 */

#ifndef TEMPO_H
#define TEMPO_H

#ifdef _WIN32
#define USE_WINDOWS_TIMER
#endif


#ifdef USE_WINDOWS_TIMER
#include <windows.h>
#else
#endif

/*
 * Funcao que retorna o horario do sistema em segundos
 * @retorno double sendo o horario do sistema em segundos
 */

double seconds();
#endif /* TEMPO_H */

