/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

InClass
    vtkPV3Foam

\*---------------------------------------------------------------------------*/

#ifndef vtkPV3FoamUpdateInfoFields_H
#define vtkPV3FoamUpdateInfoFields_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<template<class> class patchType, class meshType>
void Foam::vtkPV3Foam::updateInfoFields
(
    vtkDataArraySelection *select
)
{
    if (debug)
    {
        Info<< "<beg> Foam::vtkPV3Foam::updateInfoFields <"
            << meshType::Mesh::typeName
            << "> [meshPtr=" << (meshPtr_ ? "set" : "NULL") << "]"
            << endl;
    }

    stringList enabledEntries;
    // enable 'p' and 'U' on the first call
    if (select->GetNumberOfArrays() == 0 && !meshPtr_)
    {
        enabledEntries.setSize(2);
        enabledEntries[0] = "p";
        enabledEntries[1] = "U";
    }
    else
    {
        // preserve the enabled selections
        enabledEntries = getSelectedArrayEntries(select);
    }

    select->RemoveAllArrays();

    // use the db directly since this might be called without a mesh,
    // but the region must get added back in
    word regionPrefix;
    if (meshRegion_ != polyMesh::defaultRegion)
    {
        regionPrefix = meshRegion_;
    }

    // Search for list of objects for this time and mesh region
    IOobjectList objects(dbPtr_(), dbPtr_().timeName(), regionPrefix);

    //- Add volume fields to GUI
    addToSelection<GeometricField<scalar, patchType, meshType> >
    (
        select,
        objects
    );
    addToSelection<GeometricField<vector, patchType, meshType> >
    (
        select,
        objects
    );
    addToSelection<GeometricField<sphericalTensor, patchType, meshType> >
    (
        select,
        objects
    );
    addToSelection<GeometricField<symmTensor, patchType, meshType> >
    (
        select,
        objects
    );
    addToSelection<GeometricField<tensor, patchType, meshType> >
    (
        select,
        objects
    );

    // restore the enabled selections
    setSelectedArrayEntries(select, enabledEntries);

    if (debug)
    {
        Info<< "<end> Foam::vtkPV3Foam::updateInfoFields" << endl;
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif
// ************************************************************************* //
