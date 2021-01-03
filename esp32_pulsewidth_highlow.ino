/***************************************************************************
   A (very simple) attempt to measure irregular pulse width
   It won't take into account bouncing, as said, it's plain simple
   It will output measures with each trigger
   Not suitable for very high frequency pulses because of long variables used
   To-do: logic to discard first measure, that won't be accurate
 ***************************************************************************/

#define IN_PIN 18             /* input pin for pulse width */
#define ISR_TYPE CHANGE           /* isr triggering mode: both rising and falling */
volatile unsigned long previousPulse = millis();     /* time measure */
volatile unsigned long lastPulse = 0;                /* secondary time measure */
volatile unsigned long pulsePeriod = 0;              /* pulse period */
volatile boolean highlow = 0;     /* to store pin status, either HIGH or LOW */

void IRAM_ATTR pulseWidth()
{
  /* update time of interruption */
  lastPulse = millis();

  /* time measured in miliseconds, from the last measurement*/
  pulsePeriod = (long)(lastPulse - previousPulse);

  /* read pin status high or low */
  highlow = digitalRead(IN_PIN);

  if (pulsePeriod > 0)
  {
    /* Print pulse period */
    Serial.print(pulsePeriod);
    Serial.print("ms @");
    Serial.println(!highlow);
  }


  /* Update previous time */
  previousPulse = lastPulse;
}

void setup() {

  /* Serial port */
  Serial.begin(115200);

  /*set pin as input*/
  pinMode(IN_PIN, INPUT_PULLDOWN);

  /*attch function to isr routine*/
  attachInterrupt(IN_PIN, pulseWidth, ISR_TYPE);

  /*read if pin is HIGH or LOW */
  highlow = digitalRead(IN_PIN);
  Serial.println(highlow);

}

void loop() {
  /* nothing here on purpose */
}
