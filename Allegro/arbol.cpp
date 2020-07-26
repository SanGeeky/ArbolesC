#include <allegro.h>

void init();
void deinit();

int main() {
	init();
	
	BITMAP *buffer;
	buffer = create_bitmap(1080, 720);
	clear_to_color(buffer, 0xFFFFFF);
	BITMAP *cero;
	cero = load_bmp("numeros/0.bmp",NULL);
	draw_sprite(screen,buffer,0,0);
	line(screen, 0, 0, 500, 500, 32);
	readkey();
	if(key[KEY_0]){
		
		draw_sprite(screen,cero,500,0);
		
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
