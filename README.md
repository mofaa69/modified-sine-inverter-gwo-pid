# Metasezgisel Algoritma Tabanlı Modifiye Sinüs Evirici Tasarımı

Bu proje, **TÜBİTAK 2209-A Lisans Araştırma Projesi** desteğiyle **Karadeniz Teknik Üniversitesi Elektrik-Elektronik Mühendisliği** bünyesinde gerçekleştirilen lisans bitirme çalışmasıdır.

---

## 📌 Proje Özeti
Bu çalışmada, modifiye sinüs inverter sisteminin güç katı boyutlandırılmış, KiCad ortamında PCB tasarımı yapılmış ve çıkış gerilim/akım kararlılığını sağlamak amacıyla Gri Kurt Optimizasyonu (GWO) tabanlı PID kontrolör kurgulanmıştır.

* **Topoloji:** Modifiye Sinüs Evirici (Inverter)
* **PCB Tasarımı:** KiCad (Şematik & Layout)
* **Algoritma & Kontrol:** PID Kontrolör, Gri Kurt Optimizasyonu (GWO)
* **Simülasyon:** MATLAB / Simulink
* **Gömülü Yazılım:** Arduino / ATtiny85 
* **Test & Doğrulama:** Osiloskop ve Güç Kaynakları ile Laboratuvar Analizi

---

## 📁 Depo İçeriği

* **`/pcb`**: Güç katı ve kontrol devresine ait KiCad şematik ve PCB layout dosyaları.
* **`/simülasyonO`**: Gri Kurt Optimizasyonu (GWO) MATLAB kodları ve bu algoritmayla beslenen Simulink inverter simülasyon modelleri.
* **`/yazılım`**: Anahtarlama elemanları (MOSFET/IGBT) için üretilen mikrokontrolcü sinyal kodları.
* **`/proje raporu`**: KTÜ Bitirme Projesi nihai raporu (PDF).

---

## 🛠️ Kullanılan Araçlar & Teknolojiler
`KiCad` | `MATLAB / Simulink` | `Arduino IDE` | `C/C++` | `Osiloskop`
