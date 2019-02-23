# Ni2ImuReader #

This sample demonstrates how to read data from 3D accelerometer and 3D gyroscope from LIPSedge M3 camera.

NOTE: LIPS [SDK 1.5.0.7](https://www.lips-hci.com/downloads/category) (or higher version) is required for using this feature

After compiling this sample program, just run:
```
Ni2ImuReader 100 100

[1] Gyro (X,Y,Z) = (-18.13, 0.21, -18.69),	Accel (X,Y,Z) = (-1.01589, -0.11834, 0.000793)
[2] Gyro (X,Y,Z) = (-18.2, 0.14, -18.69),	Accel (X,Y,Z) = (-1.01687, -0.120536, -0.015738)
[3] Gyro (X,Y,Z) = (-18.2, 0.21, -18.62),	Accel (X,Y,Z) = (-1.01583, -0.120414, -0.016836)
[4] Gyro (X,Y,Z) = (-18.13, 0, -18.62),	Accel (X,Y,Z) = (-1.01663, -0.11956, -0.015677)
[5] Gyro (X,Y,Z) = (-18.2, 0.07, -18.62),	Accel (X,Y,Z) = (-1.01638, -0.119255, -0.016958)
[6] Gyro (X,Y,Z) = (-18.2, 0.14, -18.69),	Accel (X,Y,Z) = (-1.01626, -0.119194, -0.0183)
...
[100] Gyro (X,Y,Z) = (-18.2, 0.28, -18.62),	Accel (X,Y,Z) = (-1.01687, -0.119316, -0.039955)
```
will output Gyro and Accel data every 100ms for 100 times

NOTE:
*  Gyro data sensitivy: +-2000 dps(degrees-per-second)
* Accel data sensitivy: +-2 g

