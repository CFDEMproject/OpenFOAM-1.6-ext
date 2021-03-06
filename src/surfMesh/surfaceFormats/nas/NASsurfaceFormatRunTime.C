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

\*---------------------------------------------------------------------------*/

#include "NASsurfaceFormat.H"

#include "addToRunTimeSelectionTable.H"
#include "addToMemberFunctionSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace fileFormats
{

// read MeshedSurface - .bdf (Bulk Data Format)
addNamedTemplatedToRunTimeSelectionTable
(
    MeshedSurface,
    NASsurfaceFormat,
    face,
    fileExtension,
    bdf
);
addNamedTemplatedToRunTimeSelectionTable
(
    MeshedSurface,
    NASsurfaceFormat,
    face,
    fileExtension,
    nas
);

// read MeshedSurface - .nas (Nastran)
addNamedTemplatedToRunTimeSelectionTable
(
    MeshedSurface,
    NASsurfaceFormat,
    triFace,
    fileExtension,
    bdf
);
addNamedTemplatedToRunTimeSelectionTable
(
    MeshedSurface,
    NASsurfaceFormat,
    triFace,
    fileExtension,
    nas
);

}
}

// ************************************************************************* //
