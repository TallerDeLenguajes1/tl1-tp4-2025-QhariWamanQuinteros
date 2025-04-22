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
void CargarTareasPendientes(Nodo **start, int *id, char *desc, int duracion);
void MostrarLista(Nodo **start);
Nodo *DesenlazarNodo(Nodo **start, char *desc);
Nodo *MostrarNodoPorID(Nodo **start, int ID);
Nodo *MostrarNodoPorPalabra(Nodo **start, char *desc);

int main()
{
    srand(time(NULL));
    int id = 1000, seleccion, duracion, numeroID;
    char buff[30];
    Nodo *ListaPendientes = CrearListaVacia();
    Nodo *ListaRealizadas = CrearListaVacia();
    do
    {
        printf("\nIngrese la descripcion de la tarea a realizar:\n");
        scanf("%s", buff);
        do
        {
            printf("\nIngrese la duracion de la tarea a realizar:\n");
            scanf("%d", &duracion);
            if (duracion < 10 || duracion > 100)
            {
                printf("\nDuracion de tarea invalida, ingrese un numero entre 10 y 100\n");
            }
        } while (duracion < 10 || duracion > 100);
        CargarTareasPendientes(&ListaPendientes, &id, buff, duracion);
        printf("\nDesea cargar otra tarea?\n\t1. Si\n\t2. No\n");
        scanf("%d", &seleccion);
    } while (seleccion != 2);
    MostrarLista(&ListaPendientes);
    do
    {
        printf("\nIngrese la tarea que desea marcar como realizada: ");
        scanf("%s", buff);
        Nodo *NodoAMover = DesenlazarNodo(&ListaPendientes, buff);
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
    printf("\n\t\t\tListado de Tareas REALIZADAS\n");
    MostrarLista(&ListaRealizadas);
    Nodo *Buscado = CrearNodo();
    do
    {
        printf("\nIngrese una forma para buscar un nodo\n1. Buscar por ID\n2. Buscar por palabra clave\n");
        scanf("%d", &seleccion);
        if (seleccion != 1 && seleccion != 2)
        {
            printf("\nSeleccion invalida\n");
        }
    } while (seleccion != 1 && seleccion != 2);
    if (seleccion == 1)
    {
        printf("\nIngrese el id buscado: ");
        scanf("%d", &numeroID);
        Buscado = MostrarNodoPorID(&ListaPendientes, numeroID);
        if (Buscado)
        {
            printf("\n\t\tNodo Buscado\nPertenece a Tareas Pendientes\nDescripcion de la tarea: %s\nDuracion de la tarea: %d\nID de la tarea: %d", Buscado->T.Descripcion, Buscado->T.Duracion, Buscado->T.TareaID);
        }
        else
        {
            Buscado = MostrarNodoPorID(&ListaRealizadas, numeroID);
            if (Buscado)
            {
                printf("\n\t\tNodo Buscado\nPertenece a Tareas Realizadas\nDescripcion de la tarea: %s\nDuracion de la tarea: %d\nID de la tarea: %d", Buscado->T.Descripcion, Buscado->T.Duracion, Buscado->T.TareaID);
            }
            else
            {
                printf("\nEl id ingresado no coincide con ningun nodo");
            }
        }
    }
    else if (seleccion == 2)
    {
        printf("\nIngrese la descripcion de la tarea buscada: ");
        scanf("%s", buff);
        Buscado = MostrarNodoPorPalabra(&ListaPendientes, buff);
        if (Buscado)
        {
            printf("\n\t\tNodo Buscado\nPertenece a Tareas Pendientes\nDescripcion de la tarea: %s\nDuracion de la tarea: %d\nID de la tarea: %d", Buscado->T.Descripcion, Buscado->T.Duracion, Buscado->T.TareaID);
        }
        else
        {
            Buscado = MostrarNodoPorPalabra(&ListaRealizadas, buff);
            if (Buscado)
            {
                printf("\n\t\tNodo Buscado\nPertenece a Tareas Realizadas\nDescripcion de la tarea: %s\nDuracion de la tarea: %d\nID de la tarea: %d", Buscado->T.Descripcion, Buscado->T.Duracion, Buscado->T.TareaID);
            }
            else
            {
                printf("\nEl id ingresado no coincide con ningun nodo");
            }
        }
    }

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
void CargarTareasPendientes(Nodo **start, int *id, char *desc, int duracion)
{
    Nodo *nuevoNodo = CrearNodo();
    nuevoNodo->T.Descripcion = (char *)malloc(strlen(desc) * sizeof(char) + 1);
    strcpy(nuevoNodo->T.Descripcion, desc);
    nuevoNodo->T.Duracion = duracion;
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
Nodo *DesenlazarNodo(Nodo **start, char *desc)
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
Nodo *MostrarNodoPorPalabra(Nodo **start, char *desc)
{
    Nodo **Aux = start;
    while (*Aux && strcmp((*Aux)->T.Descripcion, desc) != 0)
    {
        Aux = &(*Aux)->Siguiente;
    }
    return (*Aux);
}
Nodo *MostrarNodoPorID(Nodo **start, int ID)
{
    Nodo **Aux = start;
    while (*Aux && (*Aux)->T.TareaID != ID)
    {
        Aux = &(*Aux)->Siguiente;
    }
    return (*Aux);
}