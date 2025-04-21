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
Nodos *CrearListaVacia();
void InsertarNodo(Nodos ** Tareas , Nodos *Nodo);
void MostrarListas(Nodos **Tareas);
void EliminarNodo(Nodos * nodo);
Nodos *QuitarNodo(Nodos * Tareas, int dato);
Nodos *BuscarNodo (Nodos **Tarea, int realizada);
void BuscarTareaPorIDoPalabra(Nodos *pendientes, Nodos *realizadas, int id, const char *clave);


int main() {
    srand(time(NULL)); // Inicializa la semilla para duración aleatoria
    // DEFINO LAS DOS LISTAS DE TAREAS CON EL TIPO DE ESTRUCTURA DE LISTAS
    // E INCIICLIAZO LAS LISTAS
    Nodos *TareasPendientes;
    TareasPendientes = CrearListaVacia();
    Nodos *TareasRealizadas;
    TareasRealizadas = CrearListaVacia();

    printf("|||||||||REGISTRO DE TAREAS|||||||||\n");
    printf("\n");
    char confirmacion;
    int i = 0;

    do {
        printf("¿Desea ingresar una tarea? (Y/N): ");
        getchar(); // limpia buffer
        scanf("%c", &confirmacion);
        if (confirmacion == 'Y') {
            Nodos *nuevo = (Nodos *)malloc(sizeof(Nodos));
            nuevo->T.TareaID = 1000 + i;
            i++;
            printf("Numero de tarea registrada: %d\n", nuevo->T.TareaID);


            getchar(); // NECESDARIO PARA PODER INGRESAR CORECATEMENTE LOS VALORES
            char *Buff; // variable auxiliar 
            Buff= (char *) malloc(100*sizeof(char)); 
            gets(Buff); // Lee el nombre del cliente
            nuevo->T.Descripcion = (char *) malloc((strlen(Buff)+1)*sizeof(char)); // Reserva memoria para el nombre del cliente
            strcpy(nuevo->T.Descripcion, Buff); // Copia el nombre del cliente a la estructura
            free(Buff); // Libera la memoria auxiliar

            printf("Ingrese la duracio de la tareas: (10 - 100)\n");
            scanf("%d", nuevo->T.Duracion);
            nuevo->Siguiente = NULL;

            InsertarNodo(TareasPendientes ,nuevo);

            printf("¿Desea ingresar una tarea?(Y/N)");
            scanf("%c", &confirmacion);
        }
    } while (confirmacion == 'Y');

    printf("Termino el registro de tareas...\n");
    printf("\n");

    /*printf("Las tareas registradas son las siguientes:\n");
    MostrarListas(TareasPendientes);*/

    char cambioRealizadas;
    do {
        printf("¿Desea marcar una tarea como realizada? (Y/N): ");
        getchar(); // limpia buffer
        scanf("%c", &cambioRealizadas);
        if (cambioRealizadas == 'Y') {
            printf("Ingrese el numero identificador de la tarea que desea marcar como realizada:\n");
            int realizada;
            scanf("%d", &realizada);
            // SACO EL NODO A PASAR DE LA LISTA DE PENDIENTES
            Nodos *tareaPasar = buscarNodo(TareasPendientes, realizada);
            // INSERTO EL NODO EN LA LISTA DE REALIZADAS
            InsertarNodo(TareasRealizadas, tareaPasar);
        }
    } while (cambioRealizadas == 'Y');

    // Mostrar listas
    MostrarLista(TareasPendientes, "TAREAS PENDIENTES");
    MostrarLista(TareasRealizadas, "TAREAS REALIZADAS");

    // Consulta por ID o palabra clave
    int id_busqueda;
    char palabra[50];
    printf("\n--- CONSULTA DE TAREAS ---\n");
    printf("Ingrese un ID de tarea para buscar (o 0 para buscar por palabra): ");
    scanf("%d", &id_busqueda);

    if (id_busqueda > 0) {
        BuscarTareaPorIDoPalabra(TareasPendientes, TareasRealizadas, id_busqueda, NULL);
    } else {
        printf("Ingrese palabra clave: ");
        getchar();
        fgets(palabra, sizeof(palabra), stdin);
        palabra[strcspn(palabra, "\n")] = 0;
        BuscarTareaPorIDoPalabra(TareasPendientes, TareasRealizadas, 0, palabra);
    }

    return 0;
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
            printf("Duracion: %d\n", aux->T.Duracion);
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

void BuscarTareaPorIDoPalabra(Nodos *pendientes, Nodos *realizadas, int id, const char *clave) {
    Nodos *aux;
    int encontrada = 0;

    if (id > 0) {
        // Buscar por ID
        for (aux = pendientes; aux != NULL; aux = aux->Siguiente) {
            if (aux->T.TareaID == id) {
                printf("\nTarea encontrada en PENDIENTES:\n");
                printf("ID: %d\nDescripción: %s\nDuración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
                break;
            }
        }

        for (aux = realizadas; aux != NULL && !encontrada; aux = aux->Siguiente) {
            if (aux->T.TareaID == id) {
                printf("\nTarea encontrada en REALIZADAS:\n");
                printf("ID: %d\nDescripción: %s\nDuración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            printf("No se encontró ninguna tarea con el ID %d.\n", id);
        }
    } else if (clave != NULL) {
        // Buscar por palabra clave (en descripción)
        printf("\nTareas que contienen \"%s\":\n", clave);
        for (aux = pendientes; aux != NULL; aux = aux->Siguiente) {
            if (strstr(aux->T.Descripcion, clave)) {
                printf("[PENDIENTE] ID: %d | Descripción: %s | Duración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
            }
        }

        for (aux = realizadas; aux != NULL; aux = aux->Siguiente) {
            if (strstr(aux->T.Descripcion, clave)) {
                printf("[REALIZADA] ID: %d | Descripción: %s | Duración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
            }
        }

        if (!encontrada) {
            printf("No se encontró ninguna tarea que contenga la palabra \"%s\".\n", clave);
        }
    }
}