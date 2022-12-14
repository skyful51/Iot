#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "Iot.h"

// 각 센서의 동작 임계값
#define DUST_THRESH 3
#define GAS_THRESH 3
#define RAIN_THRESH 3

class Sensor
{
    public:

        // 생성자
        Sensor(int dust_pin, int gas_pin, int rain_pin);

        void StartSensing();

        // 각 센서로부터 센서값을 읽어오는 메서드
        void GetDustValue();
        void GetGasValue();
        void GetRainValue();
        bool GetDustFlag();
        bool GetGasFlag();

    private:

        // 각 센서로부터 아날로그 입력을 받아오는 핀 번호
        int dust_pin_;
        int gas_pin_;
        int rain_pin_;

        // 상태 표시 LED가 연결된 핀 번호
        int dust_led_pin_;
        int gat_led_pin_;
        int rain_led_pin;

        // 실내 공기질, 야외 먼지 플래그
        bool is_gas_;
        bool is_dust_;
        bool is_rain_;
};

#endif