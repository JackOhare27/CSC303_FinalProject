from twilio.rest import Client
import serial
import string
import time
account_sid = 'INPUT SID'
auth_token = 'INPUT TOKEN'
twilio_number = '+19452073273'
target_number = '+18652350837'


client = Client(account_sid, auth_token)
#Grab serial from usb port
ser = serial.Serial('/dev/ttyACM0',9600)
while True:
    #read through each line and decode into int
    distance = 0
    serialdata=ser.readline()
    li = serialdata.decode()
    distance  = int(li)
    print(distance)
    #if door is opened
    if(distance >= 20):
        message = client.messages.create(
                     body="Door has been opened!",
                     from_=twilio_number,
                     to=target_number
                 )
        
        continue
    
