#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/ext/matrix_float3x3.hpp>

namespace tnah::Physics
{
	enum BodyType {Dynamic, Static};

	struct BodyMass 
	{
		BodyMass() { SetMass(); }

		void SetMass(float mass = 1.0f) 
		{
			Mass = mass;
			InverseMass = 1.0f / Mass;
		}

		glm::vec3 CentreOfMass = {};
		float Mass = 1.0f;
		float InverseMass = 1.0f;
	};

	struct LinearDampening 
	{
		float Dampening = 0.0f;

		float operator = (const float& value)
		{
			Dampening = value;
			return Dampening;
		}

		operator float() const 
		{
			return Dampening;
		}
	};


	struct AngularDampening
	{
		float Dampening = 0.0f;

		float operator = (const float& value)
		{
			Dampening = value;
			return Dampening;
		}

		operator float() const
		{
			return Dampening;
		}
	};



	//velocities

	struct LinearVelocity 
	{
		glm::vec3 Velocity = {};

		operator glm::vec3() { return Velocity; }
		operator glm::vec3() const { return Velocity; }
	};

	struct AngularVelocity 
	{
		glm::vec3 Velocity = {};

		operator glm::vec3() { return Velocity; }
		operator glm::vec3() const { return Velocity; }
	};


	//force torque

	struct Force
	{
		glm::vec3 Forces = {};

		glm::vec3 operator = (const glm::vec3& value) 
		{
			Forces = value;
			return Forces;
		}
	};

	struct Torque
	{
		glm::vec3 Torques = {};

		glm::vec3 operator = (const glm::vec3& value) 
		{
			Torques = value;
			return Torques;
		}
	};

	//Inertia tensor

	struct InertiaTensor 
	{
		glm::mat3 Tensor = glm::mat3(1.0f);
		glm::mat3 InvesrseTensor = glm::inverse(Tensor);
	};
}