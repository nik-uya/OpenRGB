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

uint8_t NX75Controller::Checksum(const std::vector<uint8_t>& data) const
{
    int sum = 0;
    for(auto b : data)
        sum += b;

    return (0xFD + sum) & 0xFF;
}

std::vector<uint8_t> NX75Controller::BuildPacket() const
{
    std::vector<uint8_t> p(REPORT_SIZE, 0x00);

    p[0] = 0x04;

    p[2] = 0x03;
    p[3] = 0x06;
    p[4] = 0x1C;

    p[7]  = state.brightness;
    p[8]  = state.speed;
    p[9]  = state.direction;
    p[10] = state.variant;
    p[11] = state.mode;

    p[12] = 0xFF;
    p[13] = 0xFF;
    p[14] = 0xFF;
    p[15] = 0x08;

    p[1] = Checksum(p);

    return p;
}

bool NX75Controller::Send(const std::vector<uint8_t>& data)
{
    if(!dev)
        return false;

    return hid_send_feature_report(
        dev,
        data.data(),
        REPORT_SIZE
    ) == REPORT_SIZE;
}

bool NX75Controller::Apply()
{
    auto pkt = BuildPacket();

    Send(pkt);
    Send(pkt); // REQUIRED commit

    return true;
}

bool NX75Controller::SetMode(uint8_t mode)
{
    state.mode = mode;
    return true;
}

bool NX75Controller::SetBrightness(uint8_t b)
{
    state.brightness = b;
    return true;
}

bool NX75Controller::SetSpeed(uint8_t s)
{
    state.speed = s;
    return true;
}

bool NX75Controller::SetDirection(bool rtl)
{
    state.direction = rtl ? 0x01 : 0x00;
    return true;
}
