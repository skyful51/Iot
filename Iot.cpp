#include "Iot.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Servo.h"
#include "Adafruit_NeoPixel.h"

Iot::Iot(int first_pin, int num_of_iots, int num_of_pixels)
{
    first_pin_ = first_pin;
    num_of_iots_ = num_of_iots;
    num_of_pixels_ = num_of_pixels;

    for (int i = 0; i < num_of_iots_; i++)
    {
        pinMode(first_pin_ + i, OUTPUT);
        digitalWrite(first_pin + 1, LOW);
    }
}

void Iot::GetCommandSignal(SoftwareSerial* p_hc06,
                           Adafruit_NeoPixel* p_neo_pixel,
                           Servo* p_servo)
{
    if (p_hc06->available())
    {
        cmd_ = p_hc06->read();
        delay(100);
        ControlIot(p_hc06, p_neo_pixel, p_servo);
    }
}

void Iot::ControlIot(SoftwareSerial* p_hc06,
                     Adafruit_NeoPixel* p_neo_pixel,
                     Servo* p_servo)
{
    if (cmd_ == 'i')
        SendBluetoothSignal(p_hc06);
    else if (cmd_ == '0' || cmd_ == '1')
        ControlLight(p_neo_pixel);
    else if (cmd_ == '2' || cmd_ == '3')
        ControlBoiler();
    else if (cmd_ == '4' || cmd_ == '5')
        ControlFan();
    else if (cmd_ == '6' || cmd_ == '7')
        ControlWindow(p_servo);
    else if (cmd_ == 'v')
        ControlValve();
}

void Iot::ControlLight(Adafruit_NeoPixel* p_neo_pixel)
{
    if (cmd_ == '0')
    {
        digitalWrite(first_pin_, LOW);
        p_neo_pixel->clear();
        p_neo_pixel->show();
    }
    else if (cmd_ == '1')
    {
        digitalWrite(first_pin_, HIGH);

        for (int i = 0; i < num_of_pixels_; i++)
            p_neo_pixel->setPixelColor(i, 50, 0, 0);
        
        p_neo_pixel->show();
    }
}

void Iot::ControlBoiler()
{
    if (cmd_ == '2')
        digitalWrite(first_pin_ + 1, LOW);
    else if (cmd_ == '3')
        digitalWrite(first_pin_ + 1, HIGH);
}

void Iot::ControlFan()
{
    if (cmd_ == '4')
        digitalWrite(first_pin_ + 2, LOW);
    else if (cmd_ == '5')
        digitalWrite(first_pin_ + 2, HIGH);
}

void Iot::ControlWindow(Servo* p_servo)
{
    if (cmd_ == '6')
    {
        digitalWrite(first_pin_ + 3, LOW);
        p_servo->write(0);
    }
    else if (cmd_ == '7')
    {
        digitalWrite(first_pin_ + 3, HIGH);
        p_servo->write(45);
    }
}

void Iot::ControlValve()
{
    digitalWrite(first_pin_ + 4, LOW);
}

void Iot::SendBluetoothSignal(SoftwareSerial* p_hc06)
{
    for (int i = 0; i < num_of_iots_; i++)
    {
        if (digitalRead(first_pin_ + i) == HIGH)
            p_hc06->write(" on");
        else if (digitalRead(first_pin_ + i) == LOW)
            p_hc06->write(" off");

        delay(100);
    }

    p_hc06->write("q");
}

// 센서 값에 따라 창문, 환풍기 제어
void Iot::SensorWindow(char cmd)
{
    if (cmd == 'c')
    {
        digitalWrite(first_pin_ + 3, LOW);
        p_servo->write(0);
    }
    else if (cmd == 'o')
    {
        digitalWrite(first_pin_ + 3, HIGH);
        p_servo->write(45);
    }
}

void Iot::SensorFan(char cmd)
{
    if (cmd_ == 'c')
        digitalWrite(first_pin_ + 2, LOW);
    else if (cmd_ == 'o')
        digitalWrite(first_pin_ + 2, HIGH);
}