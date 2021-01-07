/*
  config.h - config the keywords for Victron.DIRECT
*/
#define RXD1 15
#define TXD1 2
String Voltage, Current;
int Soc;
#define MPPT_75_10
//#define SmartShunt
// MPPT 75 | 10
#ifdef MPPT_75_10

	const byte buffsize = 32;
	const byte value_bytes = 33;
	const byte label_bytes = 9;
	const byte num_keywords = 19;


	char keywords[num_keywords][label_bytes] = {
	"PID",
	"FWE",
	"SER#",
	"V",
	"I",
	"VPV",
	"PPV",
	"CS",
	"ERR",
	"LOAD",
	"IL",
	"H19",
	"H20",
	"H21",
	"H22",
	"H23",
	"HSDS",
	"BMV",
  "SOC"
//  "Checksum"
	};
	#define PID 0
	#define FWE 1
	#define SER 2	// Offically SER# but # does not play that well as macro
	#define V 3     // ScV
	#define I 4     // ScI
	#define VPV 5   // PVV
	#define PPV 6   // PVI = PVV / VPV
	#define CS 7    // ScS
	#define ERR 8   // ScERR
	#define LOAD 9  // SLs
	#define IL 10   // SLI
	#define H19 11
	#define H20 12
	#define H21 13
	#define H22 14
	#define H23 15
	#define HSDS 16
  #define BMV 17
  #define SOC 18
//	#define CHECKSUM 19
#endif

// MPPT 100 | 20
#ifdef MPPT_100_20

	const byte buffsize = 32;
	const byte value_bytes = 33;
	const byte label_bytes = 9;
	const byte num_keywords = 20;

	char keywords[num_keywords][label_bytes] = {
	"PID",
	"FW",
	"SER#",
	"V",
	"I",
	"VPV",
	"PPV",
	"CS",
	"MPPT",
	"OR",
	"ERR",
	"LOAD",
	"IL",
	"H19",
	"H20",
	"H21",
	"H22",
	"H23",
	"HSDS",
	"Checksum"
	};
	#define PID 0
	#define FW 1
	#define SER 2
	#define V 3
	#define I 4
	#define VPV 5
	#define PPV 6
	#define MPPT 7
	#define OR 8
	#define CS 9
	#define ERR 10
	#define LOAD 11
	#define IL 12
	#define H19 13
	#define H20 14
	#define H21 15
	#define H22 16
	#define H23 17
	#define HSDS 18
	#define CHECKSUM 19
#endif

#ifdef SmartShunt

  const byte buffsize = 32;
  const byte value_bytes = 33;
  const byte label_bytes = 9;
  const byte num_keywords = 8;

  char keywords[num_keywords][label_bytes] = {
  "PID",
  "FW",
  "V",
  "I",
  "CS",
  "LOAD",
  "BMV",
  "SOC"
  };
  #define PID 0
  #define FW 1
  #define V 2     // ScV
  #define I 3     // ScI
  #define CS 4    // ScS
  #define LOAD 5  // SLs
  #define BMV 6
  #define SOC 7
//  #define CHECKSUM 19
#endif
