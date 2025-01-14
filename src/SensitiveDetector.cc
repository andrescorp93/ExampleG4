#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include"SensitiveDetector.hh"
#include<G4SystemOfUnits.hh>
#include"G4VProcess.hh"
#include<G4ParticleGun.hh>

using namespace std;
std::ofstream posfile;



SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name),
						     HIST_MAX(5.*keV),
						     HIST_MIN(0*keV)
{
    posfile.open("distribution.dat");
    posfile << "partID" << "\t" << "trackID" << "\t" << "partname" << "\t" << "procName" << "\t" << "denergy, eV" << "\t" << "positionX, um" << "\t" << "positionY, um" << "\t" << "positionZ, um" << std::endl;
    posfile.close();
  for(int i = 0; i<NOBINS; i++)
    histogram[i] = 0;
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* hist)
{
  G4ThreeVector position = step->GetTrack()->GetPosition();
  // double kinenergy = step->GetTrack()->GetKineticEnergy() / eV;
  double denergy = step->GetTotalEnergyDeposit() / eV;
  // double nonionenergy = step->GetNonIonizingEnergyDeposit() / eV;
  posfile.open("distribution.dat", ios::app);
  G4int partID = step->GetTrack()->GetParentID();
  G4int trackID = step->GetTrack()->GetTrackID();
  G4String partname = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4StepPoint* postPoint = step->GetPostStepPoint();
  G4String procName = postPoint->GetProcessDefinedStep()->GetProcessName();
  if (denergy > 0){
  // posfile << partID << "\t" << trackID << "\t" << partname << "\t" << procName << "\t" << kinenergy << "\t" << denergy << "\t" << nonionenergy << "\t" << position.getX() / um << "\t" << position.getY() / um << "\t" << position.getZ() / um << std::endl;}
  posfile << partID << "\t" << trackID << "\t" << partname << "\t" << procName << "\t" << denergy << "\t" << position.getX() / um << "\t" << position.getY() / um << "\t" << position.getZ() / um << std::endl;}
  posfile.close();
  double energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  int index = int(floor((energy-HIST_MIN)/bin_width));
  if(index >= 0 && index < NOBINS)
    histogram[index]++;

  //step->GetTrack()->SetTrackStatus(fStopAndKill);
  return true;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}



SensitiveDetector::~SensitiveDetector()
{
    
    std::ofstream file("spectrum.dat");
  
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  for(int i = 0; i<NOBINS; i++)
  {
    double energy = i*bin_width + HIST_MIN;
    file << std::setw(15) << energy/keV << "\t"
	 << std::setw(15) << histogram[i] << std::endl;
  }
}
