#!/usr/bin/python

"""
Original Code:
  Summary: XMODEM protocol implementation.
  Home-page: https://github.com/tehmaze/xmodem
  Author: Wijnand Modderman, Jeff Quast
  License: MIT

Stripped down and modified for this bootloader by Joe George 2015-2016
"""

from sys import argv

def getArgs():
    '''
    Get filename and serial port arguments

    '''

    script, filename, tty = argv

    return (filename, tty)

if __name__ == "__main__":
    args = getArgs()
    print args[0]
    print args[1]



