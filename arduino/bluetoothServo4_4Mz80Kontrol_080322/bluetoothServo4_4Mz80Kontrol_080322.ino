// BLUETOOTH ŞİFRESİ: 3434 'DÜR. TABLET DE BUNU GİRMEK GEREKLİDİR.
#include <SoftwareSerial.h>
SoftwareSerial yeniSeriPort(10, 11);
#include <Servo.h>  /* Servo kutuphanesi projeye dahil edildi */
/*DEĞİŞKENLER TANIMLANIYOR*/
#define mz1 4 // MZ80-1 sensör 4. pine bağlandı
#define mz2 7 // MZ80-2 sensör 7. pine bağlandı
#define mz3 8 // MZ80-3 sensör 8. pine bağlandı
#define mz4 12 // MZ80-4 sensör 12. pine bağlandı
#define aktifLed A0

byte durum = 0;
int kontrolDelay=100;
// NOT: SERVO MOTORLARIN KAPAĞA BAĞLANTI KONUMUNDAN KAYNAKLI KAPAĞIN KAPALMA AÇISI:90, KAPAK KAPANMA AÇISI İSE: 0 DIR.
byte closeAngle = 90; // Servo-1'in kapanma açısı:90 derece
byte openAngle = 0; // Servo-1'in açılma açısı:0 derece
int sayac = 0; // GEÇİCİ OLARAK
long simdikiZaman = 0;
byte millis_durum = 0;
// SERVOLAR TANIMLANIYOR
Servo servo1;  /* servo motor nesnesi yaratildi */
Servo servo2;  /* servo motor nesnesi yaratildi */
Servo servo3;  /* servo motor nesnesi yaratildi */
Servo servo4;  /* servo motor nesnesi yaratildi */
/*
  MZ80 MESAFE SENSÖRÜ KULLANIMI
  Kırmızı kablo : +5V
  Yeşil kablo : GND
  Sarı kablo : Data
  ------------------
  Kahverengi: +5V
  Mavi: GND,
  Siyah: Data
*/


void setup()
{
  // MZ80'LER GİRİŞ OLARAK TANIMLANIYOR
  pinMode(mz1, INPUT_PULLUP);
  pinMode(mz2, INPUT_PULLUP);
  pinMode(mz3, INPUT_PULLUP);
  pinMode(mz4, INPUT_PULLUP);
  // 13. PİN ÇIKIŞ OLARAK TANIMLANIYOR
  pinMode(aktifLed, OUTPUT);
  digitalWrite(aktifLed,LOW);
  
  Serial.begin(9600);   //Seri iletişimi başlatır
  yeniSeriPort.begin(9600); // bluetooth ile haberleşme için
  servo1.attach(3); /* Servo1 9 numarali pine baglandi. 9 PWM bir uç*/
  servo2.attach(5); /* Servo1 9 numarali pine baglandi. 9 PWM bir uç*/
  servo3.attach(6); /* Servo1 9 numarali pine baglandi. 9 PWM bir uç*/
  servo4.attach(9); /* Servo1 9 numarali pine baglandi. 9 PWM bir uç*/
  // TÜM KAPAKLARI KAPATMAK İÇİN closeAngle DEĞERİ VERİLİYOR.
  servo1.write(closeAngle); // Servo1 90 dereceye çekildi.
  servo2.write(closeAngle); // Servo2 90 dereceye çekildi.
  servo3.write(closeAngle); // Servo3 90 dereceye çekildi.
  servo4.write(closeAngle); // Servo4 90 dereceye çekildi.
  
}
void loop()
{
  // servoKontrol();
  // servoAcKapat(3,50);
  seriHaberlesme();
  // SensorKontrol();
}

void SensorKontrol() {
  // SENSOR-1
  Serial.print("SENSOR-1:");
  Serial.print(digitalRead(mz1));
  Serial.print("\t");
  // SENSOR-2
  Serial.print("SENSOR-2:");
  Serial.print(digitalRead(mz2));
  Serial.print("\t");
  // SENSOR-3
  Serial.print("SENSOR-3:");
  Serial.print(digitalRead(mz3));
  Serial.print("\t");
  // SENSOR-4
  Serial.print("SENSOR-4:");
  Serial.print(digitalRead(mz4));
  Serial.print("\t");
  Serial.print("\n");
  delay(1000);
}

