#ifndef __MENU_H__
#define __MENU_H__

#include "Hw_Config.h"
#include "ESP8266.h"


#ifdef MENU_LOCAL
#define MENU_DEF
#else
#define MENU_DEF      extern
#endif

MENU_DEF int main_menu();
MENU_DEF int menu();


#endif