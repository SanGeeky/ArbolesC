#include <iostream>
#include<conio.h>
#include<iostream>
#include<stdio.h>
using namespace std;

class AVL;

// Clase Nodo de Arbol AVL:
class Nodo {
			  public:
			   // Constructor:
			   Nodo(const int dat, Nodo *pad=NULL, Nodo *izq=NULL, Nodo *der=NULL) :
			     dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
			   // Miembros:
			   int dato;
			   int FE;
			   Nodo *izquierdo;
			   Nodo *derecho;
			   Nodo *padre;
			   friend class AVL;
};

class AVL {
			  public:
			   enum {IZQUIERDO, DERECHO};
			   // Punteros de la lista, para cabeza y nodo actual:
			   Nodo *raiz;
			   Nodo *actual;
			   int contador;
			   int altura;
			
			  public:
			   // Constructor y destructor b�sicos:
			   AVL() : raiz(NULL), actual(NULL) {}
			   ~AVL() { Podar(raiz); }
			   // Insertar en �rbol ordenado:
			   void Insertar(const int dat);
			   // Borrar un elemento del �rbol:
			   void Borrar(const int dat);
			   // Funci�n de b�squeda:
			   bool Buscar(const int dat);
			   // Comprobar si el �rbol est� vac�o:
			   bool Vacio(Nodo *r) { return r==NULL; }
			   // Comprobar si es un nodo hoja:
			   bool EsHoja(Nodo *r) { return !r->derecho && !r->izquierdo; }
			   // Contar n�mero de nodos:
			   const int NumeroNodos();
			   const int AlturaArbol();
			   // Calcular altura de un dato:
			   int Altura(const int dat);
			   // Devolver referencia al dato del nodo actual:
			   int &ValorActual() { return actual->dato; }
			   // Moverse al nodo raiz:
			   void Raiz() { actual = raiz; }
			   // Aplicar una funci�n a cada elemento del �rbol:
			   void InOrden(void (*func)(int&, int) , Nodo *nodo=NULL, bool r=true);
			   void PreOrden(void (*func)(int&, int) , Nodo *nodo=NULL, bool r=true);
			   void PostOrden(void (*func)(int&, int) , Nodo *nodo=NULL, bool r=true);
			   void imprimir(void (*func)(int&, int) , Nodo *nodo, bool r,int x,int y, int x1);
			  private:
			   // Funciones de equilibrado:
			   void Equilibrar(Nodo *nodo, int, bool);
			   void RSI(Nodo* nodo);
			   void RSD(Nodo* nodo);
			   void RDI(Nodo* nodo);
			   void RDD(Nodo* nodo);
			   // Funciones auxiliares
			   void Podar(Nodo* &);
			   void auxContador(Nodo*);
			   void auxAltura(Nodo*, int);

};

// Poda: borrar todos los nodos a partir de uno, incluido
void AVL::Podar(Nodo* &nodo)
{
   // Algoritmo recursivo, recorrido en postorden
			   if(nodo) {
			      Podar(nodo->izquierdo); // Podar izquierdo
			      Podar(nodo->derecho);   // Podar derecho
			      delete nodo;            // Eliminar nodo
			      nodo = NULL;
			   }
}

// Insertar un dato en el �rbol AVL
void AVL::Insertar(const int dat)
{
   Nodo *padre = NULL;

   //cout << "Insertar: " << dat << endl;
   actual = raiz;
   // Buscar el dato en el �rbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat > actual->dato) actual = actual->derecho;
      else if(dat < actual->dato) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual)) return;
   // Si padre es NULL, entonces el �rbol estaba vac�o, el nuevo nodo ser�
   // el nodo raiz
   if(Vacio(padre)) raiz = new Nodo(dat);
   // Si el dato es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(dat < padre->dato) {
      padre->izquierdo = new Nodo(dat, padre);
      Equilibrar(padre, IZQUIERDO, true);
   }
   // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(dat > padre->dato) {
      padre->derecho = new Nodo(dat, padre);
      Equilibrar(padre, DERECHO, true);
   }
}

