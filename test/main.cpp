#include "shader_factory.h"

#include <iostream>

int main()
{
    ShaderFactory vertexFactory;

    std::shared_ptr<PipelineFunction> spFuncInitGlobalStruct(new PipelineFunction("InitGlobalStruct"));
    spFuncInitGlobalStruct->SetShaderFile("shader/vert_pipeline_function_init_global_struct.vs");
    
    std::shared_ptr<PipelineFunction> spFuncVertexProcess(new PipelineFunction("VertexProcess"));
    spFuncVertexProcess->SetShaderFile("shader/vert_pipeline_function_vert_process.vs");
    
    std::shared_ptr<PipelineFunction> spFuncVertexOut(new PipelineFunction("VertexOut"));
    spFuncVertexOut->SetShaderFile("shader/vert_pipeline_function_vert_out.vs");

    std::shared_ptr<PipelineStep> spVertexStep(new PipelineStep);
    spVertexStep->AddPipelineFunction(0, spFuncInitGlobalStruct);
    spVertexStep->AddPipelineFunction(1, spFuncVertexProcess);
    spVertexStep->AddPipelineFunction(2, spFuncVertexOut);

    std::cout << "Begin process" << std::endl;
    spVertexStep->Process();
    std::cout << "End process" << std::endl;

    vertexFactory.AddPipelineStep(0, spVertexStep);
    vertexFactory.SetLibraryFile("shader/vert_library_function.vs");

    std::cout << "Begin Generate" << std::endl;
    std::string vertexShaderContent = vertexFactory.GenerateShaderContent();
    std::cout << "End Generate" << std::endl;

    std::ofstream ofile("./vertex.vs", std::ios_base::binary | std::ios_base::out);
    ofile.write(vertexShaderContent.c_str(), vertexShaderContent.length());
    ofile.close();
}