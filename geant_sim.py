from geant4_pybind import *

import math
import sys


class DetectorConstruction(G4VUserDetectorConstruction):
    def __init__(self):
        super(DetectorConstruction, self).__init__()


class PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):
    def __init__(self):
        super(PrimaryGeneratorAction, self).__init__()


detector = DetectorConstruction()
G4RunManager.SetUserInitialization(detector)
physicsList = G4EmDNAPhysics_option2()
G4RunManager.SetUserInitialization(physicsList)
G4RunManager.SetUserAction(PrimaryGeneratorAction())

G4RunManager.Initialize()