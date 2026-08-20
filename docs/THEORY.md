# Gigatruss theory

Gigatruss v0.1 implements the direct stiffness method for a linear-elastic 2D truss.

## Assumptions

Each member is treated as a pin-jointed axial bar:

- small displacements
- linear elastic material
- axial deformation only
- no bending stiffness
- no shear deformation
- no distributed member loads
- two translational degrees of freedom per node

For node `i`, the unknown displacement vector is

```text
u_i = [u_x, u_y]
```

For an `n`-node model the global displacement vector therefore contains `2n` entries.

## Element geometry

For an element joining nodes 1 and 2,

```text
dx = x2 - x1
dy = y2 - y1
L  = sqrt(dx^2 + dy^2)
c  = dx / L
s  = dy / L
```

where `c` and `s` are the direction cosines.

## Element stiffness matrix

The 4x4 element stiffness matrix expressed in global coordinates is

```text
          EA
k_e = -------- *
           L

[  c^2    cs   -c^2   -cs ]
[   cs   s^2    -cs  -s^2 ]
[ -c^2   -cs    c^2    cs ]
[  -cs  -s^2     cs   s^2 ]
```

The element DOF map is

```text
[2*a, 2*a+1, 2*b, 2*b+1]
```

for zero-based node indices `a` and `b`.

Gigatruss adds each coefficient of `k_e` into the corresponding location in the dense global stiffness matrix `K`.

## Global equilibrium

The assembled system is

```text
K U = F
```

where

- `K` is the global stiffness matrix
- `U` is the global nodal displacement vector
- `F` is the global applied load vector

## Boundary conditions

v0.1 supports prescribed zero displacements. For every restrained DOF, Gigatruss zeroes its row and column, writes `1` on the diagonal, and sets the corresponding load entry to zero.

Because the prescribed displacement is zero, this transformation preserves the solution of the free DOFs.

## Linear solver

The constrained dense system is solved using Gaussian elimination with partial pivoting:

1. choose the row with the largest absolute pivot candidate
2. swap it into the active pivot row
3. eliminate all entries beneath the pivot
4. back-substitute from the final row upward

A pivot with magnitude below `1e-9` is treated as a singular system and aborts the solve.

This is not intended to be the long-term solver for large structures. It is intentionally simple, deterministic, and implementable entirely in current Brainrot.

## Reaction recovery

Before applying constraints, Gigatruss stores copies of the original stiffness matrix and load vector.

After solving for `U`, support reactions are recovered from

```text
R = K_original * U - F_original
```

Only restrained DOFs are reported as support reactions.

## Member force and stress

For a solved element, the axial extension is

```text
delta = [-c, -s, c, s] * u_e
```

where `u_e` is the four-entry element displacement vector.

Axial force is

```text
N = EA/L * delta
```

and axial stress is

```text
sigma = N / A
```

Gigatruss uses the sign convention:

```text
N >= 0  -> tension
N < 0   -> compression
```

## Canonical verification problem

v0.1 ships one symmetric triangular truss:

```text
node 1 = (0, 0), restrained X and Y
node 2 = (4, 0), restrained Y
node 3 = (2, 3)

E = 200 GPa
A = 0.001 m^2
Fy(node 3) = -10 kN
```

The expected solution is approximately

```text
U2x = +6.6666667e-5 m
U3x = +3.3333333e-5 m
U3y = -1.52422685e-4 m

R1y = +5000 N
R2y = +5000 N

N1 = +3333.333 N
N2 = -6009.252 N
N3 = -6009.252 N
```

Those values are used as the v0.1 numerical oracle.
