# Thunderhead

Thunderhead is a PET extruder designed by TechforTrade for producing filament
for use in 3D printing. A special emphasis throughout the design has been placed
on using affordable and easily attinable materials.
This repository serves as a host for documentation and as a snapshot of the
development being done on our
[GrabCAD Workbench](https://workbench.grabcad.com/workbench/projects/gcvN9Xsi01SW-lFGhJRj_-4vqndCMFAaoUt_-UQBdidnVn#/space/gc8b8c582LagITdwrMEId6wysTlJX_nukUvWoRwEQ_1f4U).

## Software

The software that faccilitates the use of Thunderheadand its accompaning
documentation can be found [here](https://github.com/Maaphoo/Thunderware).

## Hardware

# Overview

This is Thunderhead:

![Thunderhead](./img/Thunderhead.png)

Thunderhead turns this:

![Shedded PET](./img/shredded_pet.jpg)

Into this:

![IMAGE HERE]()

It does this by

1. Melting PET
2. Pushing it through a very small hole (4mm)
3. Pulling the filament that comes out through a water bath to cool the plastic down
4. Winding the plastic up on a spool for future use
5. Repeating

In order to make the documentation more paletable, from here on the
machine will be described in parts.

## Extruder

![Extruder](Extruder)

The most important part of Thunderhead is the extruder. Driving by a !SPEC HERE!
stepper motor, Thunderhead pushes shredded PET through a heated barrel with an auger
which causes the plastic to melt. This melted plastic is then pushed out of a hole
with a diameter of 5mm.

### Stepper
229$ for motor and 160 driver (driver KL-2283)
A **NEMA42** stepper with a touque rating of 4100 *oz*/*in* is used.
Although this is hard to source locally, we rationalize
our choice with the following points:

1. More touque == More better. With a higher tourque, we can move at higher speeds without the fear of skipped steps.
2. It's easy to use, and very robust.
3. Variable frequence drives are commonly more expensive and their extra tourque is not needed.

(A **NEMA34** has been show to be a usuful alternative, and due to its relativly
very low cost, it is a hard constestant for the spotlight.)

### Auger

Auger is a half inch diameter 18 inch long ship auger deisgned for drilling
holes in wood. Easy to obtain, low cost (22$) and very robust,
work very well when one considers that they are not designed for plastic
extrusion. While a properly deisgned screw (a plastic extrusion screw)
would work better, we have found these augers to be quite practical.

### Heat

![Heating zones]()

#### Heating Zones

The barrel of the extruder has a total of 5 heating zones, two on the barrel,
two on the cooling tube and one on the nozzle. Each heating zone has its own
temperature sensor and control circuitry allowing the temperatures to be set
independently of each other. The first two heating zones on the barrel are
typically set near 265°C.  High temperature fiberglass insulation is used to
reduce heat loss.

At the end of the barrel, the plastic makes a 90° turn and heads straight down
inside of the cooling tube. This tube with its two heating zones is held at a
temperature of around 195 °C. The idea is to cool the plastic as much as possible
before it leaves the nozzle. The nozzle has the final heating zone, and can be
set to a higher temperature to help improve the surface finish of the plastic
and possibly improve the flow of plastic near the inside walls of the nozzle.
This granular control help obtain plug flow (as opposed to laminar flow.)

Laminar Flow:
![Laminar Flow]()
Plug Flow:
![Plug Flow]()

This is done by decreasing the outside viscocity (through heat) and increasing
the inside viscocity by cooling it (via the cooling stages).

#### Heaters

The first two zones are 1/2" by two feet long tape heater. The 104W tape heaters are
fibreglass insulated nichrome wire which can be run on 110 or 220 VAC. They are purchased
from briskheat and are sutible for use on an electrical conductive surface. They are
rated up to 700°C which is much higher than our current need, allowing us to make design
changes without worrying about heat. In the future it maybe worthwile to change
to a bandheater for cost reasons.

#### Thermistors

#### Control


### Breaker Plate & Fume Control

Between the end of the barrel and the cooling tube is the breaker plate, which
helps to straighten the flow of the polymer. The rotation of the screw creates
a twist in the polymer, which it would “remember” were there no breaker plate.
This twist causes wavy corkscrew shaped filament.

Finally, the extruder has a sheet metal cover, which captures fumes and channels
them into an exhaust duct.

### End

While the recommended diameter of the final output is 1/2 half of the diameter
of the preceding pipe (giving us a diameter of 3mm), we have had problems with an
unsufficant neck-down distance. (This is the distane that the plastic naturally
decreases in diameter due to tension.) As such, we have an final extrusion diameter of 4mm.

## Starve Feeder

![Starve Feeder]()

The extruder is fed by a starve feeder. Using a vibratory conveyor, PET is fed to
the extruder at a precise rate. This is done with spring steel (sections of cut tape measure)
and a motor with an of center weight.

## Water Bath

![Water Bath]()

PET plastic crystalizes if it cools too slowly. Crystallization causes the plastic
to become more brittle and opaque which are not desired qualities in PET 3D
printer filament. To avoid crystallization, the plastic is extruded straight
into a water bath where the temperature of the plastic is reduced fast enough
to avoid crystallization.

### Guides

There are 7 guide wheels in the water bath that hold
the filament in a straight line as it passes through the water bath. The first
is a large aluminum disk with a grooved edge. It spins with a tangential velocity
matching the velocity of the filament, which helps to avoid skipping that is
observed when the wheel is stationary. The other guides are v-grooved rollers
(though they don’t spin). They guide the filament while allowing bumps and
bends to pass without hanging up.

## Out Feed

The outfeed is used to pull the filament through the water bath and control its
diameter (see Figure 4 for image). It consists of a diameter sensor and a set of
rollers driven by a stepper motor. The diameter sensor will be located just
below the nozzle and the outfeed rollers are located at the end of the water bath.

Ideally, if the extruder were to extrude at a constant rate, the outfeed could
be set at a corresponding constant rate to achieve the desired filament diameter
by drawing down the hot plastic. The diameter sensor could be placed near the
outfeed rollers and used to make sure the rollers are running at the correct
speed. Due to the non-uniform nature of the bottle flake and the lack of a
screw designed for plastic extrusion (among other possible issues), the rate at
which plastic leaves the extruder varies and thus the required outfeed roller
speed required to obtain the desired diameter also varies.

The diameter sensor will be used to determine if the outfeed roller speed needs
to be adjusted to keep the filament within the desired tolerance. To be effective,
it needs to be located where the plastic is being drawn down. This is just under
the nozzle where the plastic is molten. The diameter sensor thus must be able to
make measurements without contacting the filament and must be waterproof. It is
currently under development [here](LINKHERE) and utilizes a laser and Charge
Coupled Device (CCD) array.

## Spooler

The spooler winds the filament onto a spool after it leaves the outfeed.
It is equipped with a sensor that measures the tension on the filament.
A proportional integral derivative (PID) controller adjusts the speed of the
spooler to maintain a constant tension.

## On Going Work

All the present files can be found
[here on our GrabCAD Workbench](https://workbench.grabcad.com/workbench/projects/gcvN9Xsi01SW-lFGhJRj_-4vqndCMFAaoUt_-UQBdidnVn#/space/gc8b8c582LagITdwrMEId6wysTlJX_nukUvWoRwEQ_1f4U).

## Maintainers

[Matthew Rogge](https://github.com/Maaphoo) and
[Michael Uttmark](https://github.com/biosafetylvl5) are currently the
maintainers of this repository.

## License
This work is licensed under the Creative Commons Attribution 4.0 International
License. To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
