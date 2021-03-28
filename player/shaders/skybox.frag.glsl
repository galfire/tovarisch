#version 300 es

precision mediump float;
  
layout(location = 0) out vec4 Colour;

in vec3 TexCoord;

uniform sampler2D skyboxTexture;

const float pi = 3.141592653589793238462643383279502884197169;

void main()
{
    vec3 direction = normalize(TexCoord);

    float longitude = atan(direction.z, direction.x);
    float latitude = acos(-direction.y);

    vec2 uv = vec2(longitude, latitude);
    uv /= vec2(2.0f * pi, pi);
    
    uv.x += 0.5;
    
    vec4 tex = texture(skyboxTexture, uv);
    Colour = tex;
}
