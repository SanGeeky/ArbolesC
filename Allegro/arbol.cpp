#include <allegro.h>
#include <iostream>

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
int x=0;
int y=0;


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

void ingresarnumero(){
	delete[] numero;
	//char *numero = new char[5];
	for(int i = 0; i < 3; i++ )
		numero[i]=NULL;
	
	int f=0;
	while(!key[KEY_ENTER] || f<3){
		char ascii=readkey();
		if(key[KEY_ENTER]) break;
		textprintf(screen,font,x,10,150,"%c",(ascii));
		x+=8;
		numero[f]=ascii;
		f++;
	}
}

void imprimirimagen(){
	
	for ( int i = 0; i < 3; i++)
	{
		if(numero[i]=='0')draw_sprite(screen,cero,x,y);
		if(numero[i]=='1')draw_sprite(screen,uno,x,y);
		if(numero[i]=='2')draw_sprite(screen,dos,x,y);
		if(numero[i]=='3')draw_sprite(screen,tres,x,y);
		if(numero[i]=='4')draw_sprite(screen,cuatro,x,y);
		if(numero[i]=='5')draw_sprite(screen,cinco,x,y);
		if(numero[i]=='6')draw_sprite(screen,seis,x,y);
		if(numero[i]=='7')draw_sprite(screen,siete,x,y);
		if(numero[i]=='8')draw_sprite(screen,ocho,x,y);
		if(numero[i]=='9')draw_sprite(screen,nueve,x,y);
		
		x+=50;
	}
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
	
	int x = 1;		
	
	while(!key[KEY_ESC]){
		y+=100;
		ingresarnumero();
		imprimirimagen();
		int n = retornarEntero();	
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
