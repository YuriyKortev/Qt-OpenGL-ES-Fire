
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif


attribute vec4 vertexAttr;
attribute vec3 veloc;
attribute float w;

uniform mat4 matrix;
in vec3 colorAttr;

varying vec3 color;
varying float phase;

uniform float time;
//Параметры волны
const float period=60.0f;


void main()
{

    vec3 pos = vertexAttr.xyz;

    phase = fract ( w + time / period );
     gl_Position = matrix * vec4 ( pos + phase * veloc, 1.0 );
     gl_PointSize = 1.0 + 3.0 * (1.0f-phase);

    color=vec4(1.0f,0.2f,0.0f,1.0f);
}
