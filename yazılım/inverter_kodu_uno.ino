#include <LiquidCrystal.h>

// --- ARDUINO UNO 50Hz TAM PROFESYONEL INVERTOR (TIMER1 + I2C LCD) ---

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ekran adresi genellikle 0x27 veya 0x3F olur. 16 sütun, 2 satır.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int kanal_A = 9;    // Pozitif yarım dalga 
const int kanal_B = 10;   // Negatif yarım dalga 
const int sensorPin = A1; // Geri besleme
const int potPin = A2;    // Potansiyometre

// PI Katsayıları
float Kp = 0.06; 
float Ki = 1.9;  

long aktif_sure_us = 2270; 
volatile uint16_t aktif_sure_ticks = 4540; 
int eski_hata = 0; 
volatile bool pozitif_yari_dalga = true;

// Ekranı titretmemek için zamanlayıcı değişkeni
unsigned long son_ekran_guncelleme = 0;

void setup() {
  pinMode(kanal_A, OUTPUT);
  pinMode(kanal_B, OUTPUT);
  digitalWrite(kanal_A, LOW);
  digitalWrite(kanal_B, LOW);

  // --- LCD BAŞLATMA ---
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Mod.Sin. Evirici");
  lcd.setCursor(0, 1);
  lcd.print("***** KTU *****");
  delay(1500);
  lcd.clear();

  // =========================================================
  // TIMER 1 AYARLARI (50.00 Hz İÇİN)
  // =========================================================
  cli(); 
  TCCR1A = 0; 
  TCCR1B = 0;
  TCNT1  = 0; 
  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS11);  
  OCR1A = 19999; 
  TIMSK1 |= (1 << OCIE1A);
  sei(); 
  // =========================================================
}

// -----------------------------------------------------------
// 1. KESME: ZAMANLAYICI A (10ms Döngüsü)
// -----------------------------------------------------------
ISR(TIMER1_COMPA_vect) {
  if (aktif_sure_ticks > 0) {
    if (pozitif_yari_dalga) {
      digitalWrite(kanal_A, HIGH); 
    } else {
      digitalWrite(kanal_B, HIGH); 
    }
    OCR1B = aktif_sure_ticks; 
    TIFR1 |= (1 << OCF1B);
    TIMSK1 |= (1 << OCIE1B);
  }
  pozitif_yari_dalga = !pozitif_yari_dalga;
}

// -----------------------------------------------------------
// 2. KESME: ZAMANLAYICI B (Kapatma)
// -----------------------------------------------------------
ISR(TIMER1_COMPB_vect) {
  digitalWrite(kanal_A, LOW);
  digitalWrite(kanal_B, LOW);
  TIMSK1 &= ~(1 << OCIE1B);
}

// -----------------------------------------------------------
// ANA DÖNGÜ
// -----------------------------------------------------------
void loop() {
  // 1. POT OKUMA VE HEDEF BELİRLEME
  int potVal = analogRead(potPin);
  
  // PI algoritması için olan ham hedef (290 - 570)
  int dinamik_setpoint = map(potVal, 0, 1023, 245, 522);

  // 2. EKRAN GÜNCELLEME (Saniyede 4 kez)
  if (millis() - son_ekran_guncelleme > 250) {
    // Ekranda göstermek için pot değerini 12.0 ile 18.0 arasına çeviriyoruz.
    // Önce 120 ile 180 arasına çevirip 10'a bölüyoruz ki ondalıklı (float) veri elde edelim.
    float ekran_voltaji = map(potVal, 0, 1023, 120, 180) / 10.0;

    lcd.setCursor(0, 0);
    lcd.print("Cikis Voltaj:");
    lcd.setCursor(0, 1);
    lcd.print(ekran_voltaji, 1); // 1 ondalık hane yazdır (Örn: 14.5)
    lcd.print(" V   ");          // Sondaki boşluklar eski yazıları temizlemek için
    
    son_ekran_guncelleme = millis();
  }

  // 3. PI HESAPLAMA VE ÇIKIŞI DÜZENLEME
  long total = 0;
  for(int i = 0; i < 5; i++) { 
    total += analogRead(sensorPin); 
  }
  int okunan_deger = total / 5;

  int hata = dinamik_setpoint - okunan_deger;
  float degisim = (hata * Ki) + ((hata - eski_hata) * Kp);
  aktif_sure_us = aktif_sure_us + degisim;
  eski_hata = hata; 

  if (aktif_sure_us > 6500) aktif_sure_us = 6500; 
  if (aktif_sure_us < 0) aktif_sure_us = 0;       

  // Değeri donanıma gönder
  cli();
  aktif_sure_ticks = aktif_sure_us * 2;
  sei();

  delay(5); // Ufak bir nefes alma arası
}
