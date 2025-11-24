#define DUCKDB_EXTENSION_MAIN

#include "quack_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

namespace duckdb {

// Forward declaration – implemented in llm_metrics_extension.cpp
void RegisterLLMFunctions(ExtensionLoader &loader);

// Internal loader that registers all LLMevaluation functions
static void LoadInternal(ExtensionLoader &loader) {
	// Register your LLM evaluation functions (exact_match, compute_metrics, etc.)
	RegisterLLMFunctions(loader);
}

void QuackExtension::Load(ExtensionLoader &loader) {
	LoadInternal(loader);
}

std::string QuackExtension::Name() {
	// This is the name used in SQL:  LOAD 'llmevaluation';
	return "llmevaluation";
}

std::string QuackExtension::Version() const {
#ifdef EXT_VERSION_QUACK
	return EXT_VERSION_QUACK;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

// Entry point for the DuckDB C++ extension
DUCKDB_CPP_EXTENSION_ENTRY(quack, loader)
 {
	duckdb::LoadInternal(loader);
}

}
