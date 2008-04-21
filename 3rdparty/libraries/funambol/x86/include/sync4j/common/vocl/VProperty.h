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


#ifndef INCL_VIRTUAL_PROPERTY
#define INCL_VIRTUAL_PROPERTY
/** @cond DEV */

#include "base/fscapi.h"
#include "base/util/WKeyValuePair.h"
#include "base/util/ArrayList.h"


// Quoted-Printable formatted lines should be max 76 chars long.
#define QP_MAX_LINE_LEN             70
#define VCARD_MAX_LINE_LEN          76


// These are special chars to escape in vCard/vCal/vTodo (version 2.1 - 3.0)
#define VCARD21_SPECIAL_CHARS       TEXT(";\\")
#define VCARD30_SPECIAL_CHARS       TEXT(";\\,")
#define RFC822_LINE_BREAK           TEXT("\r\n")


// ------------ Public functions --------------
char* escapeSpecialChars(const char* inputString, char* version);
char*    convertToQP(const char* input, int start);
bool     encodingIsNeed(const char *in);
char* folding(const char* inputString, const int maxLine);
char* unfolding(const char* inputString);



// ------------ Class VProperty ---------------

class VProperty : public ArrayElement {

private:

    char* name;
    void set(char** p, const char* v);

    ArrayList* parameters;
    ArrayList* values;

    // This is only used as a buffer for 'getValue()'
    char* valueBuf;

 public:

    VProperty(const char* propName , const char* propValue  = 0);
    ~VProperty();
    ArrayElement* clone();
    void setName (const char* name);
    char* getName(char* buf = 0, int size = -1);

    void addValue(const char* value);
    bool removeValue(const int index);
    char* getValue(int index);
    int valueCount();

    // For back-compatibility (to remove)
    char* getValue(char* buf = 0);
    void setValue (const char* value);
    char* getPropComponent(int i);

    void addParameter(const char* paramName, const char* paramValue);
    void removeParameter(char* paramName);
    bool containsParameter(char* paramName);
    // Warning: the name does not always uniquely identify
    // the parameter, some of them may occur multiple times.
    // Use getParameterValue(int index) to get the value which
    // corresponds to a specific parameter.
    char* getParameterValue(char* paramName);
    char* getParameterValue(int index);
    char* getParameter(int index);
    int parameterCount();
    bool equalsEncoding(char* encoding);
    //char* getPropComponent(int i);
    bool isType(char* type);
    char* toString(char* version = 0);

 };

/** @endcond */
#endif
