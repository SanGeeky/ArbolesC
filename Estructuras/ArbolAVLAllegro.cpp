#include <allegro.h>
#include <iostream>
#include<conio.h>
#include<iostream>
#include<stdio.h>
using namespace std;
int Menu();
int MenuMostrar();
void Mostrar(int &d, int x,int y);
void Mostrar2(int &d, int FE,int x, int y);
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
			  private:
			   enum {IZQUIERDO, DERECHO};
			  
			   Nodo *raiz;
			   Nodo *actual;
			   int contador;
			   int altura;
			
			  public:
			  
			   AVL() : raiz(NULL), actual(NULL) {}
			   ~AVL() { Podar(raiz); }
			 
			   void Insertar(const int dat);
			 
			   bool Borrar(const int dat);
			 
			   bool Buscar(const int dat);
			  
			   bool Vacio(Nodo *r) { return r==NULL; }
			  
			   bool EsHoja(Nodo *r) { return !r->derecho && !r->izquierdo; }
			 
			   const int NumeroNodos();
			   const int AlturaArbol();
			   
			   const int MostrarArbol();
			   const int MostrarDatos(int op);
			   const int PedirDato(int opc);
			  
			   int Altura(const int dat);
			  
			   int &ValorActual() { return actual->dato; }
			  
			   void Raiz() { actual = raiz; }
			   
			   void InOrden(void (*func)(int&, int, int, int) , Nodo *nodo=NULL, bool r=true,int x=170);
			   void PreOrden(void (*func)(int&, int, int, int) , Nodo *nodo=NULL, bool r=true,int x=170);
			   void PostOrden(void (*func)(int&, int, int, int) , Nodo *nodo=NULL, bool r=true,int x=170);
			   void Imprimir(void (*func)(int&, int, int) , Nodo *nodo, bool r,int x,int y, int x1);
			  private:
			   
			   void Equilibrar(Nodo *nodo, int, bool);
			   void RSI(Nodo* nodo);
			   void RSD(Nodo* nodo);
			   void RDI(Nodo* nodo);
			   void RDD(Nodo* nodo);
			   
			   void Podar(Nodo* &);
			   void auxContador(Nodo*);
			   void auxAltura(Nodo*, int);

};

// Poda: borrar todos los nodos a partir de uno, incluido
void AVL::Podar(Nodo* &nodo)
{
   // Algoritmo recursivo, recorrido en postorden
			   if(nodo) {
			      Podar(nodo->izquierdo); 
			      Podar(nodo->derecho);   
			      delete nodo;           
			      nodo = NULL;
			   }
}


void AVL::Insertar(const int dat)
{
   Nodo *padre = NULL;
   actual = raiz;
   
 
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat > actual->dato) actual = actual->derecho;
      else if(dat < actual->dato) actual = actual->izquierdo;
   }

  
   if(!Vacio(actual)) return;
 
   if(Vacio(padre)) raiz = new Nodo(dat);
   
   else if(dat < padre->dato) {
      padre->izquierdo = new Nodo(dat, padre);
      Equilibrar(padre, IZQUIERDO, true);
   }

   else if(dat > padre->dato) {
      padre->derecho = new Nodo(dat, padre);
      Equilibrar(padre, DERECHO, true);
   }
}


void AVL::Equilibrar(Nodo *nodo, int rama, bool nuevo)
{
   bool salir = false;

   // Recorrer camino inverso actualizando valores de FE:
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--;
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; 
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = true;
      else if(nodo->FE == -2) { 
         if(nodo->izquierdo->FE == 1) RDD(nodo); 
         else RSD(nodo);                        
         salir = true;
      }
      else if(nodo->FE == 2) {  // Rotar a izquierdas y salir:
         if(nodo->derecho->FE == -1) RDI(nodo); 
         else RSI(nodo);                        
         salir = true;
      }
      if(nodo->padre) 
         if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
      nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
   }   
}

void AVL::RDD(Nodo* nodo)
{
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


   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;
   

   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;


   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}


