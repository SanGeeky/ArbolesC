#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct nodo
{
    int inf, inf2;
    struct nodo *sig, *ant, *sig2, *ant2;
} * pri, *nue, *aux, *ult, *dato, *aux2; // * pri2, *nue2, *aux3, *ult2, *dato2, *aux4;

struct nodo2
{
    int inf2;
    struct nodo2 *sig2, *ant2;
} * pri2, *nue2, *aux3, *ult2, *dato2, *aux4;

struct listaPadre
{
    int inf;
    struct listaPadre *sig, *ant;
    struct listaHijo *hijo;
} * priPadre, *ultPadre, *nuePadre, *auxPadre, *datoPadre;

struct listaHijo
{
    int inf;
    struct listaHijo *sig;
    struct listaHijo *ant;
    struct listaPadre *padre;
} * priHijo, *ultHijo, *nueHijo, *auxHijo, *datoHijo;

void vaciarlista()
{
    // se iran eliminando todos los elementos
    // hasta que pri sea NULL
    // obtendremos nuestra lista vacia
    while (pri != NULL)
    {
        aux = pri;
        pri = pri->sig;
        //cout << pri->sig;
        delete aux;
    }
}

void listar(nodo *list)
{
    system("cls");
    if (list != NULL)
    {
        aux = list;
        cout << "pri:    \n";
        while (aux != NULL)
        {
            cout << aux->inf << " -> ";
            aux = aux->sig;
        }
    }
    else
        cout << "Cola VACIA....\n";
    cin.ignore();
    cin.get();
}

void listar2(nodo2 *list2)
{
    system("cls");
    if (list2 != NULL)
    {
        aux3 = list2;
        cout << "pri:    \n";
        while (aux3 != NULL)
        {
            cout << aux3->inf2 << " -> ";
            aux3 = aux3->sig2;
        }
    }
    else
        cout << "Cola VACIA....\n";
    cin.ignore();
    cin.get();
}

void ingresar() // Genera lista de aleatorios
{
    vaciarlista();

    srand(time(NULL));
    int num, count;
    cout << "Digite de que tamaño desea la lista(minimo 30)";
    cin >> count;
    for (int i = 0; i < count; i++)
    {
        if (pri == NULL)
        {
            pri = new nodo();
            pri2 = new nodo2();
            num = rand() % 99;
            pri->inf = num;
            pri2->inf2 = num;
            ult = pri;
            ult2 = pri2;
            ult->sig = NULL;
            ult2->sig2 = NULL;
            pri->ant = NULL;
            pri2->ant2 = NULL;
        }
        else
        {

            num = rand() % 99;

            nue2 = new nodo2(); //reserva espacio
            nue2->inf2 = num;   //guarda informacion
            ult2->sig2 = nue2;
            nue2->ant2 = ult2;
            ult2 = nue2;
            ult2->sig2 = NULL;

            if (num < pri->inf) //ingresar primero nuevo
            {

                nue = new nodo(); //reserva espacio
                nue->inf = num;   //pide el valor
                nue->sig = pri;
                pri->ant = nue;
                pri = nue;
                pri->ant = NULL;
            }
            else
            {
                if (num > ult->inf)
                {
                    nue = new nodo();
                    nue->inf = num;
                    ult->sig = nue;
                    nue->ant = ult;
                    ult = nue;
                    ult->sig = NULL;
                }
                else
                {
                    aux = pri;
                    while (aux != NULL && num != aux->inf && num > aux->inf)
                    { //VALIDAR QUE NO ESTE REPETIDO
                        //
                        dato = aux;
                        aux = aux->sig;
                    }
                    if (aux->inf == num)
                    {
                        //                    cout << "Repetido...";
                        //                    system("pause");
                    }
                    else
                    { //ingresar un numero en medio
                        nue = new nodo();
                        nue->inf = num;
                        dato->sig = nue;
                        nue->ant = dato;
                        nue->sig = aux;
                        aux->ant = nue;
                    }
                }
            }
        }
    }
    listar2(pri2);
    cout << "\n";
    listar(pri);
    system("PAUSE");
}

