#pragma once

#include <sstream>

struct ParserResult
{
    // TODO: consider duplicate string occured in different shader file
    std::string strVertexIn;
    std::string strUniformVarying;
    std::string strGlobalStructure;
    std::string strLibraryFunction;
    std::string strPipelineFunction;

    void Clear()
    {
        strVertexIn ="";
        strUniformVarying = "";
        strGlobalStructure = "";
        strLibraryFunction = "";
        strPipelineFunction = "";
    }

    void Append(const ParserResult& parserResult)
    {
        strVertexIn += parserResult.strVertexIn;
        strUniformVarying += parserResult.strUniformVarying;
        strGlobalStructure += parserResult.strGlobalStructure;
        strLibraryFunction += parserResult.strLibraryFunction;
        strPipelineFunction += parserResult.strPipelineFunction;
    }

    void PrintSelf()
    {
        std::cout << "\n";
        std::cout << "VertexIn: " << strVertexIn << std::endl;
        std::cout << "UniformVarying: " << strUniformVarying << std::endl;
        std::cout << "GlobalStructure: " << strGlobalStructure << std::endl;
        std::cout << "LibraryFunc: " << strLibraryFunction << std::endl;
        std::cout << "PipelineFunc: " << strPipelineFunction << std::endl;
        std::cout << std::endl;
    }
};

class ShaderParser
{
public:
    ShaderParser() = default;
    ~ShaderParser() = default;

    ParserResult Parsing(const std::string& strShaderContent)
    {
        std::cout << "shaderContent: " << strShaderContent << std::endl;
        std::cout << "======================" << std::endl;
        std::stringstream ss;
        ss << strShaderContent;
        std::string strLine;

        ParseBlockType eCurBlockType = UNDEFINED;
        ParserResult result;
        while (getline(ss, strLine))
        {
            std::cout << "*************** Line: " << strLine << std::endl;
            // If the eCurBlockType is changed, return true
            // else return false
            if (!UpdateBlockType(strLine, eCurBlockType))
            {
                switch (eCurBlockType)
                {
                case VERTEXIN:
                    result.strVertexIn += strLine;
                    break;
                case UNIFORM_VARYING:
                    result.strUniformVarying += strLine;
                    break;
                case GLOBAL_STRUCTURE:
                    result.strGlobalStructure += strLine;
                    break;
                case LIBRARY_FUNCTION:
                    result.strLibraryFunction += strLine;
                    break;
                case PIPELINE_FUNCTION:
                    result.strPipelineFunction += strLine;
                    break;
                }
            }
        }

        std::cout << "======================" << std::endl;
        result.PrintSelf();
        std::cout << "======================" << std::endl;
        return result;
    }

private:
    enum ParseBlockType
    {
        UNDEFINED,
        VERTEXIN,
        UNIFORM_VARYING,
        GLOBAL_STRUCTURE,
        LIBRARY_FUNCTION,
        PIPELINE_FUNCTION
    };

    bool UpdateBlockType(const std::string& strLine, ParseBlockType& eCurBlockType)
    {
        auto processPerBlock = [&eCurBlockType](const std::string &strLine,
                                             ParseBlockType eBlockType,
                                             const std::string &strBegin,
                                             const std::string &strEnd,
                                             const std::string &strErrorMsg) -> bool {
            if (strLine.find(strBegin) != std::string::npos)
            {
                eCurBlockType = eBlockType;
                return true;
            }
            else if (strLine.find(strEnd) != std::string::npos)
            {
                if (eCurBlockType != eBlockType)
                {
                    std::cout << strErrorMsg << std::endl;
                    throw std::runtime_error(strErrorMsg);
                }
                eBlockType = UNDEFINED;
                return true;
            }
            return false;
        };

        if (processPerBlock(strLine, VERTEXIN, m_strBeginVertexIn, m_strEndVertexIn, "Begin End VertexIn not in pair"))
        {
            return true;
        }
        if (processPerBlock(strLine, UNIFORM_VARYING, m_strBeginUniformVarying, m_strEndUniformVarying, "Begin End UniformVarying not in pair"))
        {
            return true;
        }
        if (processPerBlock(strLine, GLOBAL_STRUCTURE, m_strBeginGlobalStructure, m_strEndGlobalStructure, "Begin End GlobalStructure not in pair"))
        {
            return true;
        }
        if (processPerBlock(strLine, LIBRARY_FUNCTION, m_strBeginLibraryFunction, m_strEndLibraryFunction, "Begin End LibraryFunction not in pair"))
        {
            return true;
        }
        if (processPerBlock(strLine, PIPELINE_FUNCTION, m_strBeginPipelineFunction, m_strEndPipelineFunction, "Begin End PipelineFunction not in pair"))
        {
            return true;
        }

        return false;
    }

    const std::string m_strBeginVertexIn = "//BEGIN_VERTEXIN";
    const std::string m_strEndVertexIn = "//END_VERTEXIN";

    const std::string m_strBeginUniformVarying = "//BEGIN_UNIFORM_VARYING";
    const std::string m_strEndUniformVarying = "//END_UNIFORM_VARYING";

    const std::string m_strBeginGlobalStructure = "//BEGIN_GLOBAL_STRUCTURE";
    const std::string m_strEndGlobalStructure = "//END_GLOBAL_STRUCTURE";

    const std::string m_strBeginLibraryFunction = "//BEGIN_LIBRARY_FUNCTION";
    const std::string m_strEndLibraryFunction = "//END_LIBRARY_FUNCTION";

    const std::string m_strBeginPipelineFunction = "//BEGIN_PIPELINE_FUNCTION";
    const std::string m_strEndPipelineFunction = "//END_PIPELINE_FUNCTION";

};