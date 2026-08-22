/*****************************************************************************************************************
    UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
    FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

    Computadoras y programacion.
    (c) Ramirez Aguilar Evelyn 323091367

    Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

*****************************************************************************************************************/

#include "stdafx.h"
#include <string.h>
#include <ctype.h>
#include "corrector.h"
#include <stdio.h>

#define TAMTOKEN 50

int esDelimitador(char c) {
    return c == ' ' || c == '\t' || c == '\n' ||
        c == ',' || c == ';' || c == '.' ||
        c == '(' || c == ')' || c == '\r';
}

int buscaPalabraEnArray(char palabra[][TAMTOKEN], int num, const char* pal) {
    for (int i = 0; i < num; i++) {
        if (strcmp(palabra[i], pal) == 0)
            return i;
    }
    return -1;
}

void ordenarAlfabetico(char palabras[][TAMTOKEN], int frecuencias[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcmp(palabras[i], palabras[j]) > 0) {
                char tmp[TAMTOKEN];
                int tmpFreq;
                strcpy_s(tmp, TAMTOKEN, palabras[i]);
                strcpy_s(palabras[i], TAMTOKEN, palabras[j]);
                strcpy_s(palabras[j], TAMTOKEN, tmp);
                tmpFreq = frecuencias[i];
                frecuencias[i] = frecuencias[j];
                frecuencias[j] = tmpFreq;
            }
        }
    }
}

/*****************************************************************************************************************
    Diccionario
******************************************************************************************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, szNombre, "r");
    if (err != 0 || fp == NULL) {
        iNumElementos = 0;
        return;
    }

    char token[TAMTOKEN];
    int pos = 0;
    iNumElementos = 0;

    int c = fgetc(fp);
    while (c != EOF) {
        if (!esDelimitador((char)c)) {
            if (pos < TAMTOKEN - 1) {
                token[pos++] = (char)tolower(c);
            }
        }
        else {
            if (pos > 0) {
                token[pos] = '\0';
                int idx = buscaPalabraEnArray(szPalabras, iNumElementos, token);
                if (idx >= 0) {
                    iEstadisticas[idx]++;
                }
                else {
                    strcpy_s(szPalabras[iNumElementos], TAMTOKEN, token);
                    iEstadisticas[iNumElementos] = 1;
                    iNumElementos++;
                }
                pos = 0;
            }
        }
        c = fgetc(fp);
    }

    if (pos > 0) {
        token[pos] = '\0';
        int idx = buscaPalabraEnArray(szPalabras, iNumElementos, token);
        if (idx >= 0) {
            iEstadisticas[idx]++;
        }
        else {
            strcpy_s(szPalabras[iNumElementos], TAMTOKEN, token);
            iEstadisticas[iNumElementos] = 1;
            iNumElementos++;
        }
    }

    fclose(fp);
    ordenarAlfabetico(szPalabras, iEstadisticas, iNumElementos);
}

/*****************************************************************************************************************
    ListaCandidatas
******************************************************************************************************************/
void ListaCandidatas(
    char szPalabrasSugeridas[][TAMTOKEN],
    int  iNumSugeridas,
    char szPalabras[][TAMTOKEN],
    int  iEstadisticas[],
    int  iNumElementos,
    char szListaFinal[][TAMTOKEN],
    int  iPeso[],
    int& iNumLista)
{
    int total = 0;

    for (int h = 0; h < iNumSugeridas; h++) {
        int idx = -1;
        for (int k = 0; k < iNumElementos; k++) {
            if (strcmp(szPalabrasSugeridas[h], szPalabras[k]) == 0) {
                idx = k;
                break;
            }
        }
        if (idx != -1) {
            strcpy_s(szListaFinal[total], TAMTOKEN, szPalabrasSugeridas[h]);
            iPeso[total] = iEstadisticas[idx];
            total++;
        }
    }

   
    int nuevo = 0;
    for (int i = 0; i < total; i++) {
        int yaExiste = 0;
        for (int j = 0; j < nuevo; j++) {
            if (strcmp(szListaFinal[j], szListaFinal[i]) == 0) {
                yaExiste = 1;
                break;
            }
        }
        if (!yaExiste) {
            strcpy_s(szListaFinal[nuevo], TAMTOKEN, szListaFinal[i]);
            iPeso[nuevo] = iPeso[i];
            nuevo++;
        }
    }
    total = nuevo;


    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if ((iPeso[j] > iPeso[i]) ||
                (iPeso[j] == iPeso[i] && strcmp(szListaFinal[j], szListaFinal[i]) < 0)) {
                int tmpW = iPeso[i];
                iPeso[i] = iPeso[j];
                iPeso[j] = tmpW;

                char tmp[TAMTOKEN];
                strcpy_s(tmp, TAMTOKEN, szListaFinal[i]);
                strcpy_s(szListaFinal[i], TAMTOKEN, szListaFinal[j]);
                strcpy_s(szListaFinal[j], TAMTOKEN, tmp);
            }
        }
    }

    iNumLista = total;
}

/* ------------------------------------------------------
   Función ClonaPalabras 
------------------------------------------------------ */
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas)
{
    const char letras[] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
    const int numLetras = 32;
    int longi = (int)strlen(szPalabraLeida);

    iNumSugeridas = 0;
    char palabraTemp[TAMTOKEN];

    if (longi > 1) {
        for (int i = 0; i < longi; i++) {
            int idx = 0;
            for (int j = 0; j < longi; j++) {
                if (j != i) {
                    palabraTemp[idx++] = szPalabraLeida[j];
                }
            }
            palabraTemp[idx] = '\0';
            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, palabraTemp);
        }

        for (int i = 0; i < longi - 1; i++) {
            strcpy_s(palabraTemp, TAMTOKEN, szPalabraLeida);
            char temp = palabraTemp[i];
            palabraTemp[i] = palabraTemp[i + 1];
            palabraTemp[i + 1] = temp;
            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, palabraTemp);
        }

    }

    for (int i = 0; i < longi; i++) {
        for (int j = 0; j < numLetras; j++) {
            strcpy_s(palabraTemp, TAMTOKEN, szPalabraLeida);
            palabraTemp[i] = letras[j];
            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, palabraTemp);
        }
    }

    for (int pos = 0; pos <= longi; pos++) {
        char buffer[TAMTOKEN];
        strcpy_s(buffer, TAMTOKEN, szPalabraLeida);

        for (int j = 0; j < numLetras; j++) {
            int idx = 0;
            for (int i = 0; i < pos; i++) {
                palabraTemp[idx++] = buffer[i];
            }
            palabraTemp[idx++] = letras[j];
            for (int i = pos; i < longi; i++) {
                palabraTemp[idx++] = buffer[i];
            }
            palabraTemp[idx] = '\0';

            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, palabraTemp);
        }
    }

    strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, szPalabraLeida);

    for (int i = 0; i < iNumSugeridas - 1; i++) {
        for (int j = i + 1; j < iNumSugeridas; j++) {
            if (strcmp(szPalabrasSugeridas[i], szPalabrasSugeridas[j]) > 0) {
                char temp[TAMTOKEN];
                strcpy_s(temp, TAMTOKEN, szPalabrasSugeridas[i]);
                strcpy_s(szPalabrasSugeridas[i], TAMTOKEN, szPalabrasSugeridas[j]);
                strcpy_s(szPalabrasSugeridas[j], TAMTOKEN, temp);
            }
        }
    }
}
