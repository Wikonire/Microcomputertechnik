___
# Projekt Mikrofon-Mischsystem

## Dokumentation und Lösung der Aufgaben
**Fach: Mikrocomputertechnik, TEKO**

## 1. Einleitung

Dieses Projekt zielt darauf ab, ein **digitales Mikrofon-Mischsystem** zu entwickeln, das **mehrere Mikrofone kombiniert und über Bluetooth an ein Smartphone gesendet wird**. Die Lautstärke jedes Mikrofons soll über **analoge Schieberegler (Slider)** individuell anpassbar sein. Das System soll in **Sitzungssituationen oder Gesprächen** eingesetzt werden, um es einer hörbeeinträchtigten Person zu ermöglichen, die Mikrofone nach Bedarf lauter oder leiser zu stellen.

Das Projekt wird schrittweise aufgebaut, um eine **zuverlässige und skalierbare Lösung** zu entwickeln und technische Herausforderungen frühzeitig zu erkennen und zu lösen.

---

## 2. Vorrecherche: Audiosignalverarbeitung für Cochlea-Implantate (CI)

Da Alwin das **Cochlear Nucleus 7 Soundprozessor**, das **Cochlear CI512 Implantat** und den **Phonak Roger Receiver** nutzt, bedeutet das für die Audiosignalübertragung Folgendes:

### 2.1 Signalverarbeitung im System

- Der **Cochlear Nucleus 7** wandelt akustische Signale in elektrische Impulse um und sendet sie an das **CI512 Implantat**.
- Das **CI512 Implantat** stimuliert dann den Hörnerv durch Elektroden im Innenohr.
- Der **Roger Receiver** (vermutlich **Roger 20**) empfängt Audiosignale von externen Mikrofonen (z. B. **Phonak Roger Pen** oder **Roger Table Mic**) und überträgt sie direkt an den **Nucleus 7**.

### 2.2 Audioquellen und Übertragungswege

- **Direktes Hören:** Der **Nucleus 7** verarbeitet Umgebungsgeräusche über sein Mikrofon.
- **Streaming über Bluetooth:** Direkte Verbindung zu Smartphones oder anderen Bluetooth-Audioquellen mit der **Cochlear-App**.
- **Roger-System:** Externe Mikrofone (z. B. **Roger Pen**) übertragen Sprache über Funk direkt an den **Roger Receiver**, wodurch störende Nebengeräusche minimiert werden.
- **FM-Übertragung:** Falls der **Roger Receiver** an ein FM-System angeschlossen ist, kann er Audiosignale von kompatiblen Geräten empfangen.

### 2.3 Wichtige Faktoren für die Audiosignalqualität

- **Sprachverständlichkeit priorisieren:** Das **Roger-System** hilft in lauten Umgebungen, indem es Sprache verstärkt.
- **Musikwiedergabe ist oft weniger präzise**, da das CI eine Frequenzbandlimitierung hat.
- **Lautstärke & Balance:** Die Signalverarbeitung des **Nucleus 7** kann individuell angepasst werden, um Komfort und Verständlichkeit zu optimieren.
- **Interferenzen vermeiden:** Elektromagnetische Störungen können die Signalübertragung beeinflussen, z. B. durch starke Magnetfelder oder ungeschirmte Geräte.

### 2.4 Frequenzbereich und Bandbreite

- CIs können typischerweise **Frequenzen zwischen 200 Hz und 8 kHz** übertragen.
- Hochfrequente Töne über 8 kHz können oft nicht präzise wiedergegeben werden.
- Tiefe Frequenzen unter 200 Hz haben wenig Einfluss auf Sprachverständlichkeit und werden daher reduziert.

**Auswirkung auf das Projekt:**
- Das Audiosignal muss mit einem **Bandpassfilter auf 200 Hz - 8 kHz** begrenzt werden.

### 2.5 Signalverarbeitung und Kodierung

- Das Signal wird in **Frequenzbänder zerlegt**, die auf verschiedene Elektroden des CIs verteilt werden.
- Die Anzahl der Frequenzbänder ist durch die **Anzahl der Elektroden (12-22) begrenzt**.

**Auswirkung auf das Projekt:**
- Ein **Equalizer oder spektrale Signalaufbereitung** könnte die Verständlichkeit verbessern.

### 2.6 Dynamikbereich und Komprimierung

