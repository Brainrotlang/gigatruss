# Gigatruss

**2D truss static analysis written entirely in [Brainrot](https://github.com/Brainrotlang/brainrot).**

Gigatruss is a small finite-element / matrix-stiffness solver whose primary engineering goal is to solve real planar truss problems and whose secondary goal is to prove that a language containing `skibidi`, `gigachad`, `flex`, `edgy`, and `bussin` can still do respectable structural mechanics.

> finite rizz method

## v0.1 scope

The first version solves one canonical three-node triangular truss using only Brainrot code:

- 2 translational DOFs per node
- 2D bar-element stiffness matrix
- dense global stiffness assembly
- zero prescribed displacements
- Gaussian elimination with partial pivoting
- nodal displacement recovery
- support reaction recovery
- member axial force and stress
- tension/compression classification
- Newton-Raphson square root implemented in Brainrot

No BLAS, LAPACK, native math library, raylib, or file I/O is required.

## Reference model

Geometry:

```text
node 1: (0, 0)  fixed X/Y
node 2: (4, 0)  fixed Y
node 3: (2, 3)
```

Members:

```text
1: 1 -> 2
2: 1 -> 3
3: 2 -> 3
```

Material and section:

```text
E = 200 GPa
A = 0.001 m^2
```

Load:

```text
node 3: Fy = -10 kN
```

Expected solution:

```text
Node 1: Ux =  0.000000000 m   Uy =  0.000000000 m
Node 2: Ux =  0.000066667 m   Uy =  0.000000000 m
Node 3: Ux =  0.000033333 m   Uy = -0.000152423 m

Node 1: Ry = +5000 N
Node 2: Ry = +5000 N

Member 1: +3333.333 N  tension      +3.333333 MPa
Member 2: -6009.252 N  compression  -6.009252 MPa
Member 3: -6009.252 N  compression  -6.009252 MPa
```

## Run

Build Brainrot, then execute:

```bash
brainrot src/gigatruss.brainrot
```

If running directly from a Brainrot checkout:

```bash
/path/to/brainrot/brainrot src/gigatruss.brainrot
```

The v0.1 model is intentionally hard-coded. Input files and general model parsing belong to a later milestone once Brainrot file I/O lands.

## Method

Gigatruss solves

```text
K u = F
```

For each element it computes

```text
L = sqrt(dx^2 + dy^2)
c = dx / L
s = dy / L
```

and assembles

```text
          EA
k_e = -------- *
           L

[  c^2    cs   -c^2   -cs ]
[   cs   s^2    -cs  -s^2 ]
[ -c^2   -cs    c^2    cs ]
[  -cs  -s^2     cs   s^2 ]
```

The constrained linear system is solved with dense Gaussian elimination and partial pivoting. Reactions are recovered from the original unconstrained system:

```text
R = K_original * U - F_original
```

See [`docs/THEORY.md`](docs/THEORY.md) for the derivation.

## Roadmap

- [x] canonical 3-node truss
- [x] global stiffness assembly
- [x] pivoted dense solver
- [x] reactions
- [x] member force / stress recovery
- [ ] reusable model representation
- [ ] arbitrary node/member counts
- [ ] model input from files
- [ ] SVG undeformed/deformed shape output
- [ ] 2D frame elements
- [ ] modal analysis
- [ ] topology optimization, because apparently we hate peace

## License

GPL-3.0.
