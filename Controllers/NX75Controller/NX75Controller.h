#pragma once
#include <cstdint>
#include <vector>
#include <memory>

struct hid_device_;

class NX75Controller
{
public:
    static constexpr uint16_t VENDOR_ID  = 0x320f;
    static constexpr uint16_t PRODUCT_ID = 0x5055;
    static constexpr size_t REPORT_SIZE = 64;

    enum Mode : uint8_t
    {
        MODE_CORRUGATED = 0x01,
        MODE_CLOUD      = 0x02,
        MODE_SERPENTINE = 0x03,
        MODE_SPECTRUM   = 0x04,
        MODE_BREATH     = 0x05,
        MODE_NORMAL     = 0x06,
        MODE_REACTION   = 0x07,
        MODE_RIPPLES    = 0x08,
        MODE_TRAVERSE   = 0x09,
        MODE_STARS      = 0x0A,
        MODE_FLOWERS    = 0x0B,
        MODE_ROLL       = 0x0C,
        MODE_WAVE       = 0x0D,
        MODE_CARTOON    = 0x0E,
        MODE_RAIN       = 0x0F,
        MODE_SCAN       = 0x10,
        MODE_SURMOUNT   = 0x11,
        MODE_SPEED      = 0x12,
        MODE_CUSTOM     = 0x13,
    };

    NX75Controller();
    ~NX75Controller();

    bool Connect();
    void Disconnect();

    bool SetLights(bool on);
    bool SetMode(uint8_t mode);
    bool SetBrightness(uint8_t level);
    bool SetSpeed(uint8_t level);
    bool SetDirection(bool rtl);

private:
    hid_device_* dev;
    uint8_t checksum(const std::vector<uint8_t>& payload) const;
    bool send_report(std::vector<uint8_t> payload);
    std::vector<uint8_t> build_base(uint8_t cmd1, uint8_t cmd2) const;
};
