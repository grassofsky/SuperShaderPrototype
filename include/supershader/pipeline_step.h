#pragma once

#include <memory>
#include <string>
#include <map>

#include "pipeline_function.h"
#include "shader_parser.h"

class PipelineFunction;

class PipelineStep
{
public:
    PipelineStep() = default;
    ~PipelineStep() = default;

    void AddPipelineFunction(int key, std::shared_ptr<PipelineFunction> spFunc)
    {
        auto iter = m_mapPipelineFunction.find(key);
        if (iter == m_mapPipelineFunction.end())
        {
            m_mapPipelineFunction.insert(std::make_pair(key, spFunc));
        }
        else
        {
            iter->second = spFunc;
        }
    }

    void RemovePipelineFunction(int key)
    {
        m_mapPipelineFunction.erase(key);
    }

    void EnablePipelineFunction(int key)
    {
        auto iter = m_mapPipelineFunction.find(key);
        if (iter != m_mapPipelineFunction.end())
        {
            iter->second->Enable();
        }
    }

    void DisablePipelineFunction(int key)
    {
        auto iter = m_mapPipelineFunction.find(key);
        if (iter != m_mapPipelineFunction.end())
        {
            iter->second->Disable();
        }
    }

    bool IsEnable() { return m_bEnabled; }

    void Enable() { m_bEnabled = true; }

    void Disable() { m_bEnabled = false; }

    // Construct shaders from pipeline functions,
    // before doing this, the pipeline function state should be set
    void Process()
    {
        m_pipelineStepContent.Clear();
        for (auto iter = m_mapPipelineFunction.begin(); iter != m_mapPipelineFunction.end(); ++iter)
        {
            if (iter->second->IsEnable())
            {
                m_pipelineStepContent.Append(iter->second->GetParserResult());
            }
        }
    }

    const ParserResult& GetParserResult()
    {
        return m_pipelineStepContent;
    }

    std::string GetPipelineFunctionCalls(std::string globalValue)
    {
        std::string result;
        for (auto iter = m_mapPipelineFunction.begin(); iter != m_mapPipelineFunction.end(); ++iter)
        {
            if (iter->second->IsEnable())
            {
                result += ("\tstep_" + iter->second->GetName() + "(" + globalValue + ");\n");
            }
        }
        return result;
    }

private:
    ParserResult m_pipelineStepContent;
    bool m_bEnabled = true;
    std::map<int, std::shared_ptr<PipelineFunction>> m_mapPipelineFunction;
};
