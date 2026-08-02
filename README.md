# Metasezgisel Algoritma Tabanlı Modifiye Sinüs Evirici Tasarımı

Bu proje, **TÜBİTAK 2209-A Lisans Araştırma Projesi** desteğiyle **Karadeniz Teknik Üniversitesi Elektrik-Elektronik Mühendisliği** bünyesinde gerçekleştirilen lisans bitirme çalışmasıdır.

---

## 📌 Proje Özeti
Bu projede, genel kullanım amaçlı metasezgisel algoritma tabanlı bir modifiye
sinüs evirici tasarımı yapılmıştır. Evirici çıkış gerilimi PID denetleyici ile kontrol
edilmiş olup, PID denetleyici parametreleri de metasezgisel algoritmalar ile belirlenmiştir. 
Bu projede, çıkış gerilimini tasarladığım PID denetleyici ile anlık
olarak kontrol ederek sistemin verimini ve kalitesini artırmayı amaçladım.

* **Topoloji:** Modifiye Sinüs Evirici (Inverter)
* **PCB Tasarımı:** KiCad (Şematik & Layout)
* **Algoritma & Kontrol:** PID Kontrolör, Gri Kurt Optimizasyonu (GWO)
* **Simülasyon:** MATLAB / Simulink
* **Gömülü Yazılım:** Arduino / ATtiny85 
* **Test & Doğrulama:** Osiloskop ve Güç Kaynakları ile Laboratuvar Analizi

---

## 📁 Depo İçeriği

* **`/pcb`**: Güç katı ve kontrol devresine ait KiCad şematik ve PCB layout dosyaları.
* **`/simülasyon`**: Gri Kurt Optimizasyonu (GWO) MATLAB kodları ve bu algoritmayla beslenen Simulink inverter simülasyon modelleri.
* **`/yazılım`**: Anahtarlama elemanları (MOSFET/IGBT) için üretilen mikrokontrolcü sinyal kodları.
* **`/proje raporu`**: KTÜ Bitirme Projesi nihai raporu (PDF).

---

## 🛠️ Kullanılan Araçlar & Teknolojiler
`KiCad` | `MATLAB / Simulink` | `Arduino IDE` | `C/C++` | `Osiloskop`
