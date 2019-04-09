#ifndef __AT_MENU_H__
#define __AT_MENU_H__

#include "menu.h"



#ifdef AT_MENU_LOCAL
#define AT_MENU_DEF
#else
#define AT_MENU_DEF        extern
#endif

AT_MENU_DEF int main_menu();
AT_MENU_DEF int menu();


#endif