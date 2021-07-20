#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example"), m_SceneCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VAO.reset(tnah::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<tnah::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(tnah::VertexBuffer::Create(vertices, sizeof(vertices)));
		tnah::BufferLayout layout = {
			{ tnah::ShaderDataType::Float3, "a_Position" },
			{ tnah::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VAO->AddVertexBuffer(vertexBuffer);



		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<tnah::IndexBuffer> indexBuffer;
		indexBuffer.reset(tnah::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VAO->SetIndexBuffer(indexBuffer);


		m_SquareVAO.reset(tnah::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<tnah::VertexBuffer> squareVB;
		squareVB.reset(tnah::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ tnah::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVAO->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<tnah::IndexBuffer> squareIB;
		squareIB.reset(tnah::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new tnah::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_SquareShader.reset(new tnah::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{

		if (tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		if (tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();

		m_SceneCamera.SetPosition(m_CameraPosition);

		if (tnah::Input::IsKeyPressed(tnah::Key::Left))
		{
			m_SceneCamera.SetRotation(m_SceneCamera.GetRotation() + 2.0f * deltaTime.GetSeconds());
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::Right))
		{
			m_SceneCamera.SetRotation(m_SceneCamera.GetRotation() - 2.0f * deltaTime.GetSeconds());
			m_SceneCamera.SetRotation(m_SceneCamera.GetRotation() - 2.0f * deltaTime.GetSeconds());
		}


		tnah::Renderer::BeginScene(m_SceneCamera);

		tnah::Renderer::Submit(m_SquareVAO, m_SquareShader);

		tnah::Renderer::Submit(m_VAO, m_Shader);

		tnah::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(tnah::Event& event) override
	{
		tnah::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<tnah::KeyPressedEvent>(TNAH_BIND_EVENTS_FN(TestLayer::OnKeyPressed));
		
	}

	bool OnKeyPressed(tnah::KeyPressedEvent& e)
	{

		return false;
		
	}

private:
	tnah::Ref<tnah::Shader> m_Shader;
	tnah::Ref<tnah::VertexArray> m_VAO;

	tnah::Ref<tnah::Shader> m_SquareShader;
	tnah::Ref<tnah::VertexArray> m_SquareVAO;
	tnah::SceneCamera m_SceneCamera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
};

class Editor : public tnah::Application
{
public:
	Editor()
		:tnah::Application("TNAH Editor")
	{
		PushOverlay(new TestLayer());
	}


	~Editor()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}
