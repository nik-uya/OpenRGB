#include "RGBController.h"
#include "NX75Controller.h"

class RGBController_NX75 : public RGBController
{
public:
    NX75Controller* dev;

    RGBController_NX75(hid_device* handle)
    {
        dev = new NX75Controller(handle);

        name   = "NX75 Keyboard";
        vendor = "NX75";
        type   = DEVICE_TYPE_KEYBOARD;
    }

    ~RGBController_NX75()
    {
        delete dev;
    }

    void SetupZones() override
    {
        zone z;
        z.name = "Keyboard";
        z.type = ZONE_TYPE_SINGLE;
        z.leds_count = 1;

        zones.push_back(z);
        leds.resize(1);
    }

    void DeviceUpdateLEDs() override
    {
        dev->Apply();
    }

    void UpdateMode() override
    {
        dev->SetMode(active_mode);
    }
};
