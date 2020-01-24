const int redPin = 10;      // nummeret til den røde LED pinnen

const int yellowPin = 9;      // nummeret til den gule LED pinnen

const int greenPin = 8;      // nummeret til den grønne LED pinnen

// Variabler som blir endret:

int redState = LOW;             // redState er brukt til hva lyset er før koden sier noe annet 

int yellowState = LOW;             // yellowState er brukt til hva lyset er før koden sier noe annet 

int greenState = LOW;             // greenState er brukt til hva lyset er før koden sier noe annet 

long StartTime = 0;       



long interval = 19000;           // dette er hvor lenge denne syklysen totalt skal vare. 

void setup() {

    // her sier koden at det skal komme lys ut av LED pinnen:

    pinMode(redPin, OUTPUT);

    pinMode(yellowPin, OUTPUT);

    pinMode(greenPin, OUTPUT);

}

void loop()

{
    
        unsigned long CheckTime = millis();

        unsigned long elapsedTime = CheckTime - StartTime;

        if (elapsedTime > interval) {

            StartTime = CheckTime;

        
    }

    if (elapsedTime < 5000) {

        redState = HIGH;

        yellowState = LOW;

        greenState = LOW;

    }

    if (elapsedTime > 5000 && elapsedTime < 7000) {
        redState = HIGH;

        yellowState = HIGH;

        greenState = LOW;
    }

    if (elapsedTime > 7000 && elapsedTime < 17000) {

        redState = LOW;

        yellowState = LOW;

        greenState = HIGH;

    }

    if (elapsedTime > 17000) {

        redState = LOW;

        yellowState = HIGH;

        greenState = LOW;

    }

    digitalWrite(redPin, redState);

    digitalWrite(greenPin, greenState);

    digitalWrite(yellowPin, yellowState);

}