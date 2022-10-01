#ifndef MESSAGEWIDGETTYPE_HPP
#define MESSAGEWIDGETTYPE_HPP

#include <qobject.h>

/*!
 * `MessageType` is the type of the messagewidget to be displayed.
 *
 */
class MessageType
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( MessageType )

public:
	/*!
	 * Enum to represent different types.
	 */
	enum class Type {
		Information = 0x001, /*!< Information type */
		Warning,	     /*!< Warning type */
		Error,		     /*!< Error type */
	};

	Q_ENUM( Type )
};
#endif
