-- https://www.youtube.com/watch?v=u9qVPpeKDFw

Material.EnableTextures = true;
Material:LoadTextureSlot(2, "Graphics/Texture/Terrain/water_normalmap.jpg")

Material.EnableLighting = false;
Material.EnableBlending = true;
Material.EnableCulling = false;
Material:SetColor(0.5, 1.0, 0.9);
Material:SetAlpha(1.0);

Material.EnableShaders = true;

Material:SetVertexProgram [[

uniform float Time;
uniform float TerrainSize;
uniform vec3 Position;
uniform mat4 WaterProjection;
varying vec3 eyeDir;

void main()
{
    vec3 t = normalize(gl_NormalMatrix * vec3(1, 0, 0));
    vec3 n = normalize(gl_NormalMatrix * vec3(0, 1, 0));
    vec3 b = cross(n, t);
    
    vec4 v = gl_Vertex;
    v.y += 0.075 * sin(0.75 * v.x + Time * 2.0) + 0.075 * sin(0.77 * v.z + Time * 1.7);

	gl_Position = gl_ModelViewProjectionMatrix * v;	
	eyeDir = vec3(gl_ModelViewMatrix * gl_Vertex);
	
	vec3 tmp;
    tmp.x = dot(eyeDir, t);
    tmp.y = dot(eyeDir, b);
    tmp.z = dot(eyeDir, n);
    eyeDir = normalize(tmp);
	
    gl_TexCoord[0] = (WaterProjection * gl_ModelViewProjectionMatrix) * gl_Vertex;

    gl_TexCoord[1].x = 0.215 * gl_Vertex.x + Time * 0.08;
    gl_TexCoord[1].y = 0.225 * gl_Vertex.z + Time * 0.08; 
    gl_TexCoord[2].x = 1.0 - (0.221 * gl_Vertex.x - Time * 0.08);
    gl_TexCoord[2].y = 1.0 - (0.229 * gl_Vertex.z - Time * 0.08);
    
	gl_TexCoord[3].s = gl_Vertex.x / TerrainSize + 0.5;
	gl_TexCoord[3].t = gl_Vertex.z / TerrainSize + 0.5;
    
    float a = 1.0 - ((gl_Position.z) / (gl_Fog.end)) * 1.0;
    gl_FrontColor = gl_Color;
    gl_FrontColor.a *= a;  
}

]]

Material:SetFragmentProgram [[

uniform sampler2D WaterReflection;
uniform sampler2D WaterLightmap;
uniform sampler2D Texture2;
uniform float Time;
varying vec3 eyeDir;

void main()
{
    vec4 reflectColor;

    vec3 light = normalize(vec3(1, 1, 1));
    vec2 projectedCoords = gl_TexCoord[0].xy / gl_TexCoord[0].w;
    
    vec4 displacement1 = texture2D(Texture2, gl_TexCoord[1].st);
    vec4 displacement2 = texture2D(Texture2, gl_TexCoord[2].st);
    vec4 lightmap = texture2D(WaterLightmap, gl_TexCoord[3].st);
    
    vec3 normal1 = (displacement1.xyz * 2.0 - 1.0) * 0.25;
    vec3 normal2 = (displacement2.xyz * 2.0 - 1.0) * 0.25;
    vec3 waterNormal = vec3(0, 1, 0);
    
    vec3 normal = normalize(normal1 + normal2);
    
    float f = 1.0 - dot(normal, light);
    vec3 inDir = light - 2.0 * f * normal;
    float fres = clamp(dot(eyeDir, inDir), 0.0, 2.0);
    
    float specularFactor = pow(fres, 16.0);
    vec4 specular = vec4(1.0, 1.0, 1.0, 0);
    
    gl_FragColor = texture2D(WaterReflection, projectedCoords + normal.xy * 0.5) * gl_Color * lightmap.r * lightmap.g + specular * specularFactor;
    gl_FragColor.a = gl_Color.a * lightmap.g * lightmap.g * lightmap.g;
}

]]