// NOT: Bu fonk. belirtilen servo motoru açar. (İstenilen atık kapağının açılması)
void servoAc(int servoNumber, int dly = 50) {
  // Serial.print("Gelen Servo Number: ");
  // Serial.println(servoNumber);
  if (servoNumber == 1) // 1. servo ise
  {
    // AÇMA
    for (int i = closeAngle; i >= openAngle; i -= 5) {
      servo1.write(i);
      delay(dly);
    }    
  } else if (servoNumber == 2) {
    // AÇMA
    for (int i = closeAngle; i >= openAngle; i -= 5) {
      servo2.write(i);
      delay(dly);
    }    
  } else if (servoNumber == 3) {
    // AÇMA
    for (int i = closeAngle; i >= openAngle; i -= 5) {
      servo3.write(i);
      delay(dly);
    }    
  } else if (servoNumber == 4) {
    // AÇMA
    for (int i = closeAngle; i >= openAngle; i -= 5) {
      servo4.write(i);
      delay(dly);
    }    
  } else {
    servo1.write(closeAngle);
    servo2.write(closeAngle);
    servo3.write(closeAngle);
    servo4.write(closeAngle);
  }
  delay(dly * 20);
}

// NOT: Bu fonk. belirtilen servo motoru kapatır. (İstenilen atık kapağının kapanması)
void servoKapat(int servoNumber, int dly = 50) {
  // Serial.print("Gelen Servo Number: ");
  // Serial.println(servoNumber);
  if (servoNumber == 1) // 1. servo ise
  {
    // KAPATMA
    for (int i = openAngle; i <= closeAngle; i += 5) {
      servo1.write(i);
      delay(dly);
    }
  } else if (servoNumber == 2) {
    // KAPATMA
    for (int i = openAngle; i <= closeAngle; i += 5) {
      servo2.write(i);
      delay(dly);
    }
  } else if (servoNumber == 3) {
    // KAPATMA
    for (int i = 0; i <= closeAngle; i += 5) {
      servo3.write(i);
      delay(dly);
    }
  } else if (servoNumber == 4) {
    // KAPATMA
    for (int i = openAngle; i <= closeAngle; i += 5) {
      servo4.write(i);
      delay(dly);
    }
  } else {
    servo1.write(closeAngle);
    servo2.write(closeAngle);
    servo3.write(closeAngle);
    servo4.write(closeAngle);
  }
}

//----------------------SERVO MOTOR KONTROLLERİ YAPILIYOR-------------------------------------
void servoKontrol() {
  // AÇMA
  for (int i = 90; i >= 0; i -= 5) {
    servo1.write(i);
    servo2.write(i);
    servo3.write(i);
    servo4.write(i);
    delay(500);
  }
  // KAPATMA
  for (int i = 0; i <= 90; i += 5) {
    servo1.write(i);
    servo2.write(i);
    servo3.write(i);
    servo4.write(i);
    delay(500);
  }
}
//--------------------------SERİ HABERLEŞME İLE SİSTEMDEN BİLGİ BEKLENİYOR----------------

