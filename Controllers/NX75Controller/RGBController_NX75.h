#pragma once

#include "RGBController.h"
#include "NX75Controller.h"

class RGBController_NX75 : public RGBController
{
public:
    RGBController_NX75(hid_device* dev);
    ~RGBController_NX75();

    void SetupZones() override;
    void DeviceUpdateLEDs() override;
    void UpdateMode() override;

private:
    NX75Controller* controller;
};
