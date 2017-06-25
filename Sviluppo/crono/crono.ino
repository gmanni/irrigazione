
#include <TouchScreen.h>
#include <UTFT.h>
#include <SD.h>

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define primaRiga 10
#define secondaRiga 40
#define terzaRiga 70
#define quartaRiga 100

typedef struct _data
{
	int giorno;
	int mese;
	int anno;
};
typedef struct _orario
{
	int ora;
	int minuti;
};

typedef struct _attivita
{
	_orario on;
	_orario off;
};

typedef struct _giornata
{
	int giorno;
	_attivita attivita[4];
};

typedef struct _settore
{
	String nome;
	bool abilitato;
	_giornata programmazione[7];

};

const int giorniMax[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int giorniMaxBisestile[] = {31,29,31,30,31,30,31,31,30,31,30,31 };

_settore settori[3];

const int PIN_SD = 4; // pin of sd card

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Various_Symbols_16x32[];

int x, y, z;

// Remember to change the model parameter to suit your display module!
UTFT tft(ILI9341_S5P, 51, 52, 5, 0, 6);


String currentMenu = "";
String statusSettori = "";
String statusSettoriMessage = "";
_orario orario;
_data oggi;

TouchScreen ts(A0, A3, A2, A1); // LANDSCAPE init TouchScreen port pins

/*
		bmpFile = SD.open("test.bmp");
		if (!bmpFile){
			Serial.println("didnt find image");
			while (1);
		}

		if (!bmpReadHeader(bmpFile)){
			Serial.println("bad bmp");
			return;
		}

		bmpdraw(bmpFile, 0, 0);
		bmpFile.close();

		*/
void setup() {
	Serial.begin(9600);
	orario.ora = 16;
	orario.minuti = 37;
	oggi.giorno = 11;
	oggi.mese = 6;
	oggi.anno = 2017;

	settori[0].nome = "settore 1";
	settori[0].abilitato = false;
	// lunedì
	settori[0].programmazione[0].giorno = 1;
	settori[0].programmazione[0].attivita[0].on.ora = 12;
	settori[0].programmazione[0].attivita[0].on.minuti = 0;
	settori[0].programmazione[0].attivita[0].off.ora = 12;
	settori[0].programmazione[0].attivita[0].off.minuti = 5;

	// martedì
	settori[0].programmazione[0].giorno = 2;
	settori[0].programmazione[0].attivita[0].on.ora = 13;
	settori[0].programmazione[0].attivita[0].on.minuti = 0;
	settori[0].programmazione[0].attivita[0].off.ora = 13;
	settori[0].programmazione[0].attivita[0].off.minuti = 5;
	
	settori[1].nome = "settore 2";
	settori[1].abilitato = false;
	
	settori[2].nome = "settore 3";
	settori[2].abilitato = false;
	
	tft.InitLCD();
	
	//statusSettoriMessage = "Settori non programmati";
	createMainMenu();
	/*
	Sd2Card card;
	card.init(SPI_FULL_SPEED, PIN_SD);

	if (!SD.begin(PIN_SD)) {
		Serial.println("failed!");
		while (1);                               // init fail, die here
	}

	Serial.println("SD OK!");

	/*bmpFile = SD.open("test.bmp");
	if (!bmpFile) {
		Serial.println("didnt find image");
		while (1);
	}*/

	/*if (!bmpReadHeader(bmpFile)) {
		Serial.println("bad bmp");
		return;
	}*/

	//bmpdraw(bmpFile, 0, 0);
	//bmpFile.close();
}

#define TS_MAXY 879
#define TS_MINY 145
#define TS_MINX 12
#define TS_MAXX 930

#define riga2_x 30
#define riga2_y 0

void retrieveTouch() {
	// a point object holds x y and z coordinates
	TSPoint p = ts.getPoint();

	x = map(p.x, TS_MINX, TS_MAXX, tft.getDisplayXSize(), 0);
	y = map(p.y, TS_MINY, TS_MAXY, tft.getDisplayYSize(), 0);
	z = p.z;
}

void getStatusSettori() {
	bool trovato = false;
	int i;
	for (i = 0; i<3; i++) {
		if (settori[i].abilitato) {
			trovato = true;
			break;
		}
	}
	if (trovato) {
		statusSettoriMessage = "Settori: OK";
	}else {
		statusSettoriMessage = "Settori: NA";
	}
	// messaggio di stato settori
	tft.print(statusSettoriMessage, LEFT, quartaRiga);
	
}

void loop() {
	retrieveTouch();
	getStatusSettori();
	if (z > MINPRESSURE && z < MAXPRESSURE) {
		Serial.print("x = ");
		Serial.print(x);
		Serial.print("\ty = ");
		Serial.println(y);

		if (y > 0 && y < 30) {
			if (x > 0 && x < 30) {
				// giorno
				Serial.println("giorno");
				currentMenu = "GG";
				disegnaMenu();
				disegnaCursore();
			}else if (x > 50 && x < 80) {
				// mese
				Serial.println("mese");
				currentMenu = "MM";
				disegnaMenu();
				disegnaCursore();

			}else if(x > 98 && x < 160) {
				// anno
				Serial.println("anno");
				currentMenu = "YY";
				disegnaMenu();
				disegnaCursore();
			}
		}else if(y>30 && y<45){
			if (x > 0 && x < 30) {
				Serial.println("ore");
				currentMenu = "O";
				disegnaMenu();
				disegnaCursore();
			}else if (x>50 && x<80) {
				Serial.println("minuti");
				currentMenu = "M";
				disegnaMenu();
				disegnaCursore();

			}else if (x>98 && x<128) {
				Serial.println("secondi");
			}
		}else if (y > 200 && y < 240) {
			if (x > 0 && x < 40) {
				Serial.println("puls +");
				if (currentMenu == "S") {
					
				}else if (currentMenu == "O") {
					if (orario.ora == 23) {
						orario.ora = 0;
					} else if (orario.ora < 23){
						orario.ora++;
					}
					disegnaCursore();
				}else if (currentMenu == "M") {
					if (orario.minuti == 59) {
						orario.minuti = 0;
					} else if (orario.ora < 58){
						orario.minuti++;
					}
					disegnaCursore();
				}else if (currentMenu == "GG") {
					if ((oggi.anno % 4) == 0) {
						if (oggi.giorno < giorniMaxBisestile[oggi.mese - 1]) {
							oggi.giorno++;
							disegnaCursore();
						}
					} else {
						if (oggi.giorno < giorniMax[oggi.mese - 1]) {
							oggi.giorno++;
							disegnaCursore();
						}
					}
					
				}else if (currentMenu == "MM") {
					if(oggi.mese < 12){
						oggi.mese++;
						disegnaCursore();
					}
				}else if (currentMenu == "YY") {
					oggi.anno++;
					disegnaCursore();
				}

			}else if (x > 60 && x < 100) {
				Serial.println("puls -");
				if (currentMenu == "S") {

				}else if (currentMenu == "O") {
					if (orario.ora == 0) {
						orario.ora = 23;
					} else if (orario.ora > 0) {
						orario.ora--;
					}
					disegnaCursore();
				}else if (currentMenu == "M") {
					if (orario.minuti == 0) {
						orario.minuti = 59;
					}else if(orario.minuti > 0){
						orario.minuti--;
					}
					
					disegnaCursore();
				}else if (currentMenu == "GG") {
					if (oggi.giorno > 1) {
						oggi.giorno--;
						disegnaCursore();
					}
				}else if (currentMenu == "MM") {
					if(oggi.mese > 1){
						oggi.mese--;
						disegnaCursore();
					}
				}else if (currentMenu == "YY") {
					oggi.anno--;
					disegnaCursore();
				}
			}else if (x > 120 && x < 180) {
				Serial.println("puls esc");
				currentMenu = "";
				disegnaMenu();
				disegnaCursore();
			}
		}
	}
}
void disegnaCursore() {
	if (currentMenu == "S") {
		
	}else if (currentMenu == "O") {
		tft.setBackColor(0, 0, 0);
		tft.setColor(255, 0, 0);
		tft.print(convertiDueCifre(orario.ora), LEFT, secondaRiga);
		tft.setColor(255, 255, 255);
	}else if (currentMenu == "M") {
		tft.setBackColor(0, 0, 0);
		tft.setColor(255, 0, 0);
		tft.print(convertiDueCifre(orario.minuti), 50, secondaRiga);
		tft.setColor(255, 255, 255);
	}else if(currentMenu == "GG"){
		tft.setBackColor(0, 0, 0);
		tft.setColor(255, 0, 0);
		tft.print(convertiDueCifre(oggi.giorno), LEFT, primaRiga);
		tft.setColor(255, 255, 255);
	}else if (currentMenu == "MM") {
		tft.setBackColor(0, 0, 0);
		tft.setColor(255, 0, 0);
		tft.print(convertiDueCifre(oggi.mese), 50, primaRiga);
		tft.setColor(255, 255, 255);
	}else if (currentMenu == "YY") {
		tft.setBackColor(0, 0, 0);
		tft.setColor(255, 0, 0);
		tft.print(String(oggi.anno, DEC), 98, primaRiga);
		tft.setColor(255, 255, 255);
	}else{
		tft.setColor(255, 255, 255);
		tft.setBackColor(0, 0, 0);
		
		// data odierna
		tft.print(convertiDueCifre(oggi.giorno), LEFT, primaRiga);
		tft.print(".", 33, primaRiga);
		tft.print(convertiDueCifre(oggi.mese), 50, primaRiga);
		tft.print(".", 83, primaRiga);
		tft.print(String(oggi.anno, DEC), 98, primaRiga);
		//tft.print("Dom", 180, primaRiga);

		// ora corrente
		tft.print(convertiDueCifre(orario.ora), LEFT, secondaRiga);
		tft.print(":", 33, secondaRiga);
		tft.print(convertiDueCifre(orario.minuti), 50, secondaRiga);
		
	}
}

void disegnaMenu() {
	if (currentMenu != "") {
		tft.setColor(204,204,204);
		//tft.setBackColor(204, 204, 204);
		tft.fillRoundRect(0, 200, 40, 240);
		
		tft.fillRoundRect(60, 200, 100, 240);
		tft.fillRoundRect(120, 200, 180, 240);

		tft.setBackColor(204, 204, 204);
		tft.setColor(255, 0, 0);
		tft.print("+", 12, 212);
		tft.print("-", 72, 212);
		tft.print("esc", 125, 212);
	}else {
		tft.setBackColor(0, 0, 0);
		tft.setColor(0, 0, 0);
		tft.fillRect(0, 200, 180, 240);

	}
}

void createMainMenu() {
	tft.clrScr();

	/*
	tft.setColor(255, 0, 0);
	tft.fillRect(0, 0, 319, 13);

	tft.setBackColor(255, 0, 0);
	tft.print("header", CENTER, 1);
	tft.setFont(SmallFont);
	tft.setFont(SevenSegNumFont);
	*/

	
	tft.setFont(BigFont);
	
	
	
	// ora corrente
	//tft.print(String(orario.ora, DEC) + ":" + String(orario.minuti, DEC), LEFT, secondaRiga);

	//tft.print(orario.ora + ":" + orario.minuti, LEFT, secondaRiga); // forse conviene eliminare i secondi che servono a poco

	//l'altezza del carattere è 15 pixel
	//tft.fillRect(0, 40, 30, 55); // ora
	//tft.fillRect(50, 40, 80, 45); // minuti
	//tft.fillRect(98, 40, 128, 45); // secondi

	// posizionamenti giorno mese e anno
	//tft.fillRect(0, 0, 30, 15); // giorno
	//tft.fillRect(50, 0, 80, 15); // mese
	//tft.fillRect(98, 0, 160, 15); // anno

	disegnaCursore();
}

String convertiDueCifre(int valoreDaConvertire) {
	String app = String(valoreDaConvertire);
	if (valoreDaConvertire < 10) {
		app = "0" + String(valoreDaConvertire);
	}
	return app;
}

