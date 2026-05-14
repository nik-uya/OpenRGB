#pragma once

#include <cstdint>
#include <vector>
#include <hidapi/hidapi.h>

class NX75Controller
{
public:
    static constexpr uint16_t VENDOR_ID  = 0x320f;
    static constexpr uint16_t PRODUCT_ID = 0x5055;
    static constexpr size_t REPORT_SIZE  = 64;

    NX75Controller(hid_device* dev);
    ~NX75Controller();

    bool SetMode(uint8_t mode);
    bool SetBrightness(uint8_t brightness);
    bool SetSpeed(uint8_t speed);
    bool SetDirection(bool rtl);

    bool Apply();

private:
    hid_device* dev;

    struct State
    {
        uint8_t mode = 0x06;
        uint8_t brightness = 0x04;
        uint8_t speed = 0x02;
        uint8_t direction = 0x00;
        uint8_t variant = 0x00;
    } state;

private:
    std::vector<uint8_t> BuildPacket() const;
    uint8_t Checksum(const std::vector<uint8_t>& data) const;
    bool Send(const std::vector<uint8_t>& data);
};
