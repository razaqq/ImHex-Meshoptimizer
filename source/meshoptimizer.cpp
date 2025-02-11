#include <hex.hpp>
#include <hex/plugin.hpp>

#include <hex/api/content_registry.hpp>
#include <pl/core/evaluator.hpp>

#include <meshoptimizer.h>

#include <romfs/romfs.hpp>

#include <optional>


IMHEX_PLUGIN_SETUP("meshoptimizer", "razaqq", "meshoptimizer library")
{
	using namespace hex;
	using namespace pl::api;
	using namespace pl::core;

	log::debug("Using romfs: '{}'", romfs::name());

	const Namespace nsMeshopt = { "meshopt" };

	ContentRegistry::PatternLanguage::addFunction(nsMeshopt, "decode_vertex_buffer", FunctionParameterCount::exactly(4), [](auto evaluator, auto params) -> std::optional<Token::Literal>
	{
		const std::vector<u8> in = params[0].toBytes();
		const size_t vertexCount = params[1].toUnsigned();
		size_t vertexSize = params[2].toUnsigned();
		auto& section = evaluator->getSection(params[3].toUnsigned());

		return meshopt_decodeVertexBuffer(section.data(), vertexCount, vertexSize, in.data(), in.size()) == 0;
	});

	ContentRegistry::PatternLanguage::addFunction(nsMeshopt, "decode_index_buffer", FunctionParameterCount::exactly(3), [](auto evaluator, auto params) -> std::optional<Token::Literal>
	{
		const std::vector<u8> in = params[0].toBytes();
		const size_t indexCount = params[1].toUnsigned();
		auto& section = evaluator->getSection(params[2].toUnsigned());

		return meshopt_decodeIndexBuffer<u16>(reinterpret_cast<u16*>(section.data()), indexCount, in.data(), in.size()) == 0;
	});
}
