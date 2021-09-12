#pragma once
#include <TNAH/Core/Core.h>
#include "TNAH/Renderer/VertexArray.h"

namespace tnah {

	/**
	 * @enum	CullMode
	 *
	 * @brief	Values that represent cull modes
	 */

	enum class CullMode
	{
		Front = 0,
		Back = 1,
		Front_And_Back = 2,
		Disabled = 3
	};

	/**
	 * @class	RendererAPI
	 *
	 * @brief	A renderer API class that provides the functions required to render, regardless of API used
	 *
	 * @author	Plush
	 * @date	12/09/2021
	 */

	class RendererAPI
	{
	public:

		/**
		 * @enum	API
		 *
		 * @brief	Values that represent apis
		 */

		enum class API
		{
			None = 0, OpenGL = 1
		};

		/**
		 * @enum	DepthFunc
		 *
		 * @brief	Values that represent depth Functions
		 */

		enum class DepthFunc
		{
			Never, Less, Equal, Lequal, Greater, NotEqual, Gequal, Always
		};

		/**
		 * @enum	APIEnum
		 *
		 * @brief	Values that represent API enums
		 */

		enum class APIEnum
		{
			CullFace, DepthTest, DepthMask,
			FrontFace_CW, FrontFace_CCW,
			CubeMap
		};
	
	public:

		/**
		 * @fn	virtual RendererAPI::~RendererAPI() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 */

		virtual ~RendererAPI() = default;

		/**
		 * @fn	virtual void RendererAPI::Init() = 0;
		 *
		 * @brief	Initializes this object
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 */

		virtual void Init() = 0;

		/**
		 * @fn	virtual void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
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

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetClearColor(const glm::vec4& color) = 0;
		 *
		 * @brief	Sets clear color
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	color	The color.
		 */

		virtual void SetClearColor(const glm::vec4& color) = 0;

		/**
		 * @fn	virtual void RendererAPI::Clear() = 0;
		 *
		 * @brief	Clears this object to its blank/initial state
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 */

		virtual void Clear() = 0;

		/**
		 * @fn	virtual void RendererAPI::Disable(const APIEnum& value) = 0;
		 *
		 * @brief	Disables the given value
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	value	The value.
		 */

		virtual void Disable(const APIEnum& value) = 0;

		/**
		 * @fn	virtual void RendererAPI::Enable(const APIEnum& value) = 0;
		 *
		 * @brief	Enables the given value
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	value	The value.
		 */

		virtual void Enable(const APIEnum& value) = 0;

		/**
		 * @fn	virtual void RendererAPI::DrawArray(const Ref<VertexArray>& vertexArray) = 0;
		 *
		 * @brief	Draw array
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 */

		virtual void DrawArray(const Ref<VertexArray>& vertexArray) = 0;

		/**
		 * @fn	virtual void RendererAPI::DrawArray(std::string type, uint32_t size) = 0;
		 *
		 * @brief	Draw array
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	type	The type.
		 * @param 	size	The size.
		 */

		virtual void DrawArray(std::string type, uint32_t size) = 0;

		/**
		 * @fn	virtual void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		 *
		 * @brief	Draw indexed
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 */

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetWireframe(const bool& enable) = 0;
		 *
		 * @brief	Sets a wireframe
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	enable	True to enable, false to disable.
		 */

		virtual void SetWireframe(const bool& enable) = 0;

		/**
		 * @fn	virtual bool RendererAPI::CheckFullScreen(const int& width, const int& height) = 0;
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

		virtual bool CheckFullScreen(const int& width, const int& height) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetCullMode(const CullMode& mode) = 0;
		 *
		 * @brief	Sets cull mode
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	mode	The mode.
		 */

		virtual void SetCullMode(const CullMode& mode) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetDepthMask(const bool& enabled) = 0;
		 *
		 * @brief	Sets depth mask
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	enabled	True to enable, false to disable.
		 */

		virtual void SetDepthMask(const bool& enabled) = 0;

		/**
		 * @fn	virtual void RendererAPI::SetDepthFunc(const DepthFunc& enabled) = 0;
		 *
		 * @brief	Sets depth function
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @param 	enabled	The enabled.
		 */

		virtual void SetDepthFunc(const DepthFunc& enabled) = 0;

		/**
		 * @fn	static API RendererAPI::GetAPI()
		 *
		 * @brief	Gets api
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @returns	api.
		 */

		static API GetAPI() { return s_API; }

		/**
		 * @fn	static Scope<RendererAPI> RendererAPI::Create();
		 *
		 * @brief	Creates a unique ptr to the API ;
		 *
		 * @author	Plush
		 * @date	12/09/2021
		 *
		 * @returns	A unique ptr to the API;
		 */

		static Scope<RendererAPI> Create();
		
	private:

		/** @brief	The API */
		static API s_API;
	};

}

