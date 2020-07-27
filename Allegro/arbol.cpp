#include <allegro.h>
#include <iostream>

void init();
void deinit();
char *numero = new char[5]; 





int main() {
	init();
	BITMAP *buffer;
	buffer = create_bitmap(1080, 720);
	clear_to_color(buffer, 0xFFFFFF);
	BITMAP *cero;
	cero = load_bmp("numeros/0.bmp",NULL);
	draw_sprite(screen,buffer,0,0);
	//line(screen, 0, 0, 500, 500, 32);
	//ascii=readkey();
	
	int x = 1;		
	int f=0;
	while(!key[KEY_ENTER] || f<3){
		char ascii=readkey();
	
		textprintf(screen,font,x,10,150,"%c",(ascii));
		x+=8;
		numero[f]=ascii;
		f++;
		/* if(key[KEY_0]){	
			draw_sprite(screen,cero,500,0);
		} */
	}
	x=0;
	for ( int i = 0; i < 3; i++)
	{
		if(numero[i]=='0')draw_sprite(screen,cero,x,100);
		
		x+=60;
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
