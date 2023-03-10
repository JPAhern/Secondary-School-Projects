#This allows use to read the sensor
import RPi.GPIO as GPIO
#This gives python an understanding of time
import time
#This imports tools which will allow us to send an email from this code
import smtplib

#This will connect our program to gmail
server = smtplib.SMTP("smtp.gmail.com", 587)
#This will begin the program's search for our gmail account
server.starttls()
#This will tell the program which gmail account to connect to
server.login("from@gmail.com", "examplepassword")

#This section defines what each pin used will do
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
#This tells python that it should treet pin 11 as an input
GPIO.setup(11, GPIO.IN)
#This tells python that it should treet pin 3 an an output
GPIO.setup(3 ,GPIO.OUT)

#This resets the motor
GPIO.output(3, False)

#This creates a variable "trap"
trap = 1

#This while loop will run constantly
while True:
    #This while loop will run untill a mouse enters the trap
    while trap < 3:
        #This will read the sensor
        i = GPIO.input(11)
        #This will keep runnunig untill a mouse is sensed
        if i==0:
            #This allows me to see the output in the console for debugging
            print ("false",i)
            #This resets the couter to avoid errors
            trap = 0
            #This will restart the loop
            time.sleep(0.3)
        #This will run once a mouse is sensed
        elif i==1:
            #This allows me to see the output in the console for debugging
            print ("true",i , trap)
            #This will count up when the sensor is triggered to avoid false readings
            trap = trap + 1
            #This will restart the loop
            time.sleep(0.3)
    
    #This while loop will close the door when a mouse enters the trap
    while trap == 3:
        #This turns the motor on
        GPIO.output(3, True)
        #This allows me to see the output in the console for debugging 
        print ("Capture")
        #This will tell the program where to send the email and what to say
        server.sendmail("from@gmail.com", "to@gmail.com", "Capture")
        #This will exit email
        server.quit
        #This will end the program
        quit()
        
