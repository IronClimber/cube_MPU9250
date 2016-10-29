//=============================================================================================
// MadgwickAHRS.h
//=============================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
// From the x-io website "Open-source resources available on this website are
// provided under the GNU General Public Licence unless an alternative licence
// is provided in source."
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=============================================================================================
#ifndef __MADGWICKAHRS_H
#define __MADGWICKAHRS_H

#include <math.h>
#include <stdint.h>

void Madgwick_init();
void Madgwick_update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float time);
void Madgwick_updateIMU(float gx, float gy, float gz, float ax, float ay, float az, float time);
float Madgwick_invSqrt(float x);
void Madgwick_computeAngles();
float Madgwick_getRoll();
float Madgwick_getPitch();
float Madgwick_getYaw();
float Madgwick_getRollRadians();
float Madgwick_getPitchRadians();
float Madgwick_getYawRadians();

#endif /* End of __MADGWICKAHRS_H */

