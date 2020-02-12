const int redPin = 10;          // nummeret til den røde LED pinnen
const int yellowPin = 9;        // nummeret til den gule LED pinnen
const int greenPin = 8;         // nummeret til den grønne LED pinnen

// Variabler som blir endret:

int redState = LOW;             // redState er brukt til hva lyset er før koden sier noe annet 
int yellowState = LOW;          // yellowState er brukt til hva lyset er før koden sier noe annet 
int greenState = LOW;           // greenState er brukt til hva lyset er før koden sier noe annet
long StartTime = 0;       

long interval = 19000;           // dette er hvor lenge denne syklysen totalt skal vare.
unsigned long CheckTime;
unsigned long elapsedTime;

void setup() {
    // her sier koden at det skal komme lys ut av LED pinnen:
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

void loop() {
    CheckTime = millis();                                           // blir brukt som teller for sekunder
    elapsedTime = CheckTime - StartTime;                            // lagrer hvor lenge programmet har kjørt

    if (elapsedTime > interval)
    {
        StartTime = CheckTime;                                      // resetter trafikklys-loopen når all tid har gått. Sørger for uendelighet
    }

    if (elapsedTime < 5000)                                         // så lenge det har gått mindre enn 5 sekunder i sekvensen vil lyset være rødt
    {
        redState = HIGH;
        yellowState = LOW;
        greenState = LOW;
    }

    if (elapsedTime > 5000 && elapsedTime < 7000)                   // når det har gått mellom 5 og 7 sekunder vil lyset bli rødt og gult
    {
        redState = HIGH;
        yellowState = HIGH;
        greenState = LOW;
    }

    if (elapsedTime > 7000 && elapsedTime < 17000)                  // mellom 7 og 17 sekunder i loopen vil lyse være grønt
    {
        redState = LOW;
        yellowState = LOW;
        greenState = HIGH;
    }

    if (elapsedTime > 17000)                                        // mellom 17 sekunder og makstid, her 19 sekunder, vil lyset være gult. Etter dette vil sekvensen starte på nytt
    {
        redState = LOW;
        yellowState = HIGH;
        greenState = LOW;
    }

    digitalWrite(redPin, redState);
    digitalWrite(greenPin, greenState);
    digitalWrite(yellowPin, yellowState);
}
