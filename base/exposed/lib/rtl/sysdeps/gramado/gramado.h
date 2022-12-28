
// gramado.h


// Process and threads priorities.

//
// Main priority sets
//

// class 1: Normal
#define PRIORITY_P1  1
#define PRIORITY_P2  2
#define PRIORITY_P3  3
// class 2: Real time
#define PRIORITY_P4  4
#define PRIORITY_P5  5
#define PRIORITY_P6  6

#define PRIORITY_BOOST  (PRIORITY_P6*3)

// Class 1: Normal
#define PRIORITY_LOW       PRIORITY_P1
#define PRIORITY_NORMAL    PRIORITY_P2
#define PRIORITY_HIGH      PRIORITY_P3
// Class 2: Real time
#define PRIORITY_LOW_RT       PRIORITY_P4
#define PRIORITY_NORMAL_RT    PRIORITY_P5
#define PRIORITY_HIGH_RT      PRIORITY_P6


// Class 1: Normal threashold
#define PRIORITY_THRESHOLD       PRIORITY_LOW
// Class 2: Real time threashold
#define PRIORITY_THRESHOLD_RT    PRIORITY_LOW_RT
// Class 1: Normal time critical
#define PRIORITY_TIME_CRITICAL       PRIORITY_HIGH
// Class 2: Real time time critical
#define PRIORITY_TIME_CRITICAL_RT    PRIORITY_HIGH_RT


// Class 1: Normal
#define PRIORITY_BATCH        PRIORITY_LOW
#define PRIORITY_INTERACTIVE  PRIORITY_NORMAL
#define PRIORITY_SYSTEM       PRIORITY_HIGH
// Class 1: Real time
#define PRIORITY_BATCH_RT        PRIORITY_LOW_RT
#define PRIORITY_INTERACTIVE_RT  PRIORITY_NORMAL_RT
#define PRIORITY_SYSTEM_RT       PRIORITY_HIGH_RT

#define PRIORITY_MIN       PRIORITY_P1
#define PRIORITY_MAX       (PRIORITY_P6 + PRIORITY_BOOST)

