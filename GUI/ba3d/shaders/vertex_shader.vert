attribute vec3 vertex;
attribute vec3 normal;
attribute vec3 axiscolor;
uniform   mat4 matProj, matModel, matObject;
varying   vec3 vo, nm, ac;

void main(void) {
  vec4 vertObj = matObject * vec4(vertex,1);
  gl_Position  = matProj * matModel * vertObj;
  vo = vertObj.xyz;
  nm = normal;
  ac = axiscolor;
}
