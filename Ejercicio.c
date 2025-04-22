#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;
typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *CrearListaVacia();
Nodo *CrearNodo();
void InsertarNodo(Nodo **start, Nodo *nodo);
void CargarTareasPendientes(Nodo **start, int *id);

int main()
{
    srand(time(NULL));
    int id = 1000;
    Nodo *ListaPendientes = CrearListaVacia();
    Nodo *ListaRealizadas = CrearListaVacia();
    Nodo *TareasRealizadas = CrearNodo();
    InsertarNodo(&ListaRealizadas, TareasRealizadas);
    CargarTareasPendientes(&ListaPendientes, &id);
    return 0;
}

Nodo *CrearListaVacia()
{
    return NULL;
}
Nodo *CrearNodo()
{
    Nodo *NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    NuevoNodo->Siguiente = NULL;
    return NuevoNodo;
}
void InsertarNodo(Nodo **start, Nodo *nodo)
{
    nodo->Siguiente = *start;
    *start = nodo;
}
void CargarTareasPendientes(Nodo **start, int *id)
{
    char buff[30];
    int seleccion;
    do
    {
        Nodo *nuevoNodo = CrearNodo();

        printf("\nIngrese la descripcion de la tarea a realizar:\n");
        scanf("%s", buff);
        nuevoNodo->T.Descripcion = (char *)malloc(strlen(buff) * sizeof(char) + 1);
        strcpy(nuevoNodo->T.Descripcion, buff);

        nuevoNodo->T.Duracion = 10 + rand() % 91;

        nuevoNodo->T.TareaID = (*id)++;

        InsertarNodo(start, nuevoNodo);

        printf("\nDesea cargar otra tarea?\n\t1. Si\n\t2. No\n");
        scanf("%d", &seleccion);
    } while (seleccion != 2);
}