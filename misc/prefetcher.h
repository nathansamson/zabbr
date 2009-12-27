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
		
		/**
		 * Run the next load of prefetching. Keep chunks as small as possible in your implementation.
		 *
		 * @return If there are no tasks left after running.
		*/
		virtual bool operator()() = 0;
		
		/**
		 * Returns the name of the prefetcher.
		 *
		 * @return The name of the prefetcher.
		*/
		virtual std::string name() = 0;
	};
}

#endif // INC_PREFETCHER_H
