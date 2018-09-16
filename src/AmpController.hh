#ifndef AMPCONTROLLER_H_s
#define AMPCONTROLLER_H_s

#include "AmpControllerState.hh"

#include <Arduino.h>


/// configuration values to initialize AmpController
struct AmpControllerConfig
{
    uint8_t loopPin;
    uint8_t mutePin;
    uint8_t soloPin;
    uint8_t channelPins[3];
};


/// control an amplifier by sending signals to emulate its footswitch
class AmpController {
public:
    /// constructor
    AmpController (
            const AmpControllerConfig& config ///< config for AmpController
            );

    /// select a channel (1 - 3) on the amp
    void channel (
            uint8_t channel,             ///< channel to select
            bool updateSavedState = true
            );

    /// enable or disable the amp fx loop
    void loop (
            bool enabled,
            bool updateSavedState = true
            );

    /// mute or unmute the amp
    void mute (
            bool enabled,
            bool updateSavedState = true
            );

    /// enable or disable the amp solo boost
    void solo (
            bool enabled,
            bool updateSavedState = true
            );

private:
    AmpControllerConfig config_;
    AmpControllerState savedState_;
};


#endif // AMPCONTROLLER_H_s
