#ifndef _CNONCOPYABLE_H_
#define _CNONCOPYABLE_H_

namespace Oz
{
	class cNonCopyable
	{
		protected:
			cNonCopyable() {}
			
			~cNonCopyable() {}
		private:
			cNonCopyable(const cNonCopyable&) = delete;
			
			cNonCopyable& operator=(const cNonCopyable &) = delete;
	};
}

#endif