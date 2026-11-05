/**
 * @file       $RCSfile: version.c $
 * @brief      This file contains version string.
 * @author     Frank Luenstroth, Dagmar Andoleit
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.14 $ $Date: 2017/06/13 10:44:58CEST $
 */

/* Note:
 * Semantic Versioning Rules (Major.Minor.Revision)
 *
 * If only an error is resolved without affecting backwards compatibility, the revision number is 
 * incremented by one - for example, from 1.0.18 to 1.0.19.
 * If a new functionality is added, the minor version number is incremented by one, provided that 
 * the newly added functionality does not prevent backwards compatibility 
 * - for example, from 1.0.19 to 1.1.0.
 * If there is a change that prevents backwards compatibility, the major version number is 
 * incremented by one - for example, from 1.1.0 to 2.0.0.
 *
 * Search for the string "Fixed-Point Library Version:" to identify the binary version of the DsFxp library.
 */


const char FxpLibVersion[] = "Fixed-Point Library Version: 1.2.1";

