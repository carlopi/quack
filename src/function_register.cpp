#include "function_register.hpp"

using namespace duckdb;

FunctionRegister::FunctionRegister() {
}

FunctionRegisterObject FunctionRegister::RegisterFunction(DatabaseInstance &db, ScalarFunction function) {
	ExtensionUtil::RegisterFunction(db, function);

        auto &system_catalog = Catalog::GetSystemCatalog(db);
        auto data = CatalogTransaction::GetSystemTransaction(db);
        auto &schema = system_catalog.GetSchema(data, DEFAULT_SCHEMA);
        auto catalog_entry = schema.GetEntry(data, CatalogType::SCALAR_FUNCTION_ENTRY, function.name);
        auto &func_entry = catalog_entry->Cast<FunctionEntry>();
	return std::move(FunctionRegisterObject(nullptr, db, func_entry));
}

FunctionRegisterObject::FunctionRegisterObject(FunctionRegister* _r, DatabaseInstance& _db, FunctionEntry& _entry) :  r(_r), db(_db), entry(_entry) {
}

FunctionRegisterObject FunctionRegisterObject::AddDescription(const char * description) {
	entry.description = string(description);

	return std::move(*this);
}

FunctionRegisterObject FunctionRegisterObject::AddExample(const char * example) {
	entry.example = string(example);

	return std::move(*this);
}
