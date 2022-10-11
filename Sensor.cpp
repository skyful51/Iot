#include "Sensor.h"
#include "Arduino.h"
#include "Iot.h"

Sensor::Sensor(int dust_pin, int gas_pin, int rain_pin)
{
    dust_pin_ = dust_pin;
    gas_pin_ = gas_pin;
    rain_pin_ = rain_pin;
}

// IoT 클래스에 메서드를 추가해야 할 지도...
void Sensor::GetDustValue()
{
    float dust_value = analogRead(dust_pin_);
    // 필요하다면 계산 로직 추가할 것...

    if (dust_value >= dust_threshold_)
    {
        if (is_gas_ == false)
        {
            Iot::SensorWindow('c');
            is_dust_ = true;
        }
    }

    else
    {
        is_dust_ = false;
    }
}

void Sensor::GetGasValue()
{
    float gas_value = analogRead(gas_pin_);
    // 필요하다면 계산 로직 추가할 것...

    if (gas_value >= gas_threshold_)
    {
        Iot::SensorFan('o');
        Iot::SensorWindow('o');
        is_gas_ = true;
    }
}

void Sensor::GetRainValue()
{
    float rain_value = analogRead(rain_pin_);
    // 필요하다면 계산 로직 추가할 것...

    if (rain_value >= rain_threshold_)
    {
        if (is_gas_ == false)
        {
            Iot::SensorWindow('c');
            is_dust_ = true;
        }
    }
}

bool Sensor::GetDustFlag()
{
    return is_dust_;
}

bool Sensor::GetGasFlag()
{
    return is_gas_;
}