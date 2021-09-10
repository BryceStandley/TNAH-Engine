#pragma once
#include <TNAH/Core/Core.h>
#include "TNAH/Renderer/VertexArray.h"

namespace tnah {

	enum class CullMode
	{
		Front = 0,
		Back = 1,
		Front_And_Back = 2,
		Disabled = 3
	};

	enum class DepthFunc
	{
		Never, Less, Equal, Lequal, Greater, NotEqual, Gequal, Always
	};

	enum class APIEnum
	{
		CullFace, DepthTest, DepthMask,
		FrontFace_CW, FrontFace_CCW,
		CubeMap
	};

	enum class DrawMode
	{
		Points,
		Lines, Line_Strip, Line_Loop, Line_Strip_Adjacency, Lines_Adjacency,
		Triangle_Strip, Triangle_Fan, Triangles, Triangles_Strip_Adjacency, Triangles_Adjacency,
		Patches
	};
	
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void Disable(const APIEnum& value) = 0;
		virtual void Enable(const APIEnum& value) = 0;

		virtual void DrawArray(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawMode& mode = DrawMode::Triangles, void* indicesStart = nullptr) = 0;
		
		virtual void SetWireframe(const bool& enable) = 0;
		virtual bool CheckFullScreen(const int& width, const int& height) = 0;
		virtual void SetCullMode(const CullMode& mode) = 0;
		virtual void SetDepthMask(const bool& enabled) = 0;
		virtual void SetDepthFunc(const DepthFunc& enabled) = 0;
		
		
		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	
	protected:
		virtual int ModeFromDrawMode(const DrawMode& mode) = 0;
	
	private:
		static API s_API;
	};

}

