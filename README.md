# r.walk.accessmod

This is an attempt to modify GRASS gis `r.walk` to accept other anisotropic formulas : tobler hiking function and bicycle function. This is an early experimental work. 

Based on `r.walk`  provided in grass 7.0 RC1. There is little chance thant this module works with another version of GRASS. 

In this version, the module takes speed map as friction map input.  

The speed map should be reclassed in three main categories, depending of the mode of transportation :

- 1000 : walking  (tobler's hiking formula) 
- 2000 : bicycling (kreuzotter formula. Takes in account elevation, air resistance, weight... and much more) 
- 3000 : other (not influenced by the slope) 

For each class, the base speed on flat surface is added to each categories. E.g.

- 3080 = car model for a base speed of 80 km/h. Elevation is ignored and an isotropic analysis is performed. 
- 2015 = bicycle model for a base speed of 15 km/h, with anisotropic analysis.
- 1002 = walking model for a base speed of 2 km/h, with anisotropic analysis.


compilation on linux, e.g.
```sh 
sudo make MODULE_TOPDIR=/usr/local/grass-7.0.1
```

compilation on mac, e.g. with hombrew grass-70
```sh
make MODULE_TOPDIR=/usr/local/Cellar/grass-70/7.0.1/grass-7.0.1
```
