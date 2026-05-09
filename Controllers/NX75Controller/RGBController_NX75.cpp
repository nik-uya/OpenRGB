#include "RGBController_NX75.h"

RGBController_NX75::RGBController_NX75(NX75Controller* c)
    : controller(c)
{
    name = "NX75 Keyboard";
    description = "NX75 vendor-specific HID RGB keyboard";
    type = DEVICE_TYPE_KEYBOARD;
    active_mode = 0;
    controller_data = c;
}

RGBController_NX75::~RGBController_NX75()
{
    delete controller;
}

void RGBController_NX75::SetupZones()
{
    zones.resize(1);
    zones[0].name = "Keyboard";
    zones[0].type = ZONE_TYPE_SINGLE;
    zones[0].leds_min = 1;
    zones[0].leds_max = 1;
    zones[0].leds_count = 1;
}

void RGBController_NX75::SetupModes()
{
    modes.resize(19);
    const char* names[] = {"Corrugated","Cloud","Serpentine","Spectrum","Breath","Normal","Reaction","Ripples","Traverse","Stars","Flowers","Roll","Wave","Cartoon","Rain","Scan","Surmount","Speed","Custom"};
    for(size_t i=0;i<19;i++)
    {
        modes[i].name = names[i];
        modes[i].value = static_cast<uint8_t>(i+1);
        modes[i].flags = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_DIRECTION_LR;
        modes[i].speed_min = 0;
        modes[i].speed_max = 4;
        modes[i].speed = 2;
        modes[i].direction = LEFT_TO_RIGHT;
    }
    modes[0].color_mode = MODE_COLOR_MODE_RANDOM;
    modes[18].flags |= MODE_FLAG_HAS_PER_LED_COLOR;
    active_mode = 0;
}

void RGBController_NX75::ResizeZone(int, int) {}
void RGBController_NX75::UpdateZoneLEDs(int) {}
void RGBController_NX75::UpdateSingleLED(int) {}

void RGBController_NX75::SetCustomMode()
{
    controller->SetMode(NX75Controller::MODE_CUSTOM);
}

void RGBController_NX75::SetMode(size_t mode)
{
    if(mode < modes.size()) controller->SetMode(modes[mode].value);
    active_mode = mode;
}
