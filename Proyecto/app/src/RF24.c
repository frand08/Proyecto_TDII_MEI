
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI_RF.h"

/****************************************************************************/

/****************************************************************************/

/****************************************************************************/

  inline void beginTransaction()
  {
	  Chip_GPIO_SetPinOutLow(LPC_GPIO,TOUCH_E);
  }

/****************************************************************************/

  inline void endTransaction()
  {
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO,TOUCH_E);
  }

/****************************************************************************/

uint8_t read_register(uint8_t reg, uint8_t* buf, uint8_t len)
{
  uint8_t status;

  beginTransaction();
  status = SPI_ReadWrite( R_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- ){
    *buf++ = SPI_ReadWrite(0xff);
  }
  endTransaction();

  return status;
}

/****************************************************************************/

uint8_t read_register_byte(uint8_t reg)
{
  uint8_t result;

  beginTransaction();
  SPI_ReadWrite( R_REGISTER | ( REGISTER_MASK & reg ) );
  result = SPI_ReadWrite(0xff);
  endTransaction();

  return result;
}

/****************************************************************************/

uint8_t write_register(uint8_t reg, const uint8_t* buf, uint8_t len)
{
  uint8_t status;

  beginTransaction();
  status = SPI_ReadWrite( W_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len )
  {
    SPI_ReadWrite(*buf);
    buf++;
    len--;
  }
    endTransaction();

  return status;
}

/****************************************************************************/

uint8_t write_register_byte(uint8_t reg, uint8_t value)
{
  uint8_t status;

  beginTransaction();
  status = SPI_ReadWrite( W_REGISTER | ( REGISTER_MASK & reg ) );
  SPI_ReadWrite(value);
  endTransaction();

  return status;
}

/****************************************************************************/

uint8_t write_payload(const void* buf, uint8_t data_len, const uint8_t writeType)
{
  uint8_t status;
  const uint8_t* current = buf;

   data_len = rf24_min(data_len, payload_size);
   uint8_t blank_len = dynamic_payloads_enabled ? 0 : (payload_size - data_len);

  beginTransaction();
  status = SPI_ReadWrite( writeType );
  while ( data_len-- ) {
    SPI_ReadWrite(*current++);
  }
  while ( blank_len-- ) {
    SPI_ReadWrite(0);
  }
  endTransaction();


  return status;
}

/****************************************************************************/

uint8_t read_payload(void* buf, uint8_t data_len)
{
  uint8_t status;
  uint8_t* current = buf;
  uint8_t blank_len =0;

  if(data_len > payload_size) data_len = payload_size;
  if(dynamic_payloads_enabled)
	  blank_len = payload_size - data_len;
  else
	  blank_len =0;

  beginTransaction();
  status = SPI_ReadWrite( R_RX_PAYLOAD );
  while ( data_len ) {
    *current = SPI_ReadWrite(0xFF);
    current++;
    data_len--;
  }
  while ( blank_len ) {
    SPI_ReadWrite(0xff);
    blank_len--;
  }
  endTransaction();

  return status;
}

/****************************************************************************/

uint8_t flush_rx(void)
{
  return spiTrans( FLUSH_RX );
}

/****************************************************************************/

uint8_t flush_tx(void)
{
  return spiTrans( FLUSH_TX );
}

/****************************************************************************/

uint8_t spiTrans(uint8_t cmd){

  uint8_t status;

  beginTransaction();
  status = SPI_ReadWrite( cmd );
  endTransaction();

  return status;
}

/****************************************************************************/

uint8_t get_status(void)
{
  return spiTrans(NOP);
}

/****************************************************************************/

void RF24(void)
{
	  p_variant = false;
	  payload_size = 32; dynamic_payloads_enabled = false; addr_width = 5;//,pipe0_reading_address(0)
  pipe0_reading_address[0]=0;
}

/****************************************************************************/

void setChannel(uint8_t channel)
{
  const uint8_t max_channel = 127;
  write_register_byte(RF_CH,rf24_min(channel,max_channel));
}

uint8_t getChannel()
{
  return read_register_byte(RF_CH);
}
/****************************************************************************/

void setPayloadSize(uint8_t size)
{
  payload_size = rf24_min(size,32);
}

/****************************************************************************/

uint8_t getPayloadSize(void)
{
  return payload_size;
}

/****************************************************************************/

