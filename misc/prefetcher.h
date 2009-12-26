#ifndef INC_PREFETCHER_H
#define INC_PREFETCHER_H

/** \file
 * File for the prefetcher.
 *
 * @author Nathan Samson
*/

#include <string>

namespace Zabbr {
	/**
	 * Interface for prefetchers.
	 * A prefetcher loads, and releases surfaces so they are in the resource cache.
	*/
	class IPrefetcher {
	public:
		virtual ~IPrefetcher() {}
		
		virtual bool operator()() = 0;
		virtual std::string name() = 0;
	};
}

#endif // INC_PREFETCHER_H
