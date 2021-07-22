#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example"), m_CameraPosition(0.0f)
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


		m_Shader.reset(tnah::Shader::Create("assets/shaders/Default.glsl"));

		m_Scene = new tnah::Scene();
		m_Camera = m_Scene->CreateGameObject();
		m_Camera.AddComponent<tnah::CameraComponent>();

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{

		if (tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.y += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.y -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		if (tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.x += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.x -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();		
		glm::mat4 transform = m_Camera.GetComponent<tnah::TransformComponent>().GetTransform();
		tnah::Renderer::BeginScene(m_Camera.GetComponent<tnah::CameraComponent>().Camera, transform);

		tnah::Renderer::Submit(m_VAO, m_Shader);

		tnah::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Controls");
		ImGui::Text("WASD to move the camera Up, Down, Left and Right");
		ImGui::End();
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

	tnah::Scene* m_Scene;
	tnah::GameObject m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	glm::vec3 m_CameraRotationRadians = glm::vec3(0);
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
