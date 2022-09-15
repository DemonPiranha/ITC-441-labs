Lab 1 Report (2022)
-------------------

Raspberry Pi Webpage controlled Stop light
------------------------------------------


Online Link:
------------

This lab is available as part of my online portfolio at: <https://github.com/DemonPiranha/ITC-441-labs.git> 

Objective
---------

The purpose of this lab is to learn the basic principles of the Raspberry Pi platform by creating a webpage-controlled stoplight. These principles include:

-   Learn to enumerate requirements from use cases and user stories

-   Learn to utilize the general-purpose input/output (GPIO) pins on the Raspberry Pi to control LEDs.

-   Learn to develop a minimum viable product and deliver new functionality through subsequent updates until the requirements are met, and all the deliverables are acceptable.

Materials
---------

I used the following materials to accomplish this lab:

-   Raspberry Pi 3b+

-   SD card with Raspbian OS

-   MicroUSB Cable with power source

-   HDMI Cable with monitor

-   USB keyboard and mouse

-   1 x breadboard

-   1 x Green LED

-   1 x Yellow LED

-   1 x Red LED

-   3 x 100 Ω Resistor (BrBlBrGl)

-   4 x Jumper Wires

References
----------

I used the following resources in this lab:

-   <https://github.com/WiringPi/WiringPi> - This is the open-source Wiring Pi code needed to use GPIO commands. Instructions for insulation can be found on the github.

-   <https://randomnerdtutorials.com/raspberry-pi-web-server-using-flask-to-control-gpios/> - Tutorial on how to host a web server using Flask with Python and HTML code. I used code provided in this as a foundation for my code.

-   <https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code-5-band> - I used this to refresh my memory on resistor values that I was using.

-   <https://ozzmaker.com/check-raspberry-software-hardware-version-command-line/> - This provides basic Raspberry commands to check hardware information.

-   <https://www.w3schools.com/python/default.asp> - W3School Python code tutorials and examples. Helped me to know the syntax for python.

