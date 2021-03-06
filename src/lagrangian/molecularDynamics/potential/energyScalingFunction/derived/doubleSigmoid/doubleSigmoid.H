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

Class
    Foam::energyScalingFunctions::doubleSigmoid

Description


SourceFiles
    doubleSigmoid.C

\*---------------------------------------------------------------------------*/

#ifndef doubleSigmoid_H
#define doubleSigmoid_H

#include "energyScalingFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace energyScalingFunctions
{

/*---------------------------------------------------------------------------*\
                        Class doubleSigmoid Declaration
\*---------------------------------------------------------------------------*/

class doubleSigmoid
:
    public energyScalingFunction
{
    // Private data

        dictionary doubleSigmoidCoeffs_;

        scalar shift1_;
        scalar scale1_;
        scalar shift2_;
        scalar scale2_;


    // Private Member Functions

        scalar sigmoidScale
        (
            const scalar r,
            const scalar shift,
            const scalar scale
        ) const;


public:

    //- Runtime type information
    TypeName("doubleSigmoid");


    // Constructors

        //- Construct from components
        doubleSigmoid
        (
            const word& name,
            const dictionary& energyScalingFunctionProperties,
            const pairPotential& pairPot
        );


    // Destructor

        ~doubleSigmoid()
        {}

    // Member Functions

        void scaleEnergy(scalar& e, const scalar r) const;

        //- Read dictionary
        bool read(const dictionary& energyScalingFunctionProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace energyScalingFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
