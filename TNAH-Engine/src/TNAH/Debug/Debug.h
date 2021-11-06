#pragma once

namespace tnah{
	namespace Debug{

		static void CoreInfo(const glm::vec3& value, const std::string& message = "")
		{
			TNAH_CORE_INFO("(Debug): {0}: X({1}) - Y({2}) - Z({3})",message, value.x, value.y, value.z);
		}

		static void CoreInfo(const glm::quat& val, const std::string& message = "")
		{
			TNAH_CORE_INFO("(Debug): {0}: X({1}) - Y({2}) - Z({3}) - W({4})",message, val.x, val.y, val.z, val.w);
		}

		static void CoreInfo(const glm::vec3& value)
		{
			TNAH_CORE_INFO("(Debug): X({0}) - Y({1}) - Z({2})", value.x, value.y, value.z);
		}

		static void CoreWarm(const glm::vec3& value)
		{
			TNAH_CORE_WARN("(Debug): X({0}) - Y({1}) - Z({2})", value.x, value.y, value.z);
		}

		static void CoreError(const glm::vec3& value)
		{
			TNAH_CORE_ERROR("(Debug): X({0}) - Y({1}) - Z({2})", value.x, value.y, value.z);
		}

	}
}