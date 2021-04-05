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
/// \file persistency/gdml/G02/include/G02DetectorConstruction.hh
/// \brief Definition of the G02DetectorConstruction class
//
//
//
// Class G02DetectorConstruction
//
// A detector construction class loading the geometry from GDML files.
//
// ----------------------------------------------------------------------------

#ifndef G02DetectorConstruction_H
#define G02DetectorConstruction_H 1


#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"
#include "G4Cache.hh"

#include "globals.hh"

class G02FieldSetup;

// ----------------------------------------------------------------------------

/// Detector construction used in GDML read/write example

class G02DetectorConstruction : public G4VUserDetectorConstruction
{
  private:
    G02DetectorConstruction();

  public:

    // Constructor and destructor
    //
    G02DetectorConstruction(const G4String& filename);
    virtual ~G02DetectorConstruction();

    // Construction of SubDetectors
    //
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:

    G4Cache<G02FieldSetup*>    fFieldSetup;

    // File name
    G4String fFileName;

    // GDMLparser
    //
    G4GDMLParser fParser;
};

// ----------------------------------------------------------------------------

#endif
