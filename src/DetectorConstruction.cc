#include"DetectorConstruction.hh"
#include"SensitiveDetector.hh" 
#include<G4NistManager.hh>
#include<G4Box.hh>
#include<G4Tubs.hh>
#include<G4LogicalVolume.hh>
#include<G4PVPlacement.hh>
#include<G4SDManager.hh>
#include<G4VisAttributes.hh>
#include<G4SystemOfUnits.hh>
using namespace std;

#define Mat(x) (G4NistManager::Instance()->FindOrBuildMaterial(x))


World::World(double size_x, double size_y, double size_z,  G4Material *mater_): mater(mater_), sizex(size_x), sizey(size_y), sizez(size_z)
{
	//double size05 = size/2;
	solid = new G4Box("world", sizex/2, sizey/2, sizez/2);
	logic = new G4LogicalVolume( solid, mater, "World", 0, 0, 0);
	physic = new G4PVPlacement(0, G4ThreeVector(), logic, "World",
				   0, false, 0);             
}

DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{

  G4NistManager* nist = G4NistManager::Instance();

  world = new World(5*um, 5*um, 5*um, Mat("G4_Galactic"));

  G4double temperature = 10. * kelvin;

  
  G4Material* water = nist->BuildMaterialWithNewDensity("Water", "G4_WATER", 0.900 * g / cm3, temperature);

  // G4Material* carbondioxide = nist->BuildMaterialWithNewDensity("carbondioxide", "G4_CARBON_DIOXIDE ", 1.561 * g / cm3, temperature);
  
  // G4Material* solidmethane = nist->BuildMaterialWithNewDensity("solidmethane", "G4_METHANE", 0.561 * g / cm3, temperature);
  
  // G4Material* carbonmonooxide = new G4Material("CO", 0.789 * g / cm3, 2, kStateSolid, temperature);
  // carbonmonooxide->AddElement(nist->FindOrBuildElement("C"), 1);
  // carbonmonooxide->AddElement(nist->FindOrBuildElement("O"), 1);

  // G4Material* methanol = nist->BuildMaterialWithNewDensity("methanol", "G4_METHANOL", 0.640 * g / cm3, temperature);
  
  // G4Material* Ice = new G4Material("Ice", 0.946*g/cm3, 4);
  // Ice->AddMaterial(water, 62.5 * perCent);
  // Ice->AddMaterial(carbonmonooxide, 18.75 * perCent);
  // Ice->AddMaterial(carbondioxide, 12.5 * perCent);
  // Ice->AddMaterial(methanol, 6.25 * perCent);

  G4Box *solidIce = new G4Box("solidIce", 100*um, 100*um, 0.5*um);
  G4LogicalVolume *logicIce = new G4LogicalVolume(solidIce, water, "logicIce");
  G4PVPlacement *physicIce = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicIce,
					       "physicIce", world->getLogic(), false, 0);
  
  G4Box *solidDet = new G4Box("solidDet", 100*um, 100*um, 10*um);
  G4LogicalVolume *logicDet = new G4LogicalVolume(solidDet, Mat("G4_Ag"), "logicDet");
  G4PVPlacement *physiDet = new G4PVPlacement(0, G4ThreeVector(0,0,-10*um), logicDet,
					      "physiDet", world->getLogic(), false, 0);

  
  SensitiveDetector *detector = new SensitiveDetector("hi there");
  
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->AddNewDetector(detector);
  logicIce->SetSensitiveDetector(detector);
  
  world->getLogic()->SetVisAttributes (G4VisAttributes::GetInvisible());
  
  return world->getPhysic();
}