// Equilibrar �rbol AVL partiendo del nodo nuevo
void AVL::Equilibrar(Nodo *nodo, int rama, bool nuevo)
{
   bool salir = false;

   // Recorrer camino inverso actualizando valores de FE:
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; // Depende de si a�adimos ...
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; // ... o borramos
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = true; // La altura de las rama que
                                      // empieza en nodo no ha variado,
                                      // salir de Equilibrar
      else if(nodo->FE == -2) { // Rotar a derechas y salir:
         if(nodo->izquierdo->FE == 1) RDD(nodo); // Rotaci�n doble
         else RSD(nodo);                         // Rotaci�n simple
         salir = true;
      }
      else if(nodo->FE == 2) {  // Rotar a izquierdas y salir:
         if(nodo->derecho->FE == -1) RDI(nodo); // Rotaci�n doble
         else RSI(nodo);                        // Rotaci�n simple
         salir = true;
      }
      if(nodo->padre) 
         if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
      nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
   }   
}

// Rotaci�n doble a derechas
void AVL::RDD(Nodo* nodo)
{
   cout << "RDD" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->izquierdo;
   Nodo *R = Q->derecho;
   Nodo *B = R->izquierdo;
   Nodo *C = R->derecho;

   if(Padre) 
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir �rbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}


