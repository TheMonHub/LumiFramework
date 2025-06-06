//
// Created by Mono on 5/6/2025.
//

#ifndef COREMETA_H
#define COREMETA_H
#include <string_view>

/**
 * @file
 * @brief Metadata header of the Lumi framework.
 *
 * This file declares the metadata-related functionalities of the Lumi framework.
 * Recommended to include this header to access version information and license details
 * as opposed to including Metadata.h directly.
 *
 * @ingroup Metadata
 *
 * @defgroup Metadata Metadata
 * This group contains all metadata-related functionalities of the Lumi framework.
 * Including version information, license details, and other related utilities.
 * @brief submodule of the Lumi framework containing metadata-related functionalities.
 */

/**
 * @namespace Lumi::Metadata
 * @brief Namespace for metadata-related functionalities.
 *
 * This namespace provides methods to query version information and license details
 * of the Lumi Core library. It is used to access metadata about the Lumi framework.
 *
 * @ingroup Metadata
 */
namespace Lumi::Metadata {

	/**
	 * @namespace Lumi::Metadata::Version
	 * @brief Namespace for information-related functionalities.
	 *
	 * This namespace provides methods to query version information
	 * of the Lumi Core library.
	 *
	 * @ingroup Metadata
	 */
	namespace Version {
		/**
		 * @brief Get the current version of the Lumi Core library.
		 *
		 * @return A string literal representing the current version of the Lumi Core library,
		 * typically in "major.minor.patch" format (e.g., "1.2.3").
		 *
		 * @see use GetVersionMajor(), GetVersionMinor(), GetVersionPatch() to get the integer values of the version.
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
	} // namespace Version

	/**
	 * @namespace Lumi::Metadata::License
	 * @brief Methods to query license details of the Lumi Framework.
	 * @ingroup Metadata
	 */
	namespace License {
		/**
		 * @brief Get the license text for the Lumi Core library.
		 *
		 * @return A string literal containing the full license text under which the Lumi
		 * Framework is distributed.
		 *
		 * @note This method can return an empty string if the license file is not available at build time. To check if
		 * the license is available, you can check the `LicenseAvailable` method.
		 *
		 * @see LicenseAvailable()
		 */
		std::string_view GetLicense();

		/**
		 * @brief Check if the Lumi library license text is available.
		 *
		 * @return `true` if the license text is accessible at runtime; `false` otherwise.
		 *
		 * @note This method confirms whether the license string returned by `GetLicense()`
		 * is populated with actual license text.
		 *
		 * @see GetLicense()
		 */
		bool LicenseAvailable();
	} // namespace License
} // namespace Lumi::Metadata

#endif // COREMETA_H
