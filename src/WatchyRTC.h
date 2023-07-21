#ifndef WATCHY_RTC_H
#define WATCHY_RTC_H

#include "config.h"
#include "time.h"
#include "Wire.h"
#include <DS3232RTC.h>
#include <Rtc_Pcf8563.h>

#define DS3231          1
#define PCF8563         2
#define RTC_DS_ADDR     0x68
#define RTC_PCF_ADDR    0x51
#define YEAR_OFFSET_DS  1970
#define YEAR_OFFSET_PCF 2000

#define RTCC_TIMER_TI_TF_PULSE 0x10 // Timer interupt pulse
#define RTCC_TIMER_TIE 0x01         // Timer Interrupt Enable
#define RTCC_TIMER_TF 0x04          // Timer Flag
#define RTCC_TIMER_ADDR 0x0e
#define RTCC_TIMER_ENABLED 0x80
#define RTCC_TIMER_DISABLED 0x00
#define RTCC_TIMER_FREQ_4kish 0x00  // 4.096 kHz
#define RTCC_TIMER_FREQ_64 0x01     // 64 Hz
#define RTCC_TIMER_FREQ_1 0x02      // 1 Hz
#define RTCC_TIMER_FREQ_min 0x03    // 1/60 Hz

class WatchyRTC {
public:
  DS3232RTC rtc_ds;
  Rtc_Pcf8563 rtc_pcf;
  uint8_t rtcType;

public:
  WatchyRTC();
  void init();
  void config(String datetime); // String datetime format is YYYY:MM:DD:HH:MM:SS
  void clearAlarm();
  void read(tmElements_t &tm);
  void set(tmElements_t tm);
  uint8_t temperature();

  void stopAlarm();
  void setTimer();
  void clearTimer();

  byte getStatus(byte loc);

private:
  void _DSConfig(String datetime);
  void _PCFConfig(String datetime);
  int _getDayOfWeek(int d, int m, int y);
  String _getValue(String data, char separator, int index);

  void updateStatus2(byte value);

  int Rtcc_Addr;
};

#endif