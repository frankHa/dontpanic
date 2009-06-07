#!/usr/bin/python
# -*- coding: utf-8 -*-

import dbus

bus=dbus.SessionBus()
application = dbus.Interface(bus.get_object('org.dontpanic','/Application'),'org.dontpanic.Application')
message = application.hello()
print message
