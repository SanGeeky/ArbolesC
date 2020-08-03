#include <allegro.h>
#include <iostream>

#include "AVL.h"

void init();
void deinit();
char *numero = new char[5]; 
BITMAP *cero;
BITMAP *uno;
BITMAP *dos;
BITMAP *tres;
BITMAP *cuatro;
BITMAP *cinco;
BITMAP *seis;
BITMAP *siete;
BITMAP *ocho;
BITMAP *nueve;
int xm=0;
int x=540;
int y=0;
int x2=0;
int y2=0;
int incI=50;
int incD=50;
int xdis=0;
int ban=0;
using namespace::std;

string stexto;
       
      FONT *fuente;
 
      // ancho total del texto enviado
      int tancho;    
      int talto; 
      int espaciado;
     
      // para delimitar el rectangulo de vision     
      int mx1,my1;
      int mx2,my2;
      // ancho y alto del rectangulo
      int ancho, alto;     
       
      // numero de lineas totales q caben en el rectangulo
      int nlineas;


int menor(int x, int y){
    if ( x < y ){
       return x;  
    }else{
       return y;   
    }       
}

int mayor(int x, int y){
    if ( x < y ){
       return y;  
    }else{
       return x;   
    }       
}

void pinta(BITMAP* b){
     int cont;
     int espacio = 0;
     char* mtexto = (char*)stexto.c_str();
     int linea=0;
     int ni;
     int altura = 0;
     float exacto;
     BITMAP *cuadro = create_bitmap(ancho,alto);
 
      
    clear_to_color(cuadro, 0x222222);
    set_trans_blender(0,0,0,130);         
    draw_trans_sprite(b, cuadro, mx1, my1);               
    set_trans_blender(0,0,0,255);         
     
    rect(b, mx1-1, my1-1, mx2-1, my2-1, 0xfcf902);
    rect(b, mx1+1, my1+1, mx2+1, my2+1, 0x363712);      
    rect(b, mx1, my1, mx2, my2, 0x222222);
        
      
     if ( tancho+espaciado > ancho ){
        // no cabe en una linea  
        string resto = stexto;
        string trozo;
        char caracter[] = " ";
        char* caracter2;
        int nuevoancho = 0;
        int nc = 0;
        int restoancho = 0;
         
         do{      
                cont=1;
                trozo = resto.substr(0,cont);
                mtexto = (char*)trozo.c_str();
                nuevoancho = text_length( fuente, mtexto ); 
                espacio = 0;                   
                while ( nuevoancho+espaciado < ancho ){
                      trozo = resto.substr(cont,1);
                      caracter2  = (char*)trozo.c_str();
                      if ( strcmp(caracter2,caracter)==0 ){
                           espacio = cont;
                      }
                      cont++;
                      trozo = resto.substr(0,cont);
                      mtexto = (char*)trozo.c_str();
                      nuevoancho = text_length( fuente, mtexto ); 
                } 
                nc = resto.length();
                trozo = resto.substr(cont,1);
                caracter2  = (char*)trozo.c_str();
                 
                if ( espacio >0 && cont < nc && strcmp(caracter2,caracter)!=0 ){
                     trozo = resto.substr(0,espacio);
                     mtexto = (char*)trozo.c_str();             
                     resto = resto.substr(espacio);
                }else{
                     trozo = resto.substr(0,cont);
                     mtexto = (char*)trozo.c_str();              
                     resto = resto.substr(cont); 
                }
                 
                      
                altura = alto - (talto*nlineas);
                exacto = ( alto / nlineas );
                ni = int( exacto );
         
                textout_centre_ex(b, fuente, mtexto, mx1+1+int(ancho/2), my1+2+(ni*linea)-(talto/2)+(ni/2) , 0x363712, -1);                        
                textout_centre_ex(b, fuente, mtexto, mx1+int(ancho/2), my1+1+(ni*linea)-(talto/2)+(ni/2) , 0xffffff, -1);            
                 
                linea++;   
                restoancho = text_length( fuente, resto.c_str() );
         }while( restoancho+espaciado > ancho ); 
         
        mtexto = (char*)resto.c_str(); 
        textout_centre_ex(b, fuente, mtexto, mx1+1+int(ancho/2), my1+2+(ni*linea)-(talto/2)+(ni/2) , 0x363712, -1);                        
        textout_centre_ex(b, fuente, mtexto, mx1+int(ancho/2), my1+1+(ni*linea)-(talto/2)+(ni/2) , 0xffffff, -1);            
                 
     }else{
            
         textout_centre_ex(b, fuente, mtexto, mx1+(ancho/2)+1, my1+1+((alto-talto)/2), 0x363712, -1);          
         textout_centre_ex(b, fuente, mtexto, mx1+(ancho/2), my1+((alto-talto)/2), 0xffffff, -1);           
           
     }   
      
 
     destroy_bitmap(cuadro);    
    
};     

