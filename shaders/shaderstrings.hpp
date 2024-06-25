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

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
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