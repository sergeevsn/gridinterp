## Seismic 3D grid interpolation/extrapolation 
### Takes 4 points of the grid with linear coordinates, geographic coordinates and inlines/crosslines.
### Interpolates onto new linear coordinates with desired step.
### Uses simple linear 4-point interpolation

Usage: 
```sh
./gridinterp <grid_param_file> <target_table_file>
```

## To build and run test:

```sh
git clone https://github.com/sergeevsn/gridinterp
cd gridinterp
mkdir build
cd build
cmake ..
make
./gridinterp ../params ../test_table.txt
```

## Param file contents:

First 4 lines - coordinaters of 4 corner points. 
First go linear coordinates, than geographic, than inlines and xlines
Next and last line is for desired linear coordinates (x1, y1, x2, y2) and desired step in meters.
Example is in ```params``` file.
