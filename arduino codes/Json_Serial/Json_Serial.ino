#include <aJSON.h>

aJsonStream serial_stream(&Serial);

void setup()
{
  Serial.begin(9600);
}

/* Process message like: { "pwm": { "8": 0, "9": 128 } } */
void processMessage(aJsonObject *msg)
{
  aJsonObject *pwm = aJson.getObjectItem(msg, "pwm");
  if (!pwm) {
    //Serial.println("no pwm data");
    return;
  }

  const static int pins[] = { 6,7,8,9};
  const static int pins_n = 4;
  for (int i = 0; i < pins_n; i++) {
    char pinstr[3];
    
    aJsonObject *pwmval = aJson.getObjectItem(pwm, pinstr);
    if (!pwmval) continue; /* Value not provided, ok. */
    if (pwmval->type != aJson_Int) {
      Serial.print("invalid data type ");
      Serial.print(pwmval->type, DEC);
      Serial.print(" for pin ");
      Serial.println(pins[i], DEC);
      continue;
    }

    Serial.print("setting pin ");
    Serial.print(pins[i], DEC);
    Serial.print(" to value ");
    Serial.println(pwmval->valueint, DEC);
    //analogWrite(pins[i], pwmval->valueint);
  }
}

void loop()
{
  if (serial_stream.available()) {
    /* First, skip any accidental whitespace like newlines. */
    serial_stream.skip();
  }

  if (serial_stream.available()) {
    /* Something real on input, let's take a look. */
    aJsonObject *msg = aJson.parse(&serial_stream);
    //processMessage(msg);
    aJson.deleteItem(msg);
  }
}
