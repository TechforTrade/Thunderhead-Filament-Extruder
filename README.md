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

1. Melting the PET
2. Shoving it through a very small hole (1.75mm)
3. dragging the filament that comes out through a water bath to cool the plastic down
4. Winding the plastic up on a spool for future use
5. Repeating

In order to make the documentation more paletable, from here on the machine will be described in parts.

## Extruder

![Extruder](Extruder)

The most important part of Thunderhead is the extruder. Driving by a !SPEC HERE!
stepper motor, Thunderhead pushes shredded PET through a heated barrel with a auger
which causes the plastic to melt. This melted plastic is then pushed out of a hole
with a diameter of 5mm.

### Stepper
229$ for motor and 160 driver (driver KL-2283)
A **NEMA42** stepper with a touque rating of 4100 *oz/in* is used. Although this is hard to source locally, we rationalize
our choice with the following points:

1. More touque == More better. With a higher tourque, we can move at higher speeds without the fear of skipped steps.
2. It's easy to use, and very robust.
3. Variable frequence drives are commonly more expensive and their extra tourque is not needed.

(A **NEMA34** has been show to be a usuful alternative, and due to its relativly
very low cost, it is a hard constestant for the spotlight.)

### Auger

### Heat

#### Zones

The areas that need to be heated are split into five zones. They are as follows:

1. The first heating zone
2. The second heating zone
3. The first cooling zone
4. The final cooling zone
5. The final heating zone

Plug flow vs laminar flow

higher inside viscocity and lower outside

better surface tension



![Heating zones]()

##### Heating Zones

As the name implies, the heating zones heat the plastic up to 260°C, the melting point of PET. However, the last zone is special, occupying position five, which is directly after the cooling zones.

Zone five

##### Cooling Zones

After the first two intial heating zones, the plastic enter the "cooling zones". However, rather
unintuitively, the cooling zones are heated much like the heating zones. But, instead of the 260°C, these zones
are heated to 200°C. This allows the plastic to cool some before it enters the water,
reducing the required length for the waterbath length.

#### Heaters

#### Thermresistors

#### Control

### Out

While the recommended diameter of the final output is 1/2 half of the diameter
of the preceding pipe (giving us a diameter of 3mm), we have had problems with an
unsufficant neck-down distance. (This is the distane that the plastic naturally
decreases in diameter due to tension.) As such, we have an final extrusion diameter of 5mm.

## Starve Feeder

![Starve Feeder]()

The extruder is fed by a starve feeder. Using a vibratory conveyor, PET is fed to
the extruder at a precise rate. This is done with spring steel (sections of cut tape measure)
and a motor with an of center weight.

## Water Bath

![Water Bath]()

The water bath cools the PET after it is extruded. How it does this is a bit complicated,
and involves a guiding system, a large aluminium roller and a motorized out feed. Let's
take it in steps.

### Wheel

### Guides

### Out Feed

## On Going Work

All the present files can be found [here on our GrabCAD Workbench](https://workbench.grabcad.com/workbench/projects/gcvN9Xsi01SW-lFGhJRj_-4vqndCMFAaoUt_-UQBdidnVn#/space/gc8b8c582LagITdwrMEId6wysTlJX_nukUvWoRwEQ_1f4U).

## Maintainers

[Matthew Rogge](https://github.com/Maaphoo) and [Michael Uttmark](https://github.com/biosafetylvl5) are currently the maintainers of this repository.

## License
This work is licensed under the Creative Commons Attribution 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
