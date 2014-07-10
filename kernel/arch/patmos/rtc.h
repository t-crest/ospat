#ifndef __POK_PATMOS_RTC_H__
#define __POK_PATMOS_RTC_H__

#define _IODEV __attribute__((address_space(1)))

typedef _IODEV unsigned int volatile * const _iodev_ptr_t;

/// linker symbol giving the base address of the timer device
extern char _timer_base;

/// linker symbol giving the base address of the exception unit
extern char _excunit_base;

// Address to access the cycle counter low register of the RTC
#define __PATMOS_RTC_CYCLE_UP_ADDR (&_timer_base+0x00)

// Address to access the cycle counter up register of the RTC
#define __PATMOS_RTC_CYCLE_LOW_ADDR (&_timer_base+0x04)

// Address to access the time in microseconds low register of the RTC
#define __PATMOS_RTC_TIME_UP_ADDR (&_timer_base+0x08)

// Address to access the time in microseconds up register of the RTC
#define __PATMOS_RTC_TIME_LOW_ADDR (&_timer_base+0x0c)

// Address to access the interrupt interval register of the RTC
#define __PATMOS_RTC_INTERVAL_ADDR (&_timer_base+0x10)

// Address to access the ISR address register of the RTC
#define __PATMOS_RTC_ISR_ADDR (&_timer_base+0x14)

// Address to access the exception unit
#define __PATMOS_RTC_EXCUNIT_ADDR (&_excunit_base)

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

// Macro to write the RTC's interrupt interval in microseconds low register
#define __PATMOS_RTC_WR_INTERVAL_TIME_LOW(interval) *((_iodev_ptr_t)__PATMOS_RTC_TIME_LOW_ADDR) = interval;

// Macro to write the RTC's interrupt interval in microseconds up register
#define __PATMOS_RTC_WR_INTERVAL_TIME_UP(interval) *((_iodev_ptr_t)__PATMOS_RTC_TIME_UP_ADDR) = interval;

// Read exception status register
#define __PATMOS_RTC_RD_EXC_STATUS(res) res = *((_iodev_ptr_t)__PATMOS_RTC_EXCUNIT_ADDR);

// Macro to write the RTC's ISR address register
#define __PATMOS_RTC_WR_ISR(address) *((_iodev_ptr_t)__PATMOS_RTC_ISR_ADDR) = address;

#endif /* __POK_PATMOS_RTC_H__ */
