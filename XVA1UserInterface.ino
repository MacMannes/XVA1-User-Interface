

/*
    XVA1 User Interface
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "RotaryEncOverMCP.h"
#include "Rotary.h"
#include "SynthParameter.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

/* First I2C MCP23017 GPIO expanders */
Adafruit_MCP23017 mcp1;  

//Array of pointers of all MCPs (for now, there's only 1)
Adafruit_MCP23017* allMCPs[] = { &mcp1 };
constexpr int numMCPs = (int)(sizeof(allMCPs) / sizeof(*allMCPs));

/* function prototypes */
void rotaryEncoderChanged(bool clockwise, int id);

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
        // outputA,B on GPA7,GPA6, register with callback and ID=1
        RotaryEncOverMCP(&mcp1, 7, 6, &rotaryEncoderChanged, 0),
        RotaryEncOverMCP(&mcp1, 1, 0, &rotaryEncoderChanged, 1),
        RotaryEncOverMCP(&mcp1, 4, 3, &rotaryEncoderChanged, 2)
};
constexpr int numEncoders = (int)(sizeof(rotaryEncoders) / sizeof(*rotaryEncoders));


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MAX = 128;
const int MIN = 1;
int currentPatchNumber = MIN;
String currentPatchName = "";
byte currentPatchData[512];

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB // New colour

struct SynthParameter param1;
struct SynthParameter param2;

unsigned long lastTransition;
unsigned long revolutionTime = 0;

void rotaryEncoderChanged(bool clockwise, int id) {
    unsigned long now = millis();
    revolutionTime = now - lastTransition;    

    int speed = 1;
    if (revolutionTime < 50) {
        speed = 20;
    } else if (revolutionTime < 125) {
        speed = 10;
    } else if (revolutionTime < 250) {
        speed = 2;
    } 

    lastTransition = now;
  
    Serial.println("Encoder " + String(id) + ": "
            + (clockwise ? String("clockwise") : String("counter-clock-wise")) + ", Speed: " + String(speed));
    if (id == 0) {
       handleMainEncoder(clockwise);
    }
    if (id == 1) {
        handleParameterChange(&param1, clockwise, speed);
        displayTwinParameters(&param1, &param2);
    }
    if (id == 2) {
        handleParameterChange(&param2, clockwise, speed);
        displayTwinParameters(&param1, &param2);
    }
}


void setup() {
    SerialUSB.begin(115200);

//    strcpy(param1.name, "FilterType");
//    param1.number = 71;
//    param1.min = 0;
//    param1.max = 21;
//    param1.descriptions[0] = "Bypass";
//    param1.descriptions[1] = "1P_LowPass";
//    param1.descriptions[2] = "2P_LowPass";
//    param1.descriptions[3] = "3P_LowPass";
//    param1.descriptions[4] = "4P_LowPass";
//    param1.descriptions[5] = "1P_HighPass";
//    param1.descriptions[6] = "2P_HighPass";
//    param1.descriptions[7] = "3P_HighPass";
//    param1.descriptions[8] = "4P_HighPass";

    strcpy(param1.name, "PerfCtl1");
    param1.type = PERFORMANCE_CTRL;
    param1.number = 400;
    param1.number2 = 401;
    param1.min = 0;
    param1.max = 511;

    strcpy(param2.name, "PerfCtl2");
    param2.type = PERFORMANCE_CTRL;
    param2.number = 402;
    param2.number2 = 403;   
    param2.min = 0;
    param2.max = 511;

//    strcpy(param1.name, "Sequencer");
//    param1.number = 428;
//    param1.min = 0;
//    param1.max = 1;    
//    param1.descriptions[0] = "OFF";
//    param1.descriptions[1] = "ON";
    
//    strcpy(param2.name, "Cutoff");
//    param2.number = 72;
//    param2.min = 0;
//    param2.max = 255;

//    strcpy(param1.name, "ARP_MODE");
//    param1.number = 450;
//    param1.min = 0;
//    param1.max = 5;    
//    strcpy(param2.name, "Octaves");
//    param2.number = 454;
//    param2.min = 0;
//    param2.max = 5;
    
  
    mcp1.begin();      // use default address 0
    //Initialize input encoders (pin mode, interrupt)
    for(int i=0; i < numEncoders; i++) {
        rotaryEncoders[i].init();
    }
    
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
       SerialUSB.println(F("SSD1306 allocation failed"));
       for(;;); // Don't proceed, loop forever
    }
  
    display.clearDisplay();
    display.drawBitmap(
      (display.width()  - LOGO_WIDTH ) / 2,
      (display.height() - LOGO_HEIGHT) / 2,
      logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
    
    Serial1.begin(500000); // XVA1 Serial
  
    tft.init();
    tft.setRotation(0);  // 0 & 2 Portrait. 1 & 3 landscapeooooooo;;
    tft.fillScreen(TFT_BLACK);
  
    tft.setCursor(0, 0, 2);
    // Set the font colour to be white with a black background, set text size multiplier to 1
    tft.setTextColor(TFT_WHITE,TFT_BLACK);  
    tft.setTextSize(1);
    tft.println("XVA1 Synthesizer");  
    
  
    // while the serial stream is not open, do nothing:
  //  while (!Serial) ; ...     
    
    SerialUSB.println("\n");
    SerialUSB.println("===================");
    SerialUSB.println("XVA1 User Interface");
    SerialUSB.println("===================\n");
    SerialUSB.print("value=");
    SerialUSB.println(currentPatchNumber);
  
    selectPatchOnSynth(currentPatchNumber);
    getPatchDataFromSynth();
    displayPatchInfo();
}

