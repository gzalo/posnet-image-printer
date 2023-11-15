#include <string.h>
#include <svc.h>
#include <printer.h>
#include <aclconio.h>
#include <aclstr.h>

char greeting2[] = "Subir y bajar con las flechas, elegir con el boton verde";

char greeting1[] = " POS Cyberciruja 2023";
char ack[] = "         by gzalo.com";

// TODO:
// Add menu and random mode

char artNames[40][18] = {
    "Cybercirujas",
    "Flashparty",
    "Linux",
    "Raspberry Pi",
    "Exceso de Windows",
    "Boleto de bondi",
    "Cara Soldan",
    "Replay",
    "Endif",
    "Poder Alien",
    "Floppy disk",
    "Right to Repair",
    "Caras del Doom",
    "Linux inside",
    "Circuito",
    "Xonotic",
    "Carpincho",
    "Joy Division",
    "Daft Punk",
    "Mate",
    "Don Epi",
    "Copas",
    "Posadas Vice",
    "General",
    "Fantasma",
    "Mandelbrot",
    "Sierpinski",
    "Lines",
    "Gatos",
    "Contiene Linux",
    "Mapa cyberciruja",
    "Commodore 64",
    "Z80 inside",
    "Partes de PC",
    "Isaac",
    "Super Hexagon",
    "Tetris",
    "Half-Life",
    "Portal gun",
    "Conectar Igualdad"
};

char filenames[40][16] = {
    "I:1/00.bmp",
    "I:1/01.bmp",
    "I:1/02.bmp",
    "I:1/03.bmp",
    "I:1/04.bmp",
    "I:1/05.bmp",
    "I:1/06.bmp",
    "I:1/07.bmp",
    "I:1/08.bmp",
    "I:1/09.bmp",
    "I:1/10.bmp",
    "I:1/11.bmp",
    "I:1/12.bmp",
    "I:1/13.bmp",
    "I:1/14.bmp",
    "I:1/15.bmp",
    "I:1/16.bmp",
    "I:1/17.bmp",
    "I:1/18.bmp",
    "I:1/19.bmp",
    "I:1/20.bmp",
    "I:1/21.bmp",
    "I:1/22.bmp",
    "I:1/23.bmp",
    "I:1/24.bmp",
    "I:1/25.bmp",
    "I:1/26.bmp",
    "I:1/27.bmp",
    "I:1/28.bmp",
    "I:1/29.bmp",
    "I:1/30.bmp",
    "I:1/31.bmp",
    "I:1/32.bmp",
    "I:1/33.bmp",
    "I:1/34.bmp",
    "I:1/35.bmp",
    "I:1/36.bmp",
    "I:1/37.bmp",
    "I:1/38.bmp",
    "I:1/39.bmp",    
};

void fontLoop() {
    uint8_t i = 0;
    while(1){
        clrscr();
        uint8_t buffer[17]; 
        for (uint8_t j = 0; j < 16; j++) {
            buffer[j] = i + j;
        }
        buffer[16] = '\0';

        write_at(buffer, strlen(buffer), 1, 1);
        SVC_WAIT(1000);
        i+= 256;
    }
}

char padding[] = "I:1/padding.bmp";

char szKeyMap[MAX_ALPNUM_KEYS][CHAR_PER_KEY]={
           "0- +Q",   "1Z.AB",   "2CDEF",  "3GHIJ",  "4KLMN",  "5OPRS",
           "6TUVW",   "7XY*,",   "8'\"#=",  "9:$~^",  "{}[]\\","&%()!"};

int main (void){
    int console = open(DEV_CONSOLE, 0);
    int hPrinter = open(DEV_COM4, 0);
    clrscr();

    fontLoop();

    while(1) {
        set_backlight(1);
        write_at(greeting2, strlen(greeting2), 1, 1);  

        write_at(greeting1, strlen(greeting1), 1, 7);  
        write_at(ack, strlen(ack), 1, 8);  
        normal_tone();

        signed char buff[21];
        int artIndex=0; 
        memset(buff, 0x0, sizeof(buff));
        set_cursor(0);

        gotoxy(1,2);

        int ret = getkbd_entry(0, "", buff, (unsigned int) 100000,
					    (unsigned int)NUMERIC, (char *)szKeyMap, sizeof(szKeyMap), 2, 1);

        if(ret <= 0) continue;

        artIndex = strn2int((char*)buff,2) - 1;

        if(artIndex > 39 || artIndex < 0) {
            continue;
        }
   
        write_at("TE TOCA:", 8, 1, 1);
        write_at(artNames[artIndex], strlen(artNames[artIndex]), 1, 2);
        error_tone();
        print_bitmapimage(hPrinter, 0, filenames[artIndex]);
        print_bitmapimage(hPrinter, 0, padding);
        SVC_WAIT(100);

        clrscr();
        write_at("Gracias!", 8, 1, 1);
        write_at("Retira tu factura", 17, 1, 2);
        SVC_WAIT(5000);
    }

    close(console);
    close(hPrinter);
    return 0;
}