- Natürliches Gehör: **120 dB Dynamik** vs. Cochlea-Implantate: **20-40 dB Dynamik**.
- Laute und leise Signale müssen **automatisch komprimiert werden**.

**Auswirkung auf das Projekt:**
- Eine **automatische Lautstärkeregelung (AGC)** muss implementiert werden.

---

## 3. Umsetzungskonzept

### **Schritt 1: Vorrecherche und Systemanforderungen**
- Untersuchung der CI-Technik und ihrer Einschränkungen.
- Festlegung der technischen Rahmenbedingungen (Bluetooth-Protokolle, Frequenzbereiche, Dynamikverhalten).

### **Schritt 2: Mikrofonintegration**
- Auswahl eines geeigneten **I2S-Mikrofons**.
- Sicherstellung, dass das **Audiosignal klar und rauschfrei** ist.

### **Schritt 3: Lautstärkeregelung über Schieberegler**
- Implementierung der analogen Lautstärkeregelung mit **Potentiometern**.

### **Schritt 4: Bluetooth-Streaming an das Smartphone**
- Nutzung von **HFP/SCO statt A2DP** für geringe Latenz.

### **Schritt 5: Erweiterung auf mehrere Mikrofone**
- Entwicklung eines Softwaremixers zur parallelen Verarbeitung mehrerer Audiosignale.

---

## 4. Technische Anforderungen und Lösungen

| Kategorie                        | Anforderung                                         | Lösung                                        |
|----------------------------------|----------------------------------------------------|----------------------------------------------|
| **Signalverarbeitung**            | 200 Hz – 8 kHz Bandpassfilter                     | Falls nötig, einfacher Software-Filter      |
|                                  | Automatische Lautstärkeregelung (AGC)              | Regelung durch Verstärkung vor dem Handy    |
| **Bluetooth-Streaming**           | Niedrige Latenz                                    | Nutzung von **HFP/SCO statt A2DP**          |
|                                  | ESP32 als Bluetooth-Headset für Handy             | HFP-Protokoll implementieren                |
| **Mikrofone**                     | Mehrere Mikrofone gleichzeitig                    | I2S-Mikrofone und Software-Mixing           |
|                                  | Rückkopplungen vermeiden                          | Grundstufe zur Geräuschreduzierung           |
|                                  | Sprechpriorisierung                               | Falls nötig, Richtmikrofon-Technik           |
| **Lautstärkeregelung**            | Regelung per Slider                               | Potentiometer als analoge Regler            |
|                                  | Reaktionszeit soll minimal sein                   | Direkte Verbindung zur Verstärkungsstufe     |
| **Elektromagnetische Abschirmung** | Störungen durch offene Platinen minimieren        | Metallgehäuse und **abgeschirmte Kabel**    |
|                                  | Störungen durch ESP32/Arduino verhindern          | **Ferritkerne & Erdung**                     |
| **Benutzerfreundlichkeit**        | LED-Anzeige für aktive Mikrofone                  | Optional LED-Steuerung implementieren        |
|                                  | Mikrofone manuell ein- und ausschalten            | Hardware-Schalter oder Softwaresteuerung     |

---

## 5. Fazit und nächste Schritte

### **Nächste Schritte**
1. **Testaufbau mit einem Mikrofon und Bluetooth-Streaming an ein Handy**.
2. **Latenz in ms messen, Signalqualität bewerten, Paketverluste loggen**.





# Projekt Mikrofon-Mischsystem,  Dokumentation und Lösung der Aufgaben,  Fach Mikrocomputertechnik, TEKO

## 1. Einleitung

Dieses Projekt zielt darauf ab, ein **digitales Mikrofon-Mischsystem** zu entwickeln, das **mehrere Mikrofone kombiniert und über Bluetooth an ein Smartphone gesendet wird**. Die Lautstärke jedes Mikrofons soll über **analoge Schieberegler (Slider)** individuell anpassbar sein. Das System soll in **Sitzungssituationen oder Gesprächen** eingesetzt werden, um es einer hörbeeinträchtigten Person zu ermöglichen, die Mikrofone nach Bedarf lauter oder leiser zu stellen.

Das Projekt wird schrittweise aufgebaut, um eine **zuverlässige und skalierbare Lösung** zu entwickeln und technische Herausforderungen frühzeitig zu erkennen und zu lösen.

---

# Vorrecherche: Audiosignalverarbeitung für Cochlea-Implantate (CI)

