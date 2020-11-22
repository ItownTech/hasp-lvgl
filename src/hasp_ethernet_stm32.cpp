/* MIT License - Copyright (c) 2020 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#include <Arduino.h>
#include "ArduinoJson.h"
#include "ArduinoLog.h"
#include "hasp_conf.h"
#include "hasp_hal.h"

#if HASP_USE_ETHERNET > 0 && !defined(ARDUINO_ARCH_ESP32)

EthernetClient EthClient;
IPAddress ip;

void ethernetSetup()
{
#if USE_BUILTIN_ETHERNET > 0
    // start Ethernet and UDP
    Log.notice(TAG_ETH, F("Begin Ethernet LAN8720"));
    if(Ethernet.begin() == 0) {
        Log.notice(TAG_ETH, F("Failed to configure Ethernet using DHCP"));
    } else {
        ip = Ethernet.localIP();
        Log.notice(TAG_ETH, F("DHCP Success got IP %d.%d.%d.%d"), ip[0], ip[1], ip[2], ip[3]);
    }

    Log.notice(TAG_ETH, F("MAC Address %s"), halGetMacAddress(0, ":"));

#else
    byte mac[6];
    uint32_t baseUID = (uint32_t)UID_BASE;
    mac[0]           = 0x00;
    mac[1]           = 0x80;
    mac[2]           = 0xE1;
    mac[3]           = (baseUID & 0x00FF0000) >> 16;
    mac[4]           = (baseUID & 0x0000FF00) >> 8;
    mac[5]           = (baseUID & 0x000000FF);

    char ethHostname[12];
    memset(ethHostname, 0, sizeof(ethHostname));
    snprintf(ethHostname, sizeof(ethHostname), PSTR("HASP-%02x%02x%02x"), mac[3], mac[4], mac[5]);

    Ethernet.setCsPin(W5500_CS);
    Ethernet.setRstPin(W5500_RST);
    Ethernet.setHostname(ethHostname);
    Log.notice(TAG_ETH, F("Begin Ethernet W5500"));
    if(Ethernet.begin(mac) == 0) {
        Log.notice(TAG_ETH, F("Failed to configure Ethernet using DHCP"));
    } else {
        ip = Ethernet.localIP();
        Log.notice(TAG_ETH, F("DHCP Success got IP %d.%d.%d.%d"), ip[0], ip[1], ip[2], ip[3]);
    }
#endif
}

void ethernetLoop(void)
{
    switch(Ethernet.maintain()) {
        case 1:
            // renewed fail
            Log.notice(TAG_ETH, F("Error: renewed fail"));
            break;

        case 2:
            // renewed success
            ip = Ethernet.localIP();
            Log.notice(TAG_ETH, F("DHCP Renew Success got IP=%d.%d.%d.%d"), ip[0], ip[1], ip[2], ip[3]);
            break;

        case 3:
            // rebind fail
            Log.notice(TAG_ETH, F("Error: rebind fail"));
            break;

        case 4:
            // rebind success
            ip = Ethernet.localIP();
            Log.notice(TAG_ETH, F("DHCP Rebind Success got IP=%d.%d.%d.%d"), ip[0], ip[1], ip[2], ip[3]);
            break;

        default:
            // nothing happened
            break;
    }
}

bool ethernetEvery5Seconds()
{
    bool state;
#if USE_BUILTIN_ETHERNET > 0
    state = Ethernet.linkStatus() == LinkON;
#else
    state = Ethernet.link() == 1;
#endif
    Log.warning(TAG_ETH, state ? F("ONLINE") : F("OFFLINE"));
    return state;
}

#endif