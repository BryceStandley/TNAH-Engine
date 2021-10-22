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
		glm::vec3 AngularVelocity = {};

		operator glm::vec3() { return AngularVelocity; }
		operator glm::vec3() const { return AngularVelocity; }
	};


	//force torque

	struct Force
	{
		glm::vec3 Force = {};

		glm::vec3 operator = (const glm::vec3& value) 
		{
			Force = value;
			return Force;
		}
	};

	struct Torque
	{
		glm::vec3 Torque = {};

		glm::vec3 operator = (const glm::vec3& value) 
		{
			Torque = value;
			return Torque;
		}
	};

	//Inertia tensor

	struct InertiaTensor 
	{
		glm::mat3 InertiaTensor = glm::mat3(1.0f);
		glm::mat3 InvesrseInertiaTensor = glm::inverse(InertiaTensor);
	};
}