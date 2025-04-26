
#include "HX711Sensor.hpp"
#include <limits>

HX711Sensor::HX711Sensor(int dataPin, int clockPin){
    m_hx711.begin(dataPin,clockPin);
}

float HX711Sensor::readRawValue(){
    int count = 0;
	while (count < RETRIES) {
		if (isReady()) {
			return m_hx711.get_value();
		}
		delay(DELAY_MS);
		count++;
	}
	
    return -std::numeric_limits<float>::max(); //Error, becarfull not to use min since min float is a value near 0
}

bool HX711Sensor::isReady(){
    return m_hx711.is_ready();
}

void HX711Sensor::setGain(byte gain){
    m_hx711.set_gain((byte)gain);
}