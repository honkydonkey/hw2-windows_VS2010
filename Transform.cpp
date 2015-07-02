// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#define PI 3.141592653589793

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    mat3 ret;
	float radian = degrees * PI / 180.0;
	float a,b,c,d,e,f,g,h,i;
	a = cos(radian)+axis.x*axis.x*(1-cos(radian));
	b = axis.y*axis.x*(1-cos(radian))+axis.z*sin(radian);
	c = axis.z*axis.x*(1-cos(radian))-axis.y*sin(radian);
	d = axis.x*axis.y*(1-cos(radian))-axis.z*sin(radian);
	e = cos(radian)+axis.y*axis.y*(1-cos(radian));
	f = axis.z*axis.y*(1-cos(radian))+axis.x*sin(radian);
	g = axis.x*axis.z*(1-cos(radian))+axis.y*sin(radian);
	h = axis.y*axis.z*(1-cos(radian))-axis.x*sin(radian);
	i = cos(radian)+axis.z*axis.z*(1-cos(radian));
	ret = mat3(a,b,c,d,e,f,g,h,i);
    return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = rotate(degrees,up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 a = glm::cross(eye,up);
	a = glm::normalize(a);
	eye = rotate(degrees,a)*eye;
	up =rotate(degrees,a)*up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	mat4 ret;
	vec3 w,u,v;
	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	w = glm::normalize(eye-center);
	u = glm::normalize(glm::cross(up,w));
	v = glm::cross(w,u);
	a = u.x;
	b = v.x;
	c = w.x;
	d = 0;
	e = u.y;
	f = v.y;
	g = w.y;
	h = 0;
	i = u.z;
	j = v.z;
	k = w.z;
	l = 0;
	m = -a*eye.x-e*eye.y-i*eye.z;
	n = -b*eye.x-f*eye.y-j*eye.z;
	o = -c*eye.x-g*eye.y-k*eye.z;
	p = 1;
	ret = mat4(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
  float theta = fovy / 2.0;
  float d1 = 1/tan(glm::radians(theta));
  float a1 = -(zFar + zNear)/(zFar - zNear);
  float b1 = -(2 * zFar * zNear)/(zFar - zNear);
  	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	a = d1/aspect;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	f = d1;
	g = 0;
	h = 0;
	i = 0;
	j = 0;
	k = a1;
	l = -1;
	m = 0;
	n = 0;
	o = b1;
	p = 0;
	ret = mat4(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
 	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	a = sx;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	f = sy;
	g = 0;
	h = 0;
	i = 0;
	j = 0;
	k = sz;
	l = 0;
	m = 0;
	n = 0;
	o = 0;
	p = 1;
	ret = mat4(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
 	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	a = 1;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	f = 1;
	g = 0;
	h = 0;
	i = 0;
	j = 0;
	k = 1;
	l = 0;
	m = tx;
	n = ty;
	o = tz;
	p = 1;
	ret = mat4(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
