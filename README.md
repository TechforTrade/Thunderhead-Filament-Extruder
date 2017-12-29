# Thunderhead Filament Extruder

The Thunderhead filament extruder is a  small scale extruder designed by Techfortrade that can be used for recycling PET plastic bottle flake directly into 3D printing filament. A special emphasis throughout the design has been placed on using affordable and easily attainable materials. This repository serves as a host for the documentation and code used with the machine. We are using GrabCAD Workbench for the hardware development and will place snapshots of the CAD files here on Github with each release. Current (though not necessarily stable) files can be accessed on our [GrabCAD partner space](https://workbench.grabcad.com/workbench/projects/gcvN9Xsi01SW-lFGhJRj_-4vqndCMFAaoUt_-UQBdidnVn#/space/gc8b8c582LagITdwrMEId6wysTlJX_nukUvWoRwEQ_1f4U).


#### The Thunderhead converts clean and dry PET flake into 3D printing Filament
<img src="./img/Flake_To_Filament.jpg" width="600" align="middle">



# Table of Contents

- [Goals](#goals)
- [PET Plastic](#pet-plastic)
- [Safety and Liability](#safety-and-liability)
- [Building the Thunderhead](#building-the-thunderhead)
- [Software](#software)
- [Operation](#operation)
- [Contributing](#contributing)
- [Maintainers](#maintainers)
- [Acknowledgements](#acknowledgements)
- [License](#license)




## Goals
The Thunderhead is designed with the intent of making it possible to recycle plastic from the post consumer waste stream into 3D printing filament on a small scale with minimal start up capital required. This makes the following possible:
- Low cost 3D printing filament anywhere in the world
- Enable local capture of the value contained in waste plastic
- Access to expensive or hard to find items via 3D printing (eg. [Open Flexure Microscope](https://github.com/rwb27/openflexure_microscope))
- Small scale business opportunities without need for large amounts of capital
- Enable local recycling where it is otherwise not possible





## PET Plastic 
The Thunderhead is designed to extrude Polyethylene Terephthalate (PET or PETE) for the following reasons:

-  Prints  very well on printers such as the Retr3D
-  Easy to find nearly anywhere on the planet
-  Has good physical properties
-  Reasonably safe to work with, especially compared to ABS which often has Brominated Flame Retardants (BFR)

PET is easily identified by the following symbol usually located on the bottom on the bottle:

<img src="./img/PET_Recycling_Symbol.png" width="100" align="middle">



There are some challenges to working with PET plastic. A few these are described below. Follow the links to get more detailed information on these and other challenges:

* **Crystalization** - PET crystalizes when cooled slowly. To avoid making filament that is brittle like glass, a water bath is used.
* **Low Viscosity** - When PET melts it has a low viscosity and a low melt strength which makes it difficult to pull into a filament with an even diameter. The Thunderhead uses a cooling tube to help increase the viscosity and melt strength before the plastic leaves the extruder. The water bath also helps to 
* **Hygroscopicity** - PET pulls water out of the air and holds on to it. This water can cause problems during extrusion and printing such as air bubbles, foaming and degredation of the plastic.
* **Hydrolysis** - The polymer chains in PET can break down in the presence of water at elevated temperatures. When this happens, the viscosity of the melt is reduced, making it difficult to extrude. To Avoid this problem, the plastic flakes must be thoroughly dried just before extrusion. 





## Safety and Liability

You are responsible for your own safety. This machine is under development. Please see the text in the license regarding **Disclaimer of Warranties and Limitation of Liability**.



## Building the Thunderhead

Please refer to our [wiki](https://github.com/TechforTrade/Thunderhead-Filament-Extruder/wiki) for detailed information on building the Thunderhead. 

#### Major Tools Needed ####

Note that you don't necessarily have to own all of these tools. A local shop could do some of the work for you. Especially the lathe and milling work. See the Wiki for a more exhaustive list.

* Drill Press
* Metal Lathe - Threading the barrel and making the shaft for the gear box
* Welding (stick, oxy-acetalene, etc.) - For welding frames together
* 3D printer - Many of the complex parts in the machine are 3D printed
* Milling Machine (optional) - For milling flats into a few parts. Could be done with grinder and hand files though more time consuming.
* Horizontal band saw (optional) - For cutting stock metal to size. A hacksaw and vice will work, but will be slower.


#### Major Components of the Thunderhead

<img src="./img/Extruder_Components.jpg" width="800" align="middle">

1. **Control Box** - Contains the power supply, Arduino, and other circuitry needed to operate the extruder. Note: The starve feeder, diameter sensors and spooler have their own control circuitry and communicate with the master Arduino via IIC.
2. **Starve Feeder**- Used to add flakes to the extruder at a constent rate. Subcomponents are:
   1. Hopper - Holdes flake ready to be extruded
   2. Vibratory Conveyer - Moves flake to the balance and keeps flake from bridging, and rat holing.
   3. Balance - Weighs out small portions of flake and then delivers them to the extruder at a constant rate. Feedback from the balance controls the vibratory conveyer.
3. **Auger Motor and Gear Box** - A large NEMA 42 stepper motor and 3:1 gear box with 3D printed gears. The stepper alows for speed control and the gearbox increases the torque on the auger.
4. **Extruder Body** - The extruder body has many components. The main components are:
   1. Feed Throat - Location where the plastic enters the barrel. Made with internal grooves to improve the feeding of the plastic into the barrel.
   2. Auger - A 1/2 in. diameter, 18 in. long wood auger used to convey the plastic through the barrel. NOTE: This is not designed for plastics extrusion and performs significantly worse than a plastic extrusion screw would. It is much less expensive though.
   3. Barrel - 1/2in I.D. DOM metal pipe through which the auger pushes the plastic. It has two heating zones that are heated by 104 watt 1/2 in. fiberglass insulated heating tape.
   4. Breaker plate - A small disk of metal with a number of holes drilled into it at the downstream end of the barrel. It acts to reduce the twist in the plastic that is caused by the screw, reducing what is called "screw beat" and improving the uniformity of the diameter. 
   5. Cooling tube - A brass tube at the end of the barrel that reduces the temperature of the plastic melt in order to increase its viscosity. The bend in the tube helps to aim the filament at the guide roller at the end of the water bath and improve roundness of the filament. It has two heating zones.
   6. Nozzle - determines diameter of melt as it leaves the extruder. Equiped with its own heating zone so that surface quality of the filament can be improved.
   7. Fume hood - Used to collect fumes given off by the extruder and channel them into a tube.
5. **Extruder Stand** - Supports the extruder. 
6. **Diameter Sensors** - Non contact laser diameter sensors with their own control electronics. The first is used to determine the diameter of the melt as it leaves the extruder and control the speed of the outfeed rollers in order to maintain a constant diameter. The second is used to monitor the final diameter and ensure that the set point of the first diameter sensor is correct.
7. **Water Bath** - Used to cool the melt quickly. This is important because otherwise, the PET would neck down to a very small diameter or cool too slowly and crystalize. Crystalized plastic is too brittle to work with a 3D printer.
8. **Outfeed Rollers** - Used to pull the filament through the water bath. Their speed determines the diameter of the filament. The rollers are controlled by the primary diameter sensor.
9. **Spooler** - Winds the filament up onto a spool. The spooler is still being worked on, early designs fought with the outfeed rollers and caused uneven filament diameters.




## Software

Please refer to our [wiki](https://github.com/TechforTrade/Thunderhead-Filament-Extruder/wiki) for detailed information on the use of the various bits of code kept in this repository.

Five firmware installations must be completed to get the Thunderhead up and running. These are:

- **Thunderware.ino** - for the Arduino mega 2560 that controls the machine (located in the controller box)
- **StarveFeeder.ino** - Upload to the Arduino Nano that controls the starve feeder.
- **Diameter_Sensor.ino (x2)** - Install on <u>both</u> the primary and QC diameter sensor Arduino Nanos.
- **Spooler.ino** - Upload to the Arduino Nano that controls the spooler.

Additionally, there is code written in Processing called **Extruder_Data_visualizer.pde** that produces real time graphs of the the output of the diameter sensors as well as the outfeed roller RPM. This can be useful for tuning the PID in the primary diameter sensor that controls the filament diameter.



## Operation

Detailed operation instructions with tips and trouble shooting are located in our [wiki](https://github.com/TechforTrade/Thunderhead-Filament-Extruder/wiki). The following summarizes basic operation. Video of this process can be found here.

#### Preparation

Before extruding, the clean PET flake must be dried. This must happen just before extruding because the PET will absorb water out of the air at room temperature. Dry the PET in a bench top oven (toaster oven) at a temperature between 150 and 170 °C for four hours. Do this in a well ventilated area. It is recomended to capture and vent the fumes with a fume hood and duct. Do not exceed 175 °C as the plastic will begin to degrade. Keep the flake in the oven until the extruder is ready to begin extruding so that the flake is exposed to room temperature air for as little time as possible.

#### Extruding

Steps

1. Power up the extruder. 
2. Select the menu option "Select Profile". For this and all following steps:
   1.  'A' is used to scroll up.
   2.  'B' is used to scoll down.
   3.  'C' is used to select.
3. Select the profile you want.
4. Select "Extrude".
   1. The extruder will enter the Preheat state, and warm the heating zones to the initial set temps.
5. When the initial set temps have been reached, the extruder will automatically enter the Soak state and soak for the number of minutes specified in the profile.
6. While the extruder is in the Soak state do the following:
   1. Remove the plastic from the oven and add it to the hopper.
   2. Home the balance by rotating the balance counter clockwise as far as it will go and then selecting "Home Balance" from the menu.
   3. Select "Feed Plastic" to turn the vibratory conveyer on.
   4. Turn the vibratory conveyor off when the flake has moved to then end of the conveyor and is about to begin filling the bucket by selecting "Feed Plastic" again.
7. At the end of the Soak state (default time is 8 minutes) the extruder will automatically enter the Extrude state.
8. Turn on the starve feeder by selecting "Starve Feeder".
9. When plastic begins to flow out of the nozzle, use the start up tool to guide the filament under the guide roller in the water bath and then place the filament between the outfeed rollers.
10. Reduce the temperatures to the extruding temperatures (the cooling tube and nozzle temps are lowered) by selecting  "Set Extrude Temps" from the menu.
11. Increase the diameter of the filament to the desired diameter by reducing the outfeed RPM. Do this by selecting "Outfeed RPM" and entering the desired rpm (typically around 18).
12. Clip off the initial section of filament that is not of the correct diameter.
13. Load the filament into the spooler and turn it on. 
14. If desired, automatic control of the outfeed roller rpm can be engaged by selecting "OF Mode". It will change from "man" to "auto". The rpm of the outfeed rollers will now be automatically adjusted to maintain the "Dia Setpoint".

#### Stopping the Extruder

At any point during the extrusion (including preheat and soak) the extruder can be stopped by pressing 'D'. You will be asked to confirm by pressing 'A' or cancel by pressing 'B'. The machine can also simply be powered off.



## Contributing

We'd love your help! You can contribute in many ways. Here are a few:

* Technical support on designs, code etc.
* Help improve the wiki and other documentation.
* Testing. Different Extrusion parameters, code, etc.
* Connect us with other interested individuals and groups.
* Donate! [Techfortrade](http://www.techfortrade.org/) is a non profit organization working to create business opportunities in low resource settings.





## On Going Work

All the of the most up to date CAD files can be found [here on our GrabCAD Workbench](https://workbench.grabcad.com/workbench/projects/gcvN9Xsi01SW-lFGhJRj_-4vqndCMFAaoUt_-UQBdidnVn#/space/gc8b8c582LagITdwrMEId6wysTlJX_nukUvWoRwEQ_1f4U).



## Planned Improvements and Experiments ##

#### Drying hopper ####
Currently the plastic is dried and then put into the hopper where it sits and
absorbs moisture. With a drying hopper, the plastic would be continuously dried
and would have no chance to absorb moisture before entering the machine. This
may help improve the melt viscosity and consistency by reducing the amount of polymer
hydrolysis.



#### New Filament support/guiding strategy ####
The shape and diameter of the filament is essentially set when the hot plastic
enters the water bath. Unwanted movement of the filament down stream from this
point can greatly impact the shape of the filament. New strategies for guiding
the filament in a controlled manner need to be explored. 



#### Nozzle Geometry and Drawdown ####
It may be fruitful to explore different nozzle geometries and the amount and
rate of drawdown. What are the optimal conditions for consistent filament?



#### Test different sources of PET ####
Not all PET resins are the same. By testing resins from various bottle sources
and even virgin pellets, it may be possible to determine whether or not some
sources have more desirable characteristics than others.



#### Melt Filter ####
A screen should be added just up stream of the breaker plate. This screen will
catch debris and improve the quality of the filament. A down side is that a melt filter may reduce, perhaps greatly, the output of the machine.



#### Explore potential additives

Desiccating agents such as CaO (quicklime) or even Portland cement might
possibly be added to scavenge water remaining in the melt, which would help
improve viscosity. Nucleating agents such as sodium benzoate and talc might be
used to encourage crystal growth, growing more numerous and smaller crystals
which may help to reduce the brittleness of crystalline polymer. Could this be a route to producing printable crystalline PET?

 

## Maintainers

[Matthew Rogge](https://github.com/Maaphoo) and [Michael Uttmark](https://github.com/biosafetylvl5) are currently the maintainers of this
repository.



## Acknowledgements

The following people and organizations provided valuable help and guidance over
the course of the project:

**Matt Clark** who provided hundreds of free man hours to assist with the re-design process.

**Frank Schoofs** who volunteered his material science expertise to assist with thermal modeling required to design heating and cooling sections of the extruder.

**Vasileios Grammatikakis** an electronics expert who has assisted with improvements to the Thunderhead electronics.

**Unilever plc.** whose PET specialists have provided insights into working with PET, drying, and testing.

## 

## License

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a>
This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
