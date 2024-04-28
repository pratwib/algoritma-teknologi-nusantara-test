import serial

port = input("Masukkan port serial: ")

ser = serial.Serial(port, 9600) 

data = 1  
ser.write(bytes(str(data), 'utf-8'))

# Tutup port serial
ser.close()

print("Data telah terkirim ke Arduino")