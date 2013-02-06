/*
 * Copyright (c) 2012, Matias Fontanini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <tins/ethernetII.h>
#include <tins/radiotap.h>
#include <tins/dot11.h>
#include <tins/ieee802_3.h>
#include "pysender.h"

using Tins::NetworkInterface;
using Tins::EthernetII;
using Tins::RadioTap;
using Tins::Dot11;
using Tins::IEEE802_3;

void PyPacketSender::send(PyPDU *pdu) {
    sender.send(*pdu->pdu());
}

void PyPacketSender::isend(const NetworkInterface &iface, PyPDU *pdu) {
    if(EthernetII *actual = dynamic_cast<EthernetII*>(pdu->pdu()))
        swap_iface_and_send(iface, actual, pdu);
    /*else if(RadioTap *actual = dynamic_cast<RadioTap>(pdu->pdu()))
        swap_iface_and_send(iface, actual, pdu);*/
    else if(Dot11 *actual = dynamic_cast<Dot11*>(pdu->pdu()))
        swap_iface_and_send(iface, actual, pdu);
    else if(IEEE802_3 *actual = dynamic_cast<IEEE802_3*>(pdu->pdu()))
        swap_iface_and_send(iface, actual, pdu);
}

void PyPacketSender::python_register() {
    using namespace boost::python;
    
    class_<PyPacketSender>("PacketSender", init<>())
        .def("send", &PyPacketSender::send)
        .def("isend", &PyPacketSender::isend)
    ;
}
