#include "ApplicationLayer.h"


ApplicationLayer::ApplicationLayer()
	:tnah::Layer("Layer")
{
	//Load a scene here to m_ActiveScene
	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	//Or 
	//m_ActiveScene = tnah::Scene::CreateSceneFromFile("Path to the .scene file");

	//Create gameobjects within the scene using the CreateGameObject function and pass in a name/tag
	m_CameraObject = m_ActiveScene->CreateGameObject("Camera");

	//Add a component to the object and get a reference to it with Add Component
	auto& camera = m_CameraObject->AddComponent<tnah::CameraComponent>();

	//Access the component and its objects
	camera.Primary = true;
	camera.Camera.SetViewportSize(1280, 720);

	//All game objects have a transform component, you can get it with the GetComponent function
	auto& transform = m_CameraObject->GetComponent<tnah::TransformComponent>();

	//Transforms have a position, rotation and scale on the XYZ axis
	transform.Position = glm::vec3(10, 10, 10);
	transform.Scale = glm::vec3(2, 2, 2);
}

void ApplicationLayer::OnUpdate(tnah::Timestep deltaTime)
{
	//Called every frame
	//Use OnUpdate to control things like input and movement

	auto& t = m_CameraObject->GetComponent<tnah::TransformComponent>();

	if (tnah::Input::IsKeyPressed(tnah::Key::W))
	{
		//Moving the camera forward at a speed of 5
		t.Position += t.Forward * 5.0f * deltaTime.GetSeconds();
	}

	if (tnah::Input::IsKeyPressed(tnah::Key::S))
	{
		//Moving the camera backwards at a speed of 5
		t.Position -= t.Forward * 5.0f * deltaTime.GetSeconds();
	}

	if (tnah::Input::IsKeyPressed(tnah::Key::D))
	{
		//Moving the camera right at a speed of 5
		t.Position += t.Right * 5.0f * deltaTime.GetSeconds();
	}

	if (tnah::Input::IsKeyPressed(tnah::Key::A))
	{
		//Moving the camera left at a speed of 5
		t.Position -= t.Right * 5.0f * deltaTime.GetSeconds();
	}


	//The scene always needs to be updated at the end of the OnUpdate Function
	// When the scene updates, it updates objects transforms, sets up rendering for the frame
	// and submits the required data to be rendered. if you dont update the scene,
	// NOTHING will be rendered to the screen except ImGui
	m_ActiveScene->OnUpdate(deltaTime);
}

void ApplicationLayer::OnFixedUpdate(tnah::PhysicsTimestep ps)
{
	//Called at fixed intervals
	//use OnFixedUpdate to update objects inline with physics updates

	m_ActiveScene->OnFixedUpdate(ps);
}

void ApplicationLayer::OnImGuiRender()
{
	//Called every frame
	//Use OnImGuiRender to render a imgui panel for the layer
	//Great to add debuging views or manipulate objects at runtime

	ImGui::Begin("Panel Name");

	//Panel ImGui specific calls go here eg.
	ImGui::Text("This is a Text Example!");

	//Or in a Collapsable header
	if (ImGui::CollapsingHeader("This header can collapse!"))
	{
		ImGui::BulletText("Great for grouping settings or text within the panel!");
		ImGui::BulletText("Im more text inside the header!");
		ImGui::ColorEdit3("Colors!", m_Colors);
	}

	//Make sure you end the panel!
	ImGui::End();
}

void ApplicationLayer::OnEvent(tnah::Event& event)
{
	//Called when an event has happened
	//Can be used to trigger input, change settings or update objects

	//I.e Updating the camera viewport when the window resizes
	// if the viewport doesn't get updated within the camera, the camera
	// wont display or renderer to the whole window. 

	if (event.GetEventType() == tnah::EventType::WindowResize)
	{
		auto& re = (tnah::WindowResizeEvent&)event;
		uint32_t  width = re.GetWidth();
		uint32_t height = re.GetHeight();
		if (m_CameraObject != nullptr)
		{
			auto& c = m_CameraObject->GetComponent<tnah::CameraComponent>();
			c.Camera.SetViewportSize(width, height);
		}
	}
}
