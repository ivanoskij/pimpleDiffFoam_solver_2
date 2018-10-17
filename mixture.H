
//////////////////////////////////////////////////////////////////////////////////////

// --- read all physical properties

Info<< "Reading droplet viscosity\n" << endl;
dimensionedScalar muW
(
    "muW",
    transportProperties.lookup("muW")
);
Info<< "Reading air viscosity\n" << endl;
dimensionedScalar mu
(
    "mu",
    transportProperties.lookup("mu")
);
Info<< "Reading volume fraction\n" << endl;
dimensionedScalar alphaW
(
    "alphaW",
    transportProperties.lookup("alphaW")
);

Info<< "Reading droplet density\n" << endl;
dimensionedScalar rhoW
(
    "rhoW",
    transportProperties.lookup("rhoW")
);

Info<< "Reading air density\n" << endl;
dimensionedScalar rho
(
    "rho",
    transportProperties.lookup("rho")
);
//////////////////////////////////////////////////////////////////////////////////////

// --- compute mixture physical properties
/*
dimensionedScalar mur
("mur",(muW+0.4*mu)/(muW+mu),dimless,0);
*/

/* --> this one works but no formula can be insered
dimensionedScalar mur
(
"mur",
dimensionSet(0, 0, 0, 0, 0, 0, 0),
0. 
);
*/

/*
Info<< "Calculating mixture viscosity (ii)\n" << endl;
const volScalarField muMix ("muMix",((muA*pow((1-alphaW),(-2.5*mur)))));

Info<< "Calculating mixture density\n" << endl;//
const volScalarField rhoMix ("rhoMix",(rhoW*alphaW+rhoA*(1-alphaW))); 

Info<< "Calculating mixture kinematic viscosity\n" << endl;
const volScalarField nuMix ("nuMix",(muMix/rhoMix));

Info<< "Calculating air kinematic viscosity\n" << endl; //
const volScalarField nuA ("nuA",(muA*pow(rhoA,-1)));
*/
//////////////////////////////////////////////////////////////////////////////////////

// --- compute mixture physical properties

Info<< "Calculating mixture viscosity\n" << endl;
volScalarField muMix
(
    IOobject
    (
        "muMix",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    mu*pow(1 - alphaW,-2.5*((muW + 0.4*mu)/(muW + mu)))
);

Info<< "Calculating mixture density\n" << endl;
volScalarField rhoMix
(
    IOobject
    (
        "rhoMix",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    rhoW*alphaW + rho*(1 - alphaW)
);


Info<< "Calculating mixture kinematic viscosity\n";
volScalarField nuMix
(
    IOobject
    (
        "nuMix",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    muMix/rhoMix
);

//////////////////////////////////////////////////////////////////////////////////////









