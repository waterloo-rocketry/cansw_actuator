### Vent Board Control Software

Runs on the vent PCB (GYOZA). To load code onto the board:
* Open MPLAB X
* Connect a PICKIT 3 to your computer via USB
* Line up the PICKIT cable such that the red wire lines up with A) the arrow on the PICKIT, and B) the MCLR marking on the board.
* Power the board through the 5V bus input. The power from the PICKIT is not sufficient to power the entire board.
* Connect a separate 12V power source to the large screw terminal at the bottom of the board. This powers the linear actuator and its control circuitry.
* Load the code onto the board using MPLAB.
