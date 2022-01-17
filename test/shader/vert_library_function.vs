//BEGIN_LIBRARY_FUNCTION
vec4 CalculateMVPosition(in vec3 vMPosition, in mat4 matView, in mat4 matModel)
{
    return matView * matModel * vec4(vMPosition, 1.0);
}
//END_LIBRARY_FUNCTION