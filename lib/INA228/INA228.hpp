/**
 * @author TSprecher
 * @date 2022:04:01 11:02:30
 */

#include <cstdint>

class INA228 {
 public:
  /**
   * @brief The ADC settings controlling the full scale range across IN+ and IN-.
   */
  enum class ADC_Ranges : bool {
    pm_163mV84 = 0, /**< ±163.84mV */
    pm_40mV96 = 1   /**< ±40.96mV */
  };

  /**
   * @brief The different operating modes.
   */
  enum class Modes : uint8_t {
    shutdown = 0x0,                   /**< Shutdown */
    trig_bus_single = 0x1,            /**< Triggered bus voltage, single shot */
    trig_shunt_single = 0x2,          /**< Triggered shunt voltage triggered, single shot */
    trig_shunt_bus_single = 0x3,      /**< Triggered shunt voltage and bus voltage, single shot */
    trig_temp_single = 0x4,           /**< Triggered temperature, single shot */
    trig_temp_bus_single = 0x5,       /**< Triggered temperature and bus voltage, single shot */
    trig_temp_bus_single = 0x6,       /**< Triggered temperature and shunt voltage, single shot */
    trig_bus_shunt_temp_single = 0x7, /**< Triggered bus voltage, shunt voltage and temperature, single shot */
    cont_bus = 0x9,                   /**< Continuous bus voltage only */
    cont_shunt = 0xA,                 /**< Continuous shunt voltage only */
    cont_shunt_bus = 0xB,             /**< Continuous shunt and bus voltage */
    cont_temp = 0xC,                  /**< Continuous temperature only */
    cont_bus_temp = 0xD,              /**< Continuous bus voltage and temperature */
    cont_temp_shunt = 0xE,            /**< Continuous temperature and shunt voltage */
    cont_bus_shunt_temp = 0xF         /**< Continuous bus, shunt voltage and temperature */
  };

  /**
   * @brief The conversion times for bus voltage, shunt voltage, and temperature.
   */
  enum class Conversion_Times : uint8_t {
    t_50us = 0x0,   /**< 50 μs */
    t_84us = 0x1,   /**< 84 μs */
    t_150us = 0x2,  /**< 150 μs */
    t_280us = 0x3,  /**< 280 μs */
    t_540us = 0x4,  /**< 540 μs */
    t_1052us = 0x5, /**< 1052 μs */
    t_2074us = 0x6, /**< 2074 μs */
    t_4120us = 0x7  /**< 4120 μs */
  };

  /**
   * @brief ADC sample averaging count, applies to all active inputs.
   * @note When >0h, the output registers are updated after the averaging has completed.
   */
  enum class Averaging_Counts : uint8_t {
    c_1 = 0x0,   /**< 1 */
    c_4 = 0x1,   /**< 4 */
    c_16 = 0x2,  /**< 16 */
    c_64 = 0x3,  /**< 64 */
    c_128 = 0x4, /**< 128 */
    c_256 = 0x5, /**< 256 */
    c_512 = 0x6, /**< 512 */
    c_1024 = 0x7 /**< 1024 */
  };

 private:
  /**
   * @brief The addresses of each register.
   */
  enum class Registers_ : uint8_t {
    config_ = 0x0,
    adc_config_ = 0x1,
    shunt_calibration_ = 0x2,
    shunt_temperature_coefficient_ = 0x3,
    shunt_voltage_measurement_ = 0x4,
    bus_voltage_measurement_ = 0x5,
    die_temperature_ = 0x6,
    current_ = 0x7,
    power_ = 0x8,
    energy_ = 0x9,
    charge_ = 0xA,
    diagnostic_flag_ = 0xB,
    shunt_overvoltage_threshold_ = 0xC,
    shunt_undervoltage_threshold_ = 0xD,
    bus_overvoltage_threshold_ = 0xE,
    bus_undervoltage_threshold_ = 0xF,
    temperature_overlimit_threshold_ = 0x10,
    power_overlimit_threshold_ = 0x11,
    manufacturer_id_ = 0x3E,
    device_id_ = 0x3F
  };

