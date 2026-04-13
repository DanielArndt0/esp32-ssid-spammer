#include "spammer.hpp"

// Pass 'true' if you want WPA2 simulation, or 'false' for open networks
spammer spmr(false);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting SSID Spammer...");

  // Initialize the library
  spmr.begin();

  Serial.println("Spamming initiated!");
}

void loop()
{
  spmr.update();
}
