<h1 align="center">🔌 ESP32 Dual Relay Control</h1>
<h3 align="center">MIT App Inventor + Node-RED + WebSocket Integration</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif" alt="ESP32">
  <img src="https://img.shields.io/badge/Node--RED-Automation-red?logo=nodered" alt="Node-RED">
  <img src="https://img.shields.io/badge/MIT-App%20Inventor-orange?logo=appinventor" alt="MIT App Inventor">
  <img src="https://img.shields.io/badge/License-Open--Source-green" alt="License">
</p>

---

## 🧩 Deskripsi Proyek

Proyek ini memungkinkan **kontrol dua relay menggunakan ESP32**, yang dapat dikendalikan secara **real-time** dari:
- **MIT App Inventor** (melalui HTTP Request)
- **Node-RED Dashboard** (melalui WebSocket)

ESP32 juga dapat mengontrol relay langsung menggunakan **tombol fisik**, dan sinkronisasi status akan otomatis dikirim ke dashboard.

---

## ⚙️ Fitur Utama

✅ Kontrol **ON/OFF** untuk dua relay secara langsung  
✅ Komunikasi **dua arah** via WebSocket  
✅ Endpoint **HTTP** untuk integrasi dengan MIT App  
✅ Sinkronisasi status otomatis antar perangkat  
✅ Kompatibel dengan dashboard IoT seperti **Node-RED UI**  
✅ Dapat dikembangkan untuk sistem **smart home automation**

---

## 🗂️ Struktur Proyek

| File | Deskripsi |
|------|------------|
| 🧠 `onoffMIT_.ino` | Program utama ESP32: koneksi WiFi, kontrol relay, dan komunikasi WebSocket. |
| 🔁 `onoffmit.json` | Flow Node-RED: menerima data dari MIT App dan meneruskannya ke ESP32. |

---

## 🚀 Cara Instalasi

### 🔧 1. Upload Program ke ESP32
1. Buka file `onoffMIT_.ino` di **Arduino IDE**.  
2. Pastikan **ESP32 Board** sudah terinstal (melalui *Board Manager*).  
3. Ubah konfigurasi WiFi:
   ```cpp
   const char* ssid = "Nama_WiFi";
   const char* password = "Password_WiFi";
   ```
4. Upload ke board ESP32.  
5. Buka **Serial Monitor (115200 baud)** → catat alamat IP ESP32.

---

### 🌐 2. Import Flow ke Node-RED
1. Jalankan Node-RED (`http://localhost:1880`).  
2. Klik **Menu → Import → Upload File**, lalu pilih `onoffmit.json`.  
3. Pastikan alamat WebSocket sesuai (`/luk`).  
4. Klik **Deploy** untuk menjalankan flow.  
5. Node HTTP `/mitapp` siap menerima request dari MIT App.

---

### 📱 3. Hubungkan MIT App Inventor
1. Buka [MIT App Inventor](https://appinventor.mit.edu/).  
2. Tambahkan komponen **Web** → ubah URL:
   ```
   http://<IP-NodeRED>:1880/mitapp
   ```
3. Gunakan blok `Web.PostText` untuk mengirim data JSON:
   ```json
   {"ON": ""}
   ```
   atau
   ```json
   {"OFF": ""}
   ```
4. Node-RED meneruskan ke ESP32 melalui WebSocket, dan relay akan aktif/mati.

---

## 🔌 Diagram Komunikasi

```
📱 MIT App
    ↓ (HTTP POST)
🧠 Node-RED
    ↓ (WebSocket)
⚡ ESP32 → Relay
```

ESP32 juga mengirim status terkini kembali ke Node-RED untuk sinkronisasi real-time.

---

## 🔧 Kebutuhan Hardware

| Komponen | Jumlah | Keterangan |
|-----------|---------|------------|
| ESP32 | 1 | Mikrokontroler utama |
| Relay Module (2-Channel) | 1 | Untuk mengontrol dua perangkat |
| Push Button | 2 | Untuk kontrol manual |
| LED (Opsional) | 1 | Indikator status |
| Kabel Jumper | Beberapa | Koneksi antar modul |

---

## 🧠 Tips & Catatan
- Pastikan **ESP32, Node-RED, dan MIT App Inventor** berada dalam **jaringan WiFi yang sama**.  
- Jika WebSocket gagal, pastikan port `81` terbuka di jaringan.  
- Dapat dikembangkan untuk:
  - Kontrol lebih dari 2 relay  
  - Penjadwalan otomatis  
  - Dashboard web untuk monitoring  

---

## 📜 Lisensi
Proyek ini bersifat **Open Source** — kamu bebas menggunakan dan memodifikasinya untuk keperluan belajar atau proyek IoT pribadi.

---

## ✨ Kontributor
Nama : Lukman Hafiz 
Girhub : github.com/Lukmanhafiz
Email : harusdpetemas22@gmail.com
