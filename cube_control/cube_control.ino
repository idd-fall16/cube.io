#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

const int qKey = D2;
void isr(void);
void handler(void);

long DEBOUNCE_DELAY = 50;
Timer timer(DEBOUNCE_DELAY, handler, true); // oneshot

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(qKey, INPUT_PULLDOWN);
  attachInterrupt(qKey, isr, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void isr(void)
{
  noInterrupts();
  if(digitalRead(qKey)==LOW){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else {
    timer.stopFromISR(); //stop on falling edge
  }
  interrupts();
}

void handler(void) {
  Serial.println('q');
}

