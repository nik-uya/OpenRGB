#include "RGBController_NX75.h"

RGBController_NX75::RGBController_NX75(hid_device* dev)
{
    controller = new NX75Controller(dev);

    name = "NX75 Keyboard";
    vendor = "NX75";
    type = DEVICE_TYPE_KEYBOARD;
}

RGBController_NX75::~RGBController_NX75()
{
    delete controller;
}

void RGBController_NX75::SetupZones()
{
    zone z;
    z.name = "Keyboard";
    z.type = ZONE_TYPE_SINGLE;
    z.leds_count = 1;

    zones.push_back(z);
    leds.resize(1);
}

void RGBController_NX75::DeviceUpdateLEDs()
{
    controller->Apply();
}

void RGBController_NX75::UpdateMode()
{
    controller->SetMode(active_mode);
}
