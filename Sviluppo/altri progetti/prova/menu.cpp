#include "menu.h"

menu::menu()
{
	
}

void menu::addOption(int indice, char testo[20], int col, int row)
{
	m.opzioni[indice].id = indice;
	strcpy(m.opzioni[indice].testo, testo);
	m.opzioni[indice].pos.col = col;
	m.opzioni[indice].pos.row = row;
	
}

void menuLcd::addMenu(int indice, char testo[20])
{
	m[indice].m.id = indice;
	strcpy(m[indice].m.testo, testo);

}

void menuLcd::addOption(int indice, char testo[20], int col, int row)
{
	m[indice].addOption(m[indice].m.opzioniLength++, testo, col, row);
}


void menuLcd::addVar(int indiceMenu, int indiceOpzione, int *v)
{
	m[indiceMenu].m.opzioni[indiceOpzione].valore = *v;
}

void menuLcd::addVar(int indiceMenu, int indiceOpzione, char* v)
{
	m[indiceMenu].m.opzioni[indiceOpzione].valore = (int) *v;
}

void menuLcd::begin(LiquidCrystal_I2C* lcd)
{
	l = lcd;
	
	l->init();
	l->backlight();
	drawMenu(0);

}

void menuLcd::drawMenu(int indice) {
	l->clear();
	//l->setCursor(0, 0);
	//l->print(m[indice].m.testo);
	int i;
	for (i = 0; i < m[indice].m.opzioniLength; i++) {
		l->setCursor(m[indice].m.opzioni[i].pos.col, m[indice].m.opzioni[i].pos.row);
		//char app[8] = { 2,3 };
		//itoa(m[indice].m.opzioni[i].valore.val, app, 10);
		//WWsprintf(app, "%d", m[indice].m.opzioni[i].valore.val);
		//strcpy(prova, m[indice].m.opzioni[i].valore.val);
		//serial.print("CIAO");
		//int app = m[indice].m.opzioni[i].valore;
		l->print(m[indice].m.opzioni[i].valore);
		l->print(m[indice].m.opzioni[i].testo);

	}
}

menuLcd::menuLcd()
{
	
}

