/* License: Apache 2.0. See LICENSE file in root directory. */
/* Copyright(c) 2019 Intel Corporation. All Rights Reserved. */
//
// Created by or on 6/25/19.
//

#ifndef LIBREALSENSE2_DEVICEHOLDER_H
#define LIBREALSENSE2_DEVICEHOLDER_H


#include "TrackingManager.h"
#include "TrackingDeviceHolder.h"
#include "libusb.h"
#include "Device.h"
#include <memory>

namespace perc{
    class Manager;
}

class DeviceHolder : public perc::EventHandler, public perc::TrackingDeviceHolder
{
public:
    DeviceHolder(libusb_device *_device, std::shared_ptr<perc::Dispatcher> _dispatcher, perc::Manager *_manager);
    virtual ~DeviceHolder();

    perc::TrackingData::DeviceInfo get_device_info() override { return m_dev_info; }
    std::shared_ptr<perc::TrackingDevice> get_device() override;

private:
    perc::TrackingData::DeviceInfo m_dev_info;
    std::shared_ptr<perc::Dispatcher> m_dispatcher;
    perc::Manager *m_manager;
    libusb_device *m_libusb_device;

};


#endif //LIBREALSENSE2_DEVICEHOLDER_H