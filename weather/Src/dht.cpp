#include "dht.h"
#include "us_timing.h"
#include <stdio.h>
#include <assert.h>

 DHTsensor::DHTsensor(DHTxx_types type,GPIO_TypeDef *port, uint16_t  pin){
	 dhtType = type;
	 data_pin = pin;
	 data_port = port;
	 last_read_time = 0;
	 for(int i = 0; i<buf_size(); ++i){
	 		buf[i] = 0;
	 }
	 if(type == DHT11){
		 ZERO_LENGTH = 30;
		 ONE_LENGTH = 70;
		 MIN_MEASURES_PAUSE = 1000;
		 FIRST_MEASURES_PAUSE = 1000;
		 START_LENGTH = 20000;
	 }else if(type ==  DHT22){
		 ZERO_LENGTH = 30;
		 ONE_LENGTH = 70;
		 MIN_MEASURES_PAUSE = 2000;
		 FIRST_MEASURES_PAUSE = 2000;
		 START_LENGTH = 600;
	 }else if(type == DHT21){
		 ZERO_LENGTH = 30;
		 ONE_LENGTH = 70;
		 MIN_MEASURES_PAUSE = 2000;
		 FIRST_MEASURES_PAUSE = 2000;
		 START_LENGTH = 600;
	 }
 }



 int DHTsensor:: buf_size()
 {
 	return sizeof(buf)/sizeof(buf[0]);
 }


 int DHTsensor::read_pulse(){
	 us_reset_counter();
	 	 while(HAL_GPIO_ReadPin(data_port, data_pin) == GPIO_PIN_RESET &&
	 			 get_us() < global_timeout_us ){}
	 	uint16_t before = get_us();
	 	if(before > global_timeout_us)
	 	{
	 #ifdef STDIO_DEBUG
	 		printf("before: %d\n", before);
	 #endif
	 		return -1;
	 	}
	 	while(HAL_GPIO_ReadPin(data_port, data_pin) == GPIO_PIN_SET &&
	 			 get_us() < global_timeout_us ){}
	 	uint16_t after = get_us();
	 	if(after > global_timeout_us)
	 	{
	 #ifdef STDIO_DEBUG
	 		printf("before: %d\n", before);
	 		printf("after: %d\n", after);
	 #endif
	 		return -1;
	 	}
	 	return after-before;
 }

 int8_t  DHTsensor::read_bit(int *pulse_length)
 {
 	int res = read_pulse();
 	if(pulse_length)
 		*pulse_length = res;

 	if(res == -1)
 		return -1;

 	assert(ZERO_LENGTH &&
 			"Code expects 0 bit pulse width to be the same");
 	assert(ONE_LENGTH &&
 			"Code expects 1 bit pulse width to be the same");
 	if( res > 0 && res < ZERO_LENGTH )
 		return 0;
 	else
 		return 1;
 }

 int DHTsensor::ms_before_first_read(){
	 return FIRST_MEASURES_PAUSE;
 }

 int DHTsensor::ms_before_next_read(){
	 return HAL_GetTick() - last_read_time;
 }
 inline int DHTsensor::get_min_measures_pause(){

	 return MIN_MEASURES_PAUSE;
 }

 inline int DHTsensor::get_start_signal_length(){
	 return START_LENGTH;
 }
 DHTxx_errors DHTsensor::read_raw_DHTxx(int force){



	 if(last_read_time - HAL_GetTick() < get_min_measures_pause()
	 				&& !force){
		 if(last_read_time==0)
			 HAL_Delay(ms_before_first_read());
	 	 return DHTXX_OK;
	 }

	 	int start_time = get_start_signal_length();
	 	if(start_time < 0 )
	 		return DHTXX_UNKNOWN_DEVICE;


	 	_pinConroller.setPinToMode(data_port, data_pin, OUTPUT);
	 	HAL_GPIO_WritePin(data_port,data_pin, GPIO_PIN_SET);
	    // Get ready
	 	udelay(250);
	 	// More or less arbitrary
	 	HAL_GPIO_WritePin(data_port, data_pin, GPIO_PIN_RESET);
	 	udelay(start_time);
	 	HAL_GPIO_WritePin(data_port,data_pin, GPIO_PIN_SET);

	 	udelay(5);              // Part of necessary time.
	 	_pinConroller.setPinToMode(data_port, data_pin, INPUT);

	 	uint16_t dt[42];
	 	int8_t res;

	 #ifdef STDIO_DEBUG
	 	int dtl[42];
	 	int idx_dtl = 0;
	 	res =  read_bit(conf, dtl + idx_dtl++); // Wait for line to go up
	     //start reading
	 	res =  read_bit(conf, dtl + idx_dtl++); // Read acknowledge from DHT
	 #else
	 	//! Wait for line to go up -- not a bit
	 	res = read_bit(0);
	 	if(res == -1)
	 		return DHTXX_NO_CONN;
	 	//! Not really a bit -- just acknowledge
	 	res = read_bit(0);
	 #endif
	 	if(res == -1)
	 		return DHTXX_NO_CONN;
	 	for(int i = 0 ; i<40; i++){
	 #ifdef STDIO_DEBUG
	 		res =  read_bit(conf, dtl + idx_dtl++);
	 #else
	 		res =  read_bit(0);
	 #endif
	 		if(res == -1)
	 			return DHTXX_NO_CONN;
	 		dt[i] = res;
	 	}

	 #ifdef STDIO_DEBUG
	  	for(int i = 0; i<42; ++i)
	 	{
	 		if(i>0 && i%8 == 0)
	 			printf(" ");
	 		printf("%01x", dt[i]);
	 	}
	  	printf("\n");
	 #endif

	 	//convert data
	  	for(int i = 0; i<buf_size(); i++){
	  		buf[i] = 0;
	  		for(int j = 0; j<8; j++){
	  			buf[i] <<= 1;
	  			buf[i] |= dt[i*8+j];
	  		}
	  	}

	 	//calculate checksum
	 	uint8_t check_sum = 0;
	 	for(int i = 0; i<4; i++){
	 		check_sum += *(buf+i);
	 	}

	 #ifdef STDIO_DEBUG
	  	for(int i = 0; i<5; ++i)
	 	{
	 		printf("%02x ", *(conf->buf+i));
	 	}
	 	printf("%02x\n", check_sum);

	 	printf("%2d | ", dtl[0]);
	 	printf("%2d | ", dtl[1]);
	  	for(int i = 0; i<40; ++i)
	 	{
	 		if(i>0 && i%8 == 0)
	 			printf(" | ");
	 		printf("%2d ", dtl[i+2]);
	 	}
	  	printf("\n");
	 #endif
	 	if (buf[4] != check_sum )
	 		return DHTXX_CS_ERROR;

	 	last_read_time = HAL_GetTick();
	 	return DHTXX_OK;
 }

 int DHTsensor::get_temperature_DHTxx(){

	 uint16_t data;
	 	switch(dhtType)
	 	{
	 	case DHT11:
	 		return 10 * buf[2];
	 		break;
	 	case DHT22:
	 	case DHT21:
	 		// Clear sign for shift
	 		data = ( (buf[2] & 0x7F) << 8 ) + buf[3];
	 		return (buf[2] & 0x80) ? -data : data;
	 		break;
	 	default:
	 		return -1;
	 	}

 }
 int DHTsensor::get_humidity_DHTxx(){

	 switch(dhtType)
	 	{
	 	case DHT11:
	 		return 10 * buf[0];
	 		break;
	 	case DHT22:
	 	case DHT21:
	 		return (buf[0] << 8) + buf[1];
	 		break;
	 	default:
	 		return -1;
	 	}
 }
 double DHTsensor::fget_temperature_DHTxx(){
	    int r = get_temperature_DHTxx();
	 	return (double)r/10;
 }
 double DHTsensor::fget_humidity_DHTxx(){
 	    int r = get_humidity_DHTxx();
 	 	return (double)r/10;
  }





