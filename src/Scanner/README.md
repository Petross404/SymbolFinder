In `Scanner` directory there is the source code that acts as a wrapper around `Driver` objects.

It defines an interface for accessing various functions of the selected `Driver` (`m_d`).

```
					 -----------------------
					|	`QObject`	|
					 _______________________

						   ^
						   |
						   |

	 ---------------------------------------------------------------------------------------
	|			`Scanner : public QObject`				 	|
	|					   		 	 			|
	| ------------------------------  ----------------------------------------------------- |
	||- Process::IDriver* m_d; 	||+ QString symbolName() const;			       ||
	||- QString m_name		||+ QByteArray standardOut() const;		       ||
	||- QByteArray m_stdOut		||+ void setInvocation( const QString& args,	       ||
	||				||			const QString& secret = "" );  ||
	||- void init()			||						       ||
	|| etc				||						       ||
	| ------------------------------  ----------------------------------------------------- |
	 _______________________________________________________________________________________

			^					^
			|					|
			|					|
		(Private members)		(Public data and member functions)
```
