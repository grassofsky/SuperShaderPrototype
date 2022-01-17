//BEGIN_VERTEXIN
layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;
//END_VERTEXIN

//BEGIN_GLOBAL_STRUCTURE
struct GlobalStruct
{
    vec3 vVertex;
    vec4 vColor;
    vec3 vNormal;

    vec4 vMVPosition;
    vec4 vMVNormal;
    vec4 vGLPosition;
};
//END_GLOBAL_STRUCTURE

//BEGIN_PIPELINE_FUNCTION
void step_InitGlobalStruct(int out GlobalStruct state)
{
    state.vVertex = vVertex;
    state.vColor = vColor;
    state.vNormal = vNormal;
}
//END_PIPELINE_FUNCTION