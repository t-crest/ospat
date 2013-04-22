// Address to access the cycle counter low register of the RTC
#define __PATMOS_RTC_CYCLE_LOW_ADDR (0xF0000100)

// Address to access the cycle counter up register of the RTC
#define __PATMOS_RTC_CYCLE_UP_ADDR (0xF0000104)

// Address to access the time in microseconds low register of the RTC
#define __PATMOS_RTC_TIME_LOW_ADDR (0xF0000108)

// Address to access the time in microseconds up register of the RTC
#define __PATMOS_RTC_TIME_UP_ADDR (0xF000010C)

// Address to access the interrupt interval register of the RTC
#define __PATMOS_RTC_INTERVAL_ADDR (0xF0000110)

// Address to access the ISR address register of the RTC
#define __PATMOS_RTC_ISR_ADDR (0xF0000114)

// Macro to read the RTC's cycle counter low register of the RTC
#define __PATMOS_RTC_RD_CYCLE_LOW(res) asm volatile ("lwl %0 = [%1];;" : "=r" (res) : "r" (__PATMOS_RTC_CYCLE_LOW_ADDR));

// Macro to read the RTC's cycle counter up register of the RTC
#define __PATMOS_RTC_RD_CYCLE_UP(res) asm volatile ("lwl %0 = [%1];;" : "=r" (res) : "r" (__PATMOS_RTC_CYCLE_UP_ADDR));

// Macro to read the RTC's time in microseconds low register of the RTC
#define __PATMOS_RTC_RD_TIME_LOW(res) asm volatile ("lwl %0 = [%1];;" : "=r" (res) : "r" (__PATMOS_RTC_TIME_LOW_ADDR));

// Macro to read the RTC's time in microseconds up register of the RTC
#define __PATMOS_RTC_RD_TIME_UP(res) asm volatile ("lwl %0 = [%1];;" : "=r" (res) : "r" (__PATMOS_RTC_TIME_UP_ADDR));

// Macro to write the RTC's cycle counter low register
#define __PATMOS_RTC_WR_CYCLE_LOW(val) asm volatile ("swl [%0] = %1;;" : : "r" (__PATMOS_RTC_CYCLE_LOW_ADDR), "r" (val));

// Macro to write the RTC's cycle counter up register
#define __PATMOS_RTC_WR_CYCLE_UP(val) asm volatile ("swl [%0] = %1;;" : : "r" (__PATMOS_RTC_CYCLE_UP_ADDR), "r" (val));

// Macro to write the RTC's interrupt interval register
#define __PATMOS_RTC_WR_INTERVAL(interval) asm volatile ("swl [%0] = %1;;" : : "r" (__PATMOS_RTC_INTERVAL_ADDR), "r" (interval));

// Macro to write the RTC's ISR address register
#define __PATMOS_RTC_WR_ISR(address) asm volatile ("swl [%0] = %1;;" : : "r" (__PATMOS_RTC_ISR_ADDR), "r" (address));