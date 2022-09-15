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
