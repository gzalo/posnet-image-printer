#include <string.h>
#include <svc.h>
#include <printer.h>
#include <aclconio.h>
#include <aclstr.h>
#include <stdlib.h>

char greeting1[] = "Elegir con las flechas, luego el btn verde";

char greeting2[] = " POS Cyberciruja 2023";
char greeting3[] = " \x14\x15  \x16\x17  by gzalo.com";

char artNames[41][21] = {
    "00. Al azar",
    "01. Cybercirujas",
    "02. Flashparty",
    "03. Linux",
    "04. Raspberry Pi",
    "05. Exceso Windows",
    "06. Boleto de bondi",
    "07. Cara Soldan",
    "08. Replay",
    "09. Endif",
    "10. Poder Alien",
    "11. Floppy disk",
    "12. Right to Repair",
    "13. Caras del Doom",
    "14. Linux inside",
    "15. Circuito",
    "16. Xonotic",
    "17. Carpincho",
    "18. Joy Division",
    "19. Daft Punk",
    "20. Mate",
    "21. Don Epi",
    "22. Copas",
    "23. Posadas Vice",
    "24. General",
    "25. Fantasma",
    "26. Mandelbrot",
    "27. Sierpinski",
    "28. Lines",
    "29. Gatos",
    "30. Contiene Linux",
    "31. Mapa cyberciruja",
    "32. Commodore 64",
    "33. Z80 inside",
    "34. Partes de PC",
    "35. Isaac",
    "36. Super Hexagon",
    "37. Tetris",
    "38. Half-Life",
    "39. Portal gun",
    "40. ConectarIgualdad"
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

// 000 EMPTY 0-15
// 016 BAT-BAT PALO-PALO FLECHA-ARR FLECHA-ABAJO DERGRUESA IZQGRUESA ArrDer Arr Abaj Enter Der Izq
// 032 Space !(33) " # ...
// 048 012345 ...
// 064 @ABC...
// 080 PQR...
// 096 `abc
// 112 prq...~ BLOQUENEGRO(127)
// 128 € PuntaBat bat chica.... Tick Cruz BloqueNegro BloqueNegro BloqueNegro
// 144 BLOQUES NEGROS
// 160 BLOQUENEGRO ¡ Cent Libra XRara Yen | Simoleon ¨ Copy ª << ¬ Negro ? -
// 176 º +- 2 3 ´ micro parraf · , 1 º >> 1/4 1/2 3/4 ¿
// 192 à á â ä a· AE Ç è é ê ë ì í î ï
// 208 Dmedio Ñ ò ó ô õ ö x O ù ú û ü Ý D Beta
// 224 a· a· aº ã ä a$ ae ç è é ê ë ì í î ï 
// 240 dx ñ ò ó ô õ ö div ss ù ù û ü ý d ÿ
void fontLoop() {
    unsigned char i = 0;
    while(1){
        clrscr();
        unsigned char buffer[17]; 
        for (unsigned char j = 0; j < 16; j++) {
            buffer[j] = i + j;
        }
        buffer[16] = '\0';

        write_at((char*)buffer, strlen((char*)buffer), 1, 1);
        SVC_WAIT(1000);
        i+= 16;
    }
}

char padding[] = "I:1/padding.bmp";

int main (void){
    int console = open(DEV_CONSOLE, 0);
    int hPrinter = open(DEV_COM4, 0);
    clrscr();
    set_cursor(0);

    int cursorPos = 0;
    int winOffset = 0;
    const int WIN_HEIGHT = 4;
    const int TOTAL_ELEMENTS = 41;
    const int TOTAL_LOGOS = 40;
    int redraw = 1;

    while(1) {
        set_backlight(1);

        if(redraw){
            redraw = 0;
            clrscr();
            write_at(greeting1, strlen(greeting1), 1, 1);  
            write_at(greeting2, strlen(greeting2), 1, 7);  
            write_at(greeting3, strlen(greeting3), 1, 8); 

            // Cursor
            write_at(">", 1, 1, 3+cursorPos); 
            for(int i=0;i<WIN_HEIGHT;i++){
                write_at(artNames[i+winOffset], strlen(artNames[i+winOffset]), 2, 3+i); 
            }
        }
        
        int pendingKeys = kbd_pending_count();
        int down = 0;
        int up = 0;
        int print = 0;
        if(pendingKeys){
            char key[1];
            read(console, key, 1);

            down = key[0] == 0xE2;
            up = key[0] == 0xE1;
            print = key[0] == 0x8D;
        }

        if(down) {
            if(cursorPos == WIN_HEIGHT-1){
                if(winOffset < TOTAL_ELEMENTS-WIN_HEIGHT){
                    winOffset ++;
                }
            } else {
                cursorPos++;
            }
            redraw = 1;
        } 

        if(up){
            if(cursorPos == 0){
                if(winOffset > 0){
                    winOffset --;
                }
            } else {
                cursorPos--;
            }
            redraw = 1;
        }

        if(print){
            int artIndex = winOffset+cursorPos;
            if(artIndex == 0){
                artIndex = rand()%TOTAL_LOGOS;
            } else {
                artIndex--;
            }

            clrscr();
            write_at("TE TOCA:", 8, 1, 1);
            write_at(artNames[artIndex+1], strlen(artNames[artIndex+1]), 1, 2);
            error_tone();
            print_bitmapimage(hPrinter, 0, filenames[artIndex]);
            print_bitmapimage(hPrinter, 0, padding);
            SVC_WAIT(100);

            clrscr();
            write_at("Gracias!", 8, 1, 1);
            write_at("Retira tu factura", 17, 1, 2);
            SVC_WAIT(5000);

            normal_tone();
            redraw = 1;
        }
        SVC_WAIT(1);
    }

    close(console);
    close(hPrinter);
    return 0;
}
