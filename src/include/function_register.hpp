#pragma once

#include "duckdb/main/extension_util.hpp"
#include "duckdb/common/optional_ptr.hpp"
#include "duckdb/catalog/catalog_entry/scalar_function_catalog_entry.hpp"

namespace duckdb {

class FunctionRegister;
class FunctionRegisterObject;

class FunctionRegister {
public:
	FunctionRegister();
	//! Register a new scalar function - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, ScalarFunction function);
/*	//! Register a new scalar function set - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, ScalarFunctionSet function);
	//! Register a new aggregate function - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, AggregateFunction function);
	//! Register a new aggregate function set - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, AggregateFunctionSet function);
	//! Register a new table function - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, TableFunction function);
	//! Register a new table function set - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, TableFunctionSet function);
	//! Register a new pragma function - throw an exception if the function already exists
	FunctionRegisterObject void RegisterFunction(DatabaseInstance &db, PragmaFunction function);
	//! Register a new pragma function set - throw an exception if the function already exists
	FunctionRegisterObject void RegisterFunction(DatabaseInstance &db, PragmaFunctionSet function);

	//! Register a CreateSecretFunction
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, CreateSecretFunction function);

	//! Register a new copy function - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, CopyFunction function);
	//! Register a new macro function - throw an exception if the function already exists
	FunctionRegisterObject RegisterFunction(DatabaseInstance &db, CreateMacroInfo &info);

	//! Register a new collation
	FunctionRegisterObject RegisterCollation(DatabaseInstance &db, CreateCollationInfo &info);

	//! Add a function overload
	FunctionRegisterObject AddFunctionOverload(DatabaseInstance &db, ScalarFunction function);
	FunctionRegisterObject AddFunctionOverload(DatabaseInstance &db, ScalarFunctionSet function);
	FunctionRegisterObject AddFunctionOverload(DatabaseInstance &db, TableFunctionSet function);

	//! Registers a new type
	FunctionRegisterObject RegisterType(DatabaseInstance &db, string type_name, LogicalType type,
	                                    bind_type_modifiers_function_t bind_type_modifiers = nullptr);

	//! Registers a new secret type
	FunctionRegisterObject RegisterSecretType(DatabaseInstance &db, SecretType secret_type);

	//! Registers a cast between two types
	FunctionRegisterObject RegisterCastFunction(DatabaseInstance &db, const LogicalType &source,
	                                            const LogicalType &target, BoundCastInfo function,
	                                            int64_t implicit_cast_cost = -1);
*/
};

class FunctionRegisterObject {
	duckdb::optional_ptr<FunctionRegister> r;
	DatabaseInstance& db;
	FunctionEntry& entry;
	string name;
public:
	explicit FunctionRegisterObject(FunctionRegister *r, DatabaseInstance& db, FunctionEntry& entry);
	FunctionRegisterObject AddDescription(const char* description);
	FunctionRegisterObject AddExample(const char* example);
};

} // namespace duckdb



