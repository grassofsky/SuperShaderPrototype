#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include "shader_parser.h"
#include "utils.h"

class PipelineFunction
{
public:
    PipelineFunction(const std::string& name) : m_strName(name)
    {

    }

    ~PipelineFunction() = default;

    bool IsEnable() { return m_bEnabled; }

    void Enable() { m_bEnabled = true; }

    void Disable() { m_bEnabled = false; }

    void SetShaderFile(const std::string& strShaderFile)
    {
        std::cout << "Start SetShaderFile " << strShaderFile << std::endl;
        m_strShaderContent = ReadFileContent(strShaderFile);
        
        ShaderParser parser;
        m_parserResult = parser.Parsing(m_strShaderContent);

        std::cout << "End SetShaderFile " << strShaderFile << std::endl;
    }

    void SetShaderString(const std::string& strShaderContent)
    {
        m_strShaderContent = strShaderContent;
        ShaderParser parser;
        m_parserResult = parser.Parsing(m_strShaderContent);
    }

    std::string GetName()
    {
        return m_strName;
    }

    const ParserResult& GetParserResult()
    {
        return m_parserResult;
    }

private:
    ParserResult m_parserResult;
    bool m_bEnabled = true;
    std::string m_strName = "";
    std::string m_strShaderContent;
};