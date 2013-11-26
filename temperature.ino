#include <LiquidCrystal.h>

int max_temp = 37, min_temp = 10, mode = 0; // 0: Welcome Mode; 1: Enter Mode; 2: Work Mode

LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6);

void Set_Mode(int mode_value)
{
    int enter = digitalRead(4);
    if(enter == LOW)
    {
        mode = mode_value;
        delay(200);
    }
}

void Get_Value(int *value)
{
    while(1)
    {
        int enter = digitalRead(4);
        int up = digitalRead(3);
        int down = digitalRead(2);

        if(up == LOW)
        {
            if(*value == 99) *value = 99;
            else (*value) = (*value) + 1;
        }
        if(down == LOW)
        {
            if(*value == 0) *value = 0;
            else (*value) = (*value) - 1;
        }
        if(enter == LOW)
        {
            delay(200);
            break;
        }
        if(*value > 9)
        {
            lcd.setCursor(1, 1);
            lcd.print(*value);
        }
        else
        {
            lcd.setCursor(1, 1);
            lcd.print(0);
            lcd.setCursor(2, 1);
            lcd.print(*value);
        }
        delay(200);
    }
}

void setup (void)
{
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, OUTPUT);
    lcd.begin(16, 2);
}

void loop (void)
{
    digitalWrite(5, HIGH);
    if(mode == 0)
    {
        lcd.clear();
        lcd.print("Welcome!");
        delay(100);
        Set_Mode(1);
    }
    if(mode == 1)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter the Max:");
        Get_Value(&max_temp);
        lcd.setCursor(0, 0);
        lcd.print("Enter the Min:");
        Get_Value(&min_temp);
        mode = 2;
    }
    if(mode == 2)
    {
        long val = analogRead(0);
        int temperature = (int)(val*0.0048828125*100);
        delay(220);
        if(temperature >= max_temp || temperature <= min_temp)
        {
            lcd.clear();
            digitalWrite(5, LOW);
            delay(280);
            Set_Mode(1);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Working!");
        lcd.setCursor(0, 1);
        lcd.print("T: ");
        lcd.print(temperature);
        lcd.print(" 'C");
        Set_Mode(1);
    }
}
