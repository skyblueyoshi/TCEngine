#pragma once

#include "GraphicsResource.h"
#include "Shader.h"

namespace Tce {

    class Program : public GraphicsResource {
    public:
        Program(std::shared_ptr<GraphicsDevice> pDevice,
                std::shared_ptr<Shader> &pVertexShader,
                std::shared_ptr<Shader> &pPixelShader);

        virtual ~Program();

        // 加载
        void Load();

        // 卸载
        void Unload();

        // 获取句柄
        inline uint32_t GetHandle() const { return m_handle; }

    private:
        std::shared_ptr<Shader> &m_pVertexShader;
        std::shared_ptr<Shader> &m_pPixelShader;
        uint32_t m_handle{};
    };

}