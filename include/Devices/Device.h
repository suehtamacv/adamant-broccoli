#ifndef DEVICE_H
#define DEVICE_H

#include <memory>
#include <GeneralClasses/Gain.h>
#include <GeneralClasses/Power.h>

/**
 * @brief The Device class represents in a generic way a device on the network.
 */
class Device {
  public:
    /**
     * @brief The DeviceType enum is used to identify the type of Device.
     */
    enum DeviceType {
        AmplifierDevice, /*!< Amplifier */
        FiberDevice, /*!< Fiber Segment */
        SplitterDevice, /*!< Splitter */
        SSSDevice, /*!< Selective Spectrum Switch */
        UndefinedDevice /*!< Undefined Device */
    };

    /**
     * @brief Device is the standard constructor for a Device.
     * @param DevType is the type of Device.
     */
    Device(DeviceType  DevType = UndefinedDevice);

    /**
     * @brief DevType is the type of device.
     */
    DeviceType DevType;
    /**
     * @brief get_Gain returns the gain (or loss) of the device.
     * @return the gain (or loss) of the device.
     */
    virtual Gain &get_Gain() = 0;
    /**
     * @brief get_Noise returns the noise generated by the device.
     * @return the noise generated by the device.
     */
    virtual Power &get_Noise() = 0;
    /**
     * @brief clone returns a pointer to a Device with the same content as this.
     * @return a pointer to a Device with the same content as this.
     */
    virtual std::shared_ptr<Device> clone() = 0;
};

#endif // DEVICE_H
