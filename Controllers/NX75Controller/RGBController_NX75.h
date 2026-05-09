#pragma once
#include "NX75Controller.h"
#include <RGBController.h>

class RGBController_NX75 : public RGBController
{
public:
    RGBController_NX75(NX75Controller* controller);
    ~RGBController_NX75() override;

    void SetupZones();
    void SetupModes();
    void ResizeZone(int zone, int new_size) override;
    void UpdateZoneLEDs(int zone) override;
    void UpdateSingleLED(int led) override;
    void SetCustomMode() override;
    void SetMode(size_t mode) override;

private:
    NX75Controller* controller;
};
