attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
uniform mat4 u_WVP;
uniform float u_currentFrame;
uniform float u_numFrames;
uniform float u_currentAction;
uniform float u_numActions;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_WVP * posL;
v_uv = vec2 (a_uv.x * (1.0/u_numFrames) + u_currentFrame/u_numFrames, a_uv.y * (1.0/u_numActions) + u_currentAction/u_numActions);
}
   