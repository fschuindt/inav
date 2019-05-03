#pragma once

#include <stdbool.h>
#include <stdint.h>

#define RC_COMMAND_AXES_COUNT 4

#define RC_COMMAND_MIN -1.0f
#define RC_COMMAND_CENTER 0.0f
#define RC_COMMAND_MAX 1.0f
#define RC_COMMAND_RANGE (RC_COMMAND_MAX - RC_COMMAND_MIN)

typedef struct rcCommand_s {
    union {
        float axes[RC_COMMAND_AXES_COUNT];
        struct {
            float roll;
            float pitch;
            float yaw;
            float throttle;
        };
    };
} rcCommand_t;

// Sets all values to neutral
void rcCommandReset(rcCommand_t *cmd);

// Rotates the given command pitch and roll by the given angle in
// radians. Used mainly for HEADFREE mode.
void rcCommandRotate(rcCommand_t *dst, const rcCommand_t *src, float radians);
void rcCommandCopy(rcCommand_t *dst, const rcCommand_t *src);

// Maps a PWM value in [PWM_RANGE_MIN, PWM_RANGE_MAX] to [RC_COMMAND_MIN, RC_COMMAND_MAX]
float rcCommandMapPWMValue(int16_t value);
// Maps a throttle PWM value in [motorConfig()->minthrottle, motorConfig->maxthrottle]
// to [RC_COMMAND_CENTER, RC_COMMAND_MAX]
float rcCommandMapUnidirectionalPWMThrottle(int16_t thr);
// Maps a PWM value in [PWM_RANGE_MIN, PWM_RANGE_MAX] to [RC_COMMAND_CENTER, RC_COMMAND_MAX]
float rcCommandMapUnidirectionalPWMValue(int16_t value);

int16_t rcCommandToPWMValue(float cmd);

// Returns the absolute value of throttle mapped to [motorConfig()->minthrottle, motorConfig->maxthrottle]
int16_t rcCommandThrottleMagnitudeToPWM(float thr);

float rcCommandConvertPWMDeadband(uint8_t deadband);