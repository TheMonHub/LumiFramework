//
// Created by Mono on 1/6/2025.
//

#ifndef CORE_H
#define CORE_H
#include <string_view>

/**
 * @mainpage %Lumi Framework Documentation
 *
 * @section intro_sec Introduction
 * Welcome to the %Lumi Framework documentation!
 * %Lumi is a modern C++ framework designed to provide a robust and flexible foundation for building applications.
 * This documentation covers the components, utilities, and features of the %Lumi framework.
 *
 * @section core_sec Core Module
 * @ref Core "Core Module"
 *  is the module of the %Lumi framework, which provides essential functionalities and utilities.
 * @note this module is mandatory for all Lumi components and serves as the foundation for the entire framework.
 * @subsection features_sec Features
 * - License and version information (@ref Metadata "Metadata")
 */

/**
 * @file
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
 * @attention This namespace is the root of the Lumi framework and contains all other namespaces.
 *
 * @ingroup Core
 */
namespace Lumi {
	/**
	 * @namespace Lumi::Core
	 * @brief The main Core namespace for the Lumi framework.
	 *
	 * This namespace encapsulates core functionalities and serves as a central point
	 * for framework-wide operations or access to core utilities.
	 * @ingroup Core
	 */
	namespace Core {}
}

#endif // CORE_H