//BEGIN_UNIFORM_VARYING
uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matNormal;
//END_UNIFORM_VARYING

//BEGIN_PIPELINE_FUNCTION
void step_VertexProcess(int out GlobalStruct state)
{
    state.vMVPosition = CalculateMVPosition(state.vVertex);
    state.vMVNormal = matNormal * vec4(vNormal, 0.0);
    state.vGLPosition = matProjection * state.vMVPosition;
}
//END_PIPELINE_FUNCTION