void loop() {
    pollAllMCPs();
}

void handleMainEncoder(bool clockwise) {
    int oldValue = currentPatchNumber;

    if (clockwise) {
      if (currentPatchNumber < MAX) {
        currentPatchNumber++;
      }
    } else {
      if (currentPatchNumber > MIN) {
        currentPatchNumber--;
      }        
    }

    SerialUSB.print("Selecting patch: ");
    SerialUSB.println(currentPatchNumber);

    if (currentPatchNumber != oldValue) {
       selectPatchOnSynth(currentPatchNumber);
       getPatchDataFromSynth();
       displayPatchInfo();
    }
}

void selectPatchOnSynth(int patchNumber) {
    int synthPatchNumber = patchNumber - 1;
    
    SerialUSB.print("Selecting patch #");
    SerialUSB.print(synthPatchNumber);
    SerialUSB.print(" on Synth...");
    
    Serial1.write('r'); // 'r' = Read program
    Serial1.write(synthPatchNumber);
  
  
    int read_status;
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead == 0 && retry != 100) {
      if (Serial1.available()) {
          read_status = Serial1.read();
          bytesRead++;
          retry = 0;
      } else {
        retry++;
        delay(10);
      }
    }  
  
    SerialUSB.print("Status=");
    SerialUSB.println(read_status, DEC);  

}

void getPatchDataFromSynth() {

    Serial1.write('d'); // 'd' = Display program

    SerialUSB.println("Reading patch data from Synth...");

    byte rxBuffer[512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
      if (Serial1.available()) {
          byte b = Serial1.read();
          rxBuffer[bytesRead] = b;
          bytesRead++;
          retry = 0;
      } else {
        retry++;
        delay(10);
      }
    }
    
//    for (int i = 0; i < sizeof(rxBuffer); i++){
//      printHex(rxBuffer[i]);
//    }
  
    SerialUSB.println();

    String patchName = "";
 
    for (int i=480; i<505; i++){
      patchName += (char)rxBuffer[i];
    }      

    SerialUSB.print("Patch name: ");
    SerialUSB.println(patchName);
    SerialUSB.println(); 
    
    Serial1.flush();

    memcpy(currentPatchData, rxBuffer, 512);
    currentPatchName = patchName; 
}

void displayPatchInfo() {
//  tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);   
    tft.drawString("Patch", 0, 30, 1);
    
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);   
  
    // Set the padding to the maximum width that the digits could occupy in font 4
    // This ensures small numbers obliterate large ones on the screen
    tft.setTextPadding(tft.textWidth("999", 4) );  
    // Draw the patch number in font 4
    tft.drawNumber(currentPatchNumber, 0, 42, 4);
  
    tft.setTextColor(TFT_RED, TFT_BLACK); 
  
    tft.setTextPadding(tft.textWidth("XXXXXXXXXXXXXXXXXXXXXXXXX", 2) );  
    // Draw the patch name in font 1
    tft.drawString(currentPatchName, 0, 75, 2);
  
    // Reset text padding to 0 otherwise all future rendered strings will use it!
    tft.setTextPadding(0);
  
    displayTwinParameters(&param1, &param2);
}

void drawCenteredText(char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
}

