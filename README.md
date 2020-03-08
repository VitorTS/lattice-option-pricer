# Lattice option pricer

Small framework to price one factor options using binomial lattices.

This project is part of my computational finance and C++ studies.

The design uses the layered approach:
Layer 1 - Lattice model
Layer 2 - Back and forward induction
Layer 3 - Model and pricing functions

Asset/option calculation implements the Trigeorgis (TRG) model:

![Trigeorgis model (TRG)](https://raw.githubusercontent.com/VitorTS/lattice-option-pricer/master/images/TRG_Trigeorgis.jpg)

The lattice is implemented using boost UBLAS triangular matrix.