void AVL::RDI(Nodo* nodo)
{
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

 
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;
   

   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;


   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

void AVL::RSD(Nodo* nodo)
{
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->izquierdo;
   Nodo *B = Q->derecho;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;


   P->izquierdo = B;
   Q->derecho = P;
   

   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   P->FE = 0;
   Q->FE = 0;
}


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


   P->derecho = B;
   Q->izquierdo = P;

   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;
   

   P->FE = 0;
   Q->FE = 0;
}

// Eliminar un elemento deL árbol AVL
bool AVL::Borrar(const int dat)
{
   Nodo *padre = NULL;
   Nodo *nodo;
   int aux;
   	
   actual = raiz;
  
      if(dat == actual->dato) { 
         if(EsHoja(actual)) { 
         	
            if(padre) 
             
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
        	
            delete actual; // Borrar el nodo
            actual = NULL;
            
           
		    if((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1)) {
		               padre->FE = 0;
		               actual = padre;
		               padre = actual->padre;
		    }	
            if(padre)
               if(padre->derecho == actual) Equilibrar(padre, DERECHO, false);
               else                         Equilibrar(padre, IZQUIERDO, false);
            return true;
         }
         else { 
         
            padre = actual;
           
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
       
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
            return true;
         }
      }
      else { 
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
         
   }
	return false;
}

void AVL::Imprimir(void (*func)(int&, int, int) , Nodo *nodo, bool r,int x,int y, int x1)
{
   if(r) nodo = raiz;  		
   if(nodo->izquierdo) Imprimir(func, nodo->izquierdo, false,x-x1,y+20,x1-70); 
   if(nodo->derecho) Imprimir(func, nodo->derecho, false,x+x1,y+20,x1-70); 
   func(nodo->dato, x,y);
}


void AVL::InOrden(void (*func)(int&, int, int, int) , Nodo *nodo, bool r, int x)
{
   x+=20;
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato, nodo->FE, x,170);
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}


void AVL::PreOrden(void (*func)(int&, int, int,int), Nodo *nodo, bool r,int x)
{
   x+=20;
   if(r) nodo = raiz;
   func(nodo->dato, nodo->FE,x,133);
   if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PreOrden(func, nodo->derecho, false);
}

void AVL::PostOrden(void (*func)(int&, int, int,int), Nodo *nodo, bool r,int x)
{
   x+=20;
   if(r) nodo = raiz;
   if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PostOrden(func, nodo->derecho, false);
   func(nodo->dato, nodo->FE,x,210);
}

bool AVL::Buscar(const int dat)
{
   actual = raiz;

   while(!Vacio(actual)) {
      if(dat == actual->dato) return true; // dato encontrado
      else if(dat > actual->dato) actual = actual->derecho; // Seguir
      else if(dat < actual->dato) actual = actual->izquierdo;
   }
   return false; // No está en árbol
}

int AVL::Altura(const int dat)
{
   int altura = 0;
   actual = raiz;

 
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; 
         altura++;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
const int AVL::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}


void AVL::auxContador(Nodo *nodo)
{
   contador++;  // Otro nodo

   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
const int AVL::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); 
   return altura;
}


void AVL::auxAltura(Nodo *nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);

   if(EsHoja(nodo) && a > altura) altura = a;
}
 

void Mostrar(int &d, int x,int y)
{
	BITMAP *buffer = create_bitmap(600,400);
	BITMAP*mostrar;

	mostrar=load_bitmap("mostrar42.bmp",NULL); 
	draw_sprite(buffer,mostrar,0,0);
	
   	textprintf(buffer, font ,x,y,150,"(%d)",(d));
   	blit(buffer, screen, 0, 0, 0, 0, 640, 480);
   	readkey();
} 


void Mostrar2(int &d, int FE,int x,int y)
{
	BITMAP *buffer = create_bitmap(600,400);
	BITMAP*mostrar;

	mostrar=load_bitmap("mostrar.bmp",NULL); 
	draw_sprite(buffer,mostrar,0,0);
	
   	textprintf(buffer, font ,x,y,150,"(%d)",(d));
   	blit(buffer, screen, 0, 0, 0, 0, 640, 480);
   	readkey();
}