Da Alwin das **Cochlear Nucleus 7 Soundprozessor**, das **Cochlear CI512 Implantat** und den **Phonak Roger Receiver** nutzt, bedeutet das für die Audiosignalübertragung Folgendes:

## 2.1 Signalverarbeitung im System

- Der **Cochlear Nucleus 7** wandelt akustische Signale in elektrische Impulse um und sendet sie an das **CI512 Implantat**.
- Das **CI512 Implantat** stimuliert dann den Hörnerv durch Elektroden im Innenohr.
- Der **Roger Receiver** (vermutlich **Roger 20**) empfängt Audiosignale von externen Mikrofonen (z. B. **Phonak Roger Pen** oder **Roger Table Mic**) und überträgt sie direkt an den **Nucleus 7**.

## 2.2 Audioquellen und Übertragungswege

- **Direktes Hören:** Der **Nucleus 7** verarbeitet Umgebungsgeräusche über sein Mikrofon.
- **Streaming über Bluetooth:** Direkte Verbindung zu Smartphones oder anderen Bluetooth-Audioquellen mit der **Cochlear-App**.
- **Roger-System:** Externe Mikrofone (z. B. **Roger Pen**) übertragen Sprache über Funk direkt an den **Roger Receiver**, wodurch störende Nebengeräusche minimiert werden.
- **FM-Übertragung:** Falls der **Roger Receiver** an ein FM-System angeschlossen ist, kann er Audiosignale von kompatiblen Geräten empfangen.

## 2.3 Was ist bei der Audiosignalqualität wichtig?

- **Sprachverständlichkeit priorisieren:** Das **Roger-System** hilft in lauten Umgebungen, indem es Sprache verstärkt.
- **Musikwiedergabe ist oft weniger präzise**, da das CI eine Frequenzbandlimitierung hat.
- **Lautstärke & Balance:** Die Signalverarbeitung des **Nucleus 7** kann individuell angepasst werden, um Komfort und Verständlichkeit zu optimieren.
- **Interferenzen vermeiden:** Elektromagnetische Störungen können die Signalübertragung beeinflussen, z. B. durch starke Magnetfelder oder ungeschirmte Geräte.

---

## 2.4 Frequenzbereich und Bandbreite

- CIs können typischerweise **Frequenzen zwischen 200 Hz und 8 kHz** übertragen.
- Hochfrequente Töne über 8 kHz können oft nicht präzise wiedergegeben werden.
- Tiefe Frequenzen unter 200 Hz haben wenig Einfluss auf Sprachverständlichkeit und werden daher reduziert.

**Auswirkung auf das Projekt:**
- Das Audiosignal muss mit einem **Bandpassfilter auf 200 Hz - 8 kHz** begrenzt werden.

## 2.5 Signalverarbeitung und Kodierung

- Das Signal wird in **Frequenzbänder zerlegt**, die auf verschiedene Elektroden des CIs verteilt werden.
- Die Anzahl der Frequenzbänder ist durch die **Anzahl der Elektroden (12-22) begrenzt**.

**Auswirkung auf das Projekt:**
- Ein **Equalizer oder spektrale Signalaufbereitung** könnte die Verständlichkeit verbessern.

## 2.6 Dynamikbereich und Komprimierung

- Natürliches Gehör: **120 dB Dynamik** vs. Cochlea-Implantate: **20-40 dB Dynamik**.
- Laute und leise Signale müssen **automatisch komprimiert werden**.

**Auswirkung auf das Projekt:**
- Eine **automatische Lautstärkeregelung (AGC)** muss implementiert werden.

## 2.7 Bluetooth-Streaming an das Handy

- **Das CI kann nicht direkt per Bluetooth verbunden werden**.
- Das Handy dient als **Empfangs- und Weiterleitungsgerät**.
- **Niedrige Latenz ist essenziell**, um Verzögerungen in Gesprächen zu vermeiden.

**Auswirkung auf das Projekt:**
- Das **ESP32 muss als Bluetooth-Headset (HFP/SCO-Protokoll) erkannt werden**.

---

## 2.8 Elektromagnetische Abschirmung

### Warum ist ein Arduino ungeschirmt?

Ein Arduino ist grundsätzlich ein **ungeschirmtes Gerät**, da die meisten Arduino-Boards keine eigene elektromagnetische Abschirmung haben:
- **Kein Metallgehäuse**: Die meisten Boards sind offen und haben keine EMV-Abschirmung.
- **Ungefilterte Signale**: GPIOs (Ein-/Ausgänge) können elektromagnetische Störungen verursachen oder aufnehmen.
- **Offene Leiterbahnen**: Leiterbahnen auf der Platine sind ungeschützt und können als Antennen wirken.

