//BEGIN_UNIFROM_VARING
out VERTEXOUT 
{
    vec4 vMVPosition;
    vec4 vMVNormal;
} vs_out;
//END_UNIFORM_VARING

//BEGIN_PIPELINE_FUNCTION
void step_VertexOut(in out GlobalStruct state)
{
    vs_out.vMVPosition = state.vMVPosition;
    vs_out.vMVNormal = state.vMVNormal;
    gl_Position = state.vGLPosition;
}
//END_PIPELINE_FUNCTION