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

		/**
		 * @fn	inline static void RenderCommand::DrawArray(const Ref<VertexArray> vertexArray)
		 *
		 * @brief	Draws using the VAO and a glDrawArrays call
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 */

		inline static void DrawArray(const Ref<VertexArray> vertexArray)
		{
			s_RendererAPI->DrawArray(vertexArray);
		}

		/**
		 * @fn	inline static void RenderCommand::DrawArray(std::string type, uint32_t size)
		 *
		 * @brief	Draws according to type and size, using glDrawArrays
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	type	The type.
		 * @param 	size	The size.
		 */

		inline static void DrawArray(std::string type, uint32_t size)
		{
			s_RendererAPI->DrawArray(type, size);
		}

		/**
		 * @fn	inline static void RenderCommand::DrawIndexed(const Ref<VertexArray> vertexArray)
		 *
		 * @brief	Draws using glDrawElements
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 */

		inline static void DrawIndexed(const Ref<VertexArray> vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
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

		/**
		 * @fn	inline static void RenderCommand::SetDepthFunc(const RendererAPI::DepthFunc& func)
		 *
		 * @brief	Sets depth function
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	func	The function.
		 */

		inline static void SetDepthFunc(const RendererAPI::DepthFunc& func)
		{
			s_RendererAPI->SetDepthFunc(func);
		}

		/**
		 * @fn	inline static void RenderCommand::Disable(const RendererAPI::APIEnum& value)
		 *
		 * @brief	Disables the given value
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	value	The value.
		 */

		inline static void Disable(const RendererAPI::APIEnum& value)
		{
			s_RendererAPI->Disable(value);
		}

		/**
		 * @fn	inline static void RenderCommand::Enable(const RendererAPI::APIEnum& value)
		 *
		 * @brief	Enables the given value
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	value	The value.
		 */

		inline static void Enable(const RendererAPI::APIEnum& value)
		{
			s_RendererAPI->Enable(value);
		}

	private:

		/** @brief	The renderer api */
		static RendererAPI* s_RendererAPI;
	};

}

