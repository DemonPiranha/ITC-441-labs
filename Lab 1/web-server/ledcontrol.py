import RPi.GPIO as GPIO
import time
from flask import Flask, render_template, request
app = Flask(__name__)

#Setup for GPIO pins and clears them all
GPIO.setwarnings(0)
GPIO.setmode (GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.output(22, GPIO.LOW)
GPIO.output(27, GPIO.LOW)
GPIO.output(17, GPIO.LOW)

#Sets Global stop variable for Cycle command
global cycle
cycle = True

#Creates a dictionary to store pin number, name, and pin state
pins = {
   22 : {'name' : 'Red Light', 'state' : GPIO.LOW},
   27 : {'name' : 'Yellow Light', 'state' : GPIO.LOW},
   17 : {'name' : 'Green Light', 'state' : GPIO.LOW}
   }

#Main function used to start as well as render the webpage after other functions
@app.route("/")
def main():
   
   #Store all the current pin states in pins dictionary
   for pin in pins:
      pins[pin]['state'] = GPIO.input(pin)
   
   #Put the pin dictionary into the template data dictionary
   templateData = {
      'pins' : pins
      }
   
   #Returns the data to the webpage
   return render_template('main.html', **templateData)


#This function runs when a URL request that includes pin number and action
@app.route("/<changePin>/<action>")
def action(changePin, action):
   
   #Call alloff to clear outputs
   alloff()
   #Gets the pin from the URL and sets it as an integer
   changePin = int(changePin)
   #Checks the state of <action> and triggers the current light on or off
   if action == "on":
      #Set the pin high
      GPIO.output(changePin, GPIO.HIGH)
   if action == "off":
      #Set the pin low
      GPIO.output(changePin, GPIO.LOW)

   return main()

@app.route("/alloff")
def alloff():
   
    #Turns cycle off if it was on
    global cycle
    cycle = False
    
    #Sets all GPIO outputs to off
    GPIO.output(22, GPIO.LOW)
    GPIO.output(27, GPIO.LOW)
    GPIO.output(17, GPIO.LOW)
    
    return main()

@app.route("/cycle")
def cycle():
    
    #Call alloff to clear outputs
    alloff()
    
    #Turns cycle on if it was on
    global cycle
    cycle = True

    #While loop that cycles the stoplight colors and checks if the cycle is still active after each sleep
    #If cycle is no longer active the loop will break
    while cycle == True:
            
        GPIO.output(17, GPIO.HIGH)
        time.sleep(5)
        if cycle == False:
            break
        GPIO.output(17, GPIO.LOW)
        GPIO.output(27, GPIO.HIGH)
        time.sleep(3)
        if cycle == False:
            break
        GPIO.output(27, GPIO.LOW)
        GPIO.output(22, GPIO.HIGH)
        time.sleep(5)
        if cycle == False:
            break
        GPIO.output(22, GPIO.LOW)
    
    return main()

#Flask task that runs the webpage on localhost
if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80, debug=True)