void generarGrafo()
{
    aux = pri;
    int decima;

    while (aux != NULL)
    {
        decima = aux->inf / 10;
        if (priPadre == NULL)
        {
            priPadre = new listaPadre();
            priPadre->inf = decima;
            ultPadre = priPadre;
            ultPadre->sig = NULL;
            priPadre->ant = NULL;
        }
        else
        {
            if (decima < priPadre->inf) //ingresar priPadremero nuevo
        {

            nuePadre = new listaPadre(); //reserva espacio
            nuePadre->inf = decima;      //pide el valor
            nuePadre->sig = priPadre;
            priPadre->ant = nuePadre;
            priPadre = nuePadre;
            priPadre->ant = NULL;
        }
        else
        {
            if (decima > ultPadre->inf)
            {
                nuePadre = new listaPadre();
                nuePadre->inf = decima;
                ultPadre->sig = nuePadre;
                nuePadre->ant = ultPadre;
                ultPadre = nuePadre;
                ultPadre->sig = NULL;
            }
            else
            {
                auxPadre = priPadre;
                while (auxPadre != NULL && decima != auxPadre->inf && decima > auxPadre->inf)
                {   //VALIDAR QUE NO ESTE REPETIDO
                    //
                    datoPadre = auxPadre;
                    auxPadre = auxPadre->sig;
                }
                if (auxPadre->inf == decima)
                {
                    //                    cout << "Repetido...";
                    //                    system("pause");
                }
                else
                { //ingresar un numero en medio
                    nuePadre = new listaPadre();
                    nuePadre->inf = decima;
                    datoPadre->sig = nuePadre;
                    nuePadre->ant = datoPadre;
                    nuePadre->sig = auxPadre;
                    auxPadre->ant = nuePadre;
                }
            }
        }
        }
        
        aux = aux->sig;

    }

    while (aux != NULL)
    {
        
    }
    
    /* if (priPadre == NULL)
    {
        cout << "No hay datos\n";
        system("pause");
    }
    else
    {
        auxPadre = priPadre;
        while (auxPadre != NULL)
        {
            cout << "\nPrincipal= " << auxPadre->inf;
            auxPadre = auxPadre->sig;
        }
        cout << endl;
        system("pause");
    } */
}

bool buscar()
{
    int numero;
    int enlaces = 1;
    if (ult == NULL)
    {
        cout << "\nLista Vacia \n";
        return false;
    }
    else
    {
        cout << "\n Numero a Buscar: ";
        cin >> numero;
        aux = ult;
        while (aux != NULL && numero != aux->inf)
        {
            aux2 = aux;
            aux = aux->ant;
            enlaces++;
        }
        if (aux == NULL)
        {
            cout << "\n Dato  NO encontrado\n";
            return false;
        }
        else
        {
            cout << "\n Dato encontrado: " << aux->inf;
            cout << "\n Enlaces: " << enlaces;
            return true;
        }
    }

    system("PAUSE");
    cin.ignore();
    cin.get();
}

void sacarLista()
{
    system("cls");
    int b;
    if (pri != NULL)
    {
        cout << "Dato a buscar: ";
        cin >> b;
        aux = pri;
        while (aux->sig != NULL && aux->inf != b)
        {
            dato = aux;
            aux = aux->sig;
        }
        if (aux->inf != b)
            cout << "\nDato no encontrado...";
        else
        {
            cout << "eliminado: " << aux->inf;
            if (aux == pri)
            {
                if (pri->sig != NULL)
                {
                    pri = aux->sig;
                    pri->ant = NULL;
                }
                else
                    pri = NULL;
            }
            else
            {
                if (aux == ult)
                {
                    ult = dato;
                    ult->sig = NULL;
                }
                else
                {
                    dato->sig = aux->sig;
                    aux->sig->ant = dato;
                }
            }
            delete aux;
        }
    }
    else
        cout << "Lista Doble Enlazada VACIA....\n";
    cin.ignore();
    cin.get();
}

void sacar() ////Saca de la lista elprimer elemento
{
    if (pri == NULL)
    {
        cout << "\n Lista Vacia\n";
    }
    else
    {
        aux = pri;
        cout << "\nSale: " << pri->inf;
        pri = pri->sig;

        //cout << pri->sig;
        delete aux;
    }
}

void inicializar()
{
    if (pri != NULL)
    {
        aux = pri;
        while (aux != NULL)
        {
            cout << "Liberado: " << aux->inf << endl;
            pri = aux->sig;
            delete aux;
            aux = pri;
        }
    }
    cout << "Lista VACIA....\n";
    //se dice un sistem pause y que pida una tecla
    cin.ignore();
    cin.get();
    // y reemplaza system pause y le quita una tecla par continuar
    // se las trabaja juntas
}

void menu()
{
    int op;
    do
    {
        do
        {
            system("cls");
            cout << "MENU DE OPCIONES"
                 << "\n1. Generar lista de numero aleatorios: "
                 << "\n2. Mostrar lista sin datos repetidos y ordenada: "
                 << "\n3. Generar Grafo"
                 << "\n4. Generar Arbol Binario"
                 << "\n5. Limpiar Estructuras"

                 << "\n6. Salir"
                 << "\nOpcion:  ";
            cin >> op;
        } while (op < 1 || op > 6);
        switch (op)
        {
        case 1:
            ingresar();
            break;
        case 2:
            listar(pri);
            break;
        case 3:
            generarGrafo();
            break;
        case 4:
            buscar();
            system("PAUSE");
            break;
        case 5:
            inicializar();
            break;
        case 6:
            sacarLista(); //se puede sacar cualquiera de la lista
            break;
        }
    } while (op != 6);
}

int main()
{
    menu();
    return 0;
}
