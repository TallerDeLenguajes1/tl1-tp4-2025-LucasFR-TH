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
void InsertarNodo(Nodos ** Tareas , Nodos *Nodo);
void MostrarListas(Nodos **Tareas);
void EliminarNodo(Nodos * nodo);
Nodos * QuitarNodo(Nodos * Tareas, int dato);
Nodos *BuscarNodo (Nodos **Tarea, int realizada);


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
    int i = 1;

    while (confirmacion == "Y") {
        Nodos * T = (Nodos *)malloc(sizeof(Nodos));
        T->T.TareaID = i + 1000;
        i++;
        printf("Numero de tarea registrada: %d\n", T->T.TareaID);
        printf("Ingrese la descripcion de la tarea:\n");

        getchar(); // NECESDARIO PARA PODER INGRESAR CORECATEMENTE LOS VALORES
        char *Buff; // variable auxiliar 
        Buff= (char *) malloc(100*sizeof(char)); 
        gets(Buff); // Lee el nombre del cliente
        T->T.Descripcion = (char *) malloc((strlen(Buff)+1)*sizeof(char)); // Reserva memoria para el nombre del cliente
        strcpy(T->T.Descripcion, Buff); // Copia el nombre del cliente a la estructura
        free(Buff); // Libera la memoria auxiliar
        
        printf("Ingrese la duracio de la tareas: (10 - 100)\n");
        scanf("%d", T->T.Duracion);
        T->Siguiente = NULL;

        InsertarNodo(TareasPendientes ,T);

        printf("¿Desea ingresar una tarea?(Y/N)");
        scanf("%c", &confirmacion);
    }

    printf("Termino el registro de tareas...\n");
    printf("\n");

    /*printf("Las tareas registradas son las siguientes:\n");
    MostrarListas(TareasPendientes);*/

    char cambioRealizadas;
    printf("Quiere marcar tareas como completas? (Y/N)\n");
    scanf("%c", cambioRealizadas);
    while (cambioRealizadas == "Y") {
        printf("Ingrese el numero identificador de la tarea que desea marcar como realizada:\n");
        int realizada;
        scanf("%d", &realizada);
        // SACO EL NODO A PASAR DE LA LISTA DE PENDIENTES
        Nodos *tareaPasar = buscarNodo(TareasPendientes, realizada);
        // INSERTO EL NODO EN LA LISTA DE REALIZADAS
        InsertarNodo(TareasRealizadas, tareaPasar);
        // OCNSULTO POR OTRO MODIFICAION
        printf("Quiere seguir marcando tareas como completas? (Y/N)\n");
        scanf("%c", cambioRealizadas);
    }


}

// DEFINICION DE MODULOS
Nodos * CrearListaVacia()
{
    return NULL;
}

void InsertarNodo(Nodos ** Tareas , Nodos *Nodo)
{
    Nodo -> Siguiente = *Tareas;
    *Tareas = Nodo ;
}

void MostrarListas(Nodos ** Tareas) {
    Nodos * aux = *Tareas;
    if (aux) {
        while (aux->Siguiente) {
            printf("ID %d\n", aux->T.TareaID);
            printf("Descripcion: %s\n", aux->T.Descripcion);
            printf("Duracion: %s\n", aux->T.Duracion);
            printf("\n");
            aux = aux -> Siguiente;
        }
    }
    
}

void EliminarNodo(Nodos * nodo)
{
    if (nodo) free(nodo);
}

Nodos * QuitarNodo(Nodos * Tareas, int dato)
{
    Nodos ** aux = Tareas;
    while (*aux != NULL && (*aux)->T.TareaID != dato) {
        aux = &(*aux)->Siguiente;
    }
    if (*aux) {
        Nodos *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return(temp);
    } else {
        return NULL; 
    }
    
}

Nodos * buscarNodo(Nodos * Tareas, int dato)
{
    Nodos * Aux = Tareas;
    while(Aux && Aux->T.TareaID != dato)
    {
        Aux = Aux -> Siguiente;
    }
    if(Aux) {
        Nodos * temp = QuitarNodo(Tareas, dato);
        return temp;
    } else {
        return NULL;
    }
}

