#pragma once
#include "Core.h"
#include <xhash>

namespace tnah {

		class UUID
		{
		public:
			UUID();
			UUID(uint64_t uuid);
			UUID(const UUID& other);

			operator uint64_t () { return m_UUID; }
			operator const uint64_t() const { return m_UUID; }
		private:
			uint64_t m_UUID;
		};
}

namespace std {

	template <>
	struct hash<tnah::UUID>
	{
		std::size_t operator()(const tnah::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}