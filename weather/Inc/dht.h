
#include "gpio.h"
#include "pinController.h"
#define global_timeout_us 1000
#define WEAK_SYMBOL  __attribute__((weak))


typedef enum {DHT_Unknown = 0, DHT11 = 1, DHT22 = 2, DHT21 = 3} DHTxx_types;
typedef enum {DHTXX_OK = 0, DHTXX_NO_CONN = 1, DHTXX_CS_ERROR = 2,
			  DHTXX_TIMEOUT = 0x30,
			  DHTXX_UNKNOWN_DEVICE = 0x40,
			}
DHTxx_errors;

class DHTsensor{

private:

	   int ZERO_LENGTH;
	   int ONE_LENGTH;
	   int MIN_MEASURES_PAUSE;
	   int FIRST_MEASURES_PAUSE;
	   int START_LENGTH;
	   PinController _pinConroller;


	    uint32_t 	  last_read_time; // Time from last physical read
		DHTxx_types   dhtType;
		//DHTxx_errors  last_error;
		GPIO_TypeDef *data_port;
		uint16_t 	  data_pin;
		uint8_t 	  buf[5];
		int ms_before_first_read();
		int ms_before_next_read();
		int buf_size();
	    int read_pulse();
	    int8_t read_bit(int *pulse_length);
	    inline int get_min_measures_pause();
	    inline int get_start_signal_length();
		inline double fget_temperature_DHTxx();
		inline double fget_humidity_DHTxx();



public:
		DHTsensor(DHTxx_types type, GPIO_TypeDef *port, uint16_t  pin);
		DHTxx_errors read_raw_DHTxx(int force);
		int get_temperature_DHTxx();
		int get_humidity_DHTxx();

};

