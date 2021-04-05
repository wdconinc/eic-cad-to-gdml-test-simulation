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
//g
/// \file persistency/gdml/G02/src/G02DetectorConstruction.cc
/// \brief Implementation of the G02DetectorConstruction class
//
//
//
// Class G02DetectorConstruction implementation
//
// ----------------------------------------------------------------------------

#include "G02DetectorConstruction.hh"

// Geant4 includes
//
#include "globals.hh"
#include "G4GeometryManager.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4AutoDelete.hh"

// GDML parser include
//
#include "G4GDMLParser.hh"

// Magnetic fields
#include "G02FieldSetup.hh"

// Constants and units
//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructor
//
G02DetectorConstruction::G02DetectorConstruction(const G4String& filename)
  : G4VUserDetectorConstruction(),
    fFileName(filename)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Destructor
//
G02DetectorConstruction::~G02DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructs geometries and materials
//
G4VPhysicalVolume* G02DetectorConstruction::Construct()
{
  // Writing or Reading of Geometry using G4GDML

  G4VPhysicalVolume* fWorldPhysVol;

  // ACTIVATING OVERLAP CHECK when read volumes are placed.
  // Can take long time in case of complex geometries
  //
  // fParser.SetOverlapCheck(true);

  fParser.Read(fFileName);

  // READING GDML FILES OPTION: 2nd Boolean argument "Validate".
  // Flag to "false" disables check with the Schema when reading GDML file.
  // See the GDML Documentation for more information.
  //
  // fParser.Read(fFileName,false);

  // Prints the material information
  //
  G4cout << *(G4Material::GetMaterialTable() ) << G4endl;

  // Giving World Physical Volume from GDML Parser
  //
  fWorldPhysVol = fParser.GetWorldVolume();

  // Set Visualization attributes to world
  //
  G4VisAttributes* BoxVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  fWorldPhysVol->GetLogicalVolume()->SetVisAttributes(BoxVisAtt);

  return fWorldPhysVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructs geometries and materials
//
void G02DetectorConstruction::ConstructSDandField()
{
  // Construct the field creator - this will register the field it creates
  if (!fFieldSetup.Get()) {
    G02FieldSetup* fieldSetup
       = new G02FieldSetup(G4ThreeVector(0.0, 0.0, 3.0*tesla));
    G4AutoDelete::Register(fieldSetup); // Kernel will delete the G02FieldSetup
    fFieldSetup.Put(fieldSetup);
  }
}
