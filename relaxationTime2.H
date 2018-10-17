
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Info<< "Reading droplet diameter\n" << endl;
dimensionedScalar dW
(
    "dW",
    transportProperties.lookup("dW")
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// compute relaxation time

const dimensionedScalar dummyV("dummyV",dimensionSet(0, 1, -1, 0, 0),1e-20); 		//dummy entry for lowes velocity 

Info<< "Calculating local Reynolds number\n" << endl;
volScalarField Reloc ("Reloc", ((max(mag(dummyV),mag(U)))*dW/nuMix));			//local reynolds number//[adim]

Info<< "Calculating drag coefficient\n" << endl;
volScalarField CW ("CW", (24/Reloc+4*pow(Reloc,-0.333)));				//drag coefficient//[adim]

Info<< "Calculating relaxation time\n" << endl;
volScalarField relt ("relt",(CW*pow(dW,2)/(18*nuMix)));					//relaxation time//[s]

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//include gravity

Info<< "Reading gravitationalProperties\n" << endl;
IOdictionary gravitationalProperties
(
    IOobject
    (
        "gravitationalProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

const dimensionedVector g(gravitationalProperties.lookup("g"));
const dimensionedScalar magg = mag(g);
const dimensionedVector gHat = g/magg;

Info<< "Creating gravity field\n" << endl;
volVectorField grav
(
    IOobject
    (
        "grav",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ, //READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    g
);

//////////////////////////////////////////////////////////////////////////////////////

//compute drift velocity and flux

Info<< "Calculating drift velocity\n" << endl;
volVectorField UW
(
    IOobject
    (
        "UW",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ, //READ_IF_PRESENT,
        IOobject::AUTO_WRITE //AUTO_WRITE
    ),
    relt*grav
);

Info<< "Calculating drift velocity flux\n" << endl;
surfaceScalarField phiW
(
    IOobject
    (
        "phiW",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE //AUTO_WRITE
    ),
    fvc::flux(UW)
);
//////////////////////////////////////////////////////////////////////////////////////
