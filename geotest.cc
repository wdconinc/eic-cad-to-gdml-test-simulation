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
/// \file persistency/gdml/G02/geotest.cc
/// \brief Main program of the persistency/gdml/G02 example
//
//
//
//
// --------------------------------------------------------------
//      GEANT 4 - geotest
//
// --------------------------------------------------------------

// Geant4 includes
//
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "globals.hh"

// A physics list factory
//
#include "G4PhysListFactory.hh"

// Example includes
//
#include "G02DetectorConstruction.hh"
#include "G02ActionInitialization.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// --------------------------------------------------------------

int main(int argc, char** argv)
{
  // Parse command line
  G4String gdmlfile("eic-cad-to-gdml-test-detector.gdml");
  G4String physlist("QGSP_BERT");
  G4String particle("e-");
  G4String macro("");
  G4int threads = 0;
  for (G4int i = 1; i < argc; ++i) {
    if      (G4String(argv[i]) == "-g") gdmlfile = argv[++i];
    else if (G4String(argv[i]) == "-l") physlist = argv[++i];
    else if (G4String(argv[i]) == "-p") particle = argv[++i];
    else if (G4String(argv[i]) == "-m") macro = argv[++i];
    else if (G4String(argv[i]) == "-t") threads  = atoi(argv[++i]);
    else return 0;
  }

  // Construct a run manager
  //
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::MT);
  if (threads > 0) runManager->SetNumberOfThreads(threads);

  // Set mandatory initialization and user action classes
  //
  G4PhysListFactory factory;
  if (! factory.IsReferencePhysList(physlist)) return 1;
  runManager->SetUserInitialization(factory.GetReferencePhysList(physlist));
  runManager->SetUserInitialization(new G02DetectorConstruction(gdmlfile));
  runManager->SetUserInitialization(new G02ActionInitialization(particle));

  // Initialize G4 kernel
  //
  runManager->Initialize();

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Open a UI session: will stay there until the user types "exit"
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() == 0 )   // Automatically run default macro for writing...
  {
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }
  else             // Interactive, provides macro in input
  {
    UImanager->ExecuteMacroFile(macro);
  }

  // Job termination
  //
  delete visManager;
  delete runManager;

  return 0;
}
