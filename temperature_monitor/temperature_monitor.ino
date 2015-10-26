#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// Normal Green Backlight
const int colorR_normal = 0;
const int colorG_normal = 109;
const int colorB_normal = 0;

// Hot Red Backlight
const int colorR_hot = 255;
const int colorG_hot = 0;
const int colorB_hot = 0;

// Cool Blue Backlight
const int colorR_cool = 0;
const int colorG_cool = 0;
const int colorB_cool = 255;

int a;
float temperature, temperatureF;
int B=3975;                  //B value of the thermistor
float resistance;
int temperature_status = 0;
const int hot_flag = 0B01;
const int cool_flag = 0B10;

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Set the normal backlight color
    lcd.setRGB(colorR_normal, colorG_normal, colorB_normal);

    // Waits for a second
    delay(1000);
}

void loop() 
{
    // set the cursor to column 0, line 0
    lcd.setCursor(0, 0);
    
    // print the temperature in celsius on 1st line
    a=analogRead(0);
    resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet&nbsp;;
    lcd.print(temperature); lcd.print(" degree C");

    // now convert the temperature to Fahrenheit and show on 2nd line
    lcd.setCursor(0, 1);
    temperatureF = (temperature * 9.0 / 5.0) + 32.0;
    lcd.print(temperatureF); lcd.print(" degree F");
    

    // Set the upper threshold to be 80 degree Fahrenheit
    if (temperatureF > 80 && (temperature_status == 0))
    {
      // action: set lcd color to red
      lcd.setRGB(colorR_hot, colorG_hot, colorB_hot);
      temperature_status |= hot_flag;
    }
    else if(temperatureF < 65 && (temperature_status == 0))
    {
      // action: set lcd color to blue
      lcd.setRGB(colorR_cool, colorG_cool, colorB_cool);
      temperature_status |= cool_flag;
    }
    else if((temperature_status != 0) && temperatureF <= 80 && temperatureF >=65)
    {
      // action: set lcd color back to normal
      lcd.setRGB(colorR_normal, colorG_normal, colorB_normal);
      //reset the status
      temperature_status = 0;
    }

    //waits for a second before updating temperature again
    delay(1000);
    

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