const int AVL::MostrarArbol()
{
	BITMAP *buffer = create_bitmap(600,400);
	
    clear_to_color(buffer, 0x333333); 
	blit(buffer, screen, 0, 0, 0, 0, 640, 480);
	
    Imprimir(Mostrar,NULL,true,250,100,150);
	readkey(); 
	return(1);
}
//Inicializa el menu principal y lee las coordenadas del mouse para hacer cambio de imagen
int Menu()
{   
    int t=0;
    int click=1,accion;
    
    BITMAP *buffer = create_bitmap(600,400);
    clear_to_color(buffer, 0x333333);
    
    BITMAP*portada;
    BITMAP*portada1;
    BITMAP*portada2;
    BITMAP*portada3;
    BITMAP*portada4;
    BITMAP*portada5;
    BITMAP*cursor;
    
    portada=load_bitmap("portada.bmp",NULL);
    portada1=load_bitmap("portada1.bmp",NULL);
    portada2=load_bitmap("portada2.bmp",NULL);
    portada3=load_bitmap("portada3.bmp",NULL);
    portada4=load_bitmap("portada4.bmp",NULL);
    portada5=load_bitmap("portada5.bmp",NULL);
    cursor=load_bitmap("cursor2.bmp",NULL); 
    
    while(click==1){
        
       t=0;            
       if(t==0){
        draw_sprite(buffer,portada,0,0);
         }  
              
       if(mouse_x>25&&mouse_x<110&&mouse_y>142&&mouse_y<166){
        draw_sprite(buffer,portada1,0,0);
           if(mouse_b & 1){
              accion=1;
              click=0;
              }
           t=1;   
        }
      
       if(mouse_x>20 && mouse_x<111 && mouse_y>188 && mouse_y<209){
        draw_sprite(buffer,portada2,0,0);
           if(mouse_b & 1){
              accion=2;
              click=0;
              }
            t=2;  
        }
     
       if(mouse_x>20 && mouse_x<88 && mouse_y>224 && mouse_y<245){ 
        draw_sprite(buffer,portada3,0,0);
           if(mouse_b & 1){
              accion=3;
              click=0; 
              }
            t=3;
        }
     
       if(mouse_x>17 && mouse_x<97 && mouse_y>264 && mouse_y<284){
        draw_sprite(buffer,portada4,0,0);
           if(mouse_b & 1){
              accion=4;
              click=0;   
              }
            t=4;  
        }
     
       if(mouse_x>20 && mouse_x<65 && mouse_y>299 && mouse_y<319){
        draw_sprite(buffer,portada5,0,0);
           if(mouse_b & 1){
              accion=5;
              click=0;   
           }
        t=5;   
        }
      
        masked_blit(cursor,buffer,0,0, mouse_x, mouse_y, 13,22);     
        blit(buffer, screen, 0, 0, 0, 0, 640, 480); 
   
   }
   return accion;
    
}


int MenuMostrar()
{   
    int t=0;
    int click=1,accion;
    
    BITMAP *buffer = create_bitmap(600,400);
    clear_to_color(buffer, 0x333333);
    
    BITMAP*mostrar;
    BITMAP*mostrar1;
    BITMAP*mostrar2;
    BITMAP*mostrar3;
    BITMAP*cursor;
    
    mostrar=load_bitmap("mostrar.bmp",NULL);
    mostrar1=load_bitmap("mostrar1.bmp",NULL);
    mostrar2=load_bitmap("mostrar2.bmp",NULL);
    mostrar3=load_bitmap("mostrar3.bmp",NULL);
    cursor=load_bitmap("cursor2.bmp",NULL); 
    
    while(click==1){
        
       t=0;            
       if(t==0){
        draw_sprite(buffer,mostrar,0,0);
         }  
              
       if(mouse_x>34 && mouse_x<125 && mouse_y>123 && mouse_y<140){
        draw_sprite(buffer,mostrar1,0,0);
           if(mouse_b & 1){
              accion=1;
              click=0;
              }
           t=1;   
        }
      
       if(mouse_x>34 && mouse_x<113 && mouse_y>160 && mouse_y<179){
        draw_sprite(buffer,mostrar2,0,0);
           if(mouse_b & 1){
              accion=2;
              click=0;
              }
            t=2;  
        }
     
       if(mouse_x>34 && mouse_x<132 && mouse_y>200 && mouse_y<217){ 
        draw_sprite(buffer,mostrar3,0,0);
           if(mouse_b & 1){
              accion=3;
              click=0; 
              }
            t=3;
        }
      
        masked_blit(cursor,buffer,0,0, mouse_x, mouse_y, 13,22);     
        blit(buffer, screen, 0, 0, 0, 0, 640, 480); 
   
   }
   return accion;
    
}