void numlineas(){
     int cont;
     int espacio = 0;
     char* mtexto = (char*)stexto.c_str();
     nlineas=1;
      
     if ( tancho+espaciado > ancho ){
        // no cabe en una linea  
        string resto = stexto;
        string trozo;
        char caracter[] = " ";
        char* caracter2;
        int nuevoancho = 0;
        int nc = 0;
        int restoancho = 0;
        do{     
                cont=1;
                trozo = resto.substr(0,cont);
                mtexto = (char*)trozo.c_str();
                nuevoancho = text_length( fuente, mtexto ); 
                espacio = 0;                   
                while ( nuevoancho+espaciado < ancho ){
                      trozo = resto.substr(cont,1);
                      caracter2 = (char*)trozo.c_str();
                      if ( strcmp(caracter2,caracter)==0 ){
                           espacio = cont;
                      }
                      cont++;
                      trozo = resto.substr(0,cont);
                      mtexto = (char*)trozo.c_str();
                      nuevoancho = text_length( fuente, mtexto ); 
                } 
                nc = resto.length();
                trozo = resto.substr(cont,1);
                caracter2 = (char*)trozo.c_str();        
                nlineas++;
                if ( espacio >0 && cont < nc && strcmp(caracter2,caracter)!=0 )
                {
                     resto = resto.substr(espacio);
                }else{
                     resto = resto.substr(cont); 
                }        
                restoancho = text_length( fuente, resto.c_str() );
        }while( restoancho+espaciado > ancho );      
                
     }          
}

void crea(const char* t, FONT* f, int x1, int y1, int x2, int y2){
   stexto = t;
   tancho = text_length( f, t );   
   talto  = text_height(f) + espaciado;
   fuente = f;
    
   mx1 = menor(x1,x2);
   mx2 = mayor(x1,x2);
   my1 = menor(y1,y2);
   my2 = mayor(y1,y2);
   ancho = abs( mx1 - mx2 );
   alto  = abs( my1 - my2 );
    
   numlineas();
 
};

int retornarEntero() //castea el char de caracteres
{
	int n = NULL;
	for ( int i = 0; i < 3; i++)
	{
		char numerochar = numero[i];
		if(numerochar==NULL) break;
		else{
			if(n == NULL)
			{
				n = numerochar - 48;
				//textprintf(screen,font,50,50,150,"%d ",(n));
			}
			else
			{
				int unidad = numerochar - 48;
				n=n*10+unidad;
			}
		}
	}
	return n;
}

void clearScreen(){
	clear_bitmap(screen);
	clear_to_color(screen, 0xFFFFFF);
    crea("                                         HOLAA BIENVENIDO A NUESTRO SIMULADOR DE ARBOLES AVL                                       *Digita cualquier numero seguido de un enter para ingresar o un backspace para eliminar un nodo de tu arbol AVL                      *Presiona 0 luego un Enter para BORRAR el arbol y empezar de nuevo                                                                *Presiona ESC para salir del programa                                                                                        *Universidad de Narino 2020*", font, 10, 500, 1070, 710); 
	pinta(screen);
}

void ingresarnumero(){
	//delete[] numero;

	for(int i = 0; i < 3; i++ )
		numero[i]=NULL;
	
	int f=0;
	xm=10;
	while(!key[KEY_ENTER] || f<3){
      
		char ascii=readkey();
		if (key[KEY_ESC])
		{
			exit(-1);
		}
		
		if(key[KEY_ENTER]){
			clearScreen();
         	break;
     	} 
		if(key[KEY_BACKSPACE]){
	    	ban=1;
			clearScreen();
	    	return;
		}

		textprintf(screen,font,xm,10,150,"%c",(ascii));
		xm+=8;
		numero[f]=ascii;
		f++;
	}
	
}

