#include "NX75Controller.h"
#include <hidapi/hidapi.h>
#include <algorithm>

NX75Controller::NX75Controller() : dev(nullptr) {}
NX75Controller::~NX75Controller() { Disconnect(); }

bool NX75Controller::Connect()
{
    if(hid_init() != 0) return false;
    dev = hid_open(VENDOR_ID, PRODUCT_ID, nullptr);
    return dev != nullptr;
}

void NX75Controller::Disconnect()
{
    if(dev)
    {
        hid_close(dev);
        dev = nullptr;
    }
    hid_exit();
}

uint8_t NX75Controller::checksum(const std::vector<uint8_t>& payload) const
{
    uint32_t sum = 0xFD;
    for(uint8_t b : payload) sum += b;
    return static_cast<uint8_t>(sum & 0xFF);
}

std::vector<uint8_t> NX75Controller::build_base(uint8_t cmd1, uint8_t cmd2) const
{
    std::vector<uint8_t> p(REPORT_SIZE, 0x00);
    p[0] = 0x04;
    p[2] = cmd1;
    p[3] = 0x06;
    p[4] = 0x1C;
    p[5] = 0x00;
    p[6] = 0x00;
    p[7] = 0x00;
    p[8] = 0x00;
    p[9] = cmd2;
    p[15] = 0xFF;
    p[16] = 0xFF;
    p[17] = 0xFF;
    p[18] = 0x08;
    p[30] = 0x01;
    p[31] = 0x00;
    p[32] = 0x01;
    p[33] = 0x00;
    return p;
}

bool NX75Controller::send_report(std::vector<uint8_t> payload)
{
    payload[1] = checksum(std::vector<uint8_t>(payload.begin() + 2, payload.end()));
    if(!dev) return false;
    int r = hid_write(dev, payload.data(), payload.size());
    return r == static_cast<int>(payload.size());
}

bool NX75Controller::SetLights(bool on)
{
    auto p = build_base(on ? 0x2F : 0x2B, on ? 0x01 : 0x01);
    p[10] = on ? 0x04 : 0x00;
    p[11] = 0x01;
    p[12] = 0x00;
    p[13] = 0x01;
    p[14] = 0x01;
    return send_report(p);
}

bool NX75Controller::SetMode(uint8_t mode)
{
    auto p = build_base(mode == MODE_CUSTOM ? 0x31 : 0x30, 0x01);
    p[10] = mode;
    p[11] = 0x01;
    p[12] = 0x01;
    p[13] = 0xFF;
    p[14] = 0xFF;
    return send_report(p);
}

bool NX75Controller::SetBrightness(uint8_t level)
{
    level = std::min<uint8_t>(level, 4);
    auto p = build_base(0x31, 0x01);
    p[9] = 0x04;
    p[10] = level;
    p[11] = 0x01;
    p[12] = 0x00;
    p[13] = 0x01;
    p[14] = 0x01;
    return send_report(p);
}

bool NX75Controller::SetSpeed(uint8_t level)
{
    level = std::min<uint8_t>(level, 4);
    auto p = build_base(0x3F, 0x0F);
    p[10] = 0x04;
    p[11] = 0x01;
    p[12] = 0x01;
    p[13] = 0x01;
    p[14] = level;
    return send_report(p);
}

bool NX75Controller::SetDirection(bool rtl)
{
    auto p = build_base(rtl ? 0x30 : 0x30, 0x01);
    p[10] = 0x04;
    p[11] = rtl ? 0x01 : 0x00;
    p[12] = rtl ? 0x01 : 0x00;
    p[13] = 0x01;
    p[14] = rtl ? 0x01 : 0x00;
    return send_report(p);
}
