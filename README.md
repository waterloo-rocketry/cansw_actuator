### Vent Board Control Software

Runs on the vent PCB (GYOZA). To load code onto the board:
* Open MPLAB X
* Connect a PICKIT 3 to your computer via USB
* Line up the PICKIT cable such that the red wire lines up with A) the arrow on the PICKIT, and B) the MCLR marking on the board.
* Power the board through the 5V bus input. The power from the PICKIT is not sufficient to power the entire board.
* Connect a separate 7.4V power source to the large screw terminal at the bottom of the board. This powers the linear actuator and its control circuitry.
* Load the code onto the board using MPLAB.

After you do work on a feature, submit a pull request and add Alex and Aaron as reviewers. When merging an approved pull request, please squash merge and enter a meaningful commit message encompassing the entire pull request. If GitHub doesn't let you do this, please do it at the command line using `git merge --squash`. Branches can be deleted once they have been merged, though it may be wise to keep the branch for a while in case something is broken and the merge needs to be reverted.

### Update to v2
#### Notes
Just Kaelan's (who is updating this codebase for vent board v2) notes on requirements for the updates.

* We have gone from needing a linear actuator to control the valve to the valve being a solenoid
  * Therefore we dont get any feedback from the valve
  * And we use a pin that goes high or low to activate the solenoid instead of whatever complicated controls were needed for linac

* there are some pullup resistors for a limit switch, those are so we can use board for more, not needed in code.

#### TODO:
* error checks