### Wann kann das ein Problem sein?

- In Umgebungen mit **starker elektromagnetischer Strahlung** (z. B. Funkanlagen, Hochspannungsleitungen) kann der Arduino gestört werden.
- Der Arduino kann selbst Störungen verursachen, wenn schlecht abgeschirmte Kabel oder Module angeschlossen sind.

### Was kann man tun?

- **Metallgehäuse nutzen**, das geerdet ist.
- **Abgeschirmte Kabel verwenden**, besonders für Sensoren und Kommunikationsleitungen.
- **Ferritkerne an Kabeln anbringen**, um Störungen zu reduzieren.
- **Gute Masseführung auf der Platine sicherstellen**.

**Auswirkung auf das Projekt:**
- Um eine saubere Signalverarbeitung zu gewährleisten, sollten **abgeschirmte Kabel und Ferritkerne** verwendet werden.
- Falls elektromagnetische Störungen auftreten, ist ein **Metallgehäuse mit Erdung** in Betracht zu ziehen.


## Bedingungen aus der Vorrecherche

Basierend auf den Erkenntnissen aus der Vorrecherche ergeben sich mehrere technische und funktionale Anforderungen, die für die Umsetzung des Projekts berücksichtigt werden müssen.

---

### 1. Anforderungen an die Signalverarbeitung

- Das Audiosignal muss für Sprachverständlichkeit optimiert werden.
- Frequenzen außerhalb von **200 Hz – 8 kHz** sollten gefiltert werden, da das CI nur diesen Bereich verarbeitet.
- Die Hauptverarbeitung des Klangs erfolgt auf dem **Handy**, daher sollte das Signal möglichst unverfälscht und mit minimalem Rauschen übertragen werden.
- Eine automatische Lautstärkeregelung (AGC) ist notwendig, da das CI nur einen begrenzten Dynamikbereich von **20-40 dB** verarbeiten kann.

**Lösung:**
- Das **ESP32 sendet das Rohsignal unverändert**, die Signalverarbeitung übernimmt das Handy.
- Falls notwendig, könnte ein einfacher **Bandpassfilter zwischen 200 Hz – 8 kHz** genutzt werden.
- Eine **stabile Verstärkungsregelung**, um Signalrauschen zu minimieren.

---

### 2. Anforderungen an das Bluetooth-Streaming

- Das **ESP32 muss als Bluetooth-Headset erkannt werden**, da das CI nicht direkt mit Bluetooth verbunden werden kann.
- Das Handy empfängt das Signal und verarbeitet es weiter.
- **Niedrige Latenz ist essenziell**, um eine verständliche Echtzeitübertragung zu gewährleisten.
- A2DP (Musik-Streaming) ist ungeeignet, da es zu hohe Latenzen erzeugt.

**Lösung:**
- Nutzung des **HFP/SCO-Protokolls** für niedrige Latenz.
- Direkte Verbindung des ESP32 mit dem Smartphone.
- Sicherstellen, dass das Bluetooth-Signal stabil bleibt.

---

### 3. Anforderungen an die Mikrofone

- Mehrere Mikrofone müssen parallel verarbeitet werden können.
- Es muss sichergestellt werden, dass kein Crosstalk oder Rückkopplung entsteht.
- Falls mehrere Sprecher*innen gleichzeitig sprechen, soll eine Priorisierung oder Noise-Cancelling möglich sein.
- Das Handy übernimmt die finale Klangverarbeitung, daher müssen die Mikrofone möglichst saubere Signale liefern.

**Lösung:**
- Verwendung von **I2S-Mikrofonen** für digitale Signalübertragung.
- Softwareseitige Steuerung der Mikrofonverstärkung.
- Falls erforderlich, eine Grundstufe zur Geräuschreduktion.

---

### 4. Anforderungen an die Lautstärkeregelung

- Die Lautstärke jedes Mikrofons soll über einen **analogen Slider (Potentiometer)** individuell einstellbar sein.
- Die Lautstärkeregelung darf keine hörbaren Störgeräusche oder Verzögerungen verursachen.
- Die Steuerung muss in Echtzeit erfolgen, um das Signal korrekt an das Handy zu senden.

