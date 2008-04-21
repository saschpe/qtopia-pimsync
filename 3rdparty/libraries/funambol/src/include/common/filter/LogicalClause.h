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
#ifndef INCL_LOGICALCLAUSE
#define INCL_LOGICALCLAUSE
/** @cond DEV */

#include "base/util/ArrayList.h"
#include "filter/Clause.h"

typedef enum {
    NOT = 0,
    AND = 1,
    OR  = 2
} LogicalClauseOperator;

class LogicalClause : public Clause {

    // ------------------------------------------------------- Private interface
private:

    LogicalClauseOperator op;
    ArrayList* operands;



    // ----------------------------------------------------- Protected interface
protected:
    /*
     * LogicalClause constructor
     *
     */
    LogicalClause();



    // -------------------------------------------------------- Public interface
public:

    ~LogicalClause();


    /*
     * LogicalClause constructor
     *
     * @param o the logical operator
     * @param ops the operands ArrayList
     * @param n how many operands are passed in ops
     */
    LogicalClause(LogicalClauseOperator o, ArrayList& ops);

    /*
     * getOperator
     *
     */
    LogicalClauseOperator getOperator();


    /*
     * setOperator
     *
     * @param p0
     */
    void setOperator(LogicalClauseOperator p0);


    /*
     * getOperands
     *
     */
    ArrayList* getOperands();


    /*
     * setOperands
     *
     * @param ops the operands ArrayList
    */
    void setOperands(ArrayList& ops);


    /*
     * isUnaryOperator
     *
     */
    BOOL isUnaryOperator();

    /*
     * Creates a new instance of this Clause
     *
     * @return the clone
     */
    ArrayElement* clone();


};


/** @endcond */
#endif
