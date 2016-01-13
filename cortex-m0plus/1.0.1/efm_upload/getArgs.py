#!/usr/bin/python

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



