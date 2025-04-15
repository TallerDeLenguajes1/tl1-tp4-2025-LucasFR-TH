#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ESTRCUTURAS PARA LAS LISTAS
typedef struct Tarea {
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tareas;

typedef struct Nodo{
    Tareas T;
    Nodos *Siguiente;
} Nodos;

// DECLARACION DE MODULOS
Nodos * CrearListaVacia();
void InsertarNodo(Nodos ** Start , Nodos *Nodo);

int main() {
    // DEFINO LAS DOS LISTAS DE TAREAS CON EL TIPO DE ESTRUCTURA DE LISTAS
    // E INCIICLIAZO LAS LISTAS
    Nodos *TareasPendientes;
    TareasPendientes = CrearListaVacia();
    Nodos *TareasRealizadas;
    TareasRealizadas = CrearListaVacia();

    printf("|||||||||REGISTRO DE TAREAS|||||||||\n");
    printf("\n");
    printf("¿Desea ingresar una tarea?(Y/N)");
    char confirmacion;
    scanf("%c", &confirmacion);
    if (confirmacion == "Y") {
        Nodos * T1 = (Nodos *)malloc(sizeof(Nodos));
        
    }
}

// DEFINICION DE MODULOS
Nodos * CrearListaVacia()
{
    return NULL;
}

void InsertarNodo(Nodos ** Start , Nodos *Nodo)
{
    Nodo -> Siguiente = *Start;
    *Start = Nodo ;
}
