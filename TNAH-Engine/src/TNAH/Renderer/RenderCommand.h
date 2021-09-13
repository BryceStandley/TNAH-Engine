#pragma once

#include "RendererAPI.h"
namespace tnah {

	/**
	 * @class	RenderCommand
	 *
	 * @brief	A render command class that makes use of the renderer API to perform openGL renderer actions
	 *
	 * @author	Plush
	 * @date	12/09/2021
	 */

	class RenderCommand
	{
	public:

		/**
		 * @fn	inline static void RenderCommand::Init()
		 *
		 * @brief	Initializes this object
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 */

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		/**
		 * @fn	inline static void RenderCommand::SetClearColor(const glm::vec4& color)
		 *
		 * @brief	Sets clear color
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	color	The color.
		 */

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		/**
		 * @fn	inline static void RenderCommand::Clear()
		 *
		 * @brief	Clears this object to its blank/initial state
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 */

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawArray(const Ref<VertexArray> vertexArray, const DrawMode& mode = DrawMode::Triangles)
		{
			s_RendererAPI->DrawArray(vertexArray, mode);
		}

		inline static void DrawIndexed(const Ref<VertexArray> vertexArray, const  DrawMode& mode = DrawMode::Triangles, void* indicesStart = nullptr)
		{
			s_RendererAPI->DrawIndexed(vertexArray, mode, indicesStart);
		}

		
		/**
		 * @fn	inline static void RenderCommand::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
		 *
		 * @brief	Sets a viewport
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	x	  	An uint32_t to process.
		 * @param 	y	  	An uint32_t to process.
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		inline static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		/**
		 * @fn	inline static void RenderCommand::SetWireframe(const bool& enable)
		 *
		 * @brief	Sets a wireframe
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	enable	True to enable, false to disable.
		 */

		inline static void SetWireframe(const bool& enable)
		{
			s_RendererAPI->SetWireframe(enable);
		}

		/**
		 * @fn	inline static bool RenderCommand::CheckFullScreen(const int width, const int height)
		 *
		 * @brief	Check full screen
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		inline static bool CheckFullScreen(const int width, const int height)
		{
			return s_RendererAPI->CheckFullScreen(width, height);
		}

		/**
		 * @fn	inline static void RenderCommand::SetCullMode(const CullMode& mode)
		 *
		 * @brief	Sets cull mode
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	mode	The mode.
		 */

		inline static void SetCullMode(const CullMode& mode)
		{
			s_RendererAPI->SetCullMode(mode);
		}

		/**
		 * @fn	inline static void RenderCommand::SetDepthMask(const bool& enabled)
		 *
		 * @brief	Sets depth mask
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	enabled	True to enable, false to disable.
		 */

		inline static void SetDepthMask(const bool& enabled)
		{
			s_RendererAPI->SetDepthMask(enabled);
		}

		inline static void SetDepthFunc(const DepthFunc& func)
		{
			s_RendererAPI->SetDepthFunc(func);
		}
		
		inline static void Disable(const APIEnum& value)
		{
			s_RendererAPI->Disable(value);
		}

		inline static void Enable(const APIEnum& value)
		{
			s_RendererAPI->Enable(value);
		}

	private:

		/** @brief	The renderer api */
		static RendererAPI* s_RendererAPI;
	};

}

