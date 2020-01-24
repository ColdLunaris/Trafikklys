const int redPin = 10;          // nummeret til den r�de LED pinnen
const int yellowPin = 9;        // nummeret til den gule LED pinnen
const int greenPin = 8;         // nummeret til den gr�nne LED pinnen
const int redPedPin = 3;        // nummeret til den r�de fotgjengerfelt LED pinnen
const int greenPedPin = 2;      // nummeret til den gr�nne fotgjengerfelt LED pinnen
const int button = 12;          // nummeret til knappen som aktiverer fotgjengerfelt

// Variabler som blir endret:

int redState = LOW;             // redState er brukt til hva lyset er f�r koden sier noe annet 
int yellowState = LOW;          // yellowState er brukt til hva lyset er f�r koden sier noe annet 
int greenState = LOW;           // greenState er brukt til hva lyset er f�r koden sier noe annet
int redPedState = LOW;          // redPedState er brukt til hva fotgjengerfelt-lyset er f�r koden sier noe annet
int greenPedState = LOW;        // greenPedState er brukt til hva fotgjengerfelt-lyset er f�r koden sier noe annet
long StartTime = 0;       

long interval = 19000;           // dette er hvor lenge denne syklysen totalt skal vare. 

void setup() {
    // her sier koden at det skal komme lys ut av LED pinnen:
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(redPedPin, OUTPUT);
    pinMode(greenPedPin, OUTPUT);

    // her sier koden at knappen skal v�re en input med intern resistans:
    pinMode(button, INPUT_PULLUP);
}

void loop() {
    unsigned long CheckTime = millis();                             // blir brukt som teller for sekunder
    unsigned long elapsedTime = CheckTime - StartTime;              // lagrer hvor lenge programmet har kj�rt

    if (elapsedTime > interval)
    {
        StartTime = CheckTime;                                      // resetter trafikklys-loopen n�r all tid har g�tt. S�rger for uendelighet
    }

    if (elapsedTime < 5000)                                         // s� lenge det har g�tt mindre enn 5 sekunder i sekvensen vil lyset v�re r�dt
    {
        redState = HIGH;
        yellowState = LOW;
        greenState = LOW;
    }

    if (elapsedTime > 5000 && elapsedTime < 7000)                   // n�r det har g�tt mellom 5 og 7 sekunder vil lyset bli r�dt og gult
    {
        redState = HIGH;
        yellowState = HIGH;
        greenState = LOW;
    }

    if (elapsedTime > 7000 && elapsedTime < 17000)                  // mellom 7 og 17 sekunder i loopen vil lyse v�re gr�nt
    {
        redState = LOW;
        yellowState = LOW;
        greenState = HIGH;
    }

    if (elapsedTime > 17000)                                        // mellom 17 sekunder og makstid, her 19 sekunder, vil lyset v�re gult. Etter dette vil sekvensen starte p� nytt
    {
        redState = LOW;
        yellowState = HIGH;
        greenState = LOW;
    }

    digitalWrite(redPin, redState);
    digitalWrite(greenPin, greenState);
    digitalWrite(yellowPin, yellowState);
    digitalWrite(redPedPin, redPedState);
    digitalWrite(greenPedPin, greenPedState);
}