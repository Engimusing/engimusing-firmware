#!/usr/bin/python

"""
Original Code:
  Summary: XMODEM protocol implementation.
  Home-page: https://github.com/tehmaze/xmodem
  Author: Wijnand Modderman, Jeff Quast
  License: MIT

Stripped down and modified for this bootloader by Joe George 2015-2016
"""

from calcCRC import calc_crc

# Protocol bytes
SOH = chr(0x01)

packet_size   = 128
pad           = '\x1a'


def asmPkt(data, sequence):

    data = data.ljust(packet_size, pad)
    crc = calc_crc(data)

    return SOH + (chr(sequence)) + (chr(0xff - sequence)) + data + (chr(crc >> 8)) + (chr(crc & 0xff))

if __name__ == "__main__":
    import sys, binhex
    out = asmPkt('abcdefghijklmnopqrstuvwxyz0123456789', 1)
    for ch in out:
        sys.stdout.write(hex(ord(ch))+' ')
    print
    print


def verify(data, fullcrc):

    data = data.ljust(packet_size, pad)
    crc = calc_crc(data, fullcrc)

    return crc
