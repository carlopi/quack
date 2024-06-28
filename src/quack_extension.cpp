#define DUCKDB_EXTENSION_MAIN
#include "duckdb.hpp"
#include "duckdb/parser/parser_extension.hpp"
#include "duckdb/parser/parsed_data/create_table_function_info.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/parser/parsed_data/create_scalar_function_info.hpp"
#include "duckdb/parser/parsed_data/create_type_info.hpp"
#include "duckdb/catalog/catalog_entry/type_catalog_entry.hpp"
#include "duckdb/planner/extension_callback.hpp"
#include "duckdb/function/cast/cast_function_set.hpp"
#include "duckdb/main/extension_util.hpp"
#include "duckdb/common/vector_operations/generic_executor.hpp"
#include "duckdb/common/exception/conversion_exception.hpp"
#include "duckdb/planner/expression/bound_constant_expression.hpp"

#include "quack_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/function/scalar_function.hpp"
#include "duckdb/main/extension_util.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>
#include "function_register.hpp"

// OpenSSL linked through vcpkg
#include <openssl/opensslv.h>

namespace duckdb {


inline void QuackScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    auto &name_vector = args.data[0];
    UnaryExecutor::Execute<string_t, string_t>(
	    name_vector, result, args.size(),
	    [&](string_t name) {
			return StringVector::AddString(result, "Quack "+name.GetString()+" 🐥");;
        });
}

inline void QuackOpenSSLVersionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    auto &name_vector = args.data[0];
    UnaryExecutor::Execute<string_t, string_t>(
	    name_vector, result, args.size(),
	    [&](string_t name) {
			return StringVector::AddString(result, "Quack " + name.GetString() +
                                                     ", my linked OpenSSL version is " +
                                                     OPENSSL_VERSION_TEXT );;
        });
}

static void LoadInternal(DatabaseInstance &instance) {
    // Register a scalar function
    auto quack_scalar_function = ScalarFunction("quack", {LogicalType::VARCHAR}, LogicalType::VARCHAR, QuackScalarFun);
    FunctionRegister quack;
    quack.RegisterFunction(instance, quack_scalar_function).AddDescription("A demo scalar function").AddExample("SELECT quack('DuckDB')");

    // Register another scalar function
    auto quack_openssl_version_scalar_function = ScalarFunction("quack_openssl_version", {LogicalType::VARCHAR},
                                                LogicalType::VARCHAR, QuackOpenSSLVersionScalarFun);
    quack.RegisterFunction(instance, quack_openssl_version_scalar_function).AddDescription("Another demo scalar function");
}

void QuackExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string QuackExtension::Name() {
	return "quack";
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

DUCKDB_EXTENSION_API void quack_init(duckdb::DatabaseInstance &db) {
	LoadInternal(db);
    //db_wrapper.LoadExtension<duckdb::QuackExtension>();
}

DUCKDB_EXTENSION_API const char *quack_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
