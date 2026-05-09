#include "NX75Controller.h"
#include "RGBController_NX75.h"
#include <hidapi/hidapi.h>
#include <vector>

void DetectNX75(std::vector<RGBController*>& rgb_controllers)
{
    if(hid_init() != 0) return;
    hid_device_info* devices = hid_enumerate(NX75Controller::VENDOR_ID, NX75Controller::PRODUCT_ID);
    for(hid_device_info* cur = devices; cur; cur = cur->next)
    {
        auto* controller = new NX75Controller();
        if(controller->Connect())
        {
            auto* rgb = new RGBController_NX75(controller);
            rgb->SetupZones();
            rgb->SetupModes();
            rgb_controllers.push_back(rgb);
        }
        else
        {
            delete controller;
        }
    }
    hid_free_enumeration(devices);
}

REGISTER_DETECTOR("NX75 Keyboard", DetectNX75);