// SERİ HABERLEŞME PROTOKÜLÜMÜZ
//------------------------------------------------------
// KAĞIT ATIK
// 1 NUMARALI KAPAK : AÇMAK İÇİN 1 (49)
// EĞER ATIK ATILDI İSE "K" BİLGİSİ GÖNDERİLİYOR
//------------------------------------------------------
// CAM ATIK
// 2 NUMARALI KAPAK : AÇMAK İÇİN 2 (50)
// EĞER ATIK ATILDI İSE "C" BİLGİSİ GÖNDERİLİYOR
//------------------------------------------------------
// PLASTİK ATIK
// 3 NUMARALI KAPAK : AÇMAK İÇİN 3 (51)
// EĞER ATIK ATILDI İSE "P" BİLGİSİ GÖNDERİLİYOR
//------------------------------------------------------
// DİĞER ATIK
// 4 NUMARALI KAPAK : AÇMAK İÇİN 4 (52)
// EĞER ATIK ATILDI İSE "D" BİLGİSİ GÖNDERİLİYOR
//------------------------------------------------------
void seriHaberlesme() {
  if (yeniSeriPort.available()) // Eğer Bluetooth bağlantısı varsa...
  {   
    int data = yeniSeriPort.read(); //Bluetooth'dan gelen değeri oku ve data değişkenine aktar.
    Serial.println(data);  //Bluetooth'dan gelen değeri serial ekrana yaz.
    // KAPAK-1 İÇİN KONTROL
    if (data == 49) //Eğer gelen değer 1 ise KAPAK-1 AÇILIYOR.
    {
      //yeniSeriPort.println("Servo1-A-");
      Serial.println(data);  //Bluetooth'dan gelen değeri serial ekrana yaz.
      servoAc(1);
      delay(kontrolDelay);
      durum = 0;
      millis_durum =0;
      sensor1Kontrol();
    }
    // KAPAK-2 İÇİN KONTROL
    else if (data == 50) // Eğer gelen değer 2 ise KAPAK-2 AÇILIYOR
    {
      Serial.println(data);  //Bluetooth'dan gelen değeri serial ekrana yaz.
      servoAc(2);
      delay(kontrolDelay);
      durum = 0;
      millis_durum =0;
      sensor2Kontrol();
    }
    // KAPAK-3 İÇİN KONTROL
    else if (data == 51) // Eğer gelen değer 3 ise KAPAK-3 AÇILIYOR
    {
      Serial.println(data);  //Bluetooth'dan gelen değeri serial ekrana yaz.
      servoAc(3);
      delay(kontrolDelay);
      durum = 0;
      millis_durum =0;
      sensor3Kontrol();
    }
    // KAPAK-4 İÇİN KONTROL
    else if (data == 52) // Eğer gelen değer 4 ise KAPAK-4 AÇILIYOR
    {
      Serial.println(data);  //Bluetooth'dan gelen değeri serial ekrana yaz.
      servoAc(4);
      delay(kontrolDelay);
      durum = 0;
      millis_durum =0;
      sensor4Kontrol();
    }
    else
      data = 0;    
  }
}

