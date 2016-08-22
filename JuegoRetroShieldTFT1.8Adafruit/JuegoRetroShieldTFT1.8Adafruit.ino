#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5

void setup(void) {
  Serial.begin(9600);

// Initialize 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("OK!");
  // COLOR DE INICIACION
    tft.fillScreen(ST7735_WHITE);
    tft.setTextSize(8);
    tft.setTextColor(ST7735_BLUE);
    tft.setCursor(15, 40);
    tft.print("TB ");
    tft.setTextSize(2);
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(15, 100);
    tft.print("TESLABEM ");
   }

    
  uint8_t readButton(void) {
  float a = analogRead(3);
  
  a *= 5.0;
  a /= 1024.0;
  
  Serial.print("Button read analog = ");
  Serial.println(a);
  if (a < 0.2) return BUTTON_DOWN;
  if (a < 1.0) return BUTTON_RIGHT;
  if (a < 1.5) return BUTTON_SELECT;
  if (a < 2.0) return BUTTON_UP;
  if (a < 3.2) return BUTTON_LEFT;
  else return BUTTON_NONE;
}
int estado = 0;
int x = 0;  
int y = 0;
int barrax = 0;
int barray = 0;
int x1 = 0;
int y1 = 0;
int x2 = 0;
int y2 = 0;
int x3 = 0;
int y3 = 0;
void loop() {
    barray = 100;
     x1 = 60;
     x2 = 108;
     x3 = 10;
    uint8_t b = readButton();
    if (b == BUTTON_LEFT){
    barrax--;
    }
    if (b == BUTTON_RIGHT) {
    barrax++;
    }
    
    // inicia el programa si se aprieta el boton central del Joystik
    if (b == BUTTON_SELECT or estado == 1) {
    tft.fillScreen(ST7735_BLACK); // Fondo negro
      tft.fillRect(x, y, 20, 20, ST7735_YELLOW); // Dibujar cuadrado 1
      tft.fillRect(x1, y1-40, 20, 20, ST7735_YELLOW); // Dibujar cuadrado 2
      tft.fillRect(x2, y2-80, 20, 20, ST7735_YELLOW); // Dibujar cuadrado 3
      tft.fillRect(x3, y3-80, 20, 20, ST7735_YELLOW); // Dibujar cuadrado 4
      tft.fillRect(barrax, barray, 30, 10, ST7735_WHITE); // Dibujar la barra que se va a mover.
    y++; // incrementar las coordenadas en "y" (hacia abajo) del primer cuadradp
    y1++; // incrementar las coordenadas en "y1" (hacia abajo) del segundo cuadrado
    y2++; // incrementar las coordenadas en "y1" (hacia abajo) del tercer cuadrado
    y3++; // // incrementar las coordenadas en "y1" (hacia abajo) del cuarto cuadrado
    estado = 1; // el valor del la variables "estado" cambia a 1.
    }
    // Cuando la coordenada "y" del cuadrado 1 es mayor a 110, "y" se vuelve 0 y "x" toma un valor random. 
    if (y>110){
       y = 0;
       x = random(108); 
    }
    // Cuando la coordenada "y" del cuadrado 2 es mayor a 150, "y" se vuelve 0+40 y "x" toma un valor random.
    if (y1>150){
      y1 = 0+40;
      x1 = random(108);
    }
    // Cuando la coordenada "y" del cuadrado 3 es mayor a 190, "y" se vuelve 0+80 y "x" toma un valor random.
    if (y2>190){
      y2 = 0+80;
      x2 = random(108);
    }
    // Cuando la coordenada "y" del cuadrado 4 es mayor a 150, "y" se vuelve 0+40 y "x" toma un valor random.
    if (y3>190){
      y3 = 0+80;
      x3 = random(108);
    }
   //Condicion para perder cuando se choca con el cuadrado 1
    if (x > barrax and x < barrax + 30 and y > 80 or x+20 > barrax and x+20 < barrax + 30 and y > 80){
    estado = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(10, 70);
    tft.print("Game Over");
    } 
    //Condicion para perder cuando se choca con el cuadrado 2
        if (x1 > barrax and x1 < barrax + 30 and y1-40 > 80 or x1+20 > barrax and x1+20 < barrax + 30 and y1-40 > 80){
    estado = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(10, 70);
    tft.print("Game Over");
    }
    //Condición para perder cuando se choca con el cuadrado 3 
    if (x2 > barrax and x2 < barrax + 30 and y2-80 > 80 or x2+20 > barrax and x2+20 < barrax + 30 and y2-80 > 80){
    estado = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(10, 70);
    tft.print("Game Over");
    }  
    //Condicion para perder cuando se choca con el cuadrado 4
    if (x3 > barrax and x3 < barrax + 30 and y3-80 > 80 or x3+20 > barrax and x3+20 < barrax + 30 and y3-80 > 80){
    estado = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(10, 70);
    tft.print("Game Over");
    }
    //Condicion para perder cuando se choca con las paredes
    if (barrax < 0 or barrax+20 >118){
    estado = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(10, 70);
    tft.print("Game Over");
    } 
}
