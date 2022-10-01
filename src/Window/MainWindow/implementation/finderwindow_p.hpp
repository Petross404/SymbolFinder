#ifndef FINDERMAINWINDOW_P_HPP
#define FINDERMAINWINDOW_P_HPP

#include <qglobal.h>	// for Q_DECLARE_PUBLIC, Q_DISABLE_COPY_MOVE
class FinderWindow;	// lines 6-6

class FinderWindowPrivate
{
	Q_DISABLE_COPY_MOVE( FinderWindowPrivate )

public:
	explicit FinderWindowPrivate( FinderWindow* pfw );
	virtual ~FinderWindowPrivate();

	void setupConnections();
	void setupWidgets();
	void setupActions();

private:
	Q_DECLARE_PUBLIC( FinderWindow );
	FinderWindow* const q_ptr;
};

#endif
