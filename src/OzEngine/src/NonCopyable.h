#ifndef _CNONCOPYABLE_H_
#define _CNONCOPYABLE_H_

namespace Oz
{
	/* Prevents multiple instances of said class being opened more than once without clearing the old first */
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