#include "duckdb.hpp"
#include "duckdb/function/scalar_function.hpp"

namespace duckdb {

// ---------- per-row helper ----------
static bool ExactMatchRow(const Value &base_val, const Value &resp_val) {
	if (base_val.IsNull() || resp_val.IsNull()) {
		return false;
	}
	return base_val.ToString() == resp_val.ToString();
}

// ---------- exact_match(base, response) -> BOOLEAN ----------
static void ExactMatchFun(DataChunk &args, ExpressionState &, Vector &result) {
	auto &base_vec     = args.data[0];
	auto &response_vec = args.data[1];

	idx_t count = args.size();
	result.SetVectorType(VectorType::FLAT_VECTOR);
	auto result_data = FlatVector::GetData<bool>(result);

	for (idx_t i = 0; i < count; i++) {
		Value base_val     = base_vec.GetValue(i);
		Value response_val = response_vec.GetValue(i);

		result_data[i] = ExactMatchRow(base_val, response_val);
		FlatVector::SetNull(result, i, false);
	}
}

// ---------- compute_metrics(base, response) -> BOOLEAN (for now) ----------
static void ComputeMetricsFun(DataChunk &args, ExpressionState &, Vector &result) {
	auto &base_vec     = args.data[0];
	auto &response_vec = args.data[1];

	idx_t count = args.size();
	result.SetVectorType(VectorType::FLAT_VECTOR);
	auto result_data = FlatVector::GetData<bool>(result);

	for (idx_t i = 0; i < count; i++) {
		Value base_val     = base_vec.GetValue(i);
		Value response_val = response_vec.GetValue(i);

		// reuse the per-row helper
		result_data[i] = ExactMatchRow(base_val, response_val);
		FlatVector::SetNull(result, i, false);
	}
}

// ---------- registration, called from quack_extension.cpp ----------
void RegisterLLMFunctions(ExtensionLoader &loader) {
	ScalarFunction exact_match_func(
	    "exact_match",
	    {LogicalType::VARCHAR, LogicalType::VARCHAR},
	    LogicalType::BOOLEAN,
	    ExactMatchFun);

	ScalarFunction compute_metrics_func(
	    "compute_metrics",
	    {LogicalType::VARCHAR, LogicalType::VARCHAR},
	    LogicalType::BOOLEAN,        // later: STRUCT with many metrics
	    ComputeMetricsFun);

	loader.RegisterFunction(exact_match_func);
	loader.RegisterFunction(compute_metrics_func);
}

} // namespace duckdb
