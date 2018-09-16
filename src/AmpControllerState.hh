#ifndef AMPCONTROLLERSTATE_H_
#define AMPCONTROLLERSTATE_H_

#include <Arduino.h>

struct AmpControllerState
{
public:
    /// constructor
    AmpControllerState ();

    /// set loop enabled state
    void loop (
            bool enabled ///< new enabled state of loop
            );

    /// set mute enabled state
    void mute (
            bool enabled ///< new enabled state of solo
            );

    /// set solo enabled state
    void solo (
            bool enabled ///< new enabled state of solo
            );

    /// set channel state
    void channel (
            uint8_t channel ///< channel to set
            );

    /// @return loop state
    bool loop () const;

    /// @return mute state
    bool mute () const;

    /// @return solo state
    bool solo () const;

    /// @return channel state
    uint8_t channel () const;

private:
    /// initialize EEPROM if this is first run
    void initializeEEPROM ();

    uint8_t state_;
};

#endif // AMPCONTROLLERSTATE_H_