void printHex(uint8_t num) {
    char hexCar[2];
  
    sprintf(hexCar, "%02X", num);
    SerialUSB.print(hexCar);
  }

void pollAllMCPs() {
    //We could also call ".poll()" on each encoder,
    //however that will cause an I2C transfer
    //for every encoder.
    //It's faster to only go through each MCP object,
    //read it, and then feed it into the encoder as input.
    for(int j = 0; j < numMCPs; j++) {
        uint16_t gpioAB = allMCPs[j]->readGPIOAB();
        for (int i=0; i < numEncoders; i++) {
            //only feed this in the encoder if this
            //is coming from the correct MCP
            if(rotaryEncoders[i].getMCP() == allMCPs[j])
                rotaryEncoders[i].feedInput(gpioAB);
        }
    }
}

void displayTwinParameters(SynthParameter *param1, SynthParameter *param2) {
    int byte1;
    int byte2;

    if (param1->type == PERFORMANCE_CTRL) {
      byte msb = currentPatchData[param1->number]; 
      byte lsb = currentPatchData[param1->number2]; 
      int combined = (msb << 7) + lsb;

      byte1 = (int)combined;      
    } else {
      byte1 = (int)currentPatchData[param1->number];      
    }    

    if (param2->type == PERFORMANCE_CTRL) {
      byte msb = currentPatchData[param2->number]; 
      byte lsb = currentPatchData[param2->number2]; 
      int combined = (msb << 7) + lsb;

      byte2 = (int)combined;      
    } else {
      byte2 = (int)currentPatchData[param2->number];      
    }    
    
    char printValue1[20];
    if (param1->type != PERFORMANCE_CTRL && byte1 < sizeof(param1->descriptions) && param1->descriptions[byte1] != nullptr) {
      strcpy(printValue1, param1->descriptions[byte1]);    
    } else {
      sprintf(printValue1,"%ld", byte1);
    }
    char printValue2[20];
    if (param2->type != PERFORMANCE_CTRL && byte2 < sizeof(param2->descriptions) && param2->descriptions[byte1] != nullptr) {
      strcpy(printValue2, param2->descriptions[byte2]);    
    } else {
      sprintf(printValue2,"%ld", byte2);
    }
  
    displayTwinParameters(param1->name, printValue1, param2->name, printValue2);
}

void displayTwinParameters(char *title1, char *value1, char *title2, char *value2) {
    display.clearDisplay();  
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    drawCenteredText(title1, 64, 0);
  
    display.setTextSize(2);
    drawCenteredText(value1, 64, 12);
  
    display.drawLine(0, 30, display.width() - 1, 30, WHITE);
  
    
    display.setTextSize(1);
    drawCenteredText(title2, 64, 34);
  
    display.setTextSize(2);
    drawCenteredText(value2, 64, 47);
    
    display.display(); 
}

void handleParameterChange(SynthParameter *param, bool clockwise, int speed) {
    int currentValue;

    if (param->type == PERFORMANCE_CTRL) {
      byte msb = currentPatchData[param->number]; 
      byte lsb = currentPatchData[param->number2]; 
      int combined = (msb << 7) + lsb;
      currentValue = combined;
    } else {    
      currentValue = currentPatchData[param->number];
    }
    int newValue = -1;
  
    if (clockwise) {
        if (currentValue < param->max) {
            newValue = currentValue + speed;
            if  (newValue > param->max) {
                newValue = param->max;
            }
        }
    } else {
        if (currentValue > param->min) {
          newValue = currentValue - speed;
            if  (newValue < param->min) {
                newValue = param->min;
            }
        }
    }

  
    if (newValue >= 0 && newValue != currentValue) {
        SerialUSB.print("New value: ");
        SerialUSB.println(newValue);
        if (param->type == PERFORMANCE_CTRL) {
          byte msb = newValue >> 7;
          byte lsb = newValue & 127;

          currentPatchData[param->number] = msb;
          currentPatchData[param->number2] = lsb;

          setParameter(param->number, msb);
          setParameter(param->number2, lsb);          
        } else {
          currentPatchData[param->number] = newValue;
    
          setParameter(param->number, newValue);
        }
    }
  
}


void setParameter(int param, int value) {
    Serial1.write('s'); // 's' = Set Parameter

    if (param > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        Serial1.write(255);
        Serial1.write(param - 256 );
        Serial1.write(value);
    } else {
        Serial1.write(param);
        Serial1.write(value);
    }
}
