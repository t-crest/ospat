#ifndef __POK_PATMOS_RTC_H__
#define __POK_PATMOS_RTC_H__

#define _IODEV __attribute__((address_space(1)))

typedef _IODEV unsigned int volatile * const _iodev_ptr_t;

// Address to access the cycle counter low register of the RTC
#define __PATMOS_RTC_CYCLE_LOW_ADDR (0xF0000300)

// Address to access the cycle counter up register of the RTC
#define __PATMOS_RTC_CYCLE_UP_ADDR (0xF0000304)

// Address to access the time in microseconds low register of the RTC
#define __PATMOS_RTC_TIME_LOW_ADDR (0xF0000308)

// Address to access the time in microseconds up register of the RTC
#define __PATMOS_RTC_TIME_UP_ADDR (0xF000030C)

// Address to access the interrupt interval register of the RTC
#define __PATMOS_RTC_INTERVAL_ADDR (0xF0000310)

// Address to access the ISR address register of the RTC
#define __PATMOS_RTC_ISR_ADDR (0xF0000314)

// Macro to read the RTC's cycle counter low register of the RTC
#define __PATMOS_RTC_RD_CYCLE_LOW(res) res = *((_iodev_ptr_t)__PATMOS_RTC_CYCLE_LOW_ADDR);

// Macro to read the RTC's cycle counter up register of the RTC
#define __PATMOS_RTC_RD_CYCLE_UP(res) res = *((_iodev_ptr_t)__PATMOS_RTC_CYCLE_UP_ADDR);

// Macro to read the RTC's time in microseconds low register of the RTC
#define __PATMOS_RTC_RD_TIME_LOW(res) res = *((_iodev_ptr_t)__PATMOS_RTC_TIME_LOW_ADDR);

// Macro to read the RTC's time in microseconds up register of the RTC
#define __PATMOS_RTC_RD_TIME_UP(res) res = *((_iodev_ptr_t)__PATMOS_RTC_TIME_UP_ADDR);

// Macro to write the RTC's cycle counter low register
#define __PATMOS_RTC_WR_CYCLE_LOW(val) *((_iodev_ptr_t)__PATMOS_RTC_CYCLE_LOW_ADDR) = val;

// Macro to write the RTC's cycle counter up register
#define __PATMOS_RTC_WR_CYCLE_UP(val) *((_iodev_ptr_t)__PATMOS_RTC_CYCLE_UP_ADDR) = val;

// Macro to write the RTC's interrupt interval register
#define __PATMOS_RTC_WR_INTERVAL(interval) *((_iodev_ptr_t)__PATMOS_RTC_INTERVAL_ADDR) = interval;

// Macro to write the RTC's ISR address register
#define __PATMOS_RTC_WR_ISR(address) *((_iodev_ptr_t)__PATMOS_RTC_ISR_ADDR) = address;

#endif /* __POK_PATMOS_RTC_H__ */