-   [https://realpython.com/python-while-loop](https://realpython.com/python-while-loop/#:~:text=Python%20provides%20two%20keywords%20that,terminates%20the%20current%20loop%20iteration) - Instructions on how to break a while loop correctly.

-   <https://realpython.com/python-sleep/> - Instructions for how to do sleep commands correctly.

-   <https://app.diagrams.net/> - Chart maker used to make the state diagram.

-   <https://1drv.ms/w/s!Ais81h0TsK5NhqEUuevEs8zMavzLag?e=hdaL2m> - Todd Berrett's example write-up. Used for formatting.

Procedures:
-----------


Observations
------------

I had fun working on this lab and it was a great way to expand on the knowledge I had from the systems I used on their own and put it all together. It took me a bit to get back into the roll of things with Python as it had been awhile since I used it however once I got going it all came back to me.

Understanding how Flask worked and how to properly use it in Python was the biggest challenge for me. I have done web hosting in previous classes but it is still a gray area for me. In this lab however I saw how I could set the host address and port which opened the page on that network. I then could view the page from another on network device by navigating to the Pis IP address. This was pretty cool for me as I remember doing this before but never understood how it worked until now.

The next difficulty I ran into was figuring out how to properly handle the light cycle. In order to have the lights light up in a pattern similar to a typical stoplight I decided to run  on and off commands inside a while loop with sleep delays in between each light. This allowed the lights to cycle correctly however once the program got into this while loop it wasn't able to break out without further intervention. I experimented with having the loop as a separate function and then thought about doing separate threads somehow but this all proved to not work. Ultimately with some help from classmates I came to the conclusion that I was overthinking things. The solution was ironically the easiest implementation. One of my classmates reminded me of global booleans that could be switched throughout the program and checked while running the loop. Putting this together with a if checks that would break the loop after every sleep the solution was complete. Aside from figuring out this there is still an issue with the webpage hanging while the loop is running. I did not have the time to find a work around for this however when another page link is clicked the page is able to properly resume. Fixing this would add far more stability to the system then is currently available.

Because there is only a single device, there isn't any communication between internal components. The single device does the following:

-   Listening on TCP port 80

-   Parsing input

-   Controlling the GPIO pins (and therefore, the LED)

-   Responding to the client with HTML

Thought Questions
-----------------

**What language did you choose for implementing this project? Why?**

I chose to implement this project using Python, HTML and inline Javascript. The Python code runs a plugin called Flask that is used to serve the web server. This ended up being a relatively comprehensible implementation due to a tutorial I found that explained how to utilize Flask. This is why I choose to go this route along with the fact that I am most familiar with Python and Javascript which helped me to expand on the tutorial and understand what was going on so that I could design it to meet all of the requirements.

**What is the purpose of the resistor in this simple circuit? What would happen if you omitted it?**

The primary purpose of the resistor is to limit the current through the LED. If the resistor wasn't there the LED would draw as much current as it could eventually causing it to burn up. This also benefits the Pi by not pulling more current than the Pi can supply and damaging the GPIO pins.

**What are practical applications of this device? What enhancements or modifications would you make?**

One use for this could be to serve as an indicator in front of an office or classroom. It could show whether the person/people inside are available to be bothered. This could also work as a way to show the status of any system really. For example it could be used to tell workers in a manufacturing plant if they are keeping up with the production rate. This could easily be enhanced by adding an API of sorts to it so that the lights could be triggered automatically by anything. Another enhancement would be to modify it with an ultrasonic sensor so that it could be used as a rough distance indicator.

**Please estimate the total time you spent on this lab and report.?**

I spent about 8 hours on the project with 4 hours on this lab report.

Certification of Work
---------------------

I certify that the solution presented in this lab represents my own work. In the case where I have borrowed code or ideas from another person, I have provided a link to the author's work in the references and included a citation in the comments of my code. 

--Blake Porter


Appendix
--------

### Appendix 1: State Diagram

![](https://lh3.googleusercontent.com/48fP6A_mxk1xbu_adeQk6CZFp-sbHipMucHWfpfk1wDb2dJn_AluOgcEpp_YMwntSbuTYt4XJdG7xiAuyCy2USRITq5rtvup86jYnNNDjjtSrmxoW67v-YgXYhpOQC5I5NC6JqH7k0ICU0QbSgVGloBzqHAyFvfnKTiFguZztiFQqNm4z5F28CKpaA)

### Appendix 2: Physical Components Layout

![](https://lh4.googleusercontent.com/SmwpVwkaulOw_wSm43FMfVg6ywxpaJktjjKiSz81XYRX3NoYfG4nClMe9wyrC--74p-y0v-YRbqcDf2rJF0TqzOBd-3SpDjrfarkWSgKTK_h_WLfeCJMuU6ZLwbgxYS4kpo5MeqlIG9KOMrfNClLXjvkPrc5vYQQbvQ0fc_uXHdpUtb_NGPIcf07mQ)

![](https://lh3.googleusercontent.com/FcQQrGS3gKV-z7Bc8f0uhQjs7_4Q1jMlOWQV6Ja96W7EqquuZqpC6V4NAarhtemFH9zn9u6fMisjTD_ytjUIT8dy4zz3gm3GSXbvngmlxt7r_2WtxTusW-HxF9r7kjgz-wztk0nzUgbgV2zL9kTSCi5AqYTPSXDs89zcDWhNiquBvQ8U_pwKEt29ig)

![](https://lh6.googleusercontent.com/RWzArNzhhcCORBgjAvtIxH1kZipxxG5j0XyovMfs4mN8rh1-tKAj7G4nx9ixkDk6Lf88TpKCOnrISolu878ovVZexfWafXr5MsmQRgZpHs-wrjcIJ2TjuYMQmlDw974brSs_L8VFh_wOzXGdvpEd7zgDP0rMBReiqEWMEeng1vDcFOuNOLV7X0BnCw)

### Appendix 3: System Interface - Web Page

State: startup

![](https://lh4.googleusercontent.com/cho71n_PY_GjRTF-L8zZM6AGzyfSMjl4M-UpKKbEu-yJ4peDt-FKBVDr96fGMcrcTaKwjlmxsGD_s6nnOU37yvFZt4eVzBo8MRCQ2VBTo4kC1gkjgAA1Bwv8HAUbQVpeJdWkVcakmGDTzfOAMPyWu1arwQRaX14zGmXbeq7qG2j6A3emQi-RRUPNag)

State: /<changepin>/<action>     This image is of state: /27/on and has similar function to the other pin states.

![](https://lh3.googleusercontent.com/yrG-OdI4ugFO4GmIOB7pxeNYN3xyOVP4kQu0KUbNBckL5M_opJfOVLf4OT9gpQMmCFRsYqHKx0GdTWneROu_2POsdbMpdy-6DHndzzmpJxI_Ho6I2iPSbJM4d0_-ugG7g1Nd16eMPN_juMqaRjDIP8Aylz9aDZkKJKql33iQgYKC3nDJn8EAvE6C8g)

State: /alloff

![](https://lh4.googleusercontent.com/KGRRLIl_Mt8OniB45qniHY8Jli4xbrdJ6Hn5c8aKF2sF-ThsVXLn9T17AfOl0kf6yAJh4QhSaaY4MvahGdmppNs9Xdu9XjhV_n0sNHDjIuVcd4btFb4-s3WVnAD5CIFn_yrHyKUvpA-d-x_R5k6dU55pZBvTPd0liDn5m8S5motbJ226wbY4ONlY3A)

State: /cycle

![](https://lh5.googleusercontent.com/1dkgA3cknYCnARFoaQ3-VSzpjy3iTQyZUPKDEvDo4XQYs9Y_Q5A8HK96XVZ4bEpPx2VKhuhuQD9L6i2VzIl4FXN-d4HrtyUbwRgYw5Z_gODMf6DV165yYVj-cE8HxnyO4eJPN9qFqAjTDIlt-7IO62oHStvexdof5pr42iTtuUwstKWTVGJkXtk0MQ)

### Appendix 4: Serial Monitor Output

### ![](https://lh3.googleusercontent.com/DSWARZ3j2iLyP68dCdUHsv0Tot0bwlBNd1Ibnh50YpLxbZE_y701nPfcGHKWOfK8NnWNqsLFQxKlnmRyT7-gUFiwAMHDuWzGG7tqG12vBEW8IPN8lpZ32Yp9wb7t05EsVSePsHoNb7So21NXYZZwHe0eiqiPq21sBYZpHkQbtxZ5oBN9eXsR0Zvdhg)

### Appendix 5: Python Code

(available at <https://github.com/DemonPiranha/ITC-441-labs/blob/main/Lab%201/web-server/ledcontrol.py> )

`
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

def colorAction(changePin, action):

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
  `

### Appendix 6: HTML Code

(available at <https://github.com/DemonPiranha/ITC-441-labs/blob/main/Lab%201/web-server/templates/main.html> )

`
<!DOCTYPE html>

<head>

   <title>RPi StopLight Server</title>

   <!-- Latest compiled and minified CSS -->

   <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">

   <!-- Optional theme -->

   <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap-theme.min.css" integrity="sha384-fLW2N01lMqjakBkx3l/M9EahuwpSfeNvV63J5ezn3uZzapT0u7EYsXMjQV+0En5r" crossorigin="anonymous">

   <!-- Latest compiled and minified JavaScript -->

   <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS" crossorigin="anonymous"></script>

</head>

<body>

   <h1>RPi StopLight Server</h1>

   {% for pin in pins %}

   <h2>{{ pins[pin].name }}

   {% if pins[pin].state == true %}

      is currently <strong>on</strong></h2><div class="row"><div class="col-md-2">

      <a href="/{{pin}}/off" class="btn btn-block btn-lg btn-default" role="button">Turn off</a></div></div>

   {% else %}

      is currently <strong>off</strong></h2><div class="row"><div class="col-md-2">

      <a href="/{{pin}}/on" class="btn btn-block btn-lg btn-primary" role="button">Turn on</a></div></div>

   {% endif %}

   {% endfor %}

   <div class="row"><div class="col-md-2"><a href="/alloff" class="btn btn-block btn-lg btn-primary" role="button">Turn on</a></div></div>

   <h2>Cycle Lights</h2>

   <div class="row"><div class="col-md-2"><a href="/cycle" class="btn btn-block btn-lg btn-primary" role="button">Turn on</a></div></div>

</body>

</html>
`
