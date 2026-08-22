# Word Completion System | Corrector Ortografico en C

![C](https://img.shields.io/badge/C-99-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Completado-brightgreen)

## Descripcion

Sistema de autocompletado y correccion de palabras implementado en **C**.
Utiliza el algoritmo de **distancia de Levenshtein** para encontrar palabras similares
en un diccionario y sugerir correcciones basadas en frecuencia de uso.

## Objetivo Principal

Implementar un algoritmo capaz de:

- Analizar la similitud entre palabras
- Completar palabras incompletas o mal escritas
- Utilizar diccionarios y libros como base de conocimiento
- Sugerir correcciones basadas en frecuencia de uso

## Caracteristicas

- Analisis de similitud mediante distancia de Levenshtein
- Generacion de palabras candidatas (insercion, eliminacion, sustitucion, transposicion)
- Filtrado de candidatas usando diccionario real
- Ordenamiento por frecuencia de uso
- Procesamiento de archivos de texto como corpus
- Lectura de diccionarios y libros

## Tecnologias Utilizadas

- **Lenguaje:** C
- **Compilador:** Visual Studio / gcc
- **Algoritmos:** Distancia de Levenshtein
- **Estructuras de datos:** Arrays multidimensionales, strings
- **Bibliotecas:** stdafx.h, string.h, ctype.h, stdio.h

## Estructura del Proyecto

Word-Completion-System
┣ Word-Completion-System.cpp
┣ README.md
┣ LICENSE
┗ .gitignore

## Compilacion y Ejecucion

### En Visual Studio:

1. Abrir Visual Studio
2. Crear un proyecto nuevo o abrir el archivo `.cpp`
3. Compilar con `Ctrl + Shift + B`
4. Ejecutar con `F5`

### En linea de comandos (gcc):

```bash
# Compilar
gcc -o corrector Word-Completion-System.cpp

# Ejecutar
./corrector

Funcionamiento del Programa
-Carga del diccionario: Lee palabras y sus frecuencias desde archivos de texto
-Entrada de palabra: El usuario escribe una palabra posiblemente mal escrita
-Generacion de candidatas: Crea variaciones mediante:

	*Eliminacion de caracteres
	*Insercion de caracteres
	*Sustitucion de caracteres
	*Transposicion de caracteres adyacentes

-Filtrado: Busca las candidatas que existen en el diccionario
-Ordenamiento: Prioriza por frecuencia de uso
-Sugerencia: Muestra las palabras mas probables

Ejemplo de Funcionamiento

-Entrada: "prog"
-Candidatas generadas: program, progama, progar, prorg, etc.
-Filtradas por diccionario: programa, programar, progreso
-Sugerencia final: programa (mayor frecuencia)

Autor

-Ramirez Aguilar Evelyn
-Universidad Nacional Autonoma de Mexico
-Facultad de Estudios Superiores - Aragon
-Materia: Computadoras y Programacion

Licencia

Este proyecto esta bajo la Licencia MIT - ver el archivo LICENSE para mas detalles.

Agradecimientos

Proyecto desarrollado con fines educativos como parte de la materia de
Computadoras y Programacion en la FES Aragon, UNAM.

Si este proyecto te fue util, dale una estrella.