**Lösung:**
- Verwendung von **Potentiometern zur Lautstärkeregelung jedes Mikrofons**.
- Softwareseitige Anpassung des Gain-Werts.
- Sicherstellen, dass die Regelung flüssig und ohne Artefakte arbeitet.

---

### 5. Anforderungen an die elektromagnetische Abschirmung

- Das ESP32 und die Mikrofonmodule sind ungeschirmt, was bedeutet, dass sie Störungen empfangen oder selbst abstrahlen können.
- Umgebungen mit starker elektromagnetischer Strahlung (z. B. WLAN, Mobilfunk) könnten die Signalqualität negativ beeinflussen.
- Der Arduino/ESP32 kann selbst Störungen verursachen, die das CI beeinflussen.

**Lösung:**
- Metallgehäuse mit Erdung, um Störungen zu minimieren.
- Abgeschirmte Kabel für Audio- und Stromleitungen.
- Ferritkerne zur Reduzierung von hochfrequenten Störungen.
- Gute Masseführung und getrennte Stromversorgung für analoge und digitale Signale.

---

### 6. Anforderungen an die Benutzerfreundlichkeit

- Das System muss einfach bedienbar sein, da der Nutzer selbst die Mikrofonlautstärke steuern kann.
- Optional: Falls mehrere Mikrofone aktiv sind, sollte eine LED-Anzeige zeigen, welche Mikrofone gerade genutzt werden.

**Lösung:**
- Einfache Schieberegler für die Lautstärkeregelung.
- Optional: LED-Visualisierung, welches Mikrofon aktiv ist.
- Möglichkeit, Mikrofone manuell ein- und auszuschalten.

---

### Zusammenfassung der technischen Anforderungen und Lösungen

| Kategorie                        | Anforderung                                         | Lösung                                        |
|----------------------------------|----------------------------------------------------|----------------------------------------------|
| **Signalverarbeitung**            | 200 Hz – 8 kHz Bandpassfilter                     | Falls nötig, einfacher Software-Filter      |
|                                  | Automatische Lautstärkeregelung (AGC)              | Regelung durch Verstärkung vor dem Handy    |
| **Bluetooth-Streaming**           | Niedrige Latenz                                    | Nutzung von **HFP/SCO statt A2DP**          |
|                                  | ESP32 als Bluetooth-Headset für Handy             | HFP-Protokoll implementieren                |
| **Mikrofone**                     | Mehrere Mikrofone gleichzeitig                    | I2S-Mikrofone und Software-Mixing           |
|                                  | Rückkopplungen vermeiden                          | Grundstufe zur Geräuschreduzierung           |
|                                  | Sprechpriorisierung                               | Falls nötig, Richtmikrofon-Technik           |
| **Lautstärkeregelung**            | Regelung per Slider                               | Potentiometer als analoge Regler            |
|                                  | Reaktionszeit soll minimal sein                   | Direkte Verbindung zur Verstärkungsstufe     |
| **Elektromagnetische Abschirmung** | Störungen durch offene Platinen minimieren        | Metallgehäuse und **abgeschirmte Kabel**    |
|                                  | Störungen durch ESP32/Arduino verhindern          | **Ferritkerne & Erdung**                     |
| **Benutzerfreundlichkeit**        | LED-Anzeige für aktive Mikrofone                  | Optional LED-Steuerung implementieren        |
|                                  | Mikrofone manuell ein- und ausschalten            | Hardware-Schalter oder Softwaresteuerung     |



---

## 3. Umsetzungskonzept

Das Projekt wird in mehrere Teilprojekte unterteilt, die schrittweise umgesetzt werden. Jede Phase baut auf der vorherigen auf, um die Funktionalität zu erweitern und Fehler frühzeitig zu erkennen.

### **Schritt 1: Vorrecherche und Systemanforderungen**
- Untersuchung der CI-Technik und ihrer Einschränkungen.
- Festlegung der technischen Rahmenbedingungen (Bluetooth-Protokolle, Frequenzbereiche, Dynamikverhalten).

### **Schritt 2: Teilprojekt Slider-Steuerung**
**Ziel:**
- Implementierung der analogen Lautstärkeregelung über Schieberegler.

**Anforderungen:**
- Anbindung eines **analogen Potentiometers** an den Mikrocontroller.
- Stabile **Messung und Skalierung der Werte**.

**Erwartetes Ergebnis:**
- Der Slider gibt stabile Werte aus.

