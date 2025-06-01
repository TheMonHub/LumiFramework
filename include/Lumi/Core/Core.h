//
// Created by Mono on 1/6/2025.
//

#ifndef CORE_H
#define CORE_H

#include <string>
#include "Lumi/Core/Lumi_export.h"

/**
 * @file Core.h
 * @brief Core library of the Lumi framework.
 *
 * LumiCore provides the foundational functionality and essential utilities for
 * the entire Lumi framework. It defines core namespaces and fundamental features
 * used across various modules.
 *
 * This file specifically declares the main `Lumi::Core` class, which serves
 * as a central access point for core framework operations.
 *
 * @note This is a fundamental module and is typically required by most other Lumi components.
 */

namespace Lumi {

	/**
	 * @brief The main Core class for the Lumi framework.
	 *
	 * This class encapsulates core functionalities and serves as a central point
	 * for framework-wide operations or access to core utilities.
	 * It provides methods to query framework information like version and license details.
	 *
	 * @ingroup core_module // Optional: Use this to group related classes in Doxygen output.
	 * // You'd define `core_module` in your Doxyfile or another comment block.
	 */
	class LUMI_DEPRECATED_API_EXPORT Core {
		public:
			/**
			 * @brief Get the current version of the Lumi Core library.
			 *
			 * @return A string representing the current version of the Lumi Core library,
			 * typically in "major.minor.patch" format (e.g., "1.2.3").
			 */
			static LUMI_API std::string GetVersion();

			/**
			 * @brief Get the license text for the Lumi Core library.
			 *
			 * @return A string containing the full license text under which the Lumi
			 * Framework is distributed.
			 */
			static LUMI_API std::string GetLicense();
	};

} // namespace Lumi

#endif // CORE_H
