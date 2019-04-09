#define MENU_LOCAL

#include "menu.h"


MENU_DEF int menu();
MENU_DEF int main_menu();

MENU_DEF int menu()
{
    int key;

    while((key = main_menu()) != 0)
    {
        switch(key)
        {
                case '1':
                printf("\r\nNo.1\n");
                
            break;

            case '2':
                printf("\r\nNo.2\n");
                
            break;
            
            case '3':
                printf("\r\nNo.3\n");
                
            break;

            case '4':
                printf("\r\nNo.4\n");
                
            break;
              
            case '5':
                printf("\r\nNo.5\n");
                
            break;

            case '6':
                printf("\r\nNo.6\n");
                
            break;

            case '7':
                printf("\r\nNo.7\n");
                
            break;

            case '8':
                printf("\r\nNo.8\n");
                
            break;

            case '9':
                printf("\r\nNo.9\n");

            break;

            case '0':
                printf("\r\nNo.0\n");
                
            break;

            case 'a':
                printf("\r\nNo.a\n");
            
            break;

            case 'b':
                printf("\r\nNo.b\n");
              
            break;

            case 'c':
                printf("\r\nNo.c\n");
            
            break;

            case 'd':
                printf("\r\nNo.d\n");
        
            break;

            case 'e':
                printf("\r\nNo.e\n");
     
            break;

            case 'f':
                printf("\r\nNo.f\n");

            break;

            case 'g':
                printf("\r\nNo.g\n");
     
            break;

            case 'h':
                printf("\r\nNo.h\n");
       
            break;

            case 'i':
                printf("\r\nNo.i\n");

            break;

            case 'j':
                printf("\r\nNo.j\n");

            break;

            case 'k':
                printf("\r\nNo.k\n");

            break;

            case 'q':
                return 0;
        }
    }
    return 0;
    
}

MENU_DEF int main_menu()
{
    int key;
    
    printf("\r\n\r\n");
    printf("-------------------------------------------------\r\n");
    printf("                  menu select \r\n");
    printf("-------------------------------------------------\r\n");
    printf(" 1. \r\n");
    printf(" 2. \r\n");
    printf(" 3. \r\n");
    printf("-------------------------------------------------\r\n");
    printf(" q. Menu Quit\r\n");
    printf("-------------------------------------------------\r\n");
    
    key = USART_GetCharacter(USART1);

    return key;
}