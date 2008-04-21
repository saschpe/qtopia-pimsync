/*
 * Funambol is a mobile platform developed by Funambol, Inc. 
 * Copyright (C) 2003 - 2007 Funambol, Inc.
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License version 3 as published by
 * the Free Software Foundation with the addition of the following permission 
 * added to Section 15 as permitted in Section 7(a): FOR ANY PART OF THE COVERED
 * WORK IN WHICH THE COPYRIGHT IS OWNED BY FUNAMBOL, FUNAMBOL DISCLAIMS THE 
 * WARRANTY OF NON INFRINGEMENT  OF THIRD PARTY RIGHTS.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Affero General Public License 
 * along with this program; if not, see http://www.gnu.org/licenses or write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 * 
 * You can contact Funambol, Inc. headquarters at 643 Bair Island Road, Suite 
 * 305, Redwood City, CA 94063, USA, or at email address info@funambol.com.
 * 
 * The interactive user interfaces in modified source and object code versions
 * of this program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU Affero General Public License version 3.
 * 
 * In accordance with Section 7(b) of the GNU Affero General Public License
 * version 3, these Appropriate Legal Notices must retain the display of the
 * "Powered by Funambol" logo. If the display of the logo is not reasonably 
 * feasible for technical reasons, the Appropriate Legal Notices must display
 * the words "Powered by Funambol".
 */
#ifndef INCL_DM_TREE_MANAGER
#define INCL_DM_TREE_MANAGER
/** @cond DEV */

#include "base/constants.h"
#include "spdm/ManagementNode.h"

/**
 * DMTreeManager is an abstract class for which implementors have to provide a
 * concrete implementation. It provides the ability to retrieve and store
 * objects into the DM platform specific repository. Note that the object
 * returned by readManagementNode() is created with the standard C++ new operator
 * and must be deleted by the caller with the standard C++ delete operator.
 */
class DMTreeManager {
    public:
        /*
         * Returns the management node identified by the given node pathname
         * (relative to the root management node). If the node is not found
         * NULL is returned.
         *
         * The ManagementNode is created with the new operator and must be
         * discarded by the caller with the operator delete. Depending on
         * which node is given, the result is either an instance
         * of SourceManagementNode or AccessManagementNode.
         */
        virtual ManagementNode* const readManagementNode(const char*  node)=0;

        /*
         * Stores the content of the node permanently in the DMTree
         */
        virtual void setManagementNode(ManagementNode& n)=0;
};

/** @endcond */
#endif
