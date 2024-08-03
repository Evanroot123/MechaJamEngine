#pragma once

const char* vertexShaderBasic = R"(
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}
)";

const char* fragmentShaderBasic = R"(
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 uColor;

void main()
{
	color = uColor;
}
)";

const char* vertexShaderGlyph = R"(
#version 330 core
layout(location = 0) in vec4 vertex;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
	texCoords = vertex.zw;
}
)";

const char* fragmentShaderGlyph = R"(
#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
	color = vec4(textColor, 1.0) * sampled;
}
)";

const char* instanceGlyphVertexShader = R"(
#version 330 core
layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 texInfo;
layout (location = 2) in mat4 model;
out vec2 texCoords;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 texSize;

void main()
{
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
	//texCoords = vertex.zw;	

	// offset
	texCoords = vertex.zw + texInfo.xy;

	// adjust for size based on uv coord
	texCoords.x += vertex.z * texInfo.z;
	texCoords.y += vertex.w * texInfo.w;

	// normalize
	texCoords.x /= texSize.x;
	texCoords.y /= texSize.y;
	
	// put into center of texel based on uv coord
	//texCoords.x += 1.0 / texSize.x * 0.5;
	//texCoords.y += 1.0 / texSize.y * 0.5;
}
)";

const char* instanceGlyphFragmentShader = R"(
#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
	color = vec4(textColor, 1.0) * sampled;
}
)";

const char* singleSpriteVertex = R"(
#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 texCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texCoords = vertex.zw;
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}
)";

const char* singleSpriteFragment = R"(
#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D image;

void main()
{
	color = texture(image, texCoords);
}
)";

const char* instancedSpriteVertex = R"(
#version 330 core
layout (location = 0) in vec4 vertex;
layout (location = 1) in mat4 model;

out vec2 texCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	texCoords = vertex.zw;
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}
)";

const char* instancedSpriteFragment = R"(
#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D image;

void main()
{
	color = texture(image, texCoords);
}
)";

const char* tileMapVertex = R"(
#version 430 core
layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 tilePos;
out vec2 texCoords;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 gridPos;
uniform vec2 texSize;
uniform ivec2 gridSize;
uniform int gridWidthPixels;
uniform int gridHeightPixels;

void main()
{
	float xpos = vertex.x * gridWidthPixels;
	float ypos = vertex.y * gridHeightPixels;
	xpos += (gl_InstanceID % gridSize.x) * gridWidthPixels + gridPos.x;
	ypos += floor(gl_InstanceID / gridSize.y) * gridHeightPixels + gridPos.y;

	//float xpos = vertex.x + (gl_InstanceID % gridSize.x) * gridWidthPixels + gridPos.x;
	//float ypos = vertex.y + floor(gl_InstanceID / gridSize.y) * gridHeightPixels + gridPos.y;
	gl_Position = projection * view * vec4(xpos, ypos, 0.0, 1.0);

	texCoords = vertex.zw;
	// offset
	//texCoords = vertex.zw + tilePos.xy;

	// adjust for size based on uv coord
	//texCoords.x += vertex.z * gridWidthPixels;
	//texCoords.y += vertex.w * gridHeightPixels;

	// normalize
	//texCoords.x /= texSize.x;
	//texCoords.y /= texSize.y;
}
)";

const char* tileMapFragment = R"(
#version 430 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D tileset;

void main()
{
	color = texture(tileset, texCoords);
}
)";

//const char* testVertex = R"(
//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;
//
//out vec3 ourColor;
//out vec2 TexCoord;
//
//void main()
//{
//    gl_Position = vec4(aPos, 1.0);
//    ourColor = aColor;
//    TexCoord = aTexCoord;
//}
//)";
//
//const char* testFragment = R"(
//#version 330 core
//out vec4 FragColor;
//  
//in vec3 ourColor;
//in vec2 TexCoord;
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    FragColor = texture(ourTexture, TexCoord);
//}
//)";