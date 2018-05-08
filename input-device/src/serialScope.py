import serial
import binascii 

def readValue(serialPort):
    return binascii.unhexlify(serialPort.readline())

def plotValue(value):
    """ Displays the value on a scaled scrolling bargraph"""
    sys.stdout.write(value)
    sys.stdout.flush()

def cheapoScope(serialPort):
    while(1):
        newValue = readValue(serialPort)
        plotValue(newValue)

if __name__ == "__main__":
    print("Start reading serial port")
    PORT = '/dev/ttyUSB0'
    BAUDRATE = 9600
    TIMEOUT = None
    SCREEN_WIDTH = 80
    ## Take command-line arguments to override defaults above
    import sys
    if len(sys.argv) == 3:
        port = sys.argv[1]
        baudrate = int(sys.argv[2])
    else: # nothing passed, use defaults
        print ("Optional arguments port, baudrate set to defaults.")
        port, baudrate = (PORT, BAUDRATE)
    serialPort = serial.Serial(port, baudrate, timeout=TIMEOUT)
    serialPort.flush()
    cheapoScope(serialPort)