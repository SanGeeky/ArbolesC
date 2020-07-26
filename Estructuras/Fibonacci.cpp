/*
Lista din�mica: 
Ingreso y salida como el de una Cola
      
*/
//////Miguel Angel Florez Pantoja
#include <iostream>
#include <cstdlib>

using namespace std;

struct nodo
{
   int inf;
   struct nodo *sig, *ant;
} * pri, *nue, *aux, *ult, *dato, *aux2;

void ingresar() // se ingresa, el  nuevo menor que el primero y mayor que el ultimo
{
   int valor;

   if (pri == NULL)
   {
      pri = new nodo();
      cout << "Primer dato: ";
      cin >> pri->inf;
      ult = pri;
      ult->sig = NULL;
      pri->ant = NULL;
   }
   else
   {
      cout << "Nuevo dato: ";
      cin >> valor;
      if (valor < pri->inf) //ingresar primero nuevo
      {

         nue = new nodo(); //reserva espacio
         nue->inf = valor; //pide el valor
         nue->sig = pri;
         pri->ant = nue;
         pri = nue;
         pri->ant = NULL;
      }
      else
      {
         if (valor > ult->inf)
         {
            nue = new nodo();
            nue->inf = valor;
            ult->sig = nue;
            nue->ant = ult;
            ult = nue;
            ult->sig = NULL;
         }
         else
         {
            aux = pri;
            while (aux != NULL && valor != aux->inf && valor > aux->inf)
            {  //VALIDAR QUE NO ESTE REPETIDO
               //
               dato = aux;
               aux = aux->sig;
            }
            if (aux->inf == valor)
            {
               cout << "Repetido...";
               system("pause");
            }
            else
            { //ingresar un numero en medio
               nue = new nodo();
               nue->inf = valor;
               dato->sig = nue;
               nue->ant = dato;
               nue->sig = aux;
               aux->ant = nue;
            }
         }
      }
   }
}

void ingresarfibonacci(int dato)
{ // NO SE PUEDE MODIFICAR LA FUNCION INGRESAR

   // Ya que es una lista ordenada por defecto 
   // agregamos los datos siempre al final de la lista

   if (pri == NULL)
   {
      //revisamos si la lista esta vacia y la inicializamos
      pri = new nodo();
      pri->inf = dato;
      ult = pri;
      //se agregan los enlaces de lista doble
      ult->sig = NULL;
      pri->ant = NULL;
   }
   else
   {
      //si la lista no esta vacia agregamos el nuevo dato
      // al final
      nue = new nodo();
      nue->inf = dato; // asignamos dato
      ult->sig = nue;  // enlazamos el ultimo nodo con el nuevo
      nue->ant = ult;  // el nuevo nodo se enlaza con el ultimo nodo
      ult = nue;       // el nuevo nodo es ahora el ultimo
      ult->sig = NULL; // ultimo apunta a null
   }
}

void listar()
{
   system("cls");
   if (pri != NULL)
   {
      aux = pri;
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

int fibonacci(int n)
{
   //llamamos al metodo vaciar lista para empezar
   //la serie desde cero
   vaciarlista();

   // inicializamos variables para hacer nuestra serie
   int suma = 1; //numero que se agregara a la serie
   int serie = 1; //resultado actual de la serie
   int resultado = 1; // resultado final

   // la serie fibonacci empieza con los numero 
   // cero y uno por lo que los agregamos por defecto a la lista
   //con la funcion ingresarfibonacci();
   // recibe como parametro el dato a ingresar
   ingresarfibonacci(0);
   ingresarfibonacci(1);
   ingresarfibonacci(1);

   //si el numero es cero o uno significa que son los primeros elementos
   //por lo tanto se retorna resultado=1
   if (n == 1 || n == 0)
   {
      //cout << resultado;
      return resultado;
   }
   else
   {
      //si la serie a obtener es mayor a cero o uno
      // se calcula la serie con el las anteriores variables declaradas
      // y se tiene como limite el 'n-esimo' numero ingresado por el usuario
      //empezando a contar desde 1 
      for (int i = 1; i < n; i++)
      {
         suma = serie; // se asigna el numero actual de la serie para ser sumado
         serie = resultado; // se asigna el resultado final de la serie
         resultado = suma + serie; // se obtiene el resultado final de la serie
         //cout << resultado << "\n";
         ingresarfibonacci(resultado); // se ingresa el resultado a la lista
      }
   }

   //retornamos el resultado final de la serie
   return resultado;
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
              << "\n1. Ingresar dato: "
              << "\n2. Listar"
              << "\n3. Sacar"
              << "\n4. Buscar"
              << "\n5. Inicializar"
              << "\n6. Sale Lista"
              << "\n7. Fibonacci"

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
         listar();
         break;
      case 3:
         sacar(); //siempre saca el primero de la lista
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
      case 7:
         int n;
         cout << "Ingrese n de serie fibonacci: " ;
         cin >> n;
         /// Agregamos la nueva funcion donde enviamos 'n' como el numero limite 
         /// de nuestra serie fibonacci
         int serie = fibonacci(n);
         cout << "\n"
              << "serie: " << serie
              << "\n";
         /// al final imprimimos el resultado final de la serie
         system("PAUSE");
      }
   } while (op != 9);
}

int main()
{
   menu();
   return 0;
}