void begin(void)
{
	uint8_t i=0xFF;
	Chip_GPIO_SetPinOutLow(LPC_GPIO, CE_PIN); //Puerto CE
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,TOUCH_E);

  // Must allow the radio time to settle else configuration bits will not necessarily stick.
  // This is actually only required following power up but some settling time also appears to
  // be required after resets too. For full coverage, we'll always assume the worst.
  // Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
  // Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
  // WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
  //delay( 5 ) ;

  // Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
  // WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
  // sizes must never be used. See documentation for a more complete explanation.
  write_register_byte(SETUP_RETR,(0X40 | 0x0F));

  // Restore our default PA level
  setPALevel( RF24_PA_MIN ) ;

  // Determine if this is a p or non-p RF24 module and then
  // reset our data rate back to default value. This works
  // because a non-P variant won't allow the data rate to
  // be set to 250Kbps.
  //if( setDataRate( RF24_250KBPS ) )
  //{
  //  p_variant = true ;
  //}

  // Then set the data rate to the slowest (and most reliable) speed supported by all
  // hardware.
  setDataRate( RF24_1MBPS ) ;

  // Initialize CRC and request 2-byte (16bit) CRC
  setCRCLength( RF24_CRC_16 ) ;

  // Disable dynamic payloads, to match dynamic_payloads_enabled setting
  write_register_byte(DYNPD,0);



  // Set up default configuration.  Callers can always change it later.
  // This channel should be universally safe and not bleed over into adjacent
  // spectrum.
  setChannel(76);

  SPI_ReadWrite(ACTIVATE);
  	SPI_ReadWrite(0x73);
  	Chip_GPIO_SetPinOutHigh(LPC_GPIO, TOUCH_E);


  	powerUp();
  		for(i=0xFF;i>0;i--);
  		for(i=0xFF;i>0;i--);
  // Flush buffers
  flush_rx();
  flush_tx();

  	// Reset current status
  	  // Notice reset and flush is the last thing we do
  	  write_register_byte(NRF_STATUS, RX_DR | TX_DS | MAX_RT );
  addr_width=5;
  p_variant = false;
  payload_size = 4;
  	  dynamic_payloads_enabled = false;
    pipe0_reading_address[0]=0;
}


/****************************************************************************/

void startListening(void)
{

  write_register_byte(CONFIG, read_register_byte(CONFIG) | PRIM_RX);
  write_register_byte(NRF_STATUS, RX_DR | TX_DS | MAX_RT );
  Chip_GPIO_SetPinOutHigh(LPC_GPIO,CE_PIN);
  // Restore the pipe0 adddress, if exists
  //if (pipe0_reading_address[0] > 0)
  //  write_register(RX_ADDR_P0, pipe0_reading_address, addr_width);


  // Flush buffers
  flush_rx();
  //if(read_register_byte(FEATURE) & EN_ACK_PAY)
	//flush_tx();

  // Go!
  //delayMicroseconds(100);
}

/****************************************************************************/


void stopListening(void)
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO, CE_PIN); //Puerto CE
  flush_tx();
  flush_rx();
}

/****************************************************************************/

void powerDown(void)
{
  Chip_GPIO_SetPinOutLow(LPC_GPIO,CE_PIN); // Guarantee CE is low on powerDown
  write_register_byte(CONFIG,read_register_byte(CONFIG) & ~PWR_UP);
}

/****************************************************************************/

//Power up now. Radio will not power down unless instructed by MCU for config changes etc.
void powerUp(void)
{
   uint8_t cfg = read_register_byte(CONFIG);

   // if not powered up then power up and wait for the radio to initialize
   if (!(cfg & PWR_UP)){
      write_register_byte(CONFIG,read_register_byte(CONFIG) | PWR_UP);

      // For nRF24L01+ to go from power down mode to TX or RX mode it must first pass through stand-by mode.
	  // There must be a delay of Tpd2stby (see Table 16.) after the nRF24L01+ leaves power down mode before
	  // the CEis set high. - Tpd2stby can be up to 5ms per the 1.0 datasheet
      //delay(5);
   }
}

/******************************************************************/


/****************************************************************************/


/****************************************************************************/

