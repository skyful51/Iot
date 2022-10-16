#include "Sensor.h"
#include "Arduino.h"
#include "Iot.h"

Sensor::Sensor(int dust_pin, int gas_pin, int rain_pin)
{
    // 각 센서가 연결된 핀 초기화
    dust_pin_ = dust_pin;
    gas_pin_ = gas_pin;
    rain_pin_ = rain_pin;

    // LED 표시 관련 설정
    pinMode(dust_led_pin_, OUTPUT);
    pinMode(gas_led_pin_, OUTPUT);
    pinMode(rain_led_pin_, OUTPUT);
}

// IoT 클래스에 메서드를 추가해야 할 지도...
void Sensor::GetDustValue()
{
    float dust_value = analogRead(dust_pin_);
    // 필요하다면 계산 로직 추가할 것...

    if (dust_value >= DUST_THRESH)
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

    if (gas_value >= GAS_THRESH)
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

    if (rain_value >= RAIN_THRESH)
    {
        if (is_gas_ == false)
        {
            Iot::SensorWindow('c');
            is_rain_ = true;
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

bool Sensor::GetRainFlag()
{
    return is_rain_;
}

void Sensor::StartSensing()
{
    GetGasValue();
    GetDustValue();
    GetRainValue();
}