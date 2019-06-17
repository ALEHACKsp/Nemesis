#include "stdafx.h"

#include "ConfigExport.hpp"

/**
 * \brief Sets the key and value in the config.
 * \param key the specified key
 * \param value the specified value for the key
 * \return true if successful
 */
auto SetConfigValueExport(const LPCWSTR key, const LPCWSTR value) -> BOOL
{
	return config.Set(key, value);
}

/**
 * \brief Gets the value of the key from the config.
 * \param key the key of the value
 * \return the value
 */
auto GetConfigValueExport(const LPCWSTR key) -> LPCWSTR
{
	return config.Get(key).c_str();
}
