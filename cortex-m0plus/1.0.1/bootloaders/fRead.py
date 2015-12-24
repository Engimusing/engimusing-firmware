#!/usr/bin/python

import sys
from oPkt import asmPkt
from oPkt import verify
from tty import checkAck

packet_size   = 128

def sendPackets(s, filename):

    stream = file(filename, 'rb')
    sequence = 1

    data = stream.read(packet_size)
    if not data:
        print "File Empty"
        return 

    errcnt = 0
    fullcrc = 0

    while 1:
        pkt = asmPkt(data, sequence)
        fullcrc = verify(data, fullcrc)

        for ch in pkt:
            s.write(ch)
            sys.stdout.write(hex(ord(ch))+' ')
        print
        print

        if checkAck(s) == True:
            print "Packet %r Transferred" % sequence
            sequence = (sequence + 1) % 0x100  # increment sequence number
            print sequence
            data = stream.read(packet_size)
            if not data:
                print "CRC of file = " + hex(fullcrc)
                return True
        else:
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
    sendPackets(filename)


    fullcrc = calc_crc(data)
    print hex(fullcrc)


