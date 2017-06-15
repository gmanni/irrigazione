
#include <LiquidCrystal_I2C.h>

#include "menu.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);

menuLcd myMenu;
int tempReaded = 0;
char *orario;
int ore;
int min;
int sec;

int dd;
int mm;
int yy;

void setup() {
	// & restituisce l'indirizzo di memoria della variabile puntata
	// * restituisce il valore della variabile puntata

	ore = 23;
	min = 24;
	sec = 25;

	dd = 01;
	mm = 02;
	yy = 16;
	orario = "ciao";

	/*orario[1] = 'i';
	orario[2] = 'a';*/
	myMenu.addMenu(0, "Root");
	myMenu.addOption(0, "", 0, 0);
	myMenu.addOption(0, "", 3, 0);
	myMenu.addOption(0, "", 6, 0);

	myMenu.addOption(0, "", 0, 1);
	myMenu.addOption(0, "", 3, 1);
	myMenu.addOption(0, "", 6, 1);

	//myMenu.addOption(0, "CALDAIA OFF", 0, 2);
	myMenu.addVar(0, 0, &ore);
	//myMenu.addVar(0, 1, &min);
	//myMenu.addVar(0, 2, &sec);

	//myMenu.addVar(0, 3, &dd);
	//myMenu.addVar(0, 4, &mm);
	//myMenu.addVar(0, 5, &yy);
	
	/*myMenu.addMenu(1, "Impostazioni");
	myMenu.addMenu(2, "Ora_Data");
	myMenu.addMenu(3, "TempSoglia");*/
	
	myMenu.begin( &lcd);
	
	Serial.begin(9600);
	Serial.println(ore);
}

void loop() {
	delay(1000);
	ore++;
	Serial.println(ore);
	myMenu.drawMenu(0);
}
/*

const int pinButton1 = 12;
const int pinButton2 = 8;

int button1Pressed = 0;
int button2Pressed = 0;
int lastButton1Pressed = 0;
int lastButton2Pressed = 0;

int menuCorrente = 0;
int riga = -1;



void setup()
{
	pinMode(pinButton1, INPUT);
	pinMode(pinButton2, INPUT);
	lcd.init();
	lcd.backlight();

	m[0].id = 1;
	m[0].testo = "ROOT";
	m[0].idParent = -1; // è la root
	m[0].numeroOpzioni = 4;

	m[0].opzioni[0].id = 0;
	m[0].opzioni[0].testo = "";
	m[0].opzioni[0].valore = "dd.mm.yy";
	m[0].opzioni[0].pos.col = 0;
	m[0].opzioni[0].pos.row = 0;

	m[0].opzioni[1].id = 1;
	m[0].opzioni[1].testo = "";
	m[0].opzioni[1].valore = "hh.mm.ss";
	m[0].opzioni[1].pos.col = 10;
	m[0].opzioni[1].pos.row = 0;
	
	m[0].opzioni[2].id = 2;
	m[0].opzioni[2].testo = "C";
	m[0].opzioni[2].valore = "xxx";
	m[0].opzioni[2].pos.col = 0;
	m[0].opzioni[2].pos.row = 1;

	m[0].opzioni[3].id = 3;
	m[0].opzioni[3].testo = "Caldaia";
	m[0].opzioni[3].valore = "OFF";
	m[0].opzioni[3].pos.col = 0;
	m[0].opzioni[3].pos.row = 2;

	
	drawMenu(0);
	Serial.begin(9600);
	lastButton1Pressed = -1;
	lastButton2Pressed = -1;
	
}  

void loop(){
	button1Pressed = digitalRead(pinButton1);
	button2Pressed = digitalRead(pinButton2);

	if (button1Pressed != lastButton1Pressed) {
		if (button1Pressed == HIGH) {
			Serial.print("btn1 pressed");
			switch (menuCorrente){
				case 0:
					drawMenu(1);
					break;
				case 1:
					switch (riga) {
						case 0:
							drawMenu(2);
							break;
						case 3:
							drawMenu(0);
							break;
						}
					break;
				case 2:
					switch (riga){

						case 3:
							drawMenu(1);
						break;
					}
					break;
			}

		}
		else {
			
		}
		// Delay a little bit to avoid bouncing
		delay(50);
		lastButton1Pressed = button1Pressed;
	}
	if (button2Pressed != lastButton2Pressed)  {
		if (button2Pressed == HIGH) {
			switch (menuCorrente) {
			case 0:
				
				break;
			case 1:
				drawCursor();
				break;
			case 2:
				riga = 3;
				break;
			}
		}
		// Delay a little bit to avoid bouncing
		delay(50);
		lastButton2Pressed = button2Pressed;
	}
}

void drawMenu(int menuIndex) {
	menuCorrente = menuIndex;
	int i, j;

	lcd.clear();
	
	for (i = 0; i < m[menuCorrente].numeroOpzioni; i++) {
		lcd.setCursor(m[menuCorrente].opzioni[i].pos.col, m[menuCorrente].opzioni[i].pos.row);
		lcd.print(m[menuCorrente].opzioni[i].valore);
	}
	riga = -1;
	case 1:
		lcd.setCursor(1, 0);
		lcd.print("Imposta ora");
		lcd.setCursor(1, 1);
		lcd.print("Imposta data");
		lcd.setCursor(1, 2);
		lcd.print("Imposta temperatura");
		lcd.setCursor(1, 3);
		lcd.print("Esci");
		riga = -1;
		Serial.println("drawMenu " + riga);
		break;
	case 2:
		lcd.setCursor(1, 0);
		lcd.print("Imposta ora");
		lcd.setCursor(1, 1);
		lcd.print("hh:mm:ss");
		lcd.setCursor(1, 2);
		lcd.print("");
		lcd.setCursor(1, 3);
		lcd.print("Esci");
		riga = -1;
		Serial.println("drawMenu " + riga);
		break;
	}
	lastButton1Pressed = -1;
	lastButton2Pressed = -1;
}
	void drawCursor() {
		Serial.println("------");
		Serial.println("drawCursor ");
		Serial.println(riga);
		Serial.println("*******");
		if (riga == 3) {
			lcd.setCursor(0, riga);
			lcd.print(" ");
			riga = 0;
			lcd.setCursor(0, riga);
			lcd.print("-");
		}
		else if (riga == -1) {
			riga = 0;
			lcd.setCursor(0, riga);
			lcd.print("-");
		}
		else {
			lcd.setCursor(0, riga);
			lcd.print(" ");
			riga++;
			lcd.setCursor(0, riga);
			lcd.print("-");
		}
}
	*/