/*
bool txStandBy(){
	while( ! (read_register_byte(FIFO_STATUS) & TX_EMPTY)) ){
		if( get_status() & MAX_RT)){
			write_register_byte(NRF_STATUS,MAX_RT) );
			Chip_GPIO_SetPinOutLow(LPC_GPIO,CE_PIN);
			flush_tx();    //Non blocking, flush the data
			return 0;
		}
	}

	Chip_GPIO_SetPinOutLow(LPC_GPIO,CE_PIN);			   //Set STANDBY-I mode
	return 1;
}
*/
/****************************************************************************/
/*
bool txStandBy_time(uint32_t timeout, bool startTx){

    if(startTx){
	  stopListening();
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO,CE_PIN);
	}
	uint32_t start = millis();

	while( ! (read_register_byte(FIFO_STATUS) & TX_EMPTY)) ){
		if( get_status() & MAX_RT)){
			write_register_byte(NRF_STATUS,MAX_RT) );
				Chip_GPIO_SetPinOutLow(LPC_GPIO,CE_PIN);										  //Set re-transmit
				Chip_GPIO_SetPinOutHigh(LPC_GPIO,CE_PIN);
				if(millis() - start >= timeout){
					Chip_GPIO_SetPinOutLow(LPC_GPIO,CE_PIN); flush_tx(); return 0;
				}
		}
	}

	Chip_GPIO_SetPinOutLow(LPC_GPIO,CE_PIN);				   //Set STANDBY-I mode
	return 1;

}
*/
/****************************************************************************/

/****************************************************************************/


/****************************************************************************/

bool available(void)
{
  return available_pipe(NULL);
}

/****************************************************************************/

bool available_pipe(uint8_t* pipe_num)
{
  if (!( read_register_byte(FIFO_STATUS) & RX_EMPTY ))
  {

    // If the caller wants the pipe number, include that
    if ( pipe_num ){
	  uint8_t status = get_status();
      *pipe_num = ( status >> RX_P_NO ) & 0b111;
  	}
  	return 1;
  }

  return 0;
}

/****************************************************************************/

void read( void* buf, uint8_t len ){

  // Fetch the payload
  read_payload( buf, len );

  //Clear the two possible interrupt flags with one command
  write_register_byte(NRF_STATUS,RX_DR | MAX_RT | TX_DS );

}


/****************************************************************************/

void openWritingPipe(uint8_t *value)
{
  // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
  // expects it LSB first too, so we're good.

  write_register(RX_ADDR_P0, value, addr_width);
  write_register(TX_ADDR, value, addr_width);


  //const uint8_t max_payload_size = 32;
  //write_register(RX_PW_P0,rf24_min(payload_size,max_payload_size));
  write_register_byte(RX_PW_P0,payload_size);
}

/****************************************************************************/


void openReadingPipe(uint8_t child, uint8_t *address)
{
  // If this is pipe 0, cache the address.  This is needed because
  // openWritingPipe() will overwrite the pipe 0 address, so
  // startListening() will have to restore it.


  if (child <= 6)
  {
    // For pipes 2-5, only write the LSB
    if ( child == 1 )
      write_register(child_pipe[child], address, addr_width);
    else
      write_register(child_pipe[child], address, 1);

    write_register_byte(child_payload_size[child],payload_size);

    // Note it would be more efficient to set all of the bits for all open
    // pipes at once.  However, I thought it would make the calling code
    // more simple to do it this way.
    write_register_byte(EN_RXADDR,read_register_byte(EN_RXADDR) | child_pipe_enable[child]);
  }
}

/****************************************************************************/
void setAddressWidth(uint8_t a_width){

	if(a_width -= 2){
		write_register_byte(SETUP_AW,a_width%4);
		addr_width = (a_width%4) + 2;
	}
}

/****************************************************************************/



/****************************************************************************/



/****************************************************************************/

void toggle_features(void)
{
    beginTransaction();
	SPI_ReadWrite( ACTIVATE );
    SPI_ReadWrite( 0x73 );
	endTransaction();
}

/****************************************************************************/

void enableDynamicPayloads(void)
{
  // Enable dynamic payload throughout the system

    //toggle_features();
    write_register_byte(FEATURE,read_register_byte(FEATURE) | EN_DPL );

  // Enable dynamic payload on all pipes
  //
  // Not sure the use case of only having dynamic payload on certain
  // pipes, so the library does not support it.
  write_register_byte(DYNPD,read_register_byte(DYNPD) | DPL_P5 | DPL_P4 | DPL_P3 | DPL_P2 | DPL_P1 | DPL_P0);

  dynamic_payloads_enabled = true;
}

/****************************************************************************/

void enableAckPayload(void)
{
  //
  // enable ack payload and dynamic payload features
  //

    //toggle_features();
    write_register_byte(FEATURE,read_register_byte(FEATURE) | EN_ACK_PAY | EN_DPL );



  //
  // Enable dynamic payload on pipes 0 & 1
  //

  write_register_byte(DYNPD,read_register_byte(DYNPD) | DPL_P1 | DPL_P0);
  dynamic_payloads_enabled = true;
}

/****************************************************************************/

void enableDynamicAck(void){
  //
  // enable dynamic ack features
  //
    //toggle_features();
    write_register_byte(FEATURE,read_register_byte(FEATURE) | EN_DYN_ACK );
}

