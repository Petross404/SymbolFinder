#ifndef QMACROS_HPP
#define QMACROS_HPP

#include <qglobal.h>

#ifndef Q_D
#	define Q_D ( Class ) Class##Private* const d = d_func()
#endif

#ifndef Q_Q
#	define Q_Q( Class ) Class* const q = q_func()
#endif

#define QDPTR( Class, where, what ) \
	Class##Private* const d = d_func() Q_ASSERT_X( d->q_ptr == this, where, what )

#endif	  // QMACROS_HPP
