#ifndef Iot_h
#define Iot_h

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Servo.h"
#include "Adafruit_NeoPixel.h"

class Iot
{
    public:
        Iot(int first_pin, int num_of_iots, int num_of_pixels);
        void GetCommandSignal(
            SoftwareSerial* p_hc06,
            Adafruit_NeoPixel* p_neo_pixel,
            Servo* p_servo);
        void ControlIot(
            SoftwareSerial* p_hc06,
            Adafruit_NeoPixel* p_neo_pixel,
            Servo* p_servo);
        void ControlLight(Adafruit_NeoPixel* p_neo_pixel);
        void ControlBoiler();
        void ControlFan();
        void ControlWindow(Servo* p_servo);
        void ControlValve();
        void SendBluetoothSignal(SoftwareSerial* p_hc06);
        void TestFunction(Adafruit_NeoPixel* p_neo_pixel, Servo* p_servo);
        void SensorWindow(char cmd);
        void SensorFan(char cmd);

    private:
        int first_pin_;
        int num_of_iots_;
        int num_of_pixels_;
        int cmd_;
};

#endif