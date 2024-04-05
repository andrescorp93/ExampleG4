#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingVerbose.hh"
#include "PhysicsList.hh"
#include<G4RunManager.hh>
#include<G4UImanager.hh>
#include<G4UIterminal.hh>
#include<G4VisExecutive.hh>
#include "G4UIExecutive.hh"
#include<G4Material.hh>
#include<G4UserRunAction.hh>
#include<G4Run.hh>
#include<iostream>
#include<string>
#include<CLHEP/Random/Random.h>
#include<time.h>
using namespace std;

const char macros[]="vis.mac";

class RunAction: public G4UserRunAction
{
public:
  void BeginOfRunAction(const G4Run* aRun)
  {
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  }
};

int main(int argc,char** argv)
{
	G4UIExecutive* ui = 0;

	G4VSteppingVerbose::SetInstance(new SteppingVerbose);
	CLHEP::HepRandom::setTheSeed(time(0)+getpid());

	G4RunManager * runManager = new G4RunManager;
	DetectorConstruction* detector_c = new DetectorConstruction;
	runManager->SetUserInitialization(detector_c);

	G4VUserPhysicsList *p = new PhysicsList;
	runManager->SetUserInitialization(p);
	
	if (argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
  
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
   
	runManager->SetUserAction(new PrimaryGeneratorAction(detector_c));
	runManager->SetUserAction(new RunAction);  

	runManager->Initialize();

	cout<<"===============================================================";
	cout<<endl;
	cout<< *(G4Material::GetMaterialTable()) << endl;
	cout<<"===============================================================";
	cout<<endl;
      
	G4UImanager * UI = G4UImanager::GetUIpointer();  
	if (ui)
	{
		UI->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UI->ApplyCommand(command + fileName);
	}

	delete visManager;
	delete runManager;

	return 0;
}
