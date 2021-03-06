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

Description


\*---------------------------------------------------------------------------*/

#include "error.H"
#include "blockMesh.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Foam::pointField Foam::blockMesh::createPoints(const dictionary& dict)
{
    blockMesh& blocks = *this;

    scalar scaleFactor = 1.0;

    // optional 'convertToMeters' (or 'scale'?)
    if (!dict.readIfPresent("convertToMeters", scaleFactor))
    {
        dict.readIfPresent("scale", scaleFactor);
    }

    Info<< nl << "Creating points with scale " << scaleFactor << endl;

    pointField points(nPoints_);

    forAll(blocks, blockLabel)
    {
        const pointField& blockPoints = blocks[blockLabel].points();

        forAll(blockPoints, blockPointLabel)
        {
            points
            [
                mergeList_
                [
                    blockPointLabel
                  + blockOffsets_[blockLabel]
                ]
            ] = scaleFactor * blockPoints[blockPointLabel];
        }
    }

    return points;
}

// ************************************************************************* //
