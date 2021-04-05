//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file persistency/gdml/G02/src/G02PrimaryGeneratorAction.cc
/// \brief Implementation of the G02PrimaryGeneratorAction class
//
//
//
// Class G02PrimaryGeneratorAction implementation
//
// ----------------------------------------------------------------------------

#include "G02PrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G02PrimaryGeneratorAction::G02PrimaryGeneratorAction(const G4String& particlename)
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0),fParticleTable(0),
   fMessenger(0),fThetaMin(0),fThetaMax(2*CLHEP::pi)
{
  // Particle gun and particle table
  //
  fParticleGun = new G4ParticleGun();
  fParticleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = fParticleTable->FindParticle(particlename);
  if (particle) fParticleGun->SetParticleDefinition(particle);
  else {
    G4cerr << "Unknown particle name " << particlename << G4endl;
    fParticleTable->DumpTable();
    exit(1);
  }

  // Messenger
  //
  fMessenger = new G4GenericMessenger(this, "/G02/primary/", "Primary Generator Action");
  fMessenger->DeclarePropertyWithUnit("thetamax","deg",fThetaMax,"Maximum generation phi angle");
  fMessenger->DeclarePropertyWithUnit("thetamin","deg",fThetaMin,"Minimum generation phi angle");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G02PrimaryGeneratorAction::~G02PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Scattering angles
  G4double en = G4RandFlat::shoot(1*GeV, 10*GeV);
  G4double th = acos(G4RandFlat::shoot(cos(fThetaMax), cos(fThetaMin)));
  G4double ph = G4RandFlat::shoot(0.0, 2*CLHEP::pi);
  G4ThreeVector r(0, 0, 0);
  G4ThreeVector u(sin(th)*cos(ph), sin(th)*sin(ph), cos(th));

  fParticleGun->SetParticleEnergy(en);
  fParticleGun->SetParticlePosition(r);
  fParticleGun->SetParticleMomentumDirection(u);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
