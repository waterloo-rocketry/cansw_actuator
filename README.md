### Actuator Board Control Software

Runs on the actuator PCB (used to be called the vent board). To load code onto the board:
* Open MPLAB X
* Connect a PICKIT 3 to your computer via USB
* Line up the PICKIT cable such that the red wire lines up with A) the arrow on the PICKIT, and B) the MCLR marking on the board.
* Power the board through the 5V canbus input. The power from the PICKIT is not sufficient to power the entire board.
* If desired, supply 9V to the 2-pin JST connector on the board in order to power the actuator.
* Load the code onto the board using MPLAB.

After you do work on a feature, submit a pull request. When merging an approved pull request, please squash merge and enter a meaningful commit message encompassing the entire pull request. If GitHub doesn't let you do this, please do it at the command line using `git merge --squash`. Branches can be deleted once they have been merged, though it may be wise to keep the branch for a while in case something is broken and the merge needs to be reverted.
