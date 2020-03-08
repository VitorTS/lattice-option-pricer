# Lattice option pricer

Small framework to price one factor options using binomial lattices.

asset/option calculation implements the Trigeorgis (TRG) model:

![Trigeorgis model (TRG)](https://raw.githubusercontent.com/VitorTS/lattice-option-pricer/master/images/TRG_Trigeorgis.jpg)

The lattice is implemented using boost UBLAS triangular matrix.