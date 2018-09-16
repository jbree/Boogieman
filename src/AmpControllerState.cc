#include "AmpControllerState.hh"

#include <EEPROM.h>

namespace
{
const uint8_t EEPROM_SIGNATURE = 0xb4;
const uint8_t EEPROM_VERSION = 0x01;
const uint8_t DEFAULT_STATE = 0b01000001; // mute on, channel 1

const uint8_t SIGNATURE_BYTE = 0;
const uint8_t VERSION_BYTE = 1;
const uint8_t STATE_BYTE = 2;

constexpr uint8_t LOOP_BIT = 0b10000000;
constexpr uint8_t MUTE_BIT = 0b01000000;
constexpr uint8_t SOLO_BIT = 0b00100000;
constexpr uint8_t CHANNEL_BITS = 0b00000011;
} // namespace


AmpControllerState::AmpControllerState ()
{
    uint8_t value = EEPROM.read(SIGNATURE_BYTE);

    if (value != EEPROM_SIGNATURE) {
        initializeEEPROM();
    }

    value = EEPROM.read(VERSION_BYTE);

    if (value != EEPROM_VERSION) {
        initializeEEPROM();
    }

    state_ = EEPROM.read(STATE_BYTE);
}


void AmpControllerState::loop (
        bool enabled
        )
{
    if (enabled) {
        // set the loop bit
        state_ |= LOOP_BIT;
    }
    else {
        // unset the loop bit
        state_ &= ~LOOP_BIT;
    }
    EEPROM.write(STATE_BYTE, state_);
}


bool AmpControllerState::loop () const
{
    return (bool)(state_ & LOOP_BIT);
}


void AmpControllerState::mute (
        bool enabled
        )
{
    if (enabled) {
        // set the loop bit
        state_ |= MUTE_BIT;
    }
    else {
        // unset the loop bit
        state_ &= ~MUTE_BIT;
    }
    EEPROM.write(STATE_BYTE, state_);
}


bool AmpControllerState::mute () const
{
    return (bool)(state_ & MUTE_BIT);
}


void AmpControllerState::solo (
        bool enabled
        )
{
    if (enabled) {
        // set the loop bit
        state_ |= SOLO_BIT;
    }
    else {
        // unset the loop bit
        state_ &= ~SOLO_BIT;
    }
    EEPROM.write(STATE_BYTE, state_);
}


bool AmpControllerState::solo () const
{
    return (bool)(state_ & SOLO_BIT);
}


void AmpControllerState::channel (
        uint8_t channel
        )
{
    state_ = (state_ & ~CHANNEL_BITS) | channel;
    EEPROM.write(STATE_BYTE, state_);
}


uint8_t AmpControllerState::channel () const
{
    return (uint8_t)(state_ & CHANNEL_BITS);
}


void AmpControllerState::initializeEEPROM ()
{
    EEPROM.write(SIGNATURE_BYTE, EEPROM_SIGNATURE);
    EEPROM.write(VERSION_BYTE, EEPROM_VERSION);
    EEPROM.write(STATE_BYTE, DEFAULT_STATE);
}
