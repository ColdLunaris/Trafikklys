const int redPin = 10;                  // nummeret til den r�de LED pinnen
const int yellowPin = 9;                // nummeret til den gule LED pinnen
const int greenPin = 8;                 // nummeret til den gr�nne LED pinnen
const int redPedPin = 3;                // nummeret til den r�de fotgjenger LED pinnen
const int greenPedPin = 2;              // nummeret til den gr�nne fotgjenger LED pinnen
const int button = 12;                  // nummeret til fotgjenger knappen
const int pedestrianWaitTime = 5000;
const int pedestrianWalkTime = 5000;
const int blinkDelay = 250;
const int startDelay = 500;

// Variabler som blir endret:

int redState = LOW;                     // redState er brukt til hva lyset er f�r koden sier noe annet 
int yellowState = LOW;                  // yellowState er brukt til hva lyset er f�r koden sier noe annet 
int greenState = LOW;                   // greenState er brukt til hva lyset er f�r koden sier noe annet
int redPedState = LOW;                  // redPedState er brukt til hva lyset er f�r koden sier noe annet
int greenPedState = LOW;                // greenPedState er brukt til hva lyset er f�r koden sier noe annet
int cooldownPeriod = 0;
unsigned long StartTime;
unsigned long elapsedTime;              // lagrer hvor lenge programmet har kj�rt
unsigned long CheckTime;                // blir brukt som teller for sekunder
unsigned long lastTime;
bool pressed = false;
bool pedMode = false;
bool cooldown = false;
bool pedModeShutdown;

long carInterval = 19000;                  // dette er hvor lenge denne syklysen totalt skal vare. 

void setup() {
    // her sier koden at det skal komme lys ut av LED pinnen:
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(redPedPin, OUTPUT);
    pinMode(greenPedPin, OUTPUT);

    // her sier koden at knappen er en input med intern resistans
    pinMode(button, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    CheckTime = millis();

    if (digitalRead(button) == LOW) pressed = true;
    if (pedMode == false) redPedState = HIGH;                           // holder fotgjenerfelt r�dt hvis knappen ikke har blitt aktivert

    if (elapsedTime < 5000 && elapsedTime > 10 && pressed == true)      // n�r knappen er aktivert og billyset er r�dt vil fotgjenger-modus starte
    {
        pedMode = true;
        pressed = false;
        lastTime = millis();
    }

    if (pedMode == true && cooldown == false)                           // s� lenge fotgjenger-modus er aktivert og ikke cooldown vil fotgjengerlyset v�re gr�nt
    {
        redPedState = LOW;
        greenPedState = HIGH;
    }

    if (pedMode == true && millis() - lastTime > pedestrianWalkTime)    // n�r det har g�tt 5000ms etter pedMode ble aktivert vil cooldown aktiveres
    {
        lastTime = millis();
        cooldown = true;
    }

    if (cooldown == true && millis() - lastTime >= blinkDelay)          // denne if-statement'en s�rger for at gr�nt lys blinker 10 ganger f�r pedMode avsluttes
    {
        lastTime = millis();

        if (greenPedState == HIGH)
        {
            greenPedState = LOW;
            cooldownPeriod++;
        }
        else greenPedState = HIGH;

        if (cooldownPeriod >= 11) pedModeShutdown = true;
    }

    if (pedModeShutdown == true)                                         // n�r pedModeShutdown er aktivert vil cooldown, pedModeShutdown og fotgjenger-modus deaktiveres. cooldownPeriod blir ogs� resatt. Det vil ta 500ms f�r bilene kj�rer igjen
    {
        pedModeShutdown = false;
        cooldownPeriod = 0;
        cooldown = false;
        pedMode = false;
        StartTime = StartTime + 5500;                                   // s�rger for at n�r fotgjengerfeltet er avsluttet tar det 500ms f�r 
    }

    unsigned long teller;
    if (pedMode == true)
    {
        teller = millis();
        Serial.println(teller);                                          // brukt for debugging

    }

    if (pedMode == false)
    {
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

        elapsedTime = CheckTime - StartTime;
        if (elapsedTime > carInterval) StartTime = CheckTime;          // resetter trafikklys-loopen n�r all tid har g�tt. S�rger for uendelighet
    }

    digitalWrite(redPin, redState);
    digitalWrite(greenPin, greenState);
    digitalWrite(yellowPin, yellowState);
    digitalWrite(redPedPin, redPedState);
    digitalWrite(greenPedPin, greenPedState);
}
