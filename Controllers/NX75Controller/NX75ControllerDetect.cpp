#include "RGBController_NX75.h"
#include <hidapi/hidapi.h>
#include <vector>

#define VENDOR_ID  0x320f
#define PRODUCT_ID 0x5055

void DetectNX75(std::vector<RGBController*>& controllers)
{
    hid_device_info* devices = hid_enumerate(VENDOR_ID, PRODUCT_ID);

    hid_device_info* cur = devices;

    while(cur)
    {
        hid_device* dev = hid_open_path(cur->path);

        if(dev)
        {
            controllers.push_back(new RGBController_NX75(dev));
        }

        cur = cur->next;
    }

    hid_free_enumeration(devices);
}
