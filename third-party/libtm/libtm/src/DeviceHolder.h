/* License: Apache 2.0. See LICENSE file in root directory. */
/* Copyright(c) 2019 Intel Corporation. All Rights Reserved. */
//
// Created by or on 6/25/19.
//

#ifndef LIBREALSENSE2_DEVICEHOLDER_H
#define LIBREALSENSE2_DEVICEHOLDER_H


#include "TrackingManager.h"
#include "TrackingDeviceHolder.h"
#include "TrackingCommon.h"
#include "libusb.h"
#include "Device.h"
#include <memory>

namespace perc{
    class Manager;
}

class DeviceHolder : public perc::EventHandler, public perc::TrackingDeviceHolder
{
public:
    DeviceHolder(libusb_device *_device, std::shared_ptr<perc::Dispatcher> _dispatcher, EventHandler* owner, perc::CompleteQueueHandler* taskHandler);
    virtual ~DeviceHolder();

    perc::TrackingData::DeviceInfo get_device_info() override { return m_dev_info; }
    std::shared_ptr<perc::TrackingDevice> get_device() override;

    // [interface] EventHandler
    virtual void onTimeout(uintptr_t timerId, const perc::Message &msg) override;

private:
    EventHandler* mOwner;
    perc::CompleteQueueHandler* mTaskHandler;
    perc::TrackingData::DeviceInfo m_dev_info;
    std::shared_ptr<perc::Dispatcher> m_dispatcher;
    libusb_device *m_libusb_device;

};


#endif //LIBREALSENSE2_DEVICEHOLDER_H
