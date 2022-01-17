#pragma once

#include <map>
#include <sstream>

#include "pipeline_step.h"
#include "utils.h"

class ShaderFactory
{
public:
    ShaderFactory() = default;
    ~ShaderFactory() = default;

    void AddPipelineStep(int key, std::shared_ptr<PipelineStep> spStep)
    {
        auto iter = m_mapStep.find(key);
        if (iter == m_mapStep.end())
        {
            m_mapStep.insert(std::make_pair(key, spStep));
        }
        else
        {
            iter->second = spStep;
        }
    }

    void RemovePipelineStep(int key)
    {
        m_mapStep.erase(key);
    }

    void EnablePipelineStep(int key)
    {
        auto iter = m_mapStep.find(key);
        if (iter != m_mapStep.end())
        {
            iter->second->Enable();
        }
    }

    void DisablePipelineStep(int key)
    {
        auto iter = m_mapStep.find(key);
        if (iter != m_mapStep.end())
        {
            iter->second->Disable();
        }
    }

    void SetLibraryFile(const std::string& strLibraryFile)
    {
        std::string strContent = ReadFileContent(strLibraryFile);
        ShaderParser parser;
        ParserResult result = parser.Parsing(strContent);
        m_strLibraryFunctions = result.strLibraryFunction;
    }

    std::string GenerateShaderContent()
    {
        ParserResult parserContent;;

        std::string globalValue = "state";
        std::string strPipelineFunctionCalls;
        // Construct shader parameters
        for (auto iter = m_mapStep.begin(); iter != m_mapStep.end(); ++iter)
        {
            if (iter->second->IsEnable())
            {
                parserContent.Append(iter->second->GetParserResult());
                strPipelineFunctionCalls += iter->second->GetPipelineFunctionCalls(globalValue);
            }
        }

        std::string strShaderContent;
        strShaderContent += parserContent.strVertexIn + "\n";
        strShaderContent += parserContent.strUniformVarying + "\n";
        strShaderContent += parserContent.strGlobalStructure + "\n";
        strShaderContent += m_strLibraryFunctions + "\n";
        strShaderContent += parserContent.strPipelineFunction + "\n";
        strShaderContent += "void main() {\n";
        strShaderContent += "    GlobalStruct state;";
        strShaderContent += strPipelineFunctionCalls;
        strShaderContent += "}";

        return strShaderContent;
    }

private:
    std::string m_strLibraryFunctions;
    std::map<int, std::shared_ptr<PipelineStep>> m_mapStep;
};