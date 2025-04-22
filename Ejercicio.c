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
void CargarTareasPendientes(Nodo **start, int *id, char *desc);
void MostrarLista(Nodo **start);
Nodo *QuitarNodoPorPalabra(Nodo **start, char *desc);
Nodo *QuitarNodoPorID(Nodo **start, int ID);

int main()
{
    srand(time(NULL));
    int id = 1000, seleccion;
    char buff[30];
    Nodo *ListaPendientes = CrearListaVacia();
    Nodo *ListaRealizadas = CrearListaVacia();
    do
    {
        printf("\nIngrese la descripcion de la tarea a realizar:\n");
        scanf("%s", buff);
        CargarTareasPendientes(&ListaPendientes, &id, buff);
        printf("\nDesea cargar otra tarea?\n\t1. Si\n\t2. No\n");
        scanf("%d", &seleccion);
    } while (seleccion != 2);
    MostrarLista(&ListaPendientes);
    do
    {
        printf("\nIngrese la tarea que desea marcar como realizada: ");
        scanf("%s", buff);
        Nodo *NodoAMover = QuitarNodoPorPalabra(&ListaPendientes, buff);
        if (NodoAMover)
        {
            InsertarNodo(&ListaRealizadas, NodoAMover);
            MostrarLista(&ListaRealizadas);
        }
        printf("\nDesea Marcar otra tarea como realizada?\n\t1. Si\n\t2. No\n");
        scanf("%d", &seleccion);
    } while (seleccion != 2);
    printf("\n\t\t\tListado de Tareas PENDIENTES\n");
    MostrarLista(&ListaPendientes);
    printf("\n\t\t\tListado de Tareas PENDIENTES\n");
    MostrarLista(&ListaRealizadas);

    getchar();
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
void CargarTareasPendientes(Nodo **start, int *id, char *desc)
{
    Nodo *nuevoNodo = CrearNodo();
    nuevoNodo->T.Descripcion = (char *)malloc(strlen(desc) * sizeof(char) + 1);
    strcpy(nuevoNodo->T.Descripcion, desc);
    nuevoNodo->T.Duracion = 10 + rand() % 91;
    nuevoNodo->T.TareaID = (*id)++;
    InsertarNodo(start, nuevoNodo);
}
void MostrarLista(Nodo **start)
{
    Nodo *Aux = *start;
    while (Aux)
    {
        printf("\nID de la tarea: %d\nDescripcion de tarea: %s\nDuracion de la tarea: %d\n", Aux->T.TareaID, Aux->T.Descripcion, Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
}
Nodo *QuitarNodoPorPalabra(Nodo **start, char *desc)
{
    Nodo **Aux = start;
    while (*Aux && strcmp((*Aux)->T.Descripcion, desc) != 0)
    {
        Aux = &(*Aux)->Siguiente;
    }
    if (*Aux)
    {
        Nodo *temp = *Aux;
        *Aux = (*Aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}
Nodo *QuitarNodoPorID(Nodo **start, int ID)
{
    Nodo **Aux = start;
    while (*Aux && (*Aux)->T.TareaID != ID)
    {
        Aux = &(*Aux)->Siguiente;
    }
    if (*Aux)
    {
        Nodo *temp = *Aux;
        *Aux = (*Aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}