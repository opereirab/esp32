#include "PZEM004tSensor.h"

PZEM004tSensor::PZEM004tSensor(/* args */)
  : Sensor(), pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN)
{
}

PZEM004tSensor::~PZEM004tSensor()
{
}

void PZEM004tSensor::setup()
{
  // PZEM_SERIAL.begin(9600);
}

void PZEM004tSensor::loop()
{
}

void PZEM004tSensor::loop(JsonObject& doc)
{

  	float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        voltage = 0.0f; 			Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        current = 0.0f; 			Serial.println("Error reading current");
    } else if (isnan(power)) {
        power = 0.0f; 				Serial.println("Error reading power");
    } else if (isnan(energy)) {
        energy = 0.0f; 				Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        frequency = 0.0f;			Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        pf = 0.0f;					Serial.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);

    }

	JsonArray values = doc.createNestedArray("values");
	values.add<float>(voltage);
	values.add<float>(current);
	values.add<float>(power);
	values.add<float>(energy);
	values.add<float>(pf);
}