void imprimirimagen(char *numero, int x, int y){
	
	xdis=x;
	
	for ( int i = 0; i < 3; i++)
	{
		
		if(numero[i]=='0')draw_sprite(screen,cero,xdis,y);
		if(numero[i]=='1')draw_sprite(screen,uno,xdis,y);
		if(numero[i]=='2')draw_sprite(screen,dos,xdis,y);
		if(numero[i]=='3')draw_sprite(screen,tres,xdis,y);
		if(numero[i]=='4')draw_sprite(screen,cuatro,xdis,y);
		if(numero[i]=='5')draw_sprite(screen,cinco,xdis,y);
		if(numero[i]=='6')draw_sprite(screen,seis,xdis,y);
		if(numero[i]=='7')draw_sprite(screen,siete,xdis,y);
		if(numero[i]=='8')draw_sprite(screen,ocho,xdis,y);
		if(numero[i]=='9')draw_sprite(screen,nueve,xdis,y);
		xdis+=35;
		
	}
}

char* retornarChar(int numero)
{
	char *numerografico = new char[5];
	for(int i = 0; i < 3; i++ )
			numerografico[i]=NULL;

	int unidad = numero % 10;
	int decena = (numero / 10) % 10;
	int centena = (numero / 10) / 10;

	if(centena>0)
	{
		numerografico[0]=48+centena;
		numerografico[1]=48+decena;
		numerografico[2]=48+unidad;
	}
	else if (decena > 0)
	{
		numerografico[0]=48+decena;
		numerografico[1]=48+unidad;
	}
	else{
		numerografico[0]=48+unidad;
	}

	return numerografico;
	
}

void graficarArbolAllegro(Nodo *recorrer, int xinterno, int yinterno, int incremento, int xanterior, int yanterior){

	if(recorrer==NULL)
        return;

    graficarArbolAllegro(recorrer->derecho, xinterno + incremento, yinterno+80, incremento-38,xinterno,yinterno);
    graficarArbolAllegro(recorrer->izquierdo, xinterno - incremento, yinterno+80, incremento-38,xinterno,yinterno);
	
    //char *numerografico = new char[5]; int numero = recorrer->dato;
	//Trae Numero 

	char *numerografico;
	numerografico = retornarChar(recorrer->dato);

	//Pinta Numero y Aristas
	imprimirimagen(numerografico,xinterno,yinterno);
	//if (recorrer != NULL && recorrer!= raiz )
	//{
		line(screen, xinterno+40, yinterno, xanterior+40, yanterior+50, 32); /// Linea izquierda a Derecha  Backslahs
 		line(screen, xinterno+40, yinterno, xanterior+40, yanterior+50, 32); /// Linez de Derecha a Izquier Slash 
		/* line(screen, xinterno+40, yinterno, xinterno+80, yinterno+150, 32);
		line(screen, xinterno+40, yinterno+50, xinterno, yinterno+150, 32); */
	//}

}


int main() {
	init();
	BITMAP *buffer;
	buffer = create_bitmap(1080, 720);
	clear_to_color(buffer, 0xFFFFFF);
	

	cero = load_bmp("numeros/0.bmp",NULL);
	uno = load_bmp("numeros/1.bmp",NULL);
	dos = load_bmp("numeros/2.bmp",NULL);
	tres = load_bmp("numeros/3.bmp",NULL);
	cuatro = load_bmp("numeros/4.bmp",NULL);
	cinco = load_bmp("numeros/5.bmp",NULL);
	seis = load_bmp("numeros/6.bmp",NULL);
	siete = load_bmp("numeros/7.bmp",NULL);
	ocho = load_bmp("numeros/8.bmp",NULL);
	nueve = load_bmp("numeros/9.bmp",NULL);
	draw_sprite(screen,buffer,0,0);
	//line(screen, 0, 0, 500, 500, 32);
	//ascii=readkey();
	
	//int x = 1;	
	
	//MENSAJE.crea("        EL Andariego          Proyecto en c++ y allegro Udenar 2020",font, 5,5,230,60 );
	clearScreen();
	//MENSAJE.crea("L",FONT,5,5,230,60);	
	
	AVL ArbolInt;
	
	while(!key[KEY_ESC]){
      
		//y+=70;
		//x+=70;
		y2=y;
		x2=x;
		

		ingresarnumero();
		//imprimirimagen();
		int n = retornarEntero();
		//Aqui agrega el nuevo nodo al arbol
      	if(ban==1){
	    	//arbolVacio(recorrer, n);
			ban=0;
		}else{
			ArbolInt.Insertar(n);
			//agregarDatos(n);
		}	
		int capas = ArbolInt.AlturaArbol();
		//textprintf(screen,font,100,100,150,"%d",capas++);
		//nodo=raiz;
		/*int capas = altura(recorrer); */
		ArbolInt.Raiz();
		graficarArbolAllegro(actual,500,25,50*(capas+1),500,25);	
	}
	readkey();
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1080, 720, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
