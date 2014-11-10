#include <MsTimer2.h>

#include <Time.h>

#include <Wire.h>

#include <TinyGPS.h>

#include <LiquidCrystal_I2C.h>

#define GPSBAUD 38400

int utc_year;
byte utc_month; 
byte utc_day; 
byte utc_hour; 
byte utc_minutes; 
byte utc_second;
byte utc_hundredths;
float fix_age;
float latitude;
float longitude;
float course;
int direction;
signed int offset;
//int altitude;
//int sats;

TinyGPS gps; 			//Initialize library
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  
        lcd.init();
        delay(20);
        lcd.init();        // initialize the lcd 
        lcd.backlight();
        lcd.print("   X-GPS Clock");
        lcd.setCursor(0,1);
        lcd.print(" Most  Accurate");
        delay(3000);
        lcd.clear();
        lcd.print("By Hackerchai");
        lcd.setCursor(0,1);
        lcd.print("hackerchai.com");
        delay(3000); 
        lcd.clear();     
        lcd.print("Acquiring GPS fi");
        lcd.setCursor(0,1);
        lcd.print("x.Waiting...");
        
  	
        Serial.begin(GPSBAUD); 
        delay(2000);
        lcd.clear();	// Start up library and begin communicating at GPSBAUD rate
           	
}

void loop() {
 
  
  
  while ( Serial.available() )	// if serail comm is available
  {
    if ( gps.encode( Serial.read() ) ) //If serial comm is delivering and TinyGPS can understand it
    {    
        //Set time zone: offset = direction * longitude * (24 / 360), where direction = 1 for east, -1 for west, and longitude is [-180,180]
	gps.f_get_position(&latitude, &longitude); //Get latitude and longitude, in degrees

	//Determine if direction is east or west for timezone formula
	course = gps.course(); 
	if (course >= 0) 	 
		direction = 1;
	else
		direction = -1;
	offset = direction * longitude * (24 / 360); //Set timezone
  
        gps.crack_datetime(&utc_year, &utc_month, &utc_day, &utc_hour, &utc_minutes, &utc_second, &utc_hundredths); //get time from GPS
	
	//altitude = gps.altitude(); 	//Get altitude
	//sats = gps.satellites(); 	//Get satellites in view

	setTime(utc_hour, utc_minutes, utc_second, utc_day, utc_month, utc_year); //pass time from GPS to time control
         		//Set time zone (manually)

	// Send to display
        lcd.print("AT-UTC: ");
        if(hour()<10)
        {
          lcd.print("0");
          lcd.print(hour());
        }
        else
        { 
        lcd.print(hour());
        }
        lcd.print(':');
        if(minute()<10)
        {
          lcd.print("0");
          lcd.print(minute());
        }
        else
        { 
        lcd.print(minute());
        }
        lcd.print(':');
        if(second()<10)
        {
          lcd.print("0");
          lcd.print(second());
        }
        else
        { 
        lcd.print(second());
        }
        lcd.home();
        
        lcd.setCursor(0,1);
	setTime(utc_hour, utc_minutes, utc_second, utc_day, utc_month, utc_year); //pass time from GPS to time control
        adjustTime(+8*3600);
        lcd.print("Peking: ");
        if(hour()<10)
        {
          lcd.print("0");
          lcd.print(hour());
        }
        else
        { 
        lcd.print(hour());
        }
        lcd.print(':');
        if(minute()<10)
        {
          lcd.print("0");
          lcd.print(minute());
        }
        else
        { 
        lcd.print(minute());
        }
        lcd.print(':');
        if(second()<10)
        {
          lcd.print("0");
          lcd.print(second());
        }
        else
        { 
        lcd.print(second());
        }
        lcd.home();
        
        
        
        
        
		
     }
  }  
}





