#include "NX75Controller.h"
#include <cstring>

NX75Controller::NX75Controller(hid_device* dev_handle)
{
    dev = dev_handle;
}

NX75Controller::~NX75Controller()
{
    if(dev)
        hid_close(dev);
}