/****************************************************************************/

void writeAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
  const uint8_t* current = buf;

  uint8_t data_len = rf24_min(len,32);

  beginTransaction();
  SPI_ReadWrite(W_ACK_PAYLOAD | ( pipe & 0b111 ) );

  while ( data_len-- )
    SPI_ReadWrite(*current++);
  endTransaction();
}

/****************************************************************************/


/****************************************************************************/

void setAutoAck(bool enable)
{
  if ( enable )
    write_register_byte(EN_AA, 0b111111);
  else
    write_register_byte(EN_AA, 0);
}

/****************************************************************************/

void setAutoAck_pipe( uint8_t pipe, bool enable )
{
  if ( pipe <= 6 )
  {
    uint8_t en_aa = read_register_byte( EN_AA ) ;
    if( enable )
    {
      en_aa |= pipe ;
    }
    else
    {
      en_aa &= ~pipe ;
    }
    write_register_byte( EN_AA, en_aa ) ;
  }
}

/****************************************************************************/

bool testCarrier(void)
{
  return ( read_register_byte(CD) & 1 );
}

/****************************************************************************/

bool testRPD(void)
{
  return ( read_register_byte(RPD) & 1 ) ;
}

/****************************************************************************/

void setPALevel(uint8_t level)
{
	  uint8_t setup = read_register_byte(RF_SETUP) ;
	  setup &= ~(RF_PWR_LOW | RF_PWR_HIGH) ;

	  // switch uses RAM (evil!)
	  if ( level == RF24_PA_MAX )
	  {
	    setup |= (RF_PWR_LOW | RF_PWR_HIGH) ;
	  }
	  else if ( level == RF24_PA_HIGH )
	  {
	    setup |= RF_PWR_HIGH ;
	  }
	  else if ( level == RF24_PA_LOW )
	  {
	    setup |= RF_PWR_LOW;
	  }
	  else if ( level == RF24_PA_MIN )
	  {
	    // nothing
	  }
	  else if ( level == RF24_PA_ERROR )
	  {
	    // On error, go to maximum PA
	    setup |= (RF_PWR_LOW | RF_PWR_HIGH) ;
	  }

	  write_register_byte( RF_SETUP, setup ) ;
}

/****************************************************************************/

uint8_t getPALevel(void)
{

  return (read_register_byte(RF_SETUP) & (RF_PWR_LOW | RF_PWR_HIGH)) >> 1 ;
}

/****************************************************************************/
bool setDataRate(rf24_datarate_e speed)
{
  bool result = false;
  uint8_t setup = read_register_byte(RF_SETUP) ;

  setup &= ~(RF_DR) ;

    // Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
    // Making it '01'
    if ( speed == RF24_2MBPS )
    {
      //wide_band = true ;
      setup |= RF_DR;
    }

  write_register_byte(RF_SETUP,setup);

  // Verify our result
  if ( read_register_byte(RF_SETUP) == setup )
    result = true;


  return result;
}
/****************************************************************************/

rf24_datarate_e getDataRate( void )
{
  rf24_datarate_e result ;
  uint8_t dr = read_register_byte(RF_SETUP) & (RF_DR);

   if ( dr  )
  {
    // '01' = 2MBPS
    result = RF24_2MBPS ;
  }
  else
  {
    // '00' = 1MBPS
    result = RF24_1MBPS ;
  }
  return result ;
}

/****************************************************************************/

void setCRCLength(rf24_crclength_e length)
{
  uint8_t config = read_register_byte(CONFIG) & ~( CRCO | EN_CRC) ;

  // switch uses RAM (evil!)
  if ( length == RF24_CRC_DISABLED )
  {
    // Do nothing, we turned it off above.
  }
  else if ( length == RF24_CRC_8 )
  {
    config |= EN_CRC;
  }
  else
  {
    config |= EN_CRC;
    config |= CRCO;
  }
  write_register_byte( CONFIG, config ) ;
}

/****************************************************************************/

rf24_crclength_e getCRCLength(void)
{
  rf24_crclength_e result = RF24_CRC_DISABLED;

  uint8_t config = read_register_byte(CONFIG) & ( CRCO | EN_CRC) ;
  uint8_t AA = read_register_byte(EN_AA);

  if ( config & EN_CRC  || AA)
  {
    if ( config & CRCO )
      result = RF24_CRC_16;
    else
      result = RF24_CRC_8;
  }

  return result;
}

/****************************************************************************/

void disableCRC( void )
{
	  uint8_t disable = (read_register_byte(CONFIG) & ~EN_CRC) ;
	  write_register_byte( CONFIG, disable );

}



