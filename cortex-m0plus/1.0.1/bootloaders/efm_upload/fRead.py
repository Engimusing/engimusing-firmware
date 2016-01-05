#!/usr/bin/python

"""
Original Code:
  Summary: XMODEM protocol implementation.
  Home-page: https://github.com/tehmaze/xmodem
  Author: Wijnand Modderman, Jeff Quast
  License: MIT

Stripped down and modified for this bootloader by Joe George 2015-2016
"""

import sys
from oPkt import asmPkt
from oPkt import verify
from tty import checkAck

packet_size   = 128
debug = 0

def sendPackets(s, filename):

    stream = file(filename, 'rb')
    sequence = 1

    data = stream.read(packet_size)
    if not data:
        print "File Empty"
        return 

    errcnt = 0
    fullcrc = 0

    print "Packet Transferred: "
    while 1:
        pkt = asmPkt(data, sequence)
        fullcrc = verify(data, fullcrc)

        for ch in pkt:
            s.write(ch)
            if debug: sys.stdout.write(hex(ord(ch))+' ')
        if debug:
            print
            print

        if checkAck(s) == True:
            if debug:
                print " %r" % sequence
            else:
                sys.stdout.write('>')
                sys.stdout.flush()
            sequence = (sequence + 1) % 0x100  # increment sequence number
            if debug: print sequence
            data = stream.read(packet_size)
            if not data:
                print
                print "CRC of file = " + hex(fullcrc)
                return True
        else:
            print
            print "Packet %r Failed" % sequence
            errcnt += 1
            if errcnt > 15:
                print "Transfer Errors"
                return False

        continue

    print "Transfer Complete"

    return True

if __name__ == "__main__":
    import sys
    from sys import argv
    script, filename = argv
    debug = 1
    sendPackets(filename)


    fullcrc = calc_crc(data)
    print hex(fullcrc)


