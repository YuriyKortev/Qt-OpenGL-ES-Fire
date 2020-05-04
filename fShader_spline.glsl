#version 330 core

in vec3 color;
in float phase;

void main()
{

    gl_FragColor=(phase)*vec4(color,1.0f);
}