  enum class Config_Masks_ : uint16_t {
    reset_ = 0b1000000000000000,
    reset_accumulation_ = 0b100000000000000,
    adc_conversion_delay_ = 0b11111111000000,
    enable_temperature_compensation_ = 0b100000,
    adc_range_ = 0b10000
  };

  enum class ADC_Config_Masks_ : uint16_t {
    mode_ = 0b1111000000000000,
    bus_voltage_conversion_time_ = 0b111000000000,
    shunt_voltage_conversion_time_ = 0b111000000,
    temperature_conversion_time_ = 0b111000,
    adc_averaging_count_ = 0b111
  };

  enum class Shunt_Calibration_Masks_ : uint16_t { shunt_calibration_ = 0b111111111111111 };

  enum class Shunt_Temperature_Coefficient_Masks_ : uint16_t { shunt_temperature_coefficient_ = 0b11111111111111 };

  enum class Shunt_Voltage_Measurement_Masks_ : uint32_t { shunt_voltage_measurement_ = 0b111111111111111111110000 };

  enum class Bus_Voltage_Measurement_Masks_ : uint32_t { bus_voltage_measurement_ = 0b111111111111111111110000 };

  enum class Temperature_Measurement_Masks_ : uint16_t { internal_die_temperature_measurement_ = 0b1111111111111111 };

  enum class Current_Result_Masks_ : uint32_t { current_result_ = 0b111111111111111111110000 };

  enum class Power_Result_Masks_ : uint32_t { power_result_ = 0b111111111111111111111111 };

  enum class Energy_Result_Masks_ : uint64_t { energy_result_ = 0b1111111111111111111111111111111111111111 };

  enum class Charge_Result_Masks_ : uint64_t { charge_result_ = 0b1111111111111111111111111111111111111111 };

  enum class Diagnostic_Flags_Masks_ : uint16_t {
    alert_latch = 0b1000000000000000,
    conversion_ready_on_alert_pin_ = 0b100000000000000,
    alert_asserted_on_completed_average_ = 0b10000000000000,
    alert_pin_polarity_ = 0b1000000000000,
    energy_health_ = 0b100000000000,
    charge_health_ = 0b10000000000,
    math_overflow_ = 0b1000000000,
    temperature_overlimit_ = 0b10000000,
    shunt_overlimit_ = 0b1000000,
    shunt_underlimit_ = 0b100000,
    bus_overlimit_ = 0b10000,
    bus_underlimit_ = 0b1000,
    power_limit_ = 0b100,
    conversion_complete_ = 0b10,
    checksum_error_ = 0b1
  };

  enum class Shunt_Overvoltage_Threshold_Masks_ : uint16_t { shunt_overvoltage_threshold_ = 0b1111111111111111 };

  enum class Shunt_Undervoltage_Threshold_Masks_ : uint16_t { shunt_undervoltage_threshold_ = 0b1111111111111111 };

  enum class Bus_Overvoltage_Threshold_Masks_ : uint16_t { bus_overvoltage_threshold_ = 0b1111111111111111 };

  enum class Bus_Undervoltage_Threshold_Masks_ : uint16_t { bus_undervoltage_threshold_ = 0b1111111111111111 };

  enum class Temperature_Overlimit_Threshold_Masks_ : uint16_t { temperature_overlimit_threshold_ = 0b1111111111111111 };

  enum class Power_Over_Limit_Threshold_Masks_ : uint16_t { power_over_limit_threshold_ = 0b1111111111111111 };

  enum class Manufacturer_ID_Masks_ : uint16_t { manufacturer_id_ = 0b1111111111111111 };

  enum class Device_ID_Masks_ : uint16_t { device_id_ = 0b1111111111111111 };
};