// Rotaci�n doble a izquierdas
void AVL::RDI(Nodo* nodo)
{
   cout << "RDI" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->derecho;
   Nodo *R = Q->izquierdo;
   Nodo *B = R->izquierdo;
   Nodo *C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir �rbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

// Rotaci�n simple a derechas
void AVL::RSD(Nodo* nodo)
{
   cout << "RSD" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->izquierdo;
   Nodo *B = Q->derecho;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir �rbol:
   P->izquierdo = B;
   Q->derecho = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Rotaci�n simple a izquierdas
void AVL::RSI(Nodo* nodo)
{
   cout << "RSI" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->derecho;
   Nodo *B = Q->izquierdo;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir �rbol:
   P->derecho = B;
   Q->izquierdo = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;
   
   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Eliminar un elemento de un �rbol AVL
void AVL::Borrar(const int dat)
{
   Nodo *padre = NULL;
   Nodo *nodo;
   int aux;

   actual = raiz;
   // Mientras sea posible que el valor est� en el �rbol
   while(!Vacio(actual)) {
      if(dat == actual->dato) { // Si el valor est� en el nodo actual
         if(EsHoja(actual)) { // Y si adem�s es un nodo hoja: lo borramos
            if(padre) // Si tiene padre (no es el nodo raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            delete actual; // Borrar el nodo
            actual = NULL;
            // El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
            // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
            if((padre->derecho == actual && padre->FE == 1) ||
               (padre->izquierdo == actual && padre->FE == -1)) {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }
            if(padre)
               if(padre->derecho == actual) Equilibrar(padre, DERECHO, false);
               else                         Equilibrar(padre, IZQUIERDO, false);
            return;
         }
         else { // Si el valor est� en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo m�s izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo m�s derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qu� ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que s�lo se eliminan nodos hoja.
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todav�a no hemos encontrado el valor, seguir busc�ndolo
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

void AVL::imprimir(void (*func)(int&, int) , Nodo *nodo, bool r,int x,int y, int x1)
{
   if(r) nodo = raiz;
   /*switch(Altura(nodo->dato)){
   			case 0: {gotoxy(77,2);func(nodo->dato, x1);break;}
   			case 1: {gotoxy(x,y);func(nodo->dato, x1);break;}
   			case 2: {gotoxy(x,y);func(nodo->dato, x1);break;}
   		}*/
   		
   if(nodo->izquierdo) imprimir(func, nodo->izquierdo, false,x-x1,y+3,x1-14); 
   if(nodo->derecho) imprimir(func, nodo->derecho, false,x+x1,y+3,x1-14);
   gotoxy(x,y);func(nodo->dato, x1);
}

// Recorrido de �rbol en inorden, aplicamos la funci�n func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::InOrden(void (*func)(int&, int) , Nodo *nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato, nodo->FE);
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}

// Recorrido de �rbol en preorden, aplicamos la funci�n func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::PreOrden(void (*func)(int&, int), Nodo *nodo, bool r)
{
   if(r) nodo = raiz;
   func(nodo->dato, nodo->FE);
   if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PreOrden(func, nodo->derecho, false);
}

// Recorrido de �rbol en postorden, aplicamos la funci�n func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::PostOrden(void (*func)(int&, int), Nodo *nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PostOrden(func, nodo->derecho, false);
   func(nodo->dato, nodo->FE);
}

// Buscar un valor en el �rbol
bool AVL::Buscar(const int dat)
{
   actual = raiz;

   // Todav�a puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return true; // dato encontrado
      else if(dat > actual->dato) actual = actual->derecho; // Seguir
      else if(dat < actual->dato) actual = actual->izquierdo;
   }
   return false; // No est� en �rbol
}

// Calcular la altura del nodo que contiene el dato dat
int AVL::Altura(const int dat)
{
   int altura = 0;
   actual = raiz;

   // Todav�a puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; // dato encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
   return -1; // No est� en �rbol
}

// Contar el n�mero de nodos
const int AVL::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnci�n auxiliar
   return contador;
}

// Funci�n auxiliar para contar nodos. Funci�n recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void AVL::auxContador(Nodo *nodo)
{
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del �rbol, que es la altura del nodo de mayor altura.
const int AVL::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); // Funci�n auxiliar
   return altura;
}

// Funci�n auxiliar para calcular altura. Funci�n recursiva de recorrido en
// postorden, el proceso es actualizar la altura s�lo en nodos hojas de mayor
// altura de la m�xima actual
void AVL::auxAltura(Nodo *nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   // Proceso, si es un nodo hoja, y su altura es mayor que la actual del
   // �rbol, actualizamos la altura actual del �rbol
   if(EsHoja(nodo) && a > altura) altura = a;
}
void bordes(int ix,int iy,int fx,int fy,int clr)
{
	textcolor(clr);
	for (int x=ix+1;x<fx;x++)
	{  gotoxy(x,iy);cprintf("�");gotoxy(x,fy);cprintf("�");	}
	for (int y=iy+1;y<fy;y++)
	{  gotoxy(ix,y);cprintf("�");gotoxy(fx,y);cprintf("�");	}
	gotoxy(ix,iy);cprintf("�");gotoxy(fx,iy);cprintf("�");
	gotoxy(ix,fy);cprintf("�");gotoxy(fx,fy);cprintf("�");
}
void m()
{  
		bordes(1,1,110,10,LIGHTCYAN);
		bordes(1,11,110,30,LIGHTCYAN);
}


void menus(int i,int x,int y,int color)
{  
		bordes(1,1,100,30,LIGHTCYAN);
		int j;
		j=y;
		switch(i)
		{ 
			case 1:bordes(23,1,61,5,14);textcolor(color);
						gotoxy(25,3);cprintf("MENU PRINCIPAL : Arboles AVL");
						gotoxy(x,y);cprintf(" 1- Insertar Datos -");y++;
						gotoxy(x,y);cprintf(" 2- Eliminar Datos -");y++;
						gotoxy(x,y);cprintf(" 3- Buscar Datos   -");y++;
						gotoxy(x,y);cprintf(" 4- Mostrar        -");y++;
						gotoxy(x,y);cprintf(" 5- Salir          -");y++;
						bordes(x-2,j-1,x+21,y,LIGHTCYAN);     //x,y,finx,finy,color;
						break;
			case 2:bordes(33,1,51,5,14);textcolor(color);
						gotoxy(35,3);cprintf(" MOSTRAR DATOS");
						gotoxy(x,y);cprintf(" 1- Inorden   -");y++;
						gotoxy(x,y);cprintf(" 2- Postorden -");y++;
						gotoxy(x,y);cprintf(" 3- Preorden  -");y++;
						gotoxy(x,y);cprintf(" 4- Regresar  -");y++;
						bordes(x-2,j-1,x+16,y,LIGHTCYAN);     //x,y,finx,finy,color;
						break;
			case 3:bordes(33,1,51,5,14);textcolor(color);
						gotoxy(35,3);cprintf(" ELIMINACION DE DATOS");
						gotoxy(x,y);cprintf(" 1- Eliminar Dato   -");y++;
						gotoxy(x,y);cprintf(" 2- Eliminar Arbol  -");y++;
						gotoxy(x,y);cprintf(" 3- Regresar        -");y++;
						bordes(x-2,j-1,x+22,y,LIGHTCYAN);     //x,y,finx,finy,color;
						break;
		}
 
}

// Funci�n de prueba para recorridos del �rbol
void Mostrar(int &d, int FE)
{
   cout << "(" << d << ")";
}
/*
int main()
{
	clrscr();
	window( 1, 1, 130, 100 );
	char op;
  	int op1,op2,op3,op4,x,y,dato,finy,cen=0,cenavl=1;
  	AVL ArbolInt;
  	do{  	
			clrscr();x=31;y=7;
			//******para empezar un nuevo arbol********
			//****************************************
		  	textcolor(LIGHTCYAN);
		  	clrscr();x=33;y=7;
			menus(1,x,y,LIGHTCYAN);      //#menu,x,y,colortexto;
			gotoxy(25,3);cprintf("ARBOLES BALANCEADOS DE BUSQUEDA");
			gotoxy(x,20);cprintf("�Elija una opcion?.....  ");std::cin>>op1;				
			
			switch(op1){ 
							case 1://INSERCION
										do{
													
													clrscr();m();
													textcolor(LIGHTCYAN);gotoxy(20,4); cprintf("INSERCION DE DATOS ");
													gotoxy(10,6); cout<<"Dato num�rico : ";cin>>dato;
													ArbolInt.Insertar(dato);
													int d=ArbolInt.AlturaArbol();
													gotoxy(55,13);ArbolInt.imprimir(Mostrar,NULL,true,54,13,26);
													gotoxy(20,9);cprintf("�Desea insertar mas datos ? s/n...  ");cin>>op;
													cen=1;
										}while(op!='n');
										//getch();
										break;
							case 2://ELIMINACION
										clrscr();
										//if(p!=NULL){
													clrscr();
												  	x=35;y=7;
												  	menus(3,x,y,LIGHTCYAN);      //#menu,x,y,colortexto;
												  	gotoxy(x,finy+3);std::cin>>op2;
												  	textcolor(YELLOW);
													switch(op2){
															  		case 1: 
															  					clrscr();
													 							textcolor(LIGHTMAGENTA);gotoxy(28,4); cprintf("ELIMINACION DE DATOS ");
																				gotoxy(12,8); cprintf("Dato a eliminar: "); std::cin>>dato;
																				ArbolInt.Borrar(dato);
																				gotoxy(12,13); cprintf("Dato Eliminado Exitosamente..");
																				break;
													 				case 2: 
																	 			clrscr();
																				//p->vacio(p); p=NULL; cen=0;
																				gotoxy(12,13); cprintf("Arbol Eliminado Exitosamente..");
																				break;
													}
										/*}else{
										 			std::cout<<"EL ARBOL SE ENCUENTRA VACIO";
										}*/
		// 								getch();
		// 								break;
		// 					case 3://BUSCAR
		// 								clrscr();
		// 								//if(p!=NULL){
		// 												textcolor(LIGHTCYAN);gotoxy(28,4); cprintf("BUSQUEDA DE DATOS ");
		// 												gotoxy(12,8); cprintf("Dato a buscar : "); std::cin>>dato;
		// 												gotoxy(12,10);ArbolInt.Borrar(dato); getch();
		// 								/*}
		// 								else{
		// 								 				std::cout<<"EL ARBOL SE ENCUENTRA VACIO";break;
		// 								}*/
		// 								getch();
		// 								break;
		// 					case 4://MOSTRAR
		// 								do{
		// 											clrscr();
		// 										  	x=35;y=7;
		// 										  	menus(2,x,y,LIGHTCYAN);      //#menu,x,y,colortexto;
		// 										  	//op4=adorno(x-1,y,15,finy-1,BLACK,BLUE);  //x,y,finx+x,finy,colorflecha,colorluego;
		// 										  	gotoxy(x,finy+3);std::cin>>op2;
		// 										  	textcolor(YELLOW);
		// 								  			switch(op2){
		// 													  		case 1: 
		// 															  			clrscr();
		// 																		//if(p!=NULL)	{
		// 																		cout << "InOrden: ";
		// 																		ArbolInt.InOrden(Mostrar); //}
		// 																		//else    	{std::cout<<"ARBOL VACIO";}
		// 																		getch();break;
		// 											 				case 2: 
		// 															 			clrscr();
		// 																		//if(p!=NULL)	{p->postorden(p); }
		// 																		cout << "PostOrden: ";
		// 																		ArbolInt.PostOrden(Mostrar);
		// 																		//else      	{std::cout<<"ARBOL VACIO";}
		// 																		getch();break;
		// 											 				case 3: 
		// 															 			clrscr();
		// 															 			cout << "PreOrden: ";
   	// 																			ArbolInt.PreOrden(Mostrar);
		// 																		//if(p!=NULL) {p->preorden(p); }
		// 																		//else       	{std::cout<<"ARBOL VACIO";}
		// 																		getch();break;
		// 											}
		// 								}
		// 								while(op2!=4);
		// 								break;
		// 				}
		// 				cen=1;
		// 				clrscr();gotoxy(25,3);std::cout<<"Final";
		// }while(op1!=5);	
  	


  	
  	
  	
  	
  	
/*  	
   // Un �rbol de enteros
   

   // Inserci�n de nodos en �rbol:
/*   ArbolInt.Insertar(15);
   ArbolInt.Insertar(4);
   ArbolInt.Insertar(20);
   ArbolInt.Insertar(3);
   ArbolInt.Insertar(25);
   ArbolInt.Insertar(6);
   ArbolInt.Insertar(8);
   ArbolInt.Insertar(65);
   ArbolInt.Insertar(50);
   ArbolInt.Insertar(23);
   ArbolInt.Insertar(70);
   ArbolInt.Insertar(82);
   ArbolInt.Insertar(68);
   ArbolInt.Insertar(39);

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Mostrar el �rbol en tres ordenes distintos:
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;

   ArbolInt.Borrar(8);
   ArbolInt.Borrar(11);

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Mostrar el �rbol en tres ordenes distintos:
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;*/

/*   // Borraremos algunos elementos:
   cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
   ArbolInt.Borrar(5);
   cout << "Borrar   5: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(8);
   cout << "Borrar   8: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(15);
   cout << "Borrar  15: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(245);
   cout << "Borrar 245: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   ArbolInt.Borrar(4);
   cout << "Borrar   4: ";
   ArbolInt.InOrden(Mostrar);
   ArbolInt.Borrar(17);
   cout << endl;
   cout << "Borrar  17: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;

   // Veamos algunos par�metros
   cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
   cout << "Altura de 1 " << ArbolInt.Altura(1) << endl;
   cout << "Altura de 10 " << ArbolInt.Altura(10) << endl;
   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   cin.get();

   // Arbol de cadenas:
   AVL<Cadena> ArbolCad;

   // Inserci�n de valores:
   ArbolCad.Insertar("Hola");
   ArbolCad.Insertar(",");
   ArbolCad.Insertar("somos");
   ArbolCad.Insertar("buenos");
   ArbolCad.Insertar("programadores");

   // Mostrar en diferentes ordenes:
   cout << "InOrden: ";
   ArbolCad.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolCad.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolCad.PostOrden(Mostrar);
   cout << endl;

   // Borrar "buenos":
   ArbolCad.Borrar("buenos");
   cout << "Borrar 'buenos': ";
   ArbolCad.InOrden(Mostrar);
   cout << endl; */
  /*  cin.get();
   return 0;
}
 */



