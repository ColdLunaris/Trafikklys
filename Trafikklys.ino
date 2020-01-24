const int button = 12;                                  // Bryter for fotgjengere
const int blinkDelay = 250;                             // Tidsinterval for blinking av lys p� fotgjengerfelt
const int ledArray[5] = { 10, 9, 8, 3, 2 };             // 10 = R�d, 9 = Gul, 8 = Gr�nn, 3 = R�d g�ende, 2 = Gr�nn g�ende
const int pedWaitTime = 5000;                           // Bestemmer hvor lenge fotgjengere m� vente p� gr�nt lys etter pedestrian-modus ble aktivert
const int pedWalkTime = 4000;                           // Bestemmer hvor lang tis fotgjernere har p� � g� f�r cooldown aktiveres
const int startDelay = 500;                             // Bestemmer at n�r pedestrian-modus er deaktivert vil det ta 500ms f�r trafikk kan krysse
const int carStageTime[3] = { 5000, 2000, 10000 };      // 5000 = Trinn 1, 2000 = Trinn 2 og 4, 10000 = Trinn 3 
const int pedStartDelay = 3000;

int carDelayTime = carStageTime[0];                     // Bestemmer ventetid f�r neste trinn
int carLedStage = 1;                                    // Trinnummer f�lger trinnummer i oppgave. Starter p� 1

unsigned long counter;                                  // Teller for millis()
unsigned long lastCount;                                // Lagrer counter-verdi til bruk i ny loop
int cooldownPeriod = 0;                                 // Teller hvor mange ganger lyset blinker f�r pedestrian-modus blir deaktivert

bool pressed = false;                                   // Teller hvor lenge bryteren har blitt holdt nede
bool noPed = true;                                      // Bestemmer om trafikklyset skal g� som normalt eller ikke. Pedestrian-modus
bool cooldown = false;                                  // Bestemmer om det er tid for � gj�re klar til � g� ut av pedestrian-modus
bool greenOn = false;                                   // Hjelper med blinking i cooldown-modus
bool noPedShutdown = false;                             // Brukes til � sl� av pedestrian-modus


void setup() {
    pinMode(button, INPUT_PULLUP);

    for (int i = 0; i <= 5; i++)
    {
        pinMode(ledArray[i], OUTPUT);
    }

    /*
    For-loopen definerer alle lys som OUTPUT
    */
}


void loop() {
    counter = millis();                                                                // Lagrer ny millis()-verdi for hver loop

    if (digitalRead(button) == LOW)                                                    // Leser av og lagrer om bryter har blitt aktivert
    {
        pressed = true;
    }

    switch (carLedStage)                                                               // Leser av hvilket trinn vi er p� i sekvensen og velger korresponderende case-nummer
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

    if (noPed == true)                                                                  // Hvis "pedestrian-modus" ikke er p� vil lys v�re r�dt
    {
        digitalWrite(ledArray[3], HIGH);
        digitalWrite(ledArray[4], LOW);
    }
    
    if (pressed == true && carLedStage == 1)                                            // Kj�rer hvis bryter er aktivert og biltrafikklys er r�dt. 
    {
        noPed = false;                                                                  // Aktiverer pedestrian-modus
        pressed = false;                                                                // Resetter bryter
        lastCount = counter;
    }
    
    if (cooldown == false && noPed == false)                                            // Aktiverer gr�nt lys hvis pedestrian-modus er aktivert. Vil ikke tvinge lyset p� under cooldown
    { 
        digitalWrite(ledArray[3], LOW); 
        digitalWrite(ledArray[4], HIGH);
    }
    
    if (noPed == false && counter - lastCount >= pedWalkTime)                           // Etter pedWalkTime med pedestrian-modus aktivert vil cooldown aktiveres
    {
        cooldown = true;
        lastCount = counter;
    }
    
    if (counter - lastCount >= blinkDelay && cooldown == true)                          // S� lenge cooldown er aktivert vil gr�nt lys blinke etter blinkDelay
    {
        if (greenOn == false)                                                           // Hvis gr�nt lys er av vil lyset bli sl�tt p�. Hvert blink blir lagret i cooldownPeriod
        {
            digitalWrite(ledArray[4], HIGH);
            greenOn = true;
            cooldownPeriod++;
        }
        else                                                                            // Hvis lyset er p� vil lyset bli sl�tt av
        {  
            digitalWrite(ledArray[4], LOW);
            greenOn = false;
        }
        lastCount = counter;

        if (cooldownPeriod >= 11) noPedShutdown = true;                                 // N�r lyset har blinket 10 ganger (m� skrive 11 for 10 blink) vil noPedShutdown bli aktivert for � avslutte pedestrian-modus
    }

    if (noPedShutdown == true)                                                          // N�r noPedShutdown er aktivert vil cooldown, noPedShutdown og pedestrian-modus deaktiveres. cooldownPeriod blir ogs� resatt
    {
        if (counter - lastCount >= startDelay)                                          // Etter pedestrian-modus er deaktivert vil det ta 500ms f�r bilene kan kj�re igjen
        {
            noPedShutdown = false;
            carLedStage = 2;
        }

        cooldown = false;
        noPed = true;
        cooldownPeriod = 0;
    }

    if (carLedStage != 1 && pressed == true && counter - lastCount >= pedWaitTime)      // Etter bryter har blitt aktivert vil det ta 5 sekunder f�r fotgjengerfeltet kan passeres
    {
        carLedStage = 4;
        lastCount = counter;
    }

    if (noPed == true)                                                                  // Vil ikke kj�re hvis pedestrian-modus er aktivert
    {
        if (counter - lastCount >= carDelayTime)                                        // Sjekker med delayTime for om det er tid for � bytte trinn
        {
            if (carLedStage < 4) carLedStage++;                                         // For trinn 1, 2 og 3 blir trinnummer �kt med en for � g� videre i sekvensen
            else carLedStage = 1;                                                       // Hvis trinn allerede er p� 4 vil trinnummer bli resatt for ny runde i sekvensen
            lastCount = counter;                                                        // Lagrer n�v�rende counter-verdi i lastCount for bruk til neste loop
        }
    }

    if (noPed == true)                                                                  // Vil ikke kj�re hvis pedestrian-modus er aktivert
    {
        switch (carLedStage)                                                            // Leser av hvilken trinn vi er p� i sekvensen og velger korresponderende case-nummer
        {
        case 1:
            carDelayTime = carStageTime[0];
            break;

        case 2:
            carDelayTime = carStageTime[1];
            break;

        case 3:
            carDelayTime = carStageTime[2];
            break;

        case 4:
            carDelayTime = carStageTime[1];
            break;
        }

        /*
        Case-nummer og tidsinterval korresponderer med trinnummer fra oppgaven
        */
    }
}
