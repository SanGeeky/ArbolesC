#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>

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

typedef struct nodoArbol
{
    int dato;
    struct nodoArbol *izq, *dere, *padre;
    int fe, alturaIzq, alturaDere;
} arbol, *parbol;
arbol *raiz, *nuevo, *recorrer;
arbol *PadreAB, *sHijo, *abuelo, *hijoHijo;

void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *padre);
void agregarDatos();
void verArbol(arbol *recorrer, int n);
void vaciarArbol(arbol *recorrer);

void postorden(arbol *recorrerinterno){
  	if (recorrerinterno != NULL) {
    	postorden(recorrerinterno->izq);
    	postorden(recorrerinterno->dere);
  	}
}


void vaciarArbol(arbol *recorrerinterno){
  	if (recorrerinterno != NULL) {
    	postorden(recorrerinterno->izq);
    	postorden(recorrerinterno->dere);
    	
    	if (recorrerinterno->dato == raiz->dato){
    		raiz=NULL;
		}else{
			delete(recorrerinterno);//Liberamos la memoria.
		}
  	}
}

void graficarArbol(arbol *recorrer, int x, int y)
{

    if (recorrer == NULL)
        return;

    graficarArbol(recorrer->dere, x + 5, y + 1);

    gotoxy(x, y);
    cprintf("%d", recorrer->dato);

    graficarArbol(recorrer->izq, x - 5, y + 1);

}

void verArbol(arbol *recorrer, int n)
{
    if (recorrer == NULL)
        return;
    verArbol(recorrer->dere, n + 1);

    for (int i = 0; i < n; i++)
        cout << "   ";

    cout << recorrer->dato << endl;

    verArbol(recorrer->izq, n + 1);
}

parbol nuevoNodo(int num)
{
    nuevo = new (arbol); //Crea la reserva de espacio en memoria.
    nuevo->dato = num;
    nuevo->izq = NULL;  //Punteros a tierra
    nuevo->dere = NULL; //Punteros a tierra

    return nuevo;
}

void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *PadreAB)
{

    if (raiz == NULL)
    {                 //Si es el primer nodo entonces la raíz aún será nula porque no existe nada dentro de ella.
        raiz = nuevo; //Asignar a la raíz el valor del nuevo nodo creado...
        raiz->padre = NULL;
    }
    else
    {
        if (nuevo->dato <= recorrer->dato)
        {
            if (recorrer->izq != NULL)
            {
                PadreAB = recorrer->izq;
                //BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
                insertarNuevo(recorrer->izq, nuevo, PadreAB);
            }
            else
            {
                recorrer->izq = nuevo;
                nuevo->padre = PadreAB;
                return;
            }
        }
        else if (nuevo->dato > recorrer->dato)
        {
            if (recorrer->dere != NULL)
            {
                PadreAB = recorrer->dere;
                //BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
                insertarNuevo(recorrer->dere, nuevo, PadreAB);
            }
            else
            {
                recorrer->dere = nuevo;
                nuevo->padre = PadreAB;
                return;
            }
        }
    }
}

void agregarDatos()
{
    system("cls");
    cout << "\nArbol " << endl;
    aux3 = pri2;
    while (aux3 != NULL)
    {

        recorrer = raiz; //Se apunta a recorrer en al mismo nodo donde apunta la raíz

        nuevo = nuevoNodo(aux3->inf2); //Almacena el nuevo nodo para luego insertarlo en el arbol.

        //Evalua si el nodo ya existe en el arbol.
        PadreAB = raiz;
        insertarNuevo(recorrer, nuevo, PadreAB);

        //BBaltura(recorrer);
        //BBnecesidadEquilibrar(recorrer);

        aux3 = aux3->sig2;
    }
    //verArbol(raiz,0);
    graficarArbol(recorrer, 40, 5);
    //system("PAUSE");
}

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
        cout << "LISTA ORDENADA:    \n\n";
        while (aux != NULL)
        {
            cout << aux->inf << " -> ";
            aux = aux->sig;
        }
    }
    else
        cout << "Lista VACIA....\n";
    cout << "\n\n";
    system("PAUSE");
}

void listar2(nodo2 *list2)
{
    system("cls");
    if (list2 != NULL)
    {
        aux3 = list2;
        cout << "Lista ORIGINAL:    \n\n";
        while (aux3 != NULL)
        {
            cout << aux3->inf2 << " -> ";
            aux3 = aux3->sig2;
        }
    }
    else
        cout << "Lista VACIA....\n";
    
    cout << "\n\n";
    system("PAUSE");

}

void ingresar() // Genera lista de aleatorios
{
    vaciarlista();

    srand(time(NULL));
    int num, count=0;
    
    do{
        system("cls");
        cout << "Digite de que tamanio desea la lista(minimo 30): ";
        cin >> count;
        if(count<30){
            cout<<"debe ser mas de 30"<<endl;
            getch();
        }
    }while(count<30);
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
}


