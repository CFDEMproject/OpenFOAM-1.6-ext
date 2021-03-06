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
    Foam::fv::gaussLaplacianScheme

Description
    Basic second-order laplacian using face-gradients and Gauss' theorem.

SourceFiles
    gaussLaplacianScheme.C

\*---------------------------------------------------------------------------*/

#ifndef gaussLaplacianScheme_H
#define gaussLaplacianScheme_H

#include "laplacianScheme.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace fv
{

/*---------------------------------------------------------------------------*\
                       Class gaussLaplacianScheme Declaration
\*---------------------------------------------------------------------------*/

template<class Type, class GType>
class gaussLaplacianScheme
:
    public fv::laplacianScheme<Type, GType>
{
    // Private Member Functions

        tmp<fvMatrix<Type> > fvmLaplacianUncorrected
        (
            const surfaceScalarField& gammaMagSf,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > gammaSnGradCorr
        (
            const surfaceVectorField& SfGammaCorr,
            const GeometricField<Type, fvPatchField, volMesh>&
        );

        //- Disallow default bitwise copy construct
        gaussLaplacianScheme(const gaussLaplacianScheme&);

        //- Disallow default bitwise assignment
        void operator=(const gaussLaplacianScheme&);


public:

    //- Runtime type information
    TypeName("Gauss");


    // Constructors

        //- Construct null
        gaussLaplacianScheme(const fvMesh& mesh)
        :
            laplacianScheme<Type, GType>(mesh)
        {}

        //- Construct from Istream
        gaussLaplacianScheme(const fvMesh& mesh, Istream& is)
        :
            laplacianScheme<Type, GType>(mesh, is)
        {}

        //- Construct from mesh, interpolation and snGradScheme schemes
        gaussLaplacianScheme
        (
            const fvMesh& mesh,
            const tmp<surfaceInterpolationScheme<GType> >& igs,
            const tmp<snGradScheme<Type> >& sngs
        )
        :
            laplacianScheme<Type, GType>(mesh, igs, sngs)
        {}


    // Destructor

        virtual ~gaussLaplacianScheme()
        {}


    // Member Functions

        tmp<GeometricField<Type, fvPatchField, volMesh> > fvcLaplacian
        (
            const GeometricField<Type, fvPatchField, volMesh>&
        );

        tmp<fvMatrix<Type> > fvmLaplacian
        (
            const GeometricField<GType, fvsPatchField, surfaceMesh>&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        tmp<GeometricField<Type, fvPatchField, volMesh> > fvcLaplacian
        (
            const GeometricField<GType, fvsPatchField, surfaceMesh>&,
            const GeometricField<Type, fvPatchField, volMesh>&
        );
};


// Use macros to emulate partial-specialisation of the the Laplacian functions
// for scalar diffusivity gamma

#define defineFvmLaplacianScalarGamma(Type)                                 \
                                                                            \
template<>                                                                  \
tmp<fvMatrix<Type> > gaussLaplacianScheme<Type, scalar>::fvmLaplacian       \
(                                                                           \
    const GeometricField<scalar, fvsPatchField, surfaceMesh>&,              \
    GeometricField<Type, fvPatchField, volMesh>&                            \
);                                                                          \
                                                                            \
template<>                                                                  \
tmp<GeometricField<Type, fvPatchField, volMesh> >                           \
gaussLaplacianScheme<Type, scalar>::fvcLaplacian                            \
(                                                                           \
    const GeometricField<scalar, fvsPatchField, surfaceMesh>&,              \
    const GeometricField<Type, fvPatchField, volMesh>&                      \
);


defineFvmLaplacianScalarGamma(scalar);
defineFvmLaplacianScalarGamma(vector);
defineFvmLaplacianScalarGamma(sphericalTensor);
defineFvmLaplacianScalarGamma(symmTensor);
defineFvmLaplacianScalarGamma(tensor);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "gaussLaplacianScheme.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
