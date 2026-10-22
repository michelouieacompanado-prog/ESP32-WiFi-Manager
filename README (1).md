# Laboratory Activity 9: ESP32 Wi-Fi Manager (Individual)

**Name:** <your full name>
**Assigned number:** 2022-3303
**Course:** BCA188
**Setup network name:** `BCA188-ESP32-2022-3303`

---

## Overview

In this activity I set up WiFiManager on an ESP32 so the board can join different Wi-Fi networks without being reprogrammed. Instead of hard-coding an SSID and password in the sketch, the ESP32 starts its own setup network when it has no saved credentials. I connect to that network with my phone, open the setup page at `192.168.4.1`, and enter the details of the Wi-Fi I want the board to use.

## Objectives

- Set up WiFiManager on an ESP32.
- Connect an ESP32 to different Wi-Fi networks without reprogramming.

## Materials

- ESP32 board
- USB cable
- Computer with the Arduino IDE
- WiFiManager library by tzapu (installed from Library Manager)
- Phone
- Two 2.4 GHz Wi-Fi networks (home router and phone hotspot)

## Setup

1. Installed ESP32 board support in the Arduino IDE.
2. Installed the **WiFiManager** library (by tzapu) from Library Manager.
3. Plugged the ESP32 into my computer with the USB cable.
4. Selected the correct board and port in the Arduino IDE.

## Program

I started from the class sketch (Example 3: Wi-Fi Manager) and made these changes:

- Changed the setup network name to `BCA188-ESP32-2022-3303`.
- Added `wm.setConfigPortalTimeout(180);` before `wm.autoConnect()`. This restarts the board if nobody completes setup within 3 minutes, so a wrong password never leaves it stuck.
- Added a BOOT button check in `loop()`: holding BOOT (GPIO 0) for 3 seconds runs `wm.resetSettings()` and restarts the board, which erases the saved Wi-Fi so the setup network appears again.

The full sketch is in [`wifi_manager/wifi_manager.ino`](wifi_manager/wifi_manager.ino).

## How to Use

1. Upload the code to the ESP32.
2. The ESP32 creates a Wi-Fi network called `BCA188-ESP32-2022-3303`.
3. Connect to that network with my phone.
4. Open `192.168.4.1` in the phone's browser.
5. Choose my Wi-Fi network and enter its password.
6. The ESP32 connects to the network, and the IP address is shown in the Serial Monitor.

**IP address shown in the Serial Monitor:** <fill in, e.g., 192.168.1.x>

## Results Table

| Task | What to do | What you observe |
|------|------------|------------------|
| 1. Wrong password | Enter a wrong password on the setup page. | <e.g., The board could not connect and the setup network `BCA188-ESP32-2022-3303` came back. If I did nothing, the board restarted after the 3-minute timeout.> |
| 2. Reset settings | Hold the BOOT button for 3 seconds while the board is running. | <e.g., The Serial Monitor printed the reset message, the board restarted, and the setup network appeared again.> |
| 3. Change the name | Change the network name, upload, and check your phone's Wi-Fi list. | <e.g., After uploading, the new network name appeared in my phone's Wi-Fi list and the old name was gone.> |
| 4. Different network | Reset the board, then connect to your phone hotspot. | <e.g., I reset the board, entered my phone hotspot details on the setup page, and the board connected with a new IP address in the Serial Monitor.> |

## Screenshots

**1. Setup page on my phone (`192.168.4.1`):**

![Setup page on phone](setup-page.png)

**2. Serial Monitor showing a connected state with an IP address:**

![Serial Monitor connected](serial-monitor.png)

## Why did the board connect to a different network without a code change?

WiFiManager stores the Wi-Fi credentials you enter on the setup page in the ESP32's flash memory instead of hard-coding them in the sketch, so resetting the board and entering new details at runtime lets it join any network without reprogramming.

## Notes and Troubleshooting

- The ESP32 only supports **2.4 GHz** Wi-Fi, so the home router and phone hotspot must both be on 2.4 GHz.
- If the setup network does not appear, check that the board has no saved credentials (hold BOOT for 3 seconds to reset) and that the Serial Monitor baud rate is set to 115200.
- The 180-second portal timeout means the board restarts and shows the setup network again if setup is not finished in time.

## Conclusion

This activity showed how WiFiManager makes an ESP32 flexible: the same uploaded code can join a home router, a phone hotspot, or any other 2.4 GHz network just by using the setup page. Combined with the portal timeout and the BOOT-button reset, the board can always recover from a wrong password or a change of network without being reprogrammed.
