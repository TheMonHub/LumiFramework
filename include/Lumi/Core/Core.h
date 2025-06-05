//
// Created by Mono on 1/6/2025.
//

#ifndef CORE_H
#define CORE_H

#include <string>

/**
 * @file Core.h
 * @brief Core header of the Lumi framework.
 *
 * This file specifically declares the main `Lumi::Core` class, which serves
 * as a central access point for core framework operations.
 *
 * @note This is a fundamental module and is required by other Lumi components.
 *
 * @ingroup Core
 *
 * @defgroup Core Core
 * @brief Core library of the Lumi framework.
 *
 * LumiCore provides the foundational functionality and essential utilities for
 * the entire Lumi framework. It defines core namespaces and fundamental features
 * used across various modules.
 */

/**
 * @namespace Lumi
 * @brief The main namespace for the Lumi framework.
 *
 * A Central namespace that encapsulates all classes, functions, and utilities
 * of the Lumi framework. It serves as the primary namespace for all Lumi-related
 * components and functionalities.
 */
namespace Lumi {

    /**
	 * @brief The main Core class for the Lumi framework.
	 *
	 * This class encapsulates core functionalities and serves as a central point
	 * for framework-wide operations or access to core utilities.
	 * It provides methods to query framework information like version and license details.
	 * @ingroup Core
	 */
	namespace Core {

		/**
		 * @name Version Information
		 * @brief Methods to query the version of the Lumi Core library.
		 * @{
		 */

       /**
		 * @brief Get the current version of the Lumi Core library.
		 *
		 * @return A string literal representing the current version of the Lumi Core library,
		 * typically in "major.minor.patch" format (e.g., "1.2.3").
		 */
		std::string_view GetVersionString();

		/**
		 * @brief Get the major version number of the Lumi Core library.
		 *
		 * @return The major version number (e.g., 1 for version "1.2.3").
		 */
       unsigned int GetVersionMajor();

       /**
       * @brief Get the minor version number of the Lumi Core library.
       *
       * @return The minor version number (e.g., 2 for version "1.2.3").
       */
       unsigned int GetVersionMinor();

       /**
        * @brief Get the patch version number of the Lumi Core library.
        *
        * @return The patch version number (e.g., 3 for version "1.2.3").
        */
       unsigned int GetVersionPatch();

       /** @} */

       /**
        * @name License Information
        * @brief Methods to query license details of the Lumi Framework.
        * @{
        */

       /**
        * @brief Get the license text for the Lumi Core library.
        *
        * @return A string literal containing the full license text under which the Lumi
        * Framework is distributed.
        *
        * @note This method can return an empty string if the license file is not available at build time. To check if the license is available, you can check the `LicenseAvailable` method.
        */
       std::string_view GetLicense();

       /**
        * @brief Check if the Lumi library license text is available.
        *
        * @return `true` if the license text is accessible at runtime; `false` otherwise.
        *
        * @note This method confirms whether the license string returned by `GetLicense()`
        * is populated with actual license text.
        */
       bool LicenseAvailable();

       /** @} */
    };

}

#endif // CORE_H