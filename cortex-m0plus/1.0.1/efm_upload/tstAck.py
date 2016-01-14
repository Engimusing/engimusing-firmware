#!/usr/bin/python

"""
Original Code:
  Summary: XMODEM protocol implementation.
  Home-page: https://github.com/tehmaze/xmodem
  Author: Wijnand Modderman, Jeff Quast
  License: MIT

Stripped down and modified for this bootloader by Joe George 2015-2016
"""

i = (0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

def checkAck(sequence):
    return i[sequence - 1]


if __name__ == "__main__":
    print checkAck(1)
    print checkAck(2)
    print checkAck(3)
    print checkAck(4)
    print checkAck(5)
    print checkAck(6)
    print checkAck(7)
    print checkAck(8)
    print checkAck(9)
    print checkAck(10)
    print checkAck(11)
    print checkAck(12)
    print checkAck(13)
    print checkAck(14)


