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


/*-----------includes----------*/

#include "generic_types.h"


/*-----------enumerations------*/


/** filterProperties: Enumeration of the filter properties supported by Loom
*/
enum filterProperties
{
    srcAddr = 1,
    dstAddr,
    srcPort,
    dstPort,
    dateTime
}


/*-----------structures-------*/


/** The queryInterface struct provides core information that defines properties of
    the current interface
    TODO: Expect this to grow as the interface takes shape
*/
struct queryInterface
{
    uint8_t *filter;
}


/*-----------prototypes--------*/


/** qiInit: Initialise the query interface
*/
int qiInit(queryInterface *qi);


/** qiAddFilter: Add a filter to the current query interface replacing any current
    filters. fi needs to be a unique list of uint8_t as dictated by the 
    filterProperties enumeration
*/
int qiAddFilter(queryInterface *qi, uint8_t *fi, size_t size);


/** qiClearFilter: Clear the current filter
*/
int qiClearFilter(queryInterface *qi);


/** qiExtendFilter: Append filter to exisiting filter. Will have to ensure that it
    is sane and there is no duplication of filter criteria.
*/
int qiExtendFilter(queryInterface *qi, uint8_t *fi, size_t size);


/** qiIsNewData: Determine whether new data is available from Loom for consumption
*/
int qiIsNewData(queryInterface *qi);


/** qiFetchNewData: Fetch new data from Loom if it exists and has been processed
*/
int qiFetchNewData(queryInterface *qi, void *data); // place holder until "data" can be defined
