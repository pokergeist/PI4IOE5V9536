/*
 * Arduino driver for Diodes Inc. PI4IOE5V9536
 * 4-channel I/O Expander IC.
 *
 * 2022-11-19  Initial release.
 *
 * Based largely on the work of github:hideakitai via github:ponoor.
*/

#ifndef PI4IOE5V9536_H
#define PI4IOE5V9536_H

#include <Arduino.h>
#include <Wire.h>

#define BASE_I2C_ADDR 0x41

enum : uint8_t {
    IOX_INPUT_PORT = 0x00,
    IOX_OUTPUT_PORT,
    IOX_POLARITY_INVERSION_PORT,
    IOX_CONFIGURATION_PORT
};

enum iox_port_t : uint8_t {
    P00,
    P01,
    P02,
    P03
};

enum iox_level_t :    uint8_t { IOX_LOW, IOX_HIGH };
enum iox_levelall_t : uint8_t { IOX_LOW_ALL = 0x00, IOX_HIGH_ALL = 0xFF };

enum iox_polarity_t :     uint8_t { IOX_ORIGINAL, IOX_INVERTED };
enum iox_polarity_all_t : uint8_t { IOX_ORIGINAL_ALL = 0x00, IOX_INVERTED_ALL = 0xFF };

enum iox_direction_t :     uint8_t { IXO_OUT, IOX_IN };
enum iox_direction_all_t : uint8_t { IOX_OUT_ALL = 0x00, IOX_IN_ALL = 0xFF };

class PI4IOE5V9536 {

  uint8_t input  {0xFF};  // value at port
  uint8_t output {0xFF};  // " " sans inversion
  uint8_t pol    {0x00};  // 1=inverted
  uint8_t dir    {0xFF};  // 0=output, 1=input
  uint8_t status;

public:

  int begin() {
    Wire.begin();
    return 0;
  }
  int begin(uint8_t out, iox_direction_all_t dir, iox_polarity_all_t pol) {
    Wire.begin();
    polarity(pol);
    if (status) return status;
    direction(dir);
    if (status) return status;
    return write(out);
  }

  uint8_t read() {
      read_bytes(IOX_INPUT_PORT, &input, 1);
      return input;
  }
  iox_level_t read(const uint8_t port) {
      uint8_t v = read();
      return (v & (1 << port)) ? IOX_HIGH : IOX_LOW;
  }

  bool write(const uint8_t value) {
      output = value;
      return write_impl();
  }
  bool write(const uint8_t port, const iox_level_t level) {
      if (level == IOX_HIGH) {
          this->output |= (1 << port);
      } else {
          this->output &= ~(1 << port);
      }
      return write_impl();
  }

  bool polarity(const uint8_t value) {
      this->pol = value;
      return polarity_impl();
  }
  bool polarity(const uint8_t port, const iox_polarity_t pol) {
      if (pol == IOX_INVERTED) {
          this->pol |= (1 << port);
      } else {
          this->pol &= ~(1 << port);
      }
      return polarity_impl();
  }

  bool direction(const uint8_t value) {
      this->dir = value;
      return direction_impl();
  }

  bool direction(const uint8_t port, const iox_direction_t dir) {
      if (dir == IOX_IN) {
          this->dir |= (1 << port);
      } else {
          this->dir &= ~(1 << port);
      }
      return direction_impl();
  }

   uint8_t i2c_error() const {
      return status;
  }

private:

  bool write_impl() {
      return write_bytes(IOX_OUTPUT_PORT, &output, 1);
  }

  bool polarity_impl() {
      return write_bytes(IOX_POLARITY_INVERSION_PORT, &pol, 1);
  }

  bool direction_impl() {
      return write_bytes(IOX_CONFIGURATION_PORT, &dir, 1);
  }

  int8_t read_bytes(const uint8_t reg, uint8_t* data, const uint8_t size) {
      Wire.beginTransmission(BASE_I2C_ADDR);
      Wire.write(reg);
      Wire.endTransmission(1);
      Wire.requestFrom(BASE_I2C_ADDR, size);
      int8_t count = 0;
      while (Wire.available()) data[count++] = Wire.read();
      return count;
  }

  bool write_bytes(const uint8_t reg, const uint8_t* data, const uint8_t size) {
      Wire.beginTransmission(BASE_I2C_ADDR);
      Wire.write(reg);
      for (uint8_t i = 0; i < size; i++) Wire.write(data[i]);
      status = Wire.endTransmission();
      return (status == 0);
  }
  
}; // class PI4IOE5V9536

#endif // _H
