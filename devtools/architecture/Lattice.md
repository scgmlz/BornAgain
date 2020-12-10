## Lattices

Typical sample construction with a 3d lattice:
```
    lattice = ba.FCCLattice(30*nm).transformed(rot.getTransform3D())
    peak_shape = ba.MisesFisherGaussPeakShape(peak_intensity, peak_width, zenith, kappa, kappa2)
    iff = ba.InterferenceFunction3DLattice(lattice)
    iff.setPositionVariance(1.)
    iff.setPeakShape(peak_shape)
```

`bake::FCCLattice` returns a `Lattice3d` with an fcc primitive cell.
