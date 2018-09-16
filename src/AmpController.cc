#include "AmpController.hh"


AmpController::AmpController (
        const AmpControllerConfig& config
        )
: config_(config)
{
    // configure output pins
    pinMode(config_.mutePin, OUTPUT);
    pinMode(config_.loopPin, OUTPUT);
    pinMode(config_.soloPin, OUTPUT);

    config_.channelPins[0] = 2;
    config_.channelPins[1] = 3;
    config_.channelPins[2] = 8;

    for (size_t i = 0; i < 3; i++) {
        pinMode(config_.channelPins[i], OUTPUT);
    }

    // set initial state from saved values
    mute(savedState_.mute(), false);
    loop(savedState_.loop(), false);
    solo(savedState_.solo(), false);
    channel(savedState_.channel(), false);
}


void AmpController::channel (
        uint8_t chan,
        bool updateSavedState
        )
{
    if (chan < 1 || chan > 3) {
        return;
    }

    for (size_t i = 0; i < 3; i++) {
        const uint8_t pin = config_.channelPins[i];

        // set selected channel pin low, others high
        const uint8_t state = ((size_t)(chan - 1) == i ? LOW : HIGH);

        digitalWrite(pin, state);
    }

    if (updateSavedState) {
        savedState_.channel(chan);
    }
}


void AmpController::loop (
        bool enabled,
        bool updateSavedState
        )
{
    const uint8_t state = enabled ? LOW : HIGH;

    digitalWrite(config_.loopPin, state);

    if (updateSavedState) {
        savedState_.loop(enabled);
    }
}


void AmpController::mute (
        bool enabled,
        bool updateSavedState
        )
{
    const uint8_t state = enabled ? LOW : HIGH;

    digitalWrite(config_.mutePin, state);

    if (updateSavedState) {
        savedState_.mute(enabled);
    }
}


void AmpController::solo (
        bool enabled,
        bool updateSavedState
        )
{
    const uint8_t state = enabled ? LOW : HIGH;

    digitalWrite(config_.soloPin, state);

    if (updateSavedState) {
        savedState_.solo(enabled);
    }
}
