#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>     // Arduino compiler can get confused if you don't include include all required headers in this file?!?
#include <ADC.h>

#include "CompileSwitches.h"
#include "AudioFreezeEffect.h"
#include "AudioFreezeInterface.h"
#include "Util.h"

#define MIX_FREEZE_CHANNEL    0
#define MIX_ORIGINAL_CHANNEL  1

// wrap in a struct to ensure initialisation order
struct IO
{
  ADC                         adc;
  AudioInputAnalog            audio_input;
  AudioOutputAnalog           audio_output;

  IO() :
    adc(),
    audio_input(A0),
    audio_output()
  {
  }
};

IO io;

AUDIO_FREEZE_EFFECT      audio_freeze_effect;
AudioMixer4              audio_mixer;

AudioConnection          patch_cord_L1( io.audio_input, 0, audio_freeze_effect, 0 );
AudioConnection          patch_cord_L2( audio_freeze_effect, 0, audio_mixer, MIX_FREEZE_CHANNEL );
AudioConnection          patch_cord_L3( io.audio_input, 0, audio_mixer, MIX_ORIGINAL_CHANNEL );
AudioConnection          patch_cord_L4( audio_mixer, 0, io.audio_output, 0 );
//AudioConnection          patch_cord_L1( audio_input, 0, io.audio_output, 0 );    // left channel passes straight through (for testing)
//AudioConnection          patch_cord_R1( io.audio_input, 1, io.audio_output, 1 );      // right channel passes straight through

AUDIO_FREEZE_INTERFACE   audio_freeze_interface;

//////////////////////////////////////

void set_adc1_to_3v3()
{
  ADC1_SC3 = 0; // cancel calibration
  ADC1_SC2 = ADC_SC2_REFSEL(0); // vcc/ext ref 3.3v

  ADC1_SC3 = ADC_SC3_CAL;  // begin calibration

  uint16_t sum;

  //serial_print("wait_for_cal\n");

  while( (ADC1_SC3 & ADC_SC3_CAL))
  {
    // wait
  }

  __disable_irq();

    sum = ADC1_CLPS + ADC1_CLP4 + ADC1_CLP3 + ADC1_CLP2 + ADC1_CLP1 + ADC1_CLP0;
    sum = (sum / 2) | 0x8000;
    ADC1_PG = sum;
    sum = ADC1_CLMS + ADC1_CLM4 + ADC1_CLM3 + ADC1_CLM2 + ADC1_CLM1 + ADC1_CLM0;
    sum = (sum / 2) | 0x8000;
    ADC1_MG = sum;

  __enable_irq();
  
}

void setup()
{
  DEBUG_OUTPUT("Setup BEGIN\n");
  
  Serial.begin(9600);

  set_adc1_to_3v3();

  serial_port_initialised = true;

  AudioMemory(12);

  audio_freeze_interface.setup();

  //audio_freeze_effect.set_wow_frequency_range( 1.25f, 3.85f );
  //audio_freeze_effect.set_flutter_frequency_range( 14.0f, 25.0f );

  delay(500);
  
  DEBUG_OUTPUT("Setup END\n");
}

void loop()
{ 
  audio_freeze_interface.update( io.adc );

  if( audio_freeze_interface.freeze_button().active() != audio_freeze_effect.is_freeze_active() )
  {
    audio_freeze_effect.set_freeze( audio_freeze_interface.freeze_button().active() );
  }

  if( audio_freeze_interface.freeze_button().active() )
  {
    const float mix = audio_freeze_interface.mix_dial().value();
    audio_mixer.gain( MIX_FREEZE_CHANNEL, mix );
    audio_mixer.gain( MIX_ORIGINAL_CHANNEL, 1.0f - mix );
  }
  else
  {
    audio_mixer.gain( MIX_FREEZE_CHANNEL,0.0f );
    audio_mixer.gain( MIX_ORIGINAL_CHANNEL, 1.0f );
  }

  if( audio_freeze_interface.mode() == 1 )
  {
    audio_freeze_effect.set_reverse( true );
  }
  else
  {
    audio_freeze_effect.set_reverse( false );
  }

  const float max_wow( 1.0f );
  const float max_flutter( 0.65f );
  audio_freeze_effect.set_wow_amount( audio_freeze_interface.wow_dial().value() * max_wow ); 
  audio_freeze_effect.set_flutter_amount( audio_freeze_interface.flutter_dial().value() * max_flutter ); 

  audio_freeze_effect.set_length( audio_freeze_interface.length_dial().value() );
  audio_freeze_effect.set_centre( audio_freeze_interface.position_dial().value() );
  audio_freeze_effect.set_speed( audio_freeze_interface.speed_dial().value(), audio_freeze_interface.alt_func() );

#ifdef DEBUG_OUTPUT
  const int processor_usage = AudioProcessorUsage();
  if( processor_usage > 30 )
  {
    Serial.print( "Performance spike: " );
    Serial.print( processor_usage );
    Serial.print( "\n" );
  }
#endif
}




