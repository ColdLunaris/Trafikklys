const int ledArray[3] = { 10, 9, 8 };                   // 10 = Rød, 9 = Gul, 8 = Grønn
const int stageTime[3] = { 5000, 2000, 10000 };         // 5000 = Trinn 1, 2000 = Trinn 2 og 4, 10000 = Trinn 3 

int delayTime = stageTime[0];                           // Bestemmer ventetid før neste trinn
int ledStage = 1;                                       // Trinnummer følger trinnummer i oppgave. Starter på 1

unsigned long counter;                                  // Teller for millis()
unsigned long lastCount;                                // Lagrer counter-verdi til bruk i ny loop


void setup() {
    for (int i = 0; i <= 3; i++)
    {
        pinMode(ledArray[i], OUTPUT);
    }

    /*
    For-loopen definerer alle lys som OUTPUT
    */
}


void loop() {
    counter = millis();                                 // Lagrer ny millis()-verdi for hver loop

    switch (ledStage)                                   // Leser av hvilket trinn vi er på i sekvensen og velger korresponderende case-nummer
    {
        case 1:
            digitalWrite(ledArray[0], HIGH);
            digitalWrite(ledArray[1], LOW);
            digitalWrite(ledArray[2], LOW);
            break;

        case 2:
            digitalWrite(ledArray[0], HIGH);
            digitalWrite(ledArray[1], HIGH);
            digitalWrite(ledArray[2], LOW);
            break;

        case 3:
            digitalWrite(ledArray[0], LOW);
            digitalWrite(ledArray[1], LOW);
            digitalWrite(ledArray[2], HIGH);
            break;

        case 4:
            digitalWrite(ledArray[0], LOW);
            digitalWrite(ledArray[1], HIGH);
            digitalWrite(ledArray[2], LOW);
            break;
    }

    /*
    Case-nummer og lys-oppsett korresponderer med trinnummer fra oppgaven
    */

    if (counter - lastCount >= delayTime)               // Sjekker med delayTime for om det er tid for å bytte trinn
    {
        if (ledStage < 4) ledStage++;                   // For trinn 1, 2 og 3 blir trinnummer økt med en for å gå videre i sekvensen
        else ledStage = 1;                              // Hvis trinn allerede er på 4 vil trinnummer bli resatt for ny runde i sekvensen
        lastCount = counter;                            // Lagrer nåværende counter-verdi i lastCount for bruk til neste loop
    }

    switch (ledStage)                                   // Leser av hvilken trinn vi er på i sekvensen og velger korresponderende case-nummer
    {
        case 1:
            delayTime = stageTime[0];
            break;

        case 2:
            delayTime = stageTime[1];
            break;

        case 3:
            delayTime = stageTime[2];
            break;

        case 4:
            delayTime = stageTime[1];
            break;
    }

    /*
    Case-nummer og tidsinterval korresponderer med trinnummer fra oppgaven
    */
}
