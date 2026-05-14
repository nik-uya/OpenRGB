#pragma once

#include "RGBController.h"
#include <hidapi/hidapi.h>
#include <vector>

class RGBController_NX75 : public RGBController
{
public:
    RGBController_NX75(hid_device* dev_handle);
    ~RGBController_NX75();

    void SetupZones() override;
    void ResizeZone(int /*zone*/, int /*new_size*/) override {}

    void DeviceUpdateLEDs() override;
    void UpdateMode() override;

private:
    hid_device* dev;

    struct NX75State
    {
        uint8_t mode       = 0x06;
        uint8_t brightness = 0x04;
        uint8_t speed      = 0x02;
        uint8_t direction  = 0x00;
        uint8_t variant    = 0x00;
    } state;

    static constexpr size_t REPORT_SIZE = 64;

private:
    std::vector<uint8_t> BuildPacket() const;
    uint8_t Checksum(const std::vector<uint8_t>& data) const;
    bool Send(const std::vector<uint8_t>& data);
};
