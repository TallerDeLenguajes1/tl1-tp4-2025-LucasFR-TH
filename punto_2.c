#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ESTRCUTURAS PARA LAS LISTAS
typedef struct Tarea {
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tareas;

typedef struct Nodo{
    Tareas T;
    struct Nodo *Siguiente;
} Nodo;

// DECLARACION DE MODULOS
Nodo *CrearListaVacia();
void InsertarNodo(Nodo **Tareas , Nodo *Nodo);
void MostrarListas(Nodo **Tareas);
void EliminarNodo(Nodo *nodo);
Nodo *QuitarNodo(Nodo **Tareas, int dato);
Nodo *BuscarNodo(Nodo **Tareas, int realizada);
void BuscarTareaPorIDoPalabra(Nodo *pendientes, Nodo *realizadas, int id, const char *clave);
void LiberarLista(Nodo *lista);


int main() {
    srand(time(NULL)); // Inicializa la semilla para duración aleatoria
    // DEFINO LAS DOS LISTAS DE TAREAS CON EL TIPO DE ESTRUCTURA DE LISTAS
    // E INCIICLIAZO LAS LISTAS
    Nodo *TareasPendientes;
    TareasPendientes = CrearListaVacia();
    Nodo *TareasRealizadas;
    TareasRealizadas = CrearListaVacia();

    printf("|||||||||REGISTRO DE TAREAS|||||||||\n");
    printf("\n");
    char confirmacion;
    int i = 0;

    do {
        printf("Desea ingresar una tarea? (Y/N): ");
        scanf("%c", &confirmacion);
        if (confirmacion == 'Y') {
            Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
            nuevo->T.TareaID = 1000 + i;
            i++;
            printf("Numero de tarea registrada: %d\n", nuevo->T.TareaID);

            printf("Ingrese la descripcion de la tarea:\n");
            getchar(); // NECESDARIO PARA PODER INGRESAR CORECATEMENTE LOS VALORES
            char *Buff; // variable auxiliar 
            Buff= (char *) malloc(300*sizeof(char)); 
            gets(Buff); // Lee el nombre del cliente
            nuevo->T.Descripcion = (char *) malloc((strlen(Buff)+1)*sizeof(char)); // Reserva memoria para el nombre del cliente
            strcpy(nuevo->T.Descripcion, Buff); // Copia el nombre del cliente a la estructura
            free(Buff); // Libera la memoria auxiliar

            printf("Ingrese la duracion de la tarea (10 - 100):\n");
            scanf("%d", nuevo->T.Duracion);
            nuevo->Siguiente = NULL;

            InsertarNodo(&TareasPendientes, nuevo);

            printf("Desea ingresar una tarea?(Y/N)");
            scanf("%c", &confirmacion);
        }
    } while (confirmacion == 'Y');

    printf("Termino el registro de tareas...\n");
    printf("\n");

    printf("|||||||||TAREAS PENDIENTES|||||||||\n");
    printf("\n");
    // MUESTRO LA LISTA DE TAREAS PENDIENTES
    MostrarListas(&TareasPendientes);
    printf("\n");

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
            Nodo *tareaPasar = BuscarNodo(&TareasPendientes, realizada);
            // INSERTO EL NODO EN LA LISTA DE REALIZADAS
            InsertarNodo(&TareasRealizadas, tareaPasar);
        }
    } while (cambioRealizadas == 'Y');

    // Mostrar listas
    MostrarListas(&TareasPendientes);
    MostrarListas(&TareasRealizadas);

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

    // LIMPIO MEMORIA
    LiberarLista(TareasPendientes);
    LiberarLista(TareasRealizadas);
    
    return 0;
}

// DEFINICION DE MODULOS
Nodo *CrearListaVacia()
{
    return NULL;
}

void InsertarNodo(Nodo **Tareas , Nodo *Nodo)
{
    Nodo -> Siguiente = *Tareas;
    *Tareas = Nodo ;
}

void MostrarListas(Nodo **Tareas) {
    Nodo *aux = *Tareas;
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

void EliminarNodo(Nodo *nodo)
{
    if (nodo) free(nodo);
}

Nodo *QuitarNodo(Nodo **Tareas, int dato)
{
    Nodo *aux = *Tareas;
    Nodo *anterior = NULL;

    // Buscar el nodo con el ID deseado
    while (aux != NULL && aux->T.TareaID != dato) {
        anterior = aux;
        aux = aux->Siguiente;
    }

    if (aux == NULL) {
        return NULL; // No encontrado
    }

    // Si el nodo a quitar es el primero
    if (anterior == NULL) {
        *Tareas = aux->Siguiente;  // Se actualiza el puntero cabeza de la lista
    } else {
        anterior->Siguiente = aux->Siguiente;
    }

    aux->Siguiente = NULL; // Desconectar el nodo
    return aux;
}

Nodo *BuscarNodo(Nodo **Tareas, int dato)
{
    Nodo *Aux = *Tareas;
    while(Aux && Aux->T.TareaID != dato)
    {
        Aux = Aux -> Siguiente;
    }
    if(Aux) {
        Nodo *temp = QuitarNodo(Tareas, dato);
        return temp;
    } else {
        return NULL;
    }
}

void BuscarTareaPorIDoPalabra(Nodo *pendientes, Nodo *realizadas, int id, const char *clave) {
    Nodo *aux;
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
            printf("No se encontro ninguna tarea con el ID %d.\n", id);
        }
    } else if (clave != NULL) {
        // Buscar por palabra clave (en descripción)
        printf("\nTareas que contienen \"%s\":\n", clave);
        for (aux = pendientes; aux != NULL; aux = aux->Siguiente) {
            if (strstr(aux->T.Descripcion, clave)) {
                printf("[PENDIENTE] ID: %d | Descripcion: %s | Duracion: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
            }
        }

        for (aux = realizadas; aux != NULL; aux = aux->Siguiente) {
            if (strstr(aux->T.Descripcion, clave)) {
                printf("[REALIZADA] ID: %d | Descripcion: %s | Duracion: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
            }
        }

        if (!encontrada) {
            printf("No se encontro ninguna tarea que contenga la palabra \"%s\".\n", clave);
        }
    }
}

void LiberarLista(Nodo *lista) {
    Nodo *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->Siguiente;

        // Liberar la descripción de la tarea (si fue asignada)
        if (aux->T.Descripcion != NULL) {
            free(aux->T.Descripcion);
        }

        // Liberar el nodo completo
        free(aux);
    }
}
