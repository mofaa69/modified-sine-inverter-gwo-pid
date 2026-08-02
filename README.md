# Metasezgisel Algoritma Tabanlı Modifiye Sinüs Evirici (Inverter) Tasarımı

Bu proje, **TÜBİTAK 2209-A Üniversite Öğrencileri Araştırma Projeleri Destekleme Programı** (Proje No: 1919B012454606) kapsamında **Karadeniz Teknik Üniversitesi Elektrik-Elektronik Mühendisliği Bölümü**'nde tamamlanmış lisans bitirme çalışmasıdır.

---

## 📌 Proje Özeti
Bu çalışmada, 24V DC giriş gerilimini 12V-18V RMS 50Hz AC çıkış gerilimine dönüştüren, 180W maksimum güce sahip kapalı çevrim bir modifiye sinüs evirici sistemi tasarlanmış ve prototipi üretilmiştir. Sistemin güç hatları pcb üzerinde yapılmamış olup 1.5mm çok damarlı kablolar ile hibrit bir şekilde yapılmıştır.

Çıkış geriliminin kararlılığını sağlamak için Arduino tabanlı bir **PID denetleyici** kurgulanmış; PID kontrolörün Kp ve Ki parametreleri metasezgisel bir sürü zekası algoritması olan **Gri Kurt Optimizasyonu (GWO)** ile optimize edilmiştir.

---

## 🛠️ Donanım & Sistem Mimarisi

* **Güç Katı & Topoloji:** 24V DC beslemeli, 4 adet **IRLZ44N MOSFET** ile kurgulanmış H-Köprüsü (H-Bridge) topolojisi.
* **Sürücü Katı & Bootstrap:** High-side MOSFET tetikleme problemini çözmek amacıyla **IR2110** sürücü entegreleri ve 47µF/25V kondansatör + UF4007 hızlı diyottan oluşan **Bootstrap (Yüzer Kaynak)** mimarisi.
* **Mikrodenetleyici:** Arduino Uno R3 (ATmega328P) — Donanımsal Timer kesmeleri (Timer1 ISR) kullanılarak 50Hz Hassas PWM sinyali üretimi.
* **Geri Besleme & Sensör:** Tam dalga diyot köprüsü (UF4007), $22k\Omega / 4.7k\Omega$ gerilim bölücü ve 10µF filtre kapasitöründen oluşan feedback devresi.
* **Kullanıcı Arayüzü:** I2C modüllü 16x2 LCD ekran ve potansiyometre ile 12V–18V arası anlık referans gerilimi ayarlama.

---

## 📊 Simülasyon ve Optimizasyon (GWO)

* **MATLAB / Simulink:** H-Köprüsü güç katı, yük değişimleri ve batarya voltaj düşümü senaryoları altında kapalı çevrim olarak simüle edilmiştir.
* **Gri Kurt Optimizasyonu (GWO):** Simulink modeliyle entegre çalışan MATLAB algoritması sayesinde minimum hata kriterine göre en ideal kontrolör parametreleri tespit edilmiştir.

---

## 📁 Depo İçeriği

* **`/pcb`**: Şematik çizimler, PCB layout ve 3D kart modelleri.
* **`/simülasyon`**: GWO optimizasyon `.m` kodları ve kapalı çevrim Simulink (`.slx`) modeli.
* **`/yazılım`**: Timer kesmeli, I2C ekran destekli ve anlık PI kontrol hesaplamalı C++ / Arduino kodları.
* **`/proje raporu`**: KTÜ Bitirme Projesi nihai raporu (PDF).

---

## 🔬 Laboratuvar & Deneysel Sonuçlar
Fiziksel olarak üretilen baskı devre (PCB) üzerinde yapılan testlerde, 8.2Ω / 4A yük altında 12.00V ve 18.03V True RMS çıkış değerleri elde edilmiş, simülasyon sonuçları ile deneysel verilerin tam uyum sağladığı doğrulanmıştır.

---

## 🛠️ Kullanılan Teknolojiler
`KiCad` | `MATLAB / Simulink` | `Arduino IDE` | `C/C++` | `GWO Algorithm` | `PID Control`