//-------------------SENSOR-1 KONTROLÜ-------------------------
void sensor1Kontrol() {
  Serial.println("buradayim");
  while (digitalRead(mz1) == 1 && durum == 0) {
    digitalWrite(aktifLed,1);
    delay(30);
    Serial.println("ATIK Bekliyorum");
    // millis() fonk. çağırılacak.
    if (millis_durum==0)
    {
      simdikiZaman = millis();
      millis_durum =1;
    }
//    Serial.print('Sure:');
//    Serial.print(simdikiZaman);
//    Serial.print('-');
//    Serial.print('Su an:');
//    Serial.println(millis());
    if(millis()>= simdikiZaman+5000) // 5 saniye geçmemiş ise
    {
      Serial.print("---------------->");
      Serial.println("giden deger:X");
      yeniSeriPort.print("X"); // X iptal anlamındadır.
      servoKapat(1);
      delay(1000);
      durum = 1;
      digitalWrite(aktifLed,0);
      simdikiZaman = millis();
      durum = 1;
      millis_durum =0;
      break;
    }
    while (digitalRead(mz1) == 0) {
      delay(30);
      Serial.println("ATIK SISTEMDE");
      if (digitalRead(mz1) == 1) 
      {         
        Serial.print("---------------->");
        Serial.println("giden deger:K");
        yeniSeriPort.print("K");
        servoKapat(1);
        delay(1000);
        durum = 1;
        digitalWrite(aktifLed,0);
        millis_durum =0;
        break;                 
      }
    }
  }
}
//-------------------SENSOR-2 KONTROLÜ-------------------------
void sensor2Kontrol() {
  Serial.println("buradayim");
  while (digitalRead(mz2) == 1 && durum == 0) {
    digitalWrite(aktifLed,1);
    delay(30);
    Serial.println("ATIK Bekliyorum");
    //---------------- 5 SANİYE BEKLEDİKTEN SONRA KAPAĞIN KAPANMASINI SAĞLAR-----------
    // millis() fonk. çağırılacak.
    if (millis_durum==0)
    {
      simdikiZaman = millis();
      millis_durum =1;
    }
//    Serial.print('Sure:');
//    Serial.print(simdikiZaman);
//    Serial.print('-');
//    Serial.print('Su an:');
//    Serial.println(millis());
    if(millis()>= simdikiZaman+5000) // 5 saniye geçmemiş ise
    {
      Serial.print("---------------->");
      Serial.println("giden deger:X");
      yeniSeriPort.print("X"); // X iptal anlamındadır.
      servoKapat(2);
      delay(1000);
      durum = 1;
      digitalWrite(aktifLed,0);
      simdikiZaman = millis();
      durum = 1;
      millis_durum =0;
      break;
    }
    //---------------- 5 SANİYE BEKLEDİKTEN SONRA KAPAĞIN KAPANMASINI SAĞLAR-----------
    while (digitalRead(mz2) == 0) {
      delay(30);
      Serial.println("ATIK SISTEMDE");
      if (digitalRead(mz2) == 1) {
        Serial.print("---------------->");
        Serial.println("giden deger:C");
        yeniSeriPort.print("C");
        servoKapat(2);
        delay(1000);
        durum = 1;
        digitalWrite(aktifLed,0);
        break;
      }
    }
  }
}
//-------------------SENSOR-3 KONTROLÜ-------------------------
void sensor3Kontrol() {
  Serial.println("buradayim");
  while (digitalRead(mz3) == 1 && durum == 0) {
    digitalWrite(aktifLed,1);
    delay(30);
    Serial.println("ATIK Bekliyorum");
    //---------------- 5 SANİYE BEKLEDİKTEN SONRA KAPAĞIN KAPANMASINI SAĞLAR-----------
    // millis() fonk. çağırılacak.
    if (millis_durum==0)
    {
      simdikiZaman = millis();
      millis_durum =1;
    }
//    Serial.print('Sure:');
//    Serial.print(simdikiZaman);
//    Serial.print('-');
//    Serial.print('Su an:');
//    Serial.println(millis());
    if(millis()>= simdikiZaman+5000) // 5 saniye geçmemiş ise
    {
      Serial.print("---------------->");
      Serial.println("giden deger:X");
      yeniSeriPort.print("X"); // X iptal anlamındadır.
      servoKapat(3);
      delay(1000);
      durum = 1;
      digitalWrite(aktifLed,0);
      simdikiZaman = millis();
      durum = 1;
      millis_durum =0;
      break;
    }
    //---------------- 5 SANİYE BEKLEDİKTEN SONRA KAPAĞIN KAPANMASINI SAĞLAR-----------
    while (digitalRead(mz3) == 0) {
      delay(30);
      Serial.println("ATIK SISTEMDE");
      if (digitalRead(mz3) == 1) {
        Serial.print("---------------->");
        Serial.println("giden deger:P");
        yeniSeriPort.print("P");
        servoKapat(3);
        delay(1000);
        durum = 1;
        digitalWrite(aktifLed,0);
        break;
      }
    }
  }
}
//-------------------SENSOR-4 KONTROLÜ-------------------------
void sensor4Kontrol() {
  Serial.println("buradayim");
  while (digitalRead(mz4) == 1 && durum == 0) {
    digitalWrite(aktifLed,1);
    delay(30);
    Serial.println("ATIK Bekliyorum");
    //---------------- 5 SANİYE BEKLEDİKTEN SONRA KAPAĞIN KAPANMASINI SAĞLAR-----------
    // millis() fonk. çağırılacak.
    if (millis_durum==0)
    {
      simdikiZaman = millis();
      millis_durum =1;
    }
//    Serial.print('Sure:');
//    Serial.print(simdikiZaman);
//    Serial.print('-');
//    Serial.print('Su an:');
//    Serial.println(millis());
    if(millis()>= simdikiZaman+5000) // 5 saniye geçmemiş ise
    {
      Serial.print("---------------->");
      Serial.println("giden deger:X");
      yeniSeriPort.print("X"); // X iptal anlamındadır.
      servoKapat(4);
      delay(1000);
      durum = 1;
      digitalWrite(aktifLed,0);
      simdikiZaman = millis();
      durum = 1;
      millis_durum =0;
      break;
    }
    //---------------- 5 SANİYE BEKLEDİKTEN SONRA KAPAĞIN KAPANMASINI SAĞLAR-----------
    while (digitalRead(mz4) == 0) {
      delay(30);
      Serial.println("ATIK SISTEMDE");
      if (digitalRead(mz4) == 1) {
        Serial.print("---------------->");
        Serial.println("giden deger:M");
        yeniSeriPort.print("M");
        servoKapat(4);
        delay(1000);
        durum = 1;
        digitalWrite(aktifLed,0);
        break;
      }
    }
  }
}
