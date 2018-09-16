#include <Arduino.h>
#include <MIDI.h>

#include "AmpController.hh"

// map the pins of DIN connector to I/O pins
constexpr uint8_t DIN3 = A2;  // channel select
constexpr uint8_t DIN4 = DD4; // mute switch
constexpr uint8_t DIN5 = DD5; // solo switch
constexpr uint8_t DIN7 = DD7; // loop switch

// map MIDI control messages to amp controls
constexpr uint8_t MUTE = 0x01;
constexpr uint8_t LOOP = 0x02;
constexpr uint8_t SOLO = 0x03;

// configure MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

// define the pin and voltages for amp controller
AmpControllerConfig ampConfig {
    DIN7, // loop pin
    DIN4, // mute pin
    DIN5, // solo pin
    { DD2, DD3, 8 } // ch 1, 2, 3 pins
};

AmpController ampController{ampConfig};

/// translate a midi control message into amp control
void controlAmp (
        AmpController& ampController,      ///< controller to send messages to
        uint8_t command,     ///< amp command
        uint8_t value     ///< amp commanded value
        );

void setup ()
{
    // Launch MIDI, by default listening to channel 1.
    MIDI.begin();
}


void loop ()
{
    if (MIDI.read()) {
        uint8_t command;
        uint8_t value;

        switch (MIDI.getType()) {
        case midi::ControlChange:
            command = MIDI.getData1();
            value = MIDI.getData2();

            controlAmp(ampController, command, value);
            break;

        case midi::ProgramChange:
            value = MIDI.getData1();
            ampController.channel(value);
            break;

        default:
            break;
        }
    }
}


void controlAmp (
        AmpController& ampController,
        uint8_t command,
        uint8_t value
        )
{
    switch (command) {
    case LOOP:
        ampController.loop((bool)value);
        break;

    case MUTE:
        ampController.mute((bool)value);
        break;

    case SOLO:
        ampController.solo((bool)value);
        break;

    default:
        break;
    }
}
