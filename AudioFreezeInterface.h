#pragma once

#include "Interface.h"

class AUDIO_FREEZE_INTERFACE
{
  static const int      LENGTH_DIAL_PIN                 = A20;
  static const int      POSITION_DIAL_PIN               = A19;
  static const int      SPEED_DIAL_PIN                  = A18;
  static const int      WOW_DIAL_PIN                    = A17;
  static const int      FLUTTER_DIAL_PIN                = A16;
  static const int      MIX_DIAL_PIN                    = A13;
  static const int      FREEZE_BUTTON_PIN               = 1;
  static const int      MODE_BUTTON_PIN                 = 2;
  static const int      LED_1_PIN                       = 29;
  static const int      LED_2_PIN                       = 11;
  static const int      LED_3_PIN                       = 7;

  static const bool     FREEZE_BUTTON_IS_TOGGLE         = true;
  static const int      NUM_LEDS                        = 3;
  static const int      NUM_MODES                       = 2;

  static const int32_t  ALT_FUNC_BUTTON_HOLD_TIME_MS   = 2000;
  
  DIAL              m_length_dial;
  DIAL              m_position_dial;
  DIAL              m_speed_dial;
  DIAL              m_wow_dial;
  DIAL              m_flutter_dial;
  DIAL              m_mix_dial;

  BUTTON            m_freeze_button;
  BUTTON            m_mode_button;
  
  LED               m_leds[NUM_LEDS];

  int               m_current_mode;
  bool              m_change_alt_func_valid;
  bool              m_alt_func;

public:

  AUDIO_FREEZE_INTERFACE();

  void          setup();
  void          update( ADC& adc );

  const DIAL&   length_dial() const;
  const DIAL&   position_dial() const;
  const DIAL&   speed_dial() const;
  const DIAL&   wow_dial() const;
  const DIAL&   flutter_dial() const;
  const DIAL&   mix_dial() const;
  const BUTTON& freeze_button() const;

  int           mode() const;
  bool          alt_func() const;
};

