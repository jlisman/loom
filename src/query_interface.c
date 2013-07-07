/*
Query Interface for use in loom (or else where).
Copyright (C) 2013 Commonwealth of Australia

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "query_interface.h"

/** qiInit: Initialise the query interface
*/
int qiInit(queryInterface *qi)
{
    if(qi != 0)
        return -1; //TODO: What error reporting are we using errno?

    qi = talloc_zero(NULL, struct queryInterface);
    if(qi) {
        return 0;
    }

    return -1; //TODO: What error reporting are we using errno?
}


/** qiAddFilter: Add a filter to the current query interface replacing any current
    filters.
*/
int qiAddFilter(queryInterface *qi, uint8_t *fi, size_t size)
{
    talloc_array(qi->filter, uint8_t, size);
    if(qi->filter) {
        //TODO: Add array sanity checker... looking for a uniqe set of uint8_t values
        //      and conforming to the filterProperties enumeration
        memcpy(qi->filter, fi, size);
        return 0;
    }

    return -1; //TODO: errno?
}


/** qiClearFilter: Clear the current filter
*/
int qiClearFilter(queryInterface *qi)
{
    if(qi->filter) // TODO: Is this necessary or does talloc_free deal with this case?
        return talloc_free(qi->filter);

    return 0;
}


/** qiExtendFilter: Append filter to exisiting filter. Will have to ensure that it
    is sane and there is no duplication of filter criteria.
*/
int qiExtendFilter(queryInterface *qi, uint8_t *fi, size_t size)
{
    return 0;
}


/** qiIsNewData: Determine whether new data is available from Loom for consumption
*/
int qiIsNewData(queryInterface *qi)
{
    return 0;
}


/** qiFetchNewData: Fetch new data from Loom if it exists and has been processed
*/
int qiFetchNewData(queryInterface *qi, void *data) // place holder until "data" can be defined
{
    return 0;
}

