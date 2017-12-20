/*************************************************************************************/
/* Graphics tool box (routines from FS Hill book)                                    */
/* Camera class implementation (chapter 7; pp.367ff)                                 */
/* CS 251                                                                            */
/* St. Vincent College                                                               */
/*************************************************************************************/
#include "camera.h"

Camera::Camera()
{viewAngle=aspect=nearDist=farDist=0;} // default constructor


// -------------set---------------
// inputs: Eye--coords for the Eye, 
//         look--where it is looking 
//         up--the up vector
// outputs: none
// purpose: sets the n,u,v vectors (internal use for camera) and sets Model Matrix
// source: FS Hill p. 367
void Camera::set(Point3 Eye, Point3 look, Vector3 up)
{	// create a modelview matrix and send it to OpenGL
  eye.set(Eye); // store the given eye position
  n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n
  u.set(up.cross(n)); // make u = up X n
  n.normalize(); u.normalize(); // make them unit length
  v.set(n.cross(u));  // make v =  n X u
  setModelViewMatrix(); // tell OpenGL 
}

void Camera::set(float eyex, float eyey, float eyez, 
		 float lookx, float looky, float lookz,
		 float upx, float upy, float upz)
{	// create a modelview matrix and send it to OpenGL
  Point3 Eye(eyex,eyey,eyez);
  Point3 look(lookx,looky,lookz);
  Vector3 up(upx,upy,upz);

  eye.set(Eye); // store the given eye position
  n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n
  u.set(up.cross(n)); // make u = up X n
  n.normalize(); u.normalize(); // make them unit length
  v.set(n.cross(u));  // make v =  n X u
  setModelViewMatrix(); // tell OpenGL 
}


// -------------setModelViewMatrix---------------
// inputs: none
// outputs: none
// purpose: uses n,u,v to set up model view matrix
// source: FS Hill p. 367
void Camera::setModelViewMatrix(void)
{ // load modelview matrix with existing camera values
  float m[16];
  Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye 
  m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u);
  m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v);
  m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n);
  m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;
  glMatrixMode(GL_MODELVIEW);
  //glPushMatrix();
  glLoadMatrixf(m); // load OpenGL's modelview matrix
  //glPopMatrix();
}

// -------------slide---------------
// inputs: delU, delV, delN -- gives quantity of slide along each vector
// outputs: none
// purpose: combines three possible slides into one function, sliding along
//          u,v,n vectors according to numbers in delU, delV, delN
// source: FS Hill p. 368
void Camera::slide(float delU, float delV, float delN)
{
  eye.x += delU * u.x + delV * v.x + delN * n.x;
  eye.y += delU * u.y + delV * v.y + delN * n.y;
  eye.z += delU * u.z + delV * v.z + delN * n.z;
  setModelViewMatrix();		// inform OpenGL
}

// -------------roll---------------
// inputs: angle -- gives quantity of roll
// outputs: none
// purpose: roll around according to given angle
// source: FS Hill p. 369
void Camera::roll(float angle)
{
  float cs = cos(3.14159265/180 * angle);
  float sn = sin(3.14159265/180 * angle);
  Vector3 t = u; 		// remember old u

  u.set(cs*t + sn*v);
  v.set(cs*v - sn*u);
  //  u.set(cs*t.x - sn*v.x, cs*t.y - sn*v.y, cs*t.z - sn*v.z); 
  //v.set(sn*t.x + cs*v.x, sn*t.y + cs*v.y, sn*t.z + cs*v.z);

  setModelViewMatrix();		// inform OpenGL
}

// -------------pitch---------------
// inputs: angle -- gives quantity of pitch
// outputs: none
// purpose: pitch according to given angle
// source: FS Hill p. 369
void Camera::pitch(float angle) // increase pitch
{
  float cs = cos(3.14159265/180 * angle);
  float sn = sin(3.14159265/180 * angle);
  Vector3 n1 = cs * n + sn * v;
  Vector3 v1 = cs * v - sn * n;

  n.set(n1);
  v.set(v1);

  setModelViewMatrix();		// inform OpenGL
}

// -------------yaw---------------
// inputs: angle -- gives quantity of yaw
// outputs: none
// purpose: yaw according to given angle
// source: FS Hill p. 369
void Camera::yaw(float angle) // increase pitch
{
  float cs = cos(3.14159265/180 * angle);
  float sn = sin(3.14159265/180 * angle);
  Vector3 n1 = cs*n + sn*u; 
  Vector3 u1 = (cs)*u - sn*n;

  u.set(u1);
  n.set(n1);
  setModelViewMatrix();		// inform OpenGL
}
  
//void Camera::setShape(float vAng, float asp, float nearD, float farD);

