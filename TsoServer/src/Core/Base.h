#include <memory>
namespace TServer
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
} // namespace TServer
