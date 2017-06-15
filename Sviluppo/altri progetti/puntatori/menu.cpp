// 
// 
// 
#include <LiquidCrystal_I2C.h>
#include "menu.h"

void MenuClass::init(HardwareSerial *port, LiquidCrystal_I2C *l)
{
	indiceVariabili = -1;
	ser = port;
	lcd = l;
	lcd->init();
	lcd->backlight();
	ser->println("INIT");
	lcd->clear();
	lcd->setCursor(0, 0);
	lcd->print("INIT");
}

void MenuClass::addMenu(int *value)
{
	partenza = value;

}

void MenuClass::addMenu2(int *value)
{
	indiceVariabili++;
	variabili[indiceVariabili] = value;
}

void MenuClass::addMenu4(_comune *value)
{
	indiceVariabili++;
	ser->print("indice variabili ");
	ser->print(indiceVariabili);
	//items[indiceVariabili]->testo = "MENU";

	items[indiceVariabili]->c = value;
	items[indiceVariabili]->stringa = value->stringa;
	ser->print(" arriva ");
	ser->println(value->stringa);
	ser->print("memorizza ");
	ser->println(items[indiceVariabili]->stringa);
}

void MenuClass::addMenu5(char * value)
{
	indiceVariabili++;
	items[indiceVariabili]->stringa = value; 
	ser->print("arriva ");
	ser->println(value);
	ser->print("memorizza ");
	ser->println(items[indiceVariabili]->stringa);
}

void MenuClass::addTempo(_tempo *value, int col, int row, char *val)
{
	/*indiceVariabili++;
	items[indiceVariabili]->testo = "MENU TEMPO";
	items[indiceVariabili]->type = 0;
	items[indiceVariabili]->t = value;
	items[indiceVariabili]->d = nullptr;
	items[indiceVariabili]->p.col = col;
	items[indiceVariabili]->p.row = row;
	items[indiceVariabili]->c.stringa = val;*/

}

void MenuClass::addData(_data * value, int col, int row)
{
	/*indiceVariabili++;
	items[indiceVariabili]->testo = "MENU DATA";
	items[indiceVariabili]->type = 1;
	items[indiceVariabili]->t = nullptr;
	items[indiceVariabili]->d = value;
	items[indiceVariabili]->p.col = col;
	items[indiceVariabili]->p.row = row;*/
}

void MenuClass::addMenu3(_comune *value)
{
	
	indiceVariabili++;
	ser->print(indiceVariabili);
	//items[indiceVariabili]->testo = "MENU";
	
	items[indiceVariabili]->c = (_comune*)value;
	ser->print(" VEDIAMO ");
	ser->println(value->stringa);
}

void MenuClass::debug()
{
	int i;

	ser->println("DEBUG ");
	//ser->println(*partenza);
	lcd->clear();
	
	//lcd->print("partenza ");
	//lcd->print (*partenza);
	//lcd->print("variabili ");
	
	for (i = 0; i <= 5; i++) {
	//	//lcd->setCursor(items[i]->p.col, items[i]->p.row);
	//	//lcd->setCursor(i*3,0);
	//	//lcd->print(*variabili[i]);
		ser->print("var");
		ser->println(i);
	//	ser->println(items[i]->testo);
		ser->print("vale ");
		ser->println(items[i]->stringa);

		lcd->print(items[i]->c->stringa);

	//	
	}
	


}

MenuClass Menu;