void imprimirGrafo()
{
    if (priPadre == NULL)
        cout << "\nNo hay datos.";
    else
    {
        auxPadre = priPadre;
        while (auxPadre != NULL)
        {
            cout << "\n\nPadre: " << auxPadre->inf;
            auxHijo = auxPadre->hijo;
            while (auxHijo != NULL)
            {
                cout << "\n\tHijo: " << auxHijo->inf;
                auxHijo = auxHijo->sig;
            }
            auxPadre = auxPadre->sig;
        }
    }
    cout << endl;
    system("pause");
}

void insertarHijo(int dato, listaPadre *nodoPadre)
{
    if (nodoPadre->hijo == NULL)
    {
        priHijo = new listaHijo();
        priHijo->inf = dato;
        ultHijo = priHijo;
        ultHijo->sig = NULL;
        priHijo->ant = NULL;
        priHijo->padre = nodoPadre;
        nodoPadre->hijo = priHijo;
    }
    else
    {
        if (dato < priHijo->inf) //ingresar priHijomero nuevo
        {

            nueHijo = new listaHijo(); //reserva espacio
            nueHijo->inf = dato;       //pide el valor
            nueHijo->sig = priHijo;
            priHijo->ant = nueHijo;
            priHijo = nueHijo;
            priHijo->ant = NULL;
            priHijo->padre = nodoPadre;
            nodoPadre->hijo = priHijo;
        }
        else
        {
            if (dato > ultHijo->inf)
            {
                nueHijo = new listaHijo();
                nueHijo->inf = dato;
                ultHijo->sig = nueHijo;
                nueHijo->ant = ultHijo;
                ultHijo = nueHijo;
                ultHijo->sig = NULL;
                ultHijo->padre = NULL;
            }
        }
    }
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
            priPadre->hijo = NULL;
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
                priPadre->hijo = NULL;
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
                    ultPadre->hijo = NULL;
                }
                else
                {
                    auxPadre = priPadre;
                    while (auxPadre != NULL && decima != auxPadre->inf && decima > auxPadre->inf)
                    { //VALIDAR QUE NO ESTE REPETIDO
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
                        nuePadre->hijo = NULL;

                        auxPadre->ant = nuePadre;
                    }
                }
            }
        }

        aux = aux->sig;
    }

    ///Agregamos NODOS Hijos Yeii
    auxPadre = priPadre;

    while (auxPadre != NULL)
    {
        aux = pri; //Volvemos a recorrer la lista
        while (aux != NULL)
        {
            decima = aux->inf / 10;
            if (auxPadre->inf == decima)
            {
                insertarHijo(aux->inf, auxPadre);
            }
            aux = aux->sig;
        }
        auxPadre = auxPadre->sig; //Seguimos con el siguiente padre
    }

    imprimirGrafo();
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
        aux3 = pri2;
        auxPadre = priPadre;
        auxHijo = auxHijo;
        while (aux3 != NULL)
        {

            if (aux != NULL)
            {
                pri = aux->sig;
                delete aux;
                aux = pri;
            }
            
            if (auxPadre != NULL)
            {
                priPadre = auxPadre->sig;
                delete auxPadre;
                auxPadre = priPadre; 
            }

            if (auxHijo != NULL)
            {
                auxHijo = auxHijo->sig;
                delete auxHijo;
                auxHijo = auxHijo; 
            }

            cout << "Liberado: " << aux3->inf2 << endl;
            
            pri2 = aux3->sig2;
           
            delete aux3; 
            aux3 = pri2; 
        }
    }
    recorrer = raiz;
    vaciarArbol(recorrer);
    cout << "Lista VACIA....\n";


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
                 << "\n2. Mostrar Lista Original: "
                 << "\n3. Mostrar lista sin datos repetidos y ordenada: "
                 << "\n4. Generar y Mostrar Grafo"
                 << "\n5. Generar y Mostrar Arbol Binario"
                 << "\n6. Limpiar Estructuras"

                 << "\n9. Salir"
                 << "\nOpcion:  ";
            cin >> op;
        } while (op < 1 || op > 9);
        switch (op)
        {
        case 1:
            ingresar();
            break;
        case 2:
            listar2(pri2);
            break;
        case 3:
            listar(pri);
            break;
        case 4:
            generarGrafo();
            break;
        case 5:
            agregarDatos();
            gotoxy(1,1);system("pause");
            break;
        case 6:
            inicializar();
            inicializar();
            cin.ignore();
            cin.get();

            break;

        }
    } while (op != 9);
}

int main()
{
    menu();
    return 0;
}