### **Schritt 3: Teilprojekt Mikrofonaufnahme**
**Ziel:**
- Integration eines oder mehrerer Mikrofone zur Spracheingabe.

**Anforderungen:**
- Auswahl eines geeigneten **I2S-Mikrofons**.
- Sicherstellung, dass das **Audiosignal klar und rauschfrei** ist.

**Erwartetes Ergebnis:**
- Das Mikrofon nimmt Sprache auf und gibt ein verständliches Signal aus.

### **Schritt 4: Teilprojekt Kombination von Slider und Mikrofon**
**Ziel:**
- Die Lautstärke des Mikrofons wird über den Slider angepasst.

**Erwartetes Ergebnis:**
- Die Lautstärke kann stabil geregelt werden.

### **Schritt 5: Teilprojekt Bluetooth-Streaming**
**Ziel:**
- Das Audiosignal wird an das Smartphone gestreamt.

**Anforderungen:**
- Nutzung von **HFP/SCO statt A2DP** für eine geringe Latenz.

**Erwartetes Ergebnis:**
- Das Smartphone erkennt das ESP32 als Headset und empfängt das Audiosignal.

### **Schritt 6: Teilprojekt Erweiterung auf mehrere Mikrofone**
**Ziel:**
- Mehrere Mikrofone simultan erfassen und mischen.

**Anforderungen:**
- Implementierung eines Softwaremixers zur Verarbeitung mehrerer Audiosignale.

**Erwartetes Ergebnis:**
- Mehrere Mikrofone können parallel genutzt werden, ohne sich gegenseitig zu stören.

### **Schritt 7: Teilprojekt Optimierung der Sprachverarbeitung**
**Ziel:**
- Verbesserung der Verständlichkeit durch Rauschunterdrückung und Lautstärkekompensation.

**Erwartetes Ergebnis:**
- Klare und verständliche Sprachübertragung.

### **Schritt 8: Langfristige Erweiterungen (Optional)**
- **LED-Anzeige**, um aktive Mikrofone zu visualisieren.
- **DSP-Filter**, um Stimmen besser voneinander zu trennen.
- **Integration einer Handy-App**, um die Lautstärkeregelung digital umzusetzen.

---

## 4. Fazit und nächste Schritte

### Wichtigste Erkenntnisse:
1. **Bluetooth-Streaming muss auf Sprache optimiert sein** (HFP/SCO statt A2DP).
2. **Frequenzbereich muss auf 200 Hz bis 8 kHz begrenzt werden**.
3. **Automatische Lautstärkeanpassung (AGC) muss integriert werden**.
4. **Mehrere Mikrofone dürfen sich nicht gegenseitig stören**.
5. **Rückkopplung und Latenz müssen minimiert werden**.

### Nächste Schritte:
1. **Testaufbau mit einem Mikrofon und Bluetooth-Streaming an ein Handy**.
2. **Implementierung der Lautstärkeregelung über Slider**.
3. **Optimierung der Signalverarbeitung (Noise-Cancelling, Lautstärkeausgleich)**.
4. **Erweiterung auf mehrere Mikrofone und Mischverhältnissteuerung**.

Dieses System wird schrittweise entwickelt, um eine **optimale Sprachübertragung mit minimaler Latenz und maximaler Verständlichkeit für hörbeeinträchtigte Nutzende zu gewährleisten**.

# Verbesserungsvorschläge von ChatGPT:
## Bluetooth-Protokoll konkretisieren
→ HFP/SCO ist richtig, aber falls es ein Gerät gibt, das nur LE Audio (Bluetooth 5.2+) unterstützt, könnte ein Fallback auf einen anderen Codec bedacht werden. Vielleicht ein Hinweis, dass Low Complexity Subband Coding (mSBC) als Standard-Codec verwendet wird?

## Bandpassfilter als Option formulieren
→ In der Auswirkung auf das Projekt könnte ergänzt werden:
Falls das Handy bereits eine frequenzoptimierte Verarbeitung durchführt, kann der Bandpassfilter auf dem ESP32 entfallen.

## Nächste Schritte noch etwas präziser
→ Beim Punkt "Testaufbau mit einem Mikrofon und Bluetooth-Streaming an ein Handy":
Vielleicht direkt dazuschreiben, welche Werte überprüft werden sollen (z. B. Latenz in ms messen, Signalqualität subjektiv bewerten, evtl. Paketverluste loggen).