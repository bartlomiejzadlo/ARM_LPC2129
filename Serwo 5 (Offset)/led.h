enum kierunek {LEWO,PRAWO};

void LedInit(void);
void LedStep(enum kierunek eKierunek);

void LedStepRight(void);
void LedStepLeft(void);

void delay(int iMiliSeconds);


void LedOn(unsigned char ucLedIndeks);

