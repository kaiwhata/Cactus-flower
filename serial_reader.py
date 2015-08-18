import serial, os

'''
ser = serial.Serial('/dev/tty.usbserial', 9600)
'''
def main():
    ser = serial.Serial('/dev/ttyACM0', 9600)

    my_file = open(get_dest("flowers.txt"), 'w')

    count = 0
    while count < 25:
        line = ser.readline()
        my_file.write(line)
        print(line)
        count = count + 1

    my_file.close()

"""
def get_dest(file_name):
    if file_name is None or not file_name:
        return None
    dest = os.path.join(os.getcwd(), file_name)
    x = 1
    name, ext = os.path.splittext(file_name)
    while os.path.exists(dest):
        file_name = '{0}.{1}{2}'.format(name, str(x), ext)
        dest = os.path.join(os.getcwd(), file_name)
        x = x + 1
    return dest
"""