const int AVL::MostrarDatos(int op)
{
	BITMAP *buffer = create_bitmap(600,400);
    clear_to_color(buffer, 0x333333);
    
    BITMAP*mostrar;
    BITMAP*cursor;
	int click,cont,t;
	mostrar=load_bitmap("mostrar.bmp",NULL);
    cursor=load_bitmap("cursor2.bmp",NULL); 
    draw_sprite(buffer,mostrar,0,0);
	blit(buffer, screen, 0, 0, 0, 0, 640, 480);
	switch(op){
												     case 1:{ 		//Insercion de datos
												          			PreOrden(Mostrar2,NULL,true,170); 
																	break;
												     }
												     case 2:{		//Eliminacion de datos
												     			 	InOrden(Mostrar2,NULL,true,170); 
												          			break;    
												    }
												     case 3:{		//Busqueda de datos
												     				PostOrden(Mostrar2,NULL,true,170); 
												          			break;
												    }
	}
	if(op==true)textprintf(buffer, font ,50,360,150,"Presione cualquier tecla para volver al menu principal..");
	blit(buffer, screen, 0, 0, 0, 0, 640, 480);
	readkey();
	return(1);
}


const int AVL::PedirDato(int opc)
{
    char respuesta='s';
	BITMAP *buffer = create_bitmap(600,400);
    clear_to_color(buffer, 0x333333);
    
    BITMAP*elimina;
    BITMAP*inserta;
    BITMAP*busca;
    BITMAP*cursor;
	int click,cont,t;
	elimina=load_bitmap("elimina.bmp",NULL);
 	inserta=load_bitmap("insercion.bmp",NULL);
    busca=load_bitmap("busca.bmp",NULL); 
    cursor=load_bitmap("cursor2.bmp",NULL);
    
    while(respuesta!='n')
    {  
			click=1;
			if(opc==1) draw_sprite(buffer,inserta,0,0);
			if(opc==2) draw_sprite(buffer,elimina,0,0);
			if(opc==3) draw_sprite(buffer,busca,0,0);
			blit(buffer, screen, 0, 0, 0, 0, 640, 480); 
		    while(click==1){
		        cont=-1;t=1;
		    	readkey();
			    if(t==1 && click==1){
			    		if(key[KEY_0])cont=0;
			    		if(key[KEY_1])cont=1;
						if(key[KEY_2])cont=2;
						if(key[KEY_3])cont=3;
						if(key[KEY_4])cont=4;
						if(key[KEY_5])cont=5;
						if(key[KEY_6])cont=6;
						if(key[KEY_7])cont=7;
						if(key[KEY_8])cont=8;
						if(key[KEY_9])cont=9;
						if(key[KEY_ENTER])click=0;
						else click=2;t=2;
						textprintf(buffer, font ,187,140,150,"%d   ",(cont));
						blit(buffer, screen, 0, 0, 0, 0, 640, 480);
				}
				 
				
		        if(t==2 && click==2){
		        		readkey();
			    		if(key[KEY_0])cont=cont*10+0;
			    		if(key[KEY_1])cont=cont*10+1;
						if(key[KEY_2])cont=cont*10+2;
						if(key[KEY_3])cont=cont*10+3;
						if(key[KEY_4])cont=cont*10+4;
						if(key[KEY_5])cont=cont*10+5;
						if(key[KEY_6])cont=cont*10+6;
						if(key[KEY_7])cont=cont*10+7;
						if(key[KEY_8])cont=cont*10+8;
						if(key[KEY_9])cont=cont*10+9;
						if(key[KEY_ENTER])click=0;
						else click=3;t=3;
						textprintf(buffer, font ,187,140,150,"%d    ",(cont)); 
						blit(buffer, screen, 0, 0, 0, 0, 640, 480);
				}  
				
				
				if(t==3 && click==3){
						readkey();
			    		if(key[KEY_0])cont=cont*10+0;
			    		if(key[KEY_1])cont=cont*10+1;
						if(key[KEY_2])cont=cont*10+2;
						if(key[KEY_3])cont=cont*10+3;
						if(key[KEY_4])cont=cont*10+4;
						if(key[KEY_5])cont=cont*10+5;
						if(key[KEY_6])cont=cont*10+6;
						if(key[KEY_7])cont=cont*10+7;
						if(key[KEY_8])cont=cont*10+8;
						if(key[KEY_9])cont=cont*10+9;
						if(key[KEY_ENTER])click=0;
						else click=0;t=0;
						textprintf(buffer, font ,187,140,150,"%d    ",(cont));
						blit(buffer, screen, 0, 0, 0, 0, 640, 480);
				} 
				
				if(cont>=0 && cont<=999) {
					switch(opc){
						case 1:{
							textprintf(buffer, font ,50,360,150,"Dato ingresado exitosamente...");
			    			Insertar(cont);
			    			Imprimir(Mostrar,NULL,true,250,100,150);
							break;
						}
						case 2:{
							bool op=Borrar(cont);
			    			if(op==true)textprintf(buffer, font ,50,360,150,"Dato Borrado Exitosamente...");
			    			else textprintf(buffer, font ,50,360,150,"Dato NO existe en el arbol...");
							break;
						}
						case 3:{
							bool op=Buscar(cont);
			    			if(op==true)textprintf(buffer, font ,50,360,150,"Dato SI existe en el arbol...");
			    			else textprintf(buffer, font ,50,360,150,"Dato NO existe en el arbol...");
							break;
						}	
					}
	
				}else textprintf(buffer, font ,50,360,150,"Dato incorrecto...");
				textprintf(buffer, font ,50,380,150,"Desea seguir? (s/n) ");
				blit(buffer, screen, 0, 0, 0, 0, 640, 480); 
				readkey();
				if(key[KEY_N]) respuesta='n';
			}	
   	}
	blit(buffer, screen, 0, 0, 0, 0, 600, 400);
	return(1);	
}


int main() 
{	
    int operacion,p,basepal=0;
    AVL ArbolInt;
    
	allegro_init();
	install_keyboard();
	install_mouse();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 400, 0, 0);
 
	BITMAP *buffer = create_bitmap(600,400);
    clear_to_color(buffer, 0x333333);
    
    BITMAP *fondo;
    BITMAP *inicio;
    
    fondo=load_bitmap("portada principal.bmp",NULL);
    inicio=load_bitmap("inicio.bmp",NULL);
    
    draw_sprite(buffer,inicio,0,0);
    textprintf(buffer, font ,50,380,150,"Preione una tecla para continuar.. ");
	blit(buffer, screen, 0, 0, 0, 0, 640, 480); 
	readkey();

    
    while(p!=5){                     
		    operacion=Menu();
		    switch(operacion){
					     case 1:{ 		//Insercion de datos
					          			int op=ArbolInt.PedirDato(1);
										break;
					     }
					     case 2:{		//Eliminacion de datos
					     			 	int op=ArbolInt.PedirDato(2);
					          			break;    
					    }
					     case 3:{		//Busqueda de datos
					     				int op=ArbolInt.PedirDato(3);
					          			break;
					    }
					     case 4:{		//Mostrar datos
					     				int op=MenuMostrar();
					     				int op2=ArbolInt.MostrarDatos(op);

					          			break;
					    }
					     case 5:{   
					          			p=5;
					          			break;            
					    }
		      }
    }
    draw_sprite(buffer,fondo,0,0);
    blit(buffer, screen, 0, 0, 0, 0, 600, 400);
	
    readkey();
	
}
END_OF_MAIN();










