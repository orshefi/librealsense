//
// Created by or on 6/25/19.
//

#include <iostream>
#include "DeviceHolder.h"
#include "Manager.h"



DeviceHolder::DeviceHolder(libusb_device *_device, std::shared_ptr<perc::Dispatcher> _dispatcher, EventHandler* owner, perc::CompleteQueueHandler* taskHandler):
m_dispatcher(_dispatcher),
m_libusb_device(_device),
mTaskHandler(taskHandler),
mOwner(owner)
{
    auto device = new perc::Device(m_libusb_device,m_dispatcher.get(), mOwner, mTaskHandler);
    device->GetDeviceInfo(m_dev_info);
    delete device;
}

DeviceHolder::~DeviceHolder()
{
    libusb_unref_device(m_libusb_device);
}


std::shared_ptr<perc::TrackingDevice> DeviceHolder::get_device() {
    auto device = std::make_shared<perc::Device>(m_libusb_device,m_dispatcher.get(), mOwner, mTaskHandler);
    libusb_ref_device(m_libusb_device);
    return device;
}

void DeviceHolder::onTimeout(uintptr_t timerId, const perc::Message & msg)
{
    // Schedule the listener itself for every 500 msec
    m_dispatcher->scheduleTimer(this, 500, perc::Message(